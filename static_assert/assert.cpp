


int main(int argc, char** argv) {
  const int i = 0;
  static_assert(i == 1, "i != 1");
}
