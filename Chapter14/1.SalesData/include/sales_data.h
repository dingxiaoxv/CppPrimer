#ifndef SALES_DATA_H_INCLUDED
#define SALES_DATA_H_INCLUDED

#include <iostream>
#include <string>

class SalesData {
  friend std::istream& operator>>(std::istream&, SalesData&);
  friend std::ostream& operator<<(std::ostream&, const SalesData&);
  friend bool operator==(const SalesData&, const SalesData&);

public:
  SalesData() = default;
  SalesData(const std::string& book) : bookNo_(book) {}
  std::string isbn() const { return bookNo_; }
  SalesData& operator+=(const SalesData&);

private:
  std::string bookNo_;
  unsigned units_sold_ = 0;
  double ori_price_ = 0.0;
  double sale_price_ = 0.0;
  double discount_ = 0.0;
};

inline bool compareIsbn(const SalesData& lhs, const SalesData& rhs);
bool operator!=(const SalesData& lhs, const SalesData& rhs);
SalesData operator+(const SalesData& lhs, const SalesData& rhs);

#endif