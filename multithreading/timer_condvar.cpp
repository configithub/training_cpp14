#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>
#include <condition_variable>

class timer {
public:

  timer() : _running{false}, _counter(0) {}

  void run() {
    _running = true;
    _t = std::thread(std::bind(&timer::process, this));
  }

  void process() noexcept {
    while(_running) {
      std::unique_lock<std::mutex> lock(_mtx);
      std::cout << "ping " << _counter << std::endl;
      ++_counter;
      _cond_var.wait_for(lock, std::chrono::seconds(1)); 
      // wait releases the lock
    }
  }

  void stop() { 
    {
      std::unique_lock<std::mutex> lock(_mtx);
      _running = false; 
    } // lock is released
    _cond_var.notify_all();
    _t.join(); 
  }


private:
  std::thread _t;
  std::mutex _mtx;
  std::condition_variable _cond_var;
  bool _running; // no need for the volatile keyword with atomics
  // we put _running as atomic because 2 threads can write this variable
  int _counter;
};


int main(int, char**) {

  timer t;
  t.run();
  std::this_thread::sleep_for(std::chrono::seconds(4));

  t.stop();

  return 0;
}
