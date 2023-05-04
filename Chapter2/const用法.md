# const的用法

## 1.1 const引用

**常量引用：**可以绑定常量和非常量，但不允许修改绑定对象的值。

**非常量引用：**不能绑定常量。

```c++
int i = 42;
const int ci = 1024;
const int &r1 = 42; //const引用可以绑定字面值
const int &r2 = ci; //const引用可以绑定常量
const int &r3 = i;	//const引用可以绑定非常量
int &r4 = i; //非常量引用可以绑定非常量
r4 = 5; //非常量引用可以修改值
int &r5 = ci; //错误，非常量引用不能绑定常量
```

## 1.2 const指针

**指向常量的指针：**可以指向常量和非常量，可以改变指向的对象，但是不能修改指向对象的值。`const int *ptrc;`

**常量指针：**可以指向常量和非常量，不能改变指向的对象，指向非常量可以修改非常量的值。常量指针必须**初始化**。`int *const cptr = &i;`

```c++
int i = 42;
const int ci = 1024;
const int *ptrc; //指向常量的指针
ptrc = &ci;
ptrc = &i; //指向常量的指针可以改变指向的对象
int *const cptr = &i; //常量指针必须初始化
*cptr = 0; //常量指针指向非常量，可以修改非常量的值
const int *const p = &ci; //指向常量的常量指针
```

## 1.3 顶层const

**顶层const：**表示修饰的对象是常量。

**底层const：**指向常量的引用或指针。

## 1.4 常量表达式

**1) 字面值**

算术类型、引用、指针是字面值类型，自定义类不是。

**2) constexpr**

```c++
constexpr int size = 20;
```

**3.用常量表达式初始化的const对象**

```c++
const int sz = size; //size是constexpr
const int len = getSize(); //getSize()不是常量表达式
```

## 1.5 const形参

**1) 顶层const形参**

实参初始化会忽略顶层const，函数重载时参数列表没有区别。

```c++
Book lookup(int id);
Book lookup(const int id); //重复声明，不进行重载
```

**2) 底层const形参**

**建议尽量使用常量引用形参：**

使用非常量引用形参只能绑定非常量，不能绑定常量、字面值、类型转换的对象（绑定的是临时量），极大地限制函数所能接受实参的类型。

但要修改传入实参对象的值，则必须使用非常量引用形参。

```c++
//返回s中第一次出现c的位置索引和出现次数
//s采用常量引用形参，既可以输入string对象，又可以输入字面值
//occurs采用非常量引用形参，用于隐式返回出现次数
string::size_type findChar(const string &s, char c, string::size_type &occurs)
{
    auto ret = s.size();
    occurs = 0;
    for (decltype(ret) i = 0; i != s.size(); ++i)
    {
        if(c == s[i])
        {
            if(ret == s.size())
            {
                ret = i;
            }
            ++occurs; //出现次数通过occurs隐式返回
        }
    }
    return ret;
}

int main()
{
    char pch[] = {'p','r','i','m','e','r','\0'};
    string s(pch);
    string::size_type occurs = 0, ret = 0;
    ret = findChar(s, 'i', occurs);
    ret = findChar("primer", 'i', occurs);

    return 0;
}
```

## 1.6 constexpr函数

用于常量表达式的函数，要遵守以下约定：

1. 函数返回类型及所有形参类型必须是字面值类型。
2. 函数体中有且只有一条return语句。

```c++
constexpr int newSize(){return 42;}
```

建议constexpr函数定义在头文件中。

## 1.7 const成员函数

1. 不能改变类成员的内容，只能读取。
2. 常量对象、引用只能调用const成员函数。
3. const成员函数以引用形式返回*this，返回的是常量引用，只能调用const成员函数。

```c++
class Sales_data
{
public:
    Sales_data() = default;
    ~Sales_data();
    std::string isbn() const;

private:
    std::string bookNo = "";
};

//在定义时也要加上const修饰
std::string Sales_data::isbn() const
{
    return bookNo;
}
```

