#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>
#include <utility>

class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price = 0.0)
      : bookNo_(book), price_(sales_price) {}
  Quote(const Quote &) = default;
  Quote(Quote &&) = default;
  Quote &operator=(const Quote &) = default;
  Quote &operator=(Quote &&) = default;
  virtual ~Quote() = default;
  
  std::string isbn() const { return bookNo_; }
  virtual double net_price(size_t n) const { return n * price_; }
  virtual Quote *clone() const & { return new Quote(*this); }
  virtual Quote *clone() && { return new Quote(std::move(*this)); }

private:
  std::string bookNo_;

protected:
  double price_;
};

class BulkQuote : public Quote {
public:
  BulkQuote() = default;
  BulkQuote(const std::string &book, double price, size_t qty = 0, double disc = 0.0)
      : Quote(book, price), min_qty_(qty), discount_(disc) {}
  double net_price(size_t n) const override {
    if (n >= min_qty_) {
      return n * (1 - discount_) * price_;
    } else {
      return n * price_;
    }
  }
  virtual BulkQuote *clone() const & { return new BulkQuote(*this); }
  virtual BulkQuote *clone() && { return new BulkQuote(std::move(*this)); }
  
  private:
  size_t min_qty_;
  double discount_;
};

double print_total(std::ostream &os, const Quote &item, size_t n) {
  double ret = item.net_price(n);
  os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret
     << std::endl;
  return ret;
}

#endif