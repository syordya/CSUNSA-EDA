//#include <ctime>
#include <iostream>

int main() {
  // std::srand(std::time(nullptr));
  int from = 10000;
  int to = 200000;
  int skip = 10000;
  for (int i = from; i <= to; i += skip) {
    std::cout << i << '\n';
    for (int j = 1; j <= i; ++j) {
      int random_number = 1 + std::rand() / ((RAND_MAX + 1u) / i);
      std::cout << random_number << ' ';
    }
    std::cout << '\n';
  }
  return 0;
}