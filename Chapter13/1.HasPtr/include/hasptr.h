#ifndef HASPTR_H
#define HASPTR_H

#include <iostream>
#include <string>

class HasPtr {
  friend void swap(HasPtr &lhs, HasPtr &rhs);

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
  std::string &operator*() const { return *ps_; }
  bool operator<(const HasPtr &rhs) const { return *ps_ < *rhs.ps_; }
  void print() { std::cout << "print func" << std::endl; }
  ~HasPtr() {
    std::cout << "destructor" << std::endl;
    if (ps_) {
      delete ps_;
    }
  }

private:
  std::string *ps_;
  int val_;
};

inline void swap(HasPtr &lhs, HasPtr &rhs) {
  std::cout << "swap " << *lhs.ps_ << " and " << rhs.ps_ << std::endl;
  using std::swap;
  swap(lhs.ps_, lhs.ps_);
  swap(lhs.val_, rhs.val_);
}

class HasPtrUse {
public:
  HasPtrUse(const std::string &str = std::string())
      : ps_(new std::string(str)), use_(new std::size_t(1)) {}
  HasPtrUse(const HasPtrUse &hpu) : ps_(hpu.ps_), use_(hpu.use_) {
    ++*hpu.use_;
  }
  HasPtrUse &operator=(const HasPtrUse &rhs) {
    ++*rhs.use_; // 先递增再递减，防止自赋值
    if (--*use_ == 0) {
      delete ps_;
      delete use_;
    }

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