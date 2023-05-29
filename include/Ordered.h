#pragma once
#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
template <class Key, class Val>
bool compare(pair<Key, Val> left, pair<Key, Val> right)
{
	return left.first < right.first;
}

template <class Key, class Val>
class OrderedTable
{
	vector<pair<Key, Val>> table;
public:

	OrderedTable() {}

	typename vector<pair<Key, Val>>::iterator findElem(Key key)
	{
		return lower_bound(table.begin(), table.end(), make_pair(key, Val()), compare<Key, Val>);
	}

	void push(Key key, Val value)
	{
		auto iter = findElem(key);
		if (!table.empty())
		{
			if (iter == table.end())
			{
				table.insert(iter, make_pair(key, value));
			}
			else
			{
				(*iter).second = value;
			}
		}
		else
		{
			table.push_back({ key, value });
		}
	}

	void erase(Key key)
	{
		auto iter = findElem(key);
		table.erase(iter);
	}

	void print()
	{
		for (auto iter = table.begin(); iter != table.end(); iter++)
		{
			cout << (*iter).first << " | " << (*iter).second << '\n';
		}
	}
};