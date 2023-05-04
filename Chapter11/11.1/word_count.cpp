#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

vector<string> stringSplit(string str, const char &split);
string &stringTrans(string &str);

vector<string> stringSplit(string str, const char &split)
{
    std::istringstream iss(str);
    string token;
    vector<string> vec;
    while (getline(iss, token, split))
    {
        vec.push_back(token);
    }
    return vec;
}

//! 练习11.3
void wordCount()
{
    cout << "please input a line:" << endl;
    string str;
    getline(cin, str);
    vector<string> words = stringSplit(str, ' ');
    map<string, size_t> wordCount;
    for (auto val : words)
    {
        //++wordCount[val];
        ++wordCount[stringTrans(val)];
    }
    for (auto val : wordCount)
    {
        cout << val.first << " occurs " << val.second << " times " << endl;
    }
}

//! 练习11.4
string &stringTrans(string &str)
{
    // 在循环中删除string元素
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] -= ('A' - 'a'); // 大写字母转小写字母
        }
        else if (',' == str[i] || '.' == str[i])
        {
            str.erase(i, 1); // 删除标点符号
        }
    }
    return str;
}

int main(int argc, char *argv[])
{
    wordCount();

    return 0;
}