#ifndef SALES_DATA_H
#define SALES_DATA_H
#include <string>

class Sales_data
{
public:
    Sales_data() = default;
    ~Sales_data();
    std::string isbn() const;

private:
    std::string bookNo = "";
};

Sales_data::Sales_data()
{
}

Sales_data::~Sales_data()
{
}

std::string Sales_data::isbn() const
{
    return bookNo;
}

#endif