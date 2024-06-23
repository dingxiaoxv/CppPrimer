#include <iostream>
#include "strvec.h"

int main(int argc, char *argv[]) {
  // StrVec vec({"a", "b", "c"});
  StrVec vec;
  std::cout << "size " << vec.size() << std::endl;
  std::cout << "capacity " << vec.capacity() << std::endl;

  vec.push_back("a");
  vec.push_back("b");
  vec.push_back("c");
  vec.push_back("d");

  vec.reserve(6);
  std::cout << "size " << vec.size() << std::endl;
  std::cout << "capacity " << vec.capacity() << std::endl;

  return 0;
}