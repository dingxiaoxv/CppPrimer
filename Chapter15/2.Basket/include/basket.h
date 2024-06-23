#ifndef BASKET_H
#define BASKET_H

#include <memory>
#include <set>

#include "quote.h"

class Basket {
public:
  void add_item(const Quote &sale) {
    items_.insert(std::shared_ptr<Quote>(sale.clone()));
  }
  void add_item(Quote &&sale) {
    items_.insert(std::shared_ptr<Quote>(std::move(sale).clone()));
  }
  double total_receipt(std::ostream &os) const {
    double sum = 0.0;
    for (auto iter = items_.cbegin(); iter != items_.cend();
         iter = items_.upper_bound(*iter)) {
      sum += print_total(os, **iter, items_.count(*iter));
    }
    os << "Total sale: " << sum << std::endl;
    return sum;
  }

private:
  static bool compare(const std::shared_ptr<Quote> &lhs,
                      std::shared_ptr<Quote> &rhs) {
    return lhs->isbn() < rhs->isbn();
  }

private:
  std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items_{compare};
};

#endif