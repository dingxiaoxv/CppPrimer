#include <iostream>
using namespace std;

void testReference()
{
    int i = 42;
    const int ci = 1024;
    const int &r1 = 42;
    const int &r2 = ci;
    const int &r3 = i;
    int &r4 = i;
    r4 = 5;
    //int &r5 = ci;
}

void testPointer()
{
    int i = 42;
    const int ci = 1024;
    const int *ptrc;
    ptrc = &ci;
    ptrc = &i;
    int *const cptr = &i;
    *cptr = 0;
    const int *const p = &ci;
}

//返回s中第一次出现c的位置索引和出现次数
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
    testReference();
    testPointer();

    char pch[] = {'p','r','i','m','e','r','\0'};
    string s(pch);
    string::size_type occurs = 0, ret = 0;
    ret = findChar(s, 'i', occurs);
    ret = findChar("primer", 'i', occurs);

    return 0;
}