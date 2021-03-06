#include <cstddef> // for size_t definition
#include <iostream>


struct unique_array {

  unique_array(size_t s) : _buffer(new char[s]), _size(s) {}
  ~unique_array() { 
    std::cout << "destroying a unique_array" << std::endl;
    delete[] _buffer; 
  }

  // disallow regular copy and assignment
  unique_array(const unique_array& a) = delete;
  unique_array& operator=(const unique_array& a) = delete;

  // move assignment
  unique_array& operator=(unique_array&& a) {
    // swap buffers and size value between the two objects
    // do not copy the buffer
    char* buf_ptr = a._buffer;
    size_t s = a._size;
    a._buffer = _buffer;
    a._size = _size;
    _buffer = buf_ptr;
    _size = s;
    std::cout << "moving buffer" << std::endl;
    return *this;
  } 
  // move constructor
  unique_array(unique_array&& a) : _buffer(nullptr), _size(0) { 
    // initialization at nullptr and 0 avoids a segfault
    // because the swapped buffer as a valid (empty) value
    std::swap(_buffer, a._buffer); // swap 2 variables, uses move if possible
    std::swap(_size, a._size);
    std::cout << "move construction" << std::endl;
  } 

  const char* get() const {
    return _buffer;
  }

  const size_t size() const {
    return _size;
  }

  private:
  char* _buffer;
  size_t _size;

};


int main(int, char**) {
  unique_array a(5);

  // unique_array& b = std::move(a); // does not compile : copy is prevented
  // const unique_array& b = std::move(a); // ok
  
  unique_array b(6);
  b = std::move(a); // b and a are swapped, 
  //   the move assignment defined in unique_array is used
  //   unique_array a shouldn't be used after this 
  std::cout << "size of b: " <<  b.size() << std::endl;
  
  unique_array c(std::move(b)); // calls the move constructor
  //   unique_array b shouldn't be used after this 
  
  std::cout << "size of c: " <<  c.size() << std::endl;


}
