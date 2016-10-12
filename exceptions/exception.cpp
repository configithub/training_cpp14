#include <exception>
#include <iostream>

class my_exc : std::exception {
  public:
  const char* what() const noexcept {
  //const char* what() const noexcept override {
      return "my exception";
  }
};


int main(int argc, char** argv) {
  my_exc e;
  try {
    throw e;
  } catch(my_exc&){
  //} catch(std::exception&){ // avoid copy with &
    std::cout << e.what() << std::endl;
  }

}
