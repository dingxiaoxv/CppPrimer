#include "strblob.h"

inline StrBlobPtr StrBlob::begin() {
  return StrBlobPtr(*this);
}

inline StrBlobPtr StrBlob::end() {
  return StrBlobPtr(*this, data_->size());
}

StrBlobPtr& StrBlobPtr::operator++() {
  check(curr_, "increment past end of StrBlobPtr");
  ++curr_;
  return *this;
}

StrBlobPtr StrBlobPtr::operator++(int) {
  StrBlobPtr ret = *this;
  ++*this;
  return ret;
}

StrBlobPtr& StrBlobPtr::operator--() {
  --curr_;
  check(curr_, "decrement past begin of StrBlobPtr");
  return *this;
}

StrBlobPtr StrBlobPtr::operator--(int) {
  StrBlobPtr ret = *this;
  --*this;
  return ret;
}

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(
    std::size_t i, const std::string& msg) const {
  auto ret = wptr_.lock();  // is shared_ptr available?
  if (!ret) throw std::runtime_error("unbound StrBlobPtr");
  if (i >= ret->size()) throw std::out_of_range(msg);
  return ret;
}

bool operator==(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  auto pl = lhs.wptr_.lock(), pr = rhs.wptr_.lock();
  if (pl == pr) {
    return (!pl || lhs.curr_ == rhs.curr_);
  } else {
    return true;
  }
}

bool operator!=(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  return !(lhs == rhs);
}

bool operator<(const StrBlobPtr& lhs, const StrBlobPtr& rhs) {
  auto pl = lhs.wptr_.lock(), pr = rhs.wptr_.lock();
  if (pl == pr) {
    if (!pl)
      return false;
    return lhs.curr_ < rhs.curr_;
  } else {
    return false;
  }
}

