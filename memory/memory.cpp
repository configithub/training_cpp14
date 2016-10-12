#include <cstddef> // for size_t definition
#include <iostream>


struct unique_array {

  unique_array(size_t s) : _buffer(new char[s]), _size(s) {}
  ~unique_array() { 
    std::cout << "destroying a unique_array" << std::endl;
    delete[] _buffer; 
  }

  // disallow copy
  unique_array(const unique_array& a) = delete;
  unique_array& operator=(const unique_array& a) = delete;

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

template <typename T> class unique_pointer {
  public:
  unique_pointer(T* o) { _obj = o; }
  ~unique_pointer() { delete _obj; }

  T* operator -> () { return _obj; }
  T& operator * () { return *_obj; }

  private:
  T* _obj;

};

int main(int, char**) {

  {
    unique_array* buf = new unique_array(4);
    unique_pointer<unique_array> buf_ptr(buf);

    int s = buf_ptr->size();
    std::cout << s << std::endl;
  } // unique_array will be deleted here

  std::cout << "byebye" << std::endl;
}
