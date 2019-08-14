#include <iostream>
#include "array.h"

int test_default_constructor() {
  Array<int, 0> array;
  return 0;
}

int main() {
  Array<int, 5> array(4);
  std::cout << array.size() << std::endl;
}
