#ifndef STR_BLOB_H_INCLUDED
#define STR_BLOB_H_INCLUDED

#include <memory>
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
  bool empty() const { return data_->empty(); }
  void push_back(const std::string& str) { data_->push_back(str); }
  StrBlobPtr begin();
  StrBlobPtr end();

private:
  std::shared_ptr<std::vector<std::string>> data_;
};

class StrBlobPtr {
  friend bool operator==(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
  friend bool operator!=(const StrBlobPtr &lhs, const StrBlobPtr &rhs);
  friend bool operator<(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

public:
  StrBlobPtr() : curr_(0) {}
  StrBlobPtr(StrBlob& sb, size_t i = 0) : wptr_(sb.data_), curr_(i) {}
  std::string& operator[](std::size_t n) { return (*wptr_.lock())[n]; }
  const std::string& operator[](std::size_t n) const {
    return (*wptr_.lock())[n];
  }
  StrBlobPtr& operator++();
  StrBlobPtr operator++(int);
  StrBlobPtr& operator--();
  StrBlobPtr operator--(int);

private:
  std::shared_ptr<std::vector<std::string>> check(std::size_t i,
                                                  const std::string& msg) const;
  std::weak_ptr<std::vector<std::string>> wptr_;
  std::size_t curr_;
};

#endif