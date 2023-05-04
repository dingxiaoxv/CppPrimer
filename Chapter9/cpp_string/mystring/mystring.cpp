#include <iostream>
#include <string>

using namespace std;

void assign()
{
	string str("string");
	string s("this is string");
	str.assign(s);
	cout << str << endl;
	str.assign("this is not string");
	cout << str << endl;
}

void insert()
{
	string str("hello");
	str.insert(str.size(), 5, '!');
	cout << str << endl;

	const char* cp = "Stately, plump Buck";
	str.assign(cp, 7);
	str.insert(str.size(), cp + 7);
	cout << str << endl;

	string s = "some other string";
	str.insert(0, s);
	cout << str << endl;
}

void erase()
{
	string str("hello");
	str.append("!!!!!");
	str.erase(str.size() - 5, 5);
	cout << str << endl;
}

void append()
{
	string str("c++ primer");
	str.append(" 4th Ed.");
	cout << str << endl;

	str.replace(11, 3, "fifth");
	cout << str << endl;
}

int main()
{
	assign();
	insert();
	erase();
	append();

	return 0;
}