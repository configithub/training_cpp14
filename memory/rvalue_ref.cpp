#include <vector>

void f_value(std::vector<char> v) {
  v.push_back('a');
}
void f_ref(std::vector<char>& v) {
  v.push_back('a');
}
void f_rvalue_ref(std::vector<char>&& v) {
  v.push_back('a');
}

int main(int, char**) {
  
  std::vector<char> v;
  f_value(v);
  f_ref(v);
  f_rvalue_ref({'b'}); // ok, {'b'} is an rvalue 
  // f_rvalue_ref(v); // does not compile
  f_rvalue_ref(std::move(v)); // ok, std::move converts a value to an rvalue ref
       // WARNING, using v after std::move(v) is undefined behavior : 
       // move transfers ownership
  // f_ref(std::move(v)); // does not compile
  // f_value(std::move(v)); // compiles, make a copy

  // ownership of v is transfered to f_rvalue_ref

  return 0;

}
