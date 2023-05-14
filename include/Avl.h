#pragma once
#include <iostream>
template <class Tkey, class Tvalue>
class AVL_tree {

	struct Node
	{
		Tkey key;
		Tvalue value;
		Node* left;
		Node* right;
		int height;

		Node() {};

		Node(Tkey k, Tvalue v) {
			key = k;
			value = v;
			left = nullptr;
			right = nullptr;
			height = 1;
		};

		~Node() {};
	};

	Node* Ninsert(Tkey Nkey, Tvalue Nvalue, Node* Nroot) {
		if (!Nroot)
			return new Node(Nkey, Nvalue);
		if (Nroot->key == Nkey) {
			return Nroot;
		}
		if (Nroot->key > Nkey) {
			Nroot->left = Ninsert(Nkey, Nvalue, Nroot->left);
		}
		if (Nroot->key < Nkey) {
			Nroot->right = Ninsert(Nkey, Nvalue, Nroot->right);
		}
		return balance(Nroot);
	}

	Node* Nfind(Tkey key, Node* root) {
		if (!root) {
			return root;
		}
		else if (root->key > key) {
			return Nfind(key, root->left);
		}
		else if (root->key < key) {
			return Nfind(key, root->right);
		}
		return root;
	}

	Node* RightRotation(Node* t) {
		Node* q = t->left;
		t->left = q->right;
		q->right = t;
		fix_height(t);
		fix_height(q);
		return q;
	}

	Node* LeftRotation(Node* t) {
		Node* p = t->right;
		t->right = p->left;
		p->left = t;
		fix_height(t);
		fix_height(p);
		return p;
	}

	Node* findMax(Node* t) {
		if (!t->right) {
			return t;
		}
		return findMax(t->right);
	}

	Node* eraseMax(Node* tl) {
		if (tl->right == nullptr)
			return tl->left;
		tl->right = eraseMax(tl->right);
		return balance(tl);
	}

	Node* Nerase(Tkey Nkey, Node* t) {
		if (!t)
			return nullptr;
		if (t->key > Nkey) {
			t->left = Nerase(Nkey, t->left);
		}
		else if (t->key < Nkey) {
			t->right = Nerase(Nkey, t->right);
		}
		else {
			Node* left = t->left;
			Node* right = t->right;
			delete t;
			if (!left)
				return right;
			Node* max = findMax(left);
			max->left = eraseMax(left);
			max->right = right;
			return balance(max);
		}
		return balance(t);
	}

	Node* balance(Node* t) {
		fix_height(t);
		if (bfact(t) == 2) {
			if (bfact(t->right) < 0) {
				t->right = RightRotation(t->right);
			}
			return LeftRotation(t);
		}
		if (bfact(t) == -2) {
			if (bfact(t->left) > 0) {
				t->left = LeftRotation(t->left);
			}
			return RightRotation(t);
		}
		return t;
	}

	int height(Node* t) {
		return t ? t->height : 0;
	}

	int bfact(Node* t) {
		return height(t->right) - height(t->left);
	}

	void fix_height(Node* t) {

		int hl = height(t->left);
		int hr = height(t->right);
		t->height = (hl > hr ? hl : hr) + 1;
	}

public:

	Node* root;

	AVL_tree() {
		root = nullptr;
	};

	void insert(Tkey Nkey, Tvalue Nvalue) {
		this->root = Ninsert(Nkey, Nvalue, this->root);
	}

	Tvalue& operator[](Tkey key) {
		Node* tmp = Nfind(key, this->root);
		if (tmp) {
			return tmp->value;
		}
		else {
			throw;
		}
	}

	void erase(Tkey Nkey) {
		this->root = Nerase(Nkey, this->root);
	}

};