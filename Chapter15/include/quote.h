#ifndef QUOTE_H
#define QUOTE_H

#include <string>
#include <iostream>

class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price) : bookNo_(book), price_(sales_price) {}
  std::string isbn() const { return bookNo_; }
  virtual double net_price(size_t n) const { return n * price_; }
  virtual void debug() {
    std::cout << "bookNo=" << bookNo_ << " price=" << price_ << std::endl;
  }
  virtual ~Quote() {
    std::cout << "destory Quote" << std::endl;
  }

private:
  std::string bookNo_;

protected:
  double price_ = 0.0;
};

class DiscQuote : public Quote {
public:
  DiscQuote() = default;
  DiscQuote(const std::string &book, double price, size_t qty, double disc) : 
    Quote(book, price), quantity_(qty), discount_(disc) { } 
  double net_price(size_t n) const = 0;
  virtual ~DiscQuote() override {
    std::cout << "destory DiscQuote" << std::endl;
  }

protected:
  size_t quantity_ = 0;
  double discount_ = 0.0;
};

class BulkQuote : public DiscQuote {
public:
  BulkQuote() = default;
  BulkQuote(const std::string &book, double price, size_t qty, double disc) : 
    DiscQuote(book, price, qty, disc) { } 
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
  virtual ~BulkQuote() override {
    std::cout << "destory BulkQuote" << std::endl;
  }
};

class LimitedQuote : public DiscQuote {
public:
  LimitedQuote() = default;
  LimitedQuote(const std::string &book, double price, size_t qty, double disc) : 
    DiscQuote(book, price, qty, disc) { } 
  double net_price(size_t n) const override {
    if (n <= quantity_) {
      return n * ( 1- discount_ ) * price_;
    } else {
      return quantity_ * (1 - discount_) * price_ + (n - quantity_) * price_;
    }
  }
};

#endif