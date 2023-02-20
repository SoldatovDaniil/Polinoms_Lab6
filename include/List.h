#include <iostream>


using namespace std;
template <class T>
class List
{
public:
	struct Node
	{
		T elem;
		Node* next;
		Node(T newElem, Node* newNext = nullptr)
		{
			elem = newElem;
			next = newNext;
		}
		Node(const Node& node)
		{
			elem = node.elem;
			delete[] next;
			next = new Node();
			next = node.next;
		}
	};

	Node* root;

	class iterator
	{
	public:
		Node* i_node;

		iterator()
		{
			i_node = nullptr;
		}

		iterator(Node* nptr)
		{
			i_node = nptr;
		}

		iterator(const iterator& iter)
		{
			i_node = iter.i_node;
		}

		~iterator()
		{
			i_node = nullptr;
		}

		iterator& operator++()
		{
			i_node = i_node->next;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			i_node = i_node->next;
			return tmp;
		}

		T& operator*()
		{
			return i_node->elem;
		}

		iterator& operator=(const iterator& it1)
		{
			i_node = it1.i_node;
			return *this;
		}

		iterator operator+(int step)
		{
			iterator tmp = i_node;
			for (int i = 0; i < step; i++)
			{
				tmp++;
			}
			return tmp;
		}

		friend bool operator==(const iterator& it1, const iterator& it2)
		{
			return (it1.i_node == it2.i_node);
		}

		friend bool operator!=(const iterator& it1, const iterator& it2)
		{
			return (it1.i_node != it2.i_node);
		}
	};

	List()
	{
		root = nullptr;
	}

	List(Node* first)
	{
		root = first;
	}

	List(int size)
	{
		root = new Node(0);
		Node* tmp = root;
		for (int i = 1; i < size; i++) {
			tmp->next = new Node(0);
			tmp = tmp->next;
		}
	}

	List(const List& other)
	{
		root = new Node(other.root->elem);
		Node* tmp = root;
		Node* res = other.root;
		while (res->next)
		{
			tmp->next = new Node(res->next->elem);
			tmp = tmp->next;
			res = res->next;
		}
	}

	~List()
	{
		clear();
	}

	List& operator=(const List& list)
	{
		root = new Node(list.root->elem);
		Node* tmp1 = root;
		Node* tmp2 = list.root;
		while (tmp2->next)
		{
			tmp1->next = new Node(tmp2->next->elem);
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		return *this;
	}

	bool empty() const
	{
		if (root == nullptr)
		{
			return true;
		}
		return false;
	}

	int getSize()
	{
		int size = 0;
		for (auto it = begin(); it != end(); ++it)
		{
			size++;
		}
		return ++size;
	}

	void clear()
	{
		if (empty())
		{
			return;
		}
		else
		{
			Node* tmp = root;
			Node* tmp2;
			while (tmp->next != nullptr)
			{
				tmp2 = tmp->next;
				delete tmp;
				tmp = tmp2;
			}
			root = nullptr;
		}
	}

	List separator()
	{
		Node* tmp1 = root;
		Node* tmp2 = root;
		if (tmp1->next == nullptr)
		{
			List<T> res1;
			return res1;
		}
		if (tmp1->next->next == nullptr)
		{
			tmp1 = tmp1->next;
			root->next = nullptr;
			List<T> res2(tmp1);
			return res2;
		}
		while (tmp1->next != nullptr && tmp1->next->next != nullptr)
		{
			tmp1 = tmp1->next->next;
			tmp2 = tmp2->next;
		}
		Node* res = tmp2->next;
		tmp2->next = nullptr;
		List<T> res3(res);
		return res3;
	}

	List merge(const List& list)
	{
		List<T> res;
		Node* tmp1 = root;
		Node* tmp2 = list.root;
		while (tmp1 != nullptr && tmp2 != nullptr)
		{
			if (tmp1->elem >= tmp2->elem)
			{
				res.push_back(tmp2->elem);
				tmp2 = tmp2->next;
			}
			else
			{
				res.push_back(tmp1->elem);
				tmp1 = tmp1->next;
			}
		}
		if (tmp1 == nullptr)
		{
			while (tmp2 != nullptr)
			{
				res.push_back(tmp2->elem);
				tmp2 = tmp2->next;
			}
		}
		else if (tmp2 == nullptr)
		{
			while (tmp1 != nullptr)
			{
				res.push_back(tmp1->elem);
				tmp1 = tmp1->next;
			}
		}
		return res;
	}

	void mergeSort()
	{
		if (root->next != nullptr)
		{
			List<T> hlist = separator();
			mergeSort();
			hlist.mergeSort();
			*this = merge(hlist); 
		}
	}

	bool check()
	{
		iterator iter = begin();
		T tmp = *iter;
		iter++;
		while (iter != end())
		{
			if (tmp > *iter)
			{
				return false;
			}
			tmp = *iter;
			iter++;
		}
		return true;
	}

	Node* findMiddle()
	{
		Node* tmp1 = root;
		Node* tmp2 = root;
		if (getSize() % 2 == 0)
		{
			tmp2 = tmp2->next->next;
		}
		else
		{
			tmp2 = tmp2->next;
		}
		while (tmp2)
		{
			tmp1 = tmp1->next;
			if (tmp2->next)
			{
				tmp2 = tmp2->next->next;
			}
			else
			{
				break;
			}
		}
		return tmp1;
	}

	void delMiddle()
	{
		if (root == nullptr || root->next == nullptr)
		{
			return;
		}
		Node* tmp1 = root;
		Node* tmp2 = root;
		Node* previous = tmp1;
		Node* prePrevious = tmp1;
		int size = 0;
		while (tmp2 != nullptr && tmp2->next != nullptr)
		{
			++size;
			tmp2 = tmp2->next->next;
			prePrevious = previous;
			previous = tmp1;
			tmp1 = tmp1->next;
		}
		if (size % 2 == 1)
		{
			previous->next = tmp1->next;
		}
		else
		{
			prePrevious->next = tmp1->next;
		}
	}

	iterator begin()
	{
		return iterator(root);
	}

	iterator end()
	{
		Node* tmp = root;
		while (tmp->next != nullptr)
		{
			tmp = tmp->next;
		}
		return iterator(tmp);
	}

	iterator insert_after(iterator pos, T value)
	{
		Node* tmp = new Node(value);
		tmp->next = pos.i_node->next;
		pos.i_node->next = tmp;
		return iterator(tmp);
	}

	iterator erase_after(iterator pos)
	{
		Node* tmp = pos.i_node;
		Node* tmp2 = tmp->next;
		tmp->next = tmp2->next;
		delete tmp2;
		return iterator(tmp->next);
	}

	void push_front(T value)
	{
		Node* node = new Node(value, nullptr);
		if (empty())
		{
			root = node;
		}
		else
		{
			node->next = root;
			root = node;
		}
	}

	void push_back(T value)
	{
		if (empty())
		{
			Node* tmp = new Node(value);
			root = tmp;
		}
		else
		{
			Node* tmp = root;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			Node* tmp2 = new Node(value);
			tmp->next = tmp2;
		}
	}

	void pop_back()
	{
		iterator iter = begin();
		for (int i = 0; i < getSize() - 2; i++)
		{
			++iter;
		}
		erase_after(iter);
	}

	void pop_front()
	{
		if (root == nullptr)
		{
			throw "Error pop_front because list is empty";
		}
		Node* tmp = root->next;
		root = tmp;
	}

	void print()
	{
		Node* tmp = root;
		while (tmp)
		{
			cout << tmp->elem;
			tmp = tmp->next;
		}
		cout << endl;
	}
};