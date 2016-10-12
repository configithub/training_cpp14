#include <thread>
#include <atomic>
#include <iostream>
#include <chrono>

class timer {
public:

  timer() : _running{false}, _counter(0) {}

  void run() {
    _running = true;
    _t = std::thread(std::bind(&timer::process, this));
  }

  void process() noexcept {
    while(_running) {
      std::this_thread::sleep_for(std::chrono::seconds(1));
      std::cout << "ping " << _counter << std::endl;
      ++_counter;
      // std::cout << "is_lock_free " << _running.is_lock_free() << std::endl;
    }
  }

  //std::atomic<bool>& is_running() { return _running; }
  //void join() { _t.join(); }

  void stop() { _running = false; _t.join(); }

  // same thing but we avoid double stops in case of multiple callers
  void stop_safe() {  
    bool v = true;
    if(_running.compare_exchange_strong(v, false)) {  // atomic compare and set
      _t.join(); 
    } 
  }

private:
  std::thread _t;
  std::atomic<bool> _running; // no need for the volatile keyword with atomics
  // we put _running as atomic because 2 threads can write this variable
  int _counter;
};


int main(int, char**) {

  timer t;
  t.run();
  std::this_thread::sleep_for(std::chrono::seconds(4));

  //std::atomic<bool>& timer_running = t.is_running();
  //timer_running = false; t.join();
  
  //t.stop();

  t.stop_safe();

  return 0;
}
