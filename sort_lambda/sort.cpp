#include <vector>
#include <iostream>
#include <algorithm>


int main(int argc, char** argv) {

  std::vector<int> v{1,2,3};

  int x = 0;
  // std::sort(v.begin(), v.end(), [](auto left, auto right) -> bool {
  // std::sort(v.begin(), v.end(), [](auto left, auto right) {
  // std::sort(v.begin(), v.end(), [this](auto left, auto right) {
  // std::sort(v.begin(), v.end(), [=](auto left, auto right) { // copy the scope
  // std::sort(v.begin(), v.end(), [&](auto left, auto right) { // keep the scope as ref
  // std::sort(v.begin(), v.end(), [x](auto left, auto right) -> bool { // use x via copy
  // std::sort(v.begin(), v.end(), [&x](auto left, auto right) -> bool { // use x via copy
  std::sort(v.begin(), v.end(), [&](auto left, auto right) -> bool { // use x via ref
    x++;
    return left >= right;
  });

  for(auto e : v) {
    std::cout << e << std::endl;
  }
  std::cout << "number of call to order op: " << x << std::endl;

  return 0;
}
