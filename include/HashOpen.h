#pragma once
#include <string>
#include <vector>

using namespace std;

template <class Val>
class HashTableOpenAdress
{
	vector<pair<int, Val>> table;
	vector<bool> isEmpty;
	int copacity = 0;
	int const step = 3;
	int const size = 197;
	double const A = (pow(5, 0.5) - 1) / 2.0;

public:

	HashTableOpenAdress()
	{
		table = vector<pair<int, Val>>(size);
		isEmpty = vector<bool>(size);

		for (int i = 0; i < size; i++)
		{
			isEmpty[i] = false;
		}

		copacity = 0;
	}

	int hash(int key)
	{
		return int(size * ((key * A) - floor(key * A)));
	}

	Val findValue(int key)
	{
		int index = hash(key);
		while (isEmpty[index])
		{
			if (table[index].first == index)
			{
				return table[index].second;
			}

			index = (index + step) % size;
		}

		return Val();
	}

	void push(int key, Val value)
	{
		int index = hash(key);
		copacity++;
		while (isEmpty[index] && table[index].first != index)
		{
			index = (index + step) % size;
		}
		isEmpty[index] = true;
		table[index].first = key;
		table[index].second = value;
	}

	void erase(int key)
	{
		if (copacity == 0)
			return;
		copacity--;
		int index = hash(key);
		while (isEmpty[index])
		{
			if (table[index].first == key)
			{
				isEmpty[index] = false;
			}
			index = (index + step) % size;
		}
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			if (isEmpty[i])
			{
				cout << table[i].first << '|' << table[i].second << '\n';
			}
		}
	}
};