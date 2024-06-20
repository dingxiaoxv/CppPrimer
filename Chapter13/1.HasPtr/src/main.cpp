#include "hasptr.h"
#include <iostream>
#include <vector>

static void fcn1(HasPtr hp) { hp.print(); }

static void fcn2(HasPtr &hp) { hp.print(); }

int main(int argc, char *argv[]) {
  std::cout << "局部变量： " << std::endl;
  HasPtr hp("test");
  std::cout << std::endl;

  std::cout << "非引用参数传递： " << std::endl;
  fcn1(hp);
  std::cout << std::endl;

  std::cout << "引用参数传递： " << std::endl;
  fcn2(hp);
  std::cout << std::endl;

  std::cout << "动态分配： " << std::endl;
  HasPtr *px = new HasPtr;
  std::cout << std::endl;

  std::cout << "添加到容器中： " << std::endl;
  std::vector<HasPtr> vx;
  vx.push_back(hp);
  std::cout << std::endl;

  std::cout << "释放动态分配对象： " << std::endl;
  delete px;
  std::cout << std::endl;

  std::cout << "间接初始化和赋值： " << std::endl;
  HasPtr hp_copy = hp;
  hp_copy = hp;
  std::cout << std::endl;

  std::cout << "程序结束： " << std::endl;
  return 0;
}