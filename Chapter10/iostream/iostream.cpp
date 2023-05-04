#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

void practice_29()
{
    ifstream in("data.txt");
    if (!in)
    {
        cout << "file open error" << endl;
        return;
    }
    istream_iterator<string> in_iter(in), eof;
    vector<string> words(in_iter, eof);
    copy(words.cbegin(), words.cend(), ostream_iterator<string>(cout, " "));
    cout << endl;
}

void practice_30()
{
    istream_iterator<int> in_iter(cin), eof;
    vector<int> vec(in_iter, eof);
    sort(vec.begin(), vec.end());
    ostream_iterator<int> out_iter(cout, " ");
    for (auto val : vec)
    {
        out_iter = val;
    }
    cout << endl;
}

void practice_31()
{
    istream_iterator<int> in_iter(cin), eof;
    vector<int> vec(in_iter, eof);
    sort(vec.begin(), vec.end());
    unique_copy(vec.begin(), vec.end(), ostream_iterator<int>(cout, " "));
    cout << endl;
}

void practice_33()
{
    string inFileName, outFileName1, outFileName2;
    cout << "please type input file name :";
    getline(cin, inFileName);
    // cin.get();
    cout << "please type output file name :";
    getline(cin, outFileName1);
    // cin.get();
    cout << "please type output file name :";
    getline(cin, outFileName2);
    // cin.get();

    ifstream in(inFileName);
    if (!in)
    {
        cout << "file open error" << endl;
        return;
    }
    ofstream out1(outFileName1), out2(outFileName2);
    istream_iterator<int> in_iter(in), eof;
    vector<int> vec(in_iter, eof);
    sort(vec.begin(), vec.end());
    ostream_iterator<int> out_iter_odd(out1, " "), out_iter_even(out2, "\n");
    for (auto val : vec)
    {
        if (val % 2 != 0)
        {
            *out_iter_odd++ = val;
        }
        else
        {
            *out_iter_even++ = val;
        }
    }
}

int main(int argc, char *argv[])
{
    // practice_29();
    // practice_30();
    // practice_31();
    practice_33();

    return 0;
}