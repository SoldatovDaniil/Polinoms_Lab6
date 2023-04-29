#include"Polinom.h"
#include<vector>
#include<algorithm>
#include<list>
template<typename Tkey, typename Tvalue>
class hash_table {
private:
	std::vector<std::list<std::pair<Tkey, Tvalue>>> table;
	int size;
	int P = 100;
public:
	class iterator {
		typename list<std::pair<Tkey, Tvalue>>::iterator it;
		hash_table* t = nullptr;
		int index; // v vectore
	public:
		iterator(typename list<std::pair<Tkey, Tvalue>>::iterator iter, int i) { it = iter; index = i; }
		bool operator ==(const iterator& iter) { return it == iter.it && index == iter.index; }
		bool operator !=(const iterator& iter) { return !(operator==(iter)); }
		std::pair<Tkey, Tvalue>& operator*() {
			std::pair<Tkey, Tvalue>& tmp = *it;
			return tmp;
		}
		iterator& operator ++() {
			if (it != t->table[index].end())
				it++;

			if (it == t->table[index].end())
			{
				index++;
				while (index + 1 < t->table.size() && (t->table[index]).size() == 0)
					index++;
				if (index == t->table.size())
					*this = t->end();
				else
					it = t->table[index].begin();
			}
			
			return *this;
		};
	};

	iterator end() { return iterator(table.back().end(), table.size() - 1); }
	iterator begin()
	{
		int ind = 0;
		while (ind + 1 < table.size() && table[ind].size() == 0)
			ind++;

		if (ind < table.size())
			return iterator(table[ind].begin(), ind);
		else
			return end();
	}

	void repacking(int new_size)
	{
		auto tmp = table;
		table.clear();
		table.resize(new_size);
		for (auto& x : tmp) for (auto& y : x)
			insert(y);
	}

	int hash_str(const std::string& str)
	{
		size_t res = 0;
		size_t  st = 1;
		for (char c : str)
		{
			res = (res + c * st)% P ;
			st *= 5;
		}
		return res;
	}

	size_t get_index(size_t hash) { return (hash % table.size()); }

	iterator insert(const std::pair<Tkey, Tvalue>& element)
	{
		size++;
		if (table.size() * 2 < size)
			repacking(table.size() * 2 + 1);

		size_t hash = hash_str(element.first);
		size_t index = get_index(hash);


		for (auto it = table[index].begin(); it != table[index].end(); ++it)
			if ((*it).first == element.first)
				return iterator(it, index);
		table[index].push_front(element);
		return iterator(table[index].begin(), index);

	}

	void erase(const Tkey& key)
	{
		size--;
		size_t hash = hash_str(key);
		size_t index = get_index(hash);

		auto prev_iter = table[index].end();
		auto it = table[index].begin();

		for (; it != table[index].end() && (*it).first != key; ++it)
		{
			prev_iter = it;
		}


		if (prev_iter != table[index].end())
		{
			table[index].erase(prev_iter);
		}
		else if ((*table[index].begin()).first == key)
		{
			table[index].pop_front();
		}

	}

	iterator find(const Tkey& key)
	{
		size_t hash = hash_str(key);
		size_t index = get_index(hash);


		for (auto it = table[index].begin(); it != table[index].end(); ++it)
			if ((*it).first == key)
				return iterator(it, index);

		return end();
	}
};