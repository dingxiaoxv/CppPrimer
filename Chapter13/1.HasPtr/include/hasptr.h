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
  HasPtr &operator=(const HasPtr &rhs) {
    std::cout << "copy-assignment operator" << std::endl;
    auto newp = new std::string(*rhs.ps_); // 先拷贝再释放，防止自赋值
    if (ps_) {
      delete ps_;
    }
    ps_ = newp;
    val_ = rhs.val_;
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

class HasPtrUse {
public:
  HasPtrUse(const std::string &str = std::string()) : ps_(new std::string(str)), use_(new std::size_t(1)) {}
  HasPtrUse(const HasPtrUse &hpu) : ps_(hpu.ps_), use_(hpu.use_) {
    ++*hpu.use_;
  }
  HasPtrUse & operator=(const HasPtrUse &rhs) {
    if (--*use_ == 0) {
      delete ps_;
      delete use_;
    }

    ++*rhs.use_;
    ps_ = rhs.ps_;
    use_ = rhs.use_;
    return *this;
  }
  ~HasPtrUse() {
    if (--*use_ == 0) {
      delete ps_;
      delete use_;
    }
  }

private:
  std::string *ps_;
  std::size_t *use_;
};

#endif