#ifndef STRBLOG_H
#define STRBLOG_H

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

class StrBlobPtr;

class StrBlob {
  friend class StrBlobPtr;

public:
  typedef std::vector<std::string>::size_type size_type;
  StrBlob() : data_(std::make_shared<std::vector<std::string>>()) {}
  StrBlob(std::initializer_list<std::string> il)
      : data_(std::make_shared<std::vector<std::string>>(il)) {}
  size_type size() const { return data_->size(); }
  bool empty() const { return data_->empty(); }
  void push_back(const std::string &str) { data_->push_back(str); }
  void pop_back() {
    check(0, "pop on empty blob");
    data_->pop_back();
  }
  std::string &front() {
    check(0, "front on empty blob");
    return data_->front();
  }
  std::string &back() {
    check(0, "back on empty blob");
    return data_->back();
  }
  StrBlobPtr begin();
  StrBlobPtr end();

private:
  void check(size_type i, const std::string &msg) const {
    if (i >= data_->size()) {
      throw std::out_of_range(msg);
    }
  }

private:
  std::shared_ptr<std::vector<std::string>> data_;
};

class StrBlobPtr {
  friend bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public:
  StrBlobPtr() : curr_(0) {}
  StrBlobPtr(StrBlob &sb, size_t i = 0) : wptr_(sb.data_), curr_(i) {}
  std::string &deref() const {
    auto ptr = check(0, "dereference past end of StrBlobPtr");
    return (*ptr)[curr_];
  }
  StrBlobPtr &incr() {
    check(0, "increment past end of StrBlobPtr");
    curr_++;
    return *this;
  }
  StrBlobPtr &decr() {
    check(-1, "decrement past begin of StrBlobPtr");
    --curr_;
    return *this;
  }

private:
  std::shared_ptr<std::vector<std::string>>
  check(std::size_t i, const std::string &msg) const {
    auto ret = wptr_.lock(); // is shared_ptr available?
    if (!ret)
      throw std::runtime_error("unbound StrBlobPtr");

    if (i >= ret->size())
      throw std::out_of_range(msg);

    return ret;
  }

private:
  std::weak_ptr<std::vector<std::string>> wptr_;
  std::size_t curr_;
};

bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  auto l = lhs.wptr_.lock(), r = rhs.wptr_.lock();
  if (l == r)
    return (!r || lhs.curr_ == rhs.curr_);
  else
    return false;
}

inline bool neq(const StrBlobPtr &lhs, const StrBlobPtr &rhs) {
  return !eq(lhs, rhs);
}

// must put behind class StrBlobPtr
inline StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

inline StrBlobPtr StrBlob::end() { return StrBlobPtr(*this, data_->size()); }

#endif