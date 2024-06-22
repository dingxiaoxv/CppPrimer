#include <iostream>
#include "strvec.h"

int main(int argc, char *argv[]) {
  StrVec vec({"a", "b", "c"});
  std::cout << "size " << vec.size() << std::endl;
  std::cout << "capacity " << vec.capacity() << std::endl;

  vec.reserve(6);
  std::cout << "size " << vec.size() << std::endl;
  std::cout << "capacity " << vec.capacity() << std::endl;

  return 0;
}