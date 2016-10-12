#include <iostream>

int f(int a, int b) {

  return a+b;
}

int main(int, char**) {

  int a =2;
  int b =3;

  std::cout << f(a,b) << std::endl;

}
