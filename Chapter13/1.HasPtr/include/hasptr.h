#ifndef HASPTR_H
#define HASPTR_H

#include <iostream>
#include <string>

class HasPtr {
public:
  HasPtr(const std::string &s = std::string())
      : ps_(new std::string(s)), val_(0) {
    std::cout << "constructor" << std::endl;
  }
  HasPtr(const HasPtr &hp) {
    std::cout << "copy constructor" << std::endl;
    ps_ = new std::string(*hp.ps_);
    val_ = hp.val_;
  }
  HasPtr &operator=(const HasPtr &hp) {
    std::cout << "copy-assignment operator" << std::endl;
    if (ps_) {
      delete ps_;
    }

    ps_ = new std::string(*hp.ps_);
    val_ = hp.val_;
    return *this;
  }
  ~HasPtr() {
    std::cout << "destructor" << std::endl;
    if (ps_) {
      delete ps_;
    }
  }
  void print() { std::cout << "print func" << std::endl; }

private:
  std::string *ps_;
  int val_;
};

#endif