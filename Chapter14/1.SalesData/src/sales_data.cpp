#include "sales_data.h"

inline bool compareIsbn(const SalesData &lhs, const SalesData &rhs) {
  return lhs.isbn() == rhs.isbn();
}

std::istream &operator>>(std::istream &in, SalesData &s) {
  in >> s.bookNo_ >> s.units_sold_ >> s.ori_price_ >> s.sale_price_;
  if (in && s.ori_price_ != 0)
    s.discount_ = s.sale_price_ / s.ori_price_;
  else
    s = SalesData();  // 输入错误，重置输入的数据
  return in;
}

std::ostream &operator<<(std::ostream &out, const SalesData &s) {
  out << s.isbn() << " " << s.units_sold_ << " " << s.ori_price_ << " "
      << s.sale_price_ << " " << s.discount_;
  return out;
}

bool operator==(const SalesData &lhs, const SalesData &rhs) {
  return lhs.units_sold_ == rhs.units_sold_ &&
         lhs.ori_price_ == rhs.ori_price_ &&
         lhs.sale_price_ == rhs.sale_price_ && lhs.isbn() == rhs.isbn();
}

bool operator!=(const SalesData &lhs, const SalesData &rhs) {
  return !(lhs == rhs);
}

SalesData &SalesData::operator+=(const SalesData &rhs) {
  units_sold_ += rhs.units_sold_;
  sale_price_ =
      (rhs.sale_price_ * rhs.units_sold_ + sale_price_ * units_sold_) /
      (rhs.units_sold_ + units_sold_);
  if (ori_price_ != 0) discount_ = sale_price_ / ori_price_;
  return *this;
}

SalesData operator+(const SalesData &lhs, const SalesData &rhs) {
  SalesData ret(lhs);  // 把 lhs 的内容拷贝到临时变量 ret 中，这种做法便于运算
  ret += rhs;  // 把 rhs 的内容加入其中
  return ret;  // 返回 ret
}
