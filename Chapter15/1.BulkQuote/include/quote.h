#ifndef QUOTE_H
#define QUOTE_H

#include <iostream>
#include <string>

class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price)
      : bookNo_(book), price_(sales_price) {}
  Quote(const Quote &q) : bookNo_(q.bookNo_), price_(q.price_) {
    std::cout << "Quote copy constructor" << std::endl;
  }
  Quote &operator=(const Quote &rhs) {
    std::cout << "Quote copy assisgnment" << std::endl;
    bookNo_ = rhs.bookNo_;
    price_ = rhs.price_;
  }
  virtual ~Quote() { std::cout << "destory Quote" << std::endl; }
  std::string isbn() const { return bookNo_; }
  virtual double net_price(size_t n) const { return n * price_; }
  virtual void debug() {
    std::cout << "bookNo=" << bookNo_ << " price=" << price_ << std::endl;
  }

private:
  std::string bookNo_;

protected:
  double price_ = 0.0;
};

class DiscQuote : public Quote {
public:
  DiscQuote() = default;
  DiscQuote(const std::string &book, double price, size_t qty, double disc)
      : Quote(book, price), quantity_(qty), discount_(disc) {}
  DiscQuote(const DiscQuote &dq)
      : Quote(dq), quantity_(dq.quantity_), discount_(dq.discount_) {
    std::cout << "DiscQuote copy constructor" << std::endl;
  }
  DiscQuote &operator=(const DiscQuote &rhs) {
    std::cout << "DiscQuote copy assisgnment" << std::endl;
    Quote::operator=(rhs);
    quantity_ = rhs.quantity_;
    discount_ = rhs.discount_;
    return *this;
  }
  virtual ~DiscQuote() override {
    std::cout << "destory DiscQuote" << std::endl;
  }
  double net_price(size_t n) const = 0;

protected:
  size_t quantity_ = 0;
  double discount_ = 0.0;
};

class BulkQuote : public DiscQuote {
public:
  BulkQuote() = default;
  BulkQuote(const std::string &book, double price, size_t qty, double disc)
      : DiscQuote(book, price, qty, disc) {}
  BulkQuote(const BulkQuote &bq) : DiscQuote(bq) {
    std::cout << "BulkQuote copy constructor" << std::endl;
  }
  BulkQuote &operator=(const BulkQuote &rhs) {
    std::cout << "BulkQuote copy assisgnment" << std::endl;
    DiscQuote::operator=(rhs);
    return *this;
  }
  virtual ~BulkQuote() override {
    std::cout << "destory BulkQuote" << std::endl;
  }
  double net_price(size_t n) const override {
    if (n >= quantity_) {
      return n * (1 - discount_) * price_;
    } else {
      return n * price_;
    }
  }
  void debug() override {
    Quote::debug();
    std::cout << "qty=" << quantity_ << " discount=" << discount_ << std::endl;
  }
};

class LimitedQuote : public DiscQuote {
public:
  using DiscQuote::DiscQuote;
  double net_price(size_t n) const override {
    if (n <= quantity_) {
      return n * (1 - discount_) * price_;
    } else {
      return quantity_ * (1 - discount_) * price_ + (n - quantity_) * price_;
    }
  }
};

#endif