#include <iostream>
#include "quote.h"

double print_total(std::ostream &os, const Quote &item, size_t n) {
  double ret  = item.net_price(n);
  os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
  return ret;
}

int main(int argc, char *argv[]) {
  Quote basic("c++ primer", 80.0);
  BulkQuote bulk("c++ primer", 80.0, 10, 0.8);
  LimitedQuote limit("c++ primer", 80.0, 10, 0.8);

  print_total(std::cout, basic, 20);
  print_total(std::cout, bulk, 20);
  print_total(std::cout, limit, 20);

  BulkQuote b(bulk), c;
  c = bulk;

  return 0;
}