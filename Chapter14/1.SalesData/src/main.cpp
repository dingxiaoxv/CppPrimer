#include <iostream>

#include "sales_data.h"

int main(int argc, char *argv[]) {
  SalesData book;
  std::cout << "请输入销售记录： " << std::endl;
  while (std::cin >> book) {
    std::cout << " ISBN、售出本数、原始价格、实售价格、折扣为" << book
              << std::endl;
  }

  return 0;
}