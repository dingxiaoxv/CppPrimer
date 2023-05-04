#include <iostream>
#include <string>

using namespace std;

void replace_iterator(string &s, const string &oldVal, const string &newVal)
{
	auto len = oldVal.size();
	if (!len)
	{
		cout << "oldVal is empty" << endl;
		return;
	}
	auto it = s.begin();
	while (it <= s.end() - len)
	{
		auto iter1 = it;
		auto iter2 = oldVal.begin();
		while (iter2 != oldVal.end())
		{
			if (*iter1 != *iter2)
				break;
			++iter1;
			++iter2;
		}
		if (iter2 == oldVal.end())
		{
			it = s.erase(it, iter1);
			if (!newVal.size())
			{
				cout << "newVal is empty" << endl;
				return;
			}
			else
			{
				iter2 = newVal.end();
				while (iter2 > newVal.begin())
				{
					--iter2;
					it = s.insert(it, *iter2);
				}
				it += newVal.size();
			}
		}
		else
		{
			++it;
		}
	}
}

void replace_index(string& s, const string& oldVal, const string& newVal)
{
	int i = 0;
	while ((i = s.find(oldVal, i)) != string::npos)
	{
		s.replace(i, oldVal.size(), newVal);
		i += newVal.size();
	}
}

int main()
{
	string s("tho thru tho!");
	replace_iterator(s, "tho", "though");
	cout << s << endl;

	replace_index(s, "thru", "through");
	cout << s << endl;

	return 0;
}