#include <iostream>


using namespace std;


template <class T>
class rbtTree 
{
public:
	enum Colors
	{
		black,
		red
	};

	template <class Key>
	struct rbtNode
	{
		

		Key key;
		Colors color;
		rbtNode<Key>* leftPointer;
		rbtNode<Key>* rightPointer;
		rbtNode<Key>* parent;

		rbtNode(Key k, Colors c, rbtNode* p, rbtNode* l, rbtNode* r) :
			color(c), key(k), leftPointer(l), rightPointer(r), parent(p) {};
	};
 
	rbtNode<T>* root;

	rbtTree<T>() : root(NULL)
	{
		root = nullptr;
	}

	~rbtTree<T>()
	{
		deleteNode(root);
	}

	void deleteNode(rbtNode<T>*& node)
	{
		if (node == NULL)
		{
			return;
		}

		deleteNode(node->leftPointer);
		deleteNode(node->rightPointer);
		delete node;
		node = nullptr;
	}

	void leftRotate(rbtNode<T>* &root, rbtNode<T>* firstNode)
	{
		rbtNode<T>* secondNode = firstNode->rightPointer;
		firstNode->rightPointer = secondNode->leftPointer;

		if (secondNode->leftPointer != NULL)
		{
			secondNode->leftPointer->parent = firstNode;
		}

		secondNode->parent = firstNode->parent;

		if (firstNode->parent == NULL)
		{
			root = secondNode;
		}
		else
		{
			if (firstNode == firstNode->parent->leftPointer)
			{
				firstNode->parent->leftPointer = secondNode;
			}
			else
			{
				firstNode->parent->rightPointer = secondNode;
			}
		}

		secondNode->leftPointer = firstNode;
		firstNode->parent = secondNode;
	}

	void rightRotate(rbtNode<T>* &root, rbtNode<T>* secondNode) {
		rbtNode<T>* firstPointer = secondNode->leftPointer;
		secondNode->leftPointer = firstPointer->rightPointer;

		if (firstPointer->rightPointer != NULL)
		{
			firstPointer->rightPointer->parent = secondNode;
		}

		firstPointer->parent = secondNode->parent;
		if (secondNode->parent == NULL)
		{
			root = firstPointer;
		}
		else 
		{
			if (secondNode == secondNode->parent->rightPointer)
			{
				secondNode->parent->rightPointer = firstPointer;
			}
			else
			{
				secondNode->parent->leftPointer = firstPointer;
			}
		}

		firstPointer->rightPointer = secondNode;
		secondNode->parent = firstPointer;
	}

	void insert(T key)
	{
		rbtNode<T>* node = new rbtNode<T>(key, red, NULL, NULL, NULL);
		insert(root, node);
	}

	void insert(rbtNode<T>* &root, rbtNode<T>* node)
	{
		rbtNode<T>* firstNode = root;
		rbtNode<T>* secondNode = NULL;

		while (firstNode != NULL)
		{
			secondNode = firstNode;

			if (node->key > firstNode->key)
			{
				firstNode = firstNode->rightPointer;
			}
			else
			{
				firstNode = firstNode->leftPointer;
			}
		}

		node->parent = secondNode;

		if (secondNode != NULL)
		{
			if (node->key > secondNode->key)
			{
				secondNode->rightPointer = node;
			}
			else
			{
				secondNode->leftPointer = node;
			}
		}
		else
		{
			root = node;
		}

		node->color = red;
		insertWithParent(root, node);
	}
	
	void insertWithParent(rbtNode<T>* &root, rbtNode<T>* node)
	{
		rbtNode<T>* parent;
		parent = node->parent;

		while (node != rbtTree::root && parent->color == red)
		{
			rbtNode<T>* upParent = parent->parent;
			if (upParent->leftPointer == parent)
			{
				rbtNode<T>* uncle = upParent->rightPointer;
				if (uncle != NULL && uncle->color == red)
				{
					parent->color = black;
					uncle->color = black;
					upParent->color = red;
					node = upParent;
					parent = node->parent;
				}
				else
				{
					if (parent->rightPointer == node)
					{
						leftRotate(root, parent);
						swap(node, parent);
					}

					rightRotate(root, upParent);
					upParent->color = red;
					parent->color = black;
					break;
				}
			}
			else
			{
				rbtNode<T>* uncle = upParent->leftPointer;
				if (uncle != NULL && uncle->color == red)
				{
					upParent->color = red;
					parent->color = black;
					uncle->color = black;

					node = upParent;
					parent = node->parent;
				}
				else
				{
					if (parent->leftPointer == node)
					{
						rightRotate(root, parent);
						swap(parent, node);
					}

					leftRotate(root, upParent);
					parent->color = black;
					upParent->color = red;
					break;
				}
			}
		}
		root->color = black;
	}

	void remove(T key)
	{
		rbtNode<T>* delNode = search(root, key);
		if (delNode != NULL)
		{
			remove(root, delNode);
		}
	}

	void remove(rbtNode<T>* &root, rbtNode<T>* node)
	{
		rbtNode<T>* child;
		rbtNode<T>* parent;
		Colors color;

		if (node->leftPointer != NULL && node->rightPointer != NULL)
		{
			rbtNode<T>* replace = node;
			replace = node->rightPointer;

			while (replace->leftPointer != NULL)
			{
				replace = replace->leftPointer;
			}
			
			if (node->parent != NULL)
			{
				if (node->parent->leftPointer == node)
				{
					node->parent->leftPointer = replace;
				}
				else
				{
					node->parent->rightPointer = replace;
				}
			}
			else
			{
				root = replace;
			}

			child = replace->rightPointer;
			parent = replace->parent;
			color = replace->color;

			if (parent == node)
			{
				parent = replace;
			}
			else
			{
				if (child != NULL)
				{
					child->parent = parent;
				}

				parent->leftPointer = child;
				replace->rightPointer = node->rightPointer;
				node->rightPointer->parent = replace;
			}

			replace->parent = node->parent;
			replace->color = node->color;
			replace->leftPointer = node->leftPointer;
			node->leftPointer->parent = replace;

			if (color == black)
			{
				removeWithParent(root, child, parent);
			}

			delete node;
			return;
		}

		if (node->leftPointer != NULL)
		{
			child = node->leftPointer;
		}
		else
		{
			child = node->rightPointer;
		}

		parent = node->parent;
		color = node->color;

		if (child)
		{
			child->parent = parent;
		}
		
		if (parent)
		{
			if (node == parent->leftPointer)
			{
				parent->leftPointer = child;
			}
			else
			{
				parent->rightPointer = child;
			}
		}

		else
		{
			rbtTree::root = child;
		}

		if (color == black)
		{
			removeWithParent(root, child, parent);
		}

		delete node;
	}

	void removeWithParent(rbtNode<T>* &root, rbtNode<T>* node, rbtNode<T>* parent)
	{
		rbtNode<T>* othernode;
		while ((!node) || node->color == black && node != rbtTree::root)
		{
			if (parent->leftPointer == node)
			{
				othernode = parent->rightPointer;
				if (othernode->color == red)
				{
					othernode->color = black;
					parent->color = red;
					leftRotate(root, parent);
					othernode = parent->rightPointer;
				}
				else
				{
					if (!(othernode->rightPointer) || othernode->rightPointer->color == black)
					{
						othernode->leftPointer->color = black;
						othernode->color = red;
						rightRotate(root, othernode);
						othernode = parent->rightPointer;
					}

					othernode->color = parent->color;
					parent->color = black;
					othernode->rightPointer->color = black;
					leftRotate(root, parent);
					node = root;
					break;
				}
			}
			else
			{
				othernode = parent->leftPointer;
				if (othernode->color == red)
				{
					othernode->color = black;
					parent->color = red;
					rightRotate(root, parent);
					othernode = parent->leftPointer;
				}
				if ((!othernode->leftPointer || othernode->leftPointer->color == black) && (!othernode->rightPointer || othernode->rightPointer->color == black))
				{
					othernode->color = red;
					node = parent;
					parent = node->parent;
				}
				else
				{
					if (!(othernode->leftPointer) || othernode->leftPointer->color == black)
					{
						othernode->rightPointer->color = black;
						othernode->color = red;
						leftRotate(root, othernode);
						othernode = parent->leftPointer;
					}

					othernode->color = parent->color;
					parent->color = black;
					othernode->leftPointer->color = black;
					rightRotate(root, parent);
					node = root;
					break;
				}
			}
		}

		if (node)
		{
			node->color = black;
		}
	}
		
	rbtNode<T>* search(T key)
	{
		return search(root, key);
	}

	rbtNode<T>* search(rbtNode<T>* node, T key) const
	{
		if (node == NULL || node->key == key)
		{
			return node;
		}
		else
		{
			if (key > node->key)
			{
				return search(node->rightPointer, key);
			}
			else
			{
				return search(node->leftPointer, key);
			}
		}
	}

	void print() 
	{
		if (root == NULL)
		{
			cout << "empty RB tree\n";
		}
		else
		{
			print(root);
		}
	}
	
	void print(rbtNode<T>* node)const 
	{
		if (node == NULL)
		{
			return;
		}
		if (node->parent == NULL)
		{
			cout << node->key << "(" << node->color << ") is root" << '\n';
		}
		else if (node->parent->leftPointer == node)
		{
			cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "left child" << '\n';
		}
		else
		{
			cout << node->key << "(" << node->color << ") is " << node->parent->key << "'s " << "right child" << '\n';
		}

		print(node->leftPointer);
		print(node->rightPointer);
	}

	//void preOrder() 
	//{
	//	if (root == NULL)
	//	{
	//		cout << "empty RB tree\n";
	//	}
	//	else
	//	{
	//		preOrder(root);
	//	}
	//}

	//void preOrder(rbtNode<T>* tree)const 
	//{
	//	if (tree != NULL) 
	//	{
	//		cout << tree->key << " ";
	//		preOrder(tree->leftPointer);
	//		preOrder(tree->rightPointer);
	//	}
	//}
	//
	//void inOrder() 
	//{
	//	if (root == NULL)
	//	{
	//		cout << "empty RB tree\n";
	//	}
	//	else
	//	{
	//		inOrder(root);
	//	}
	//}
	//
	//void inOrder(rbtNode<T>* tree) const 
	//{
	//	if (tree != NULL) 
	//	{
	//		inOrder(tree->leftPointer);
	//		cout << tree->key << " ";
	//		inOrder(tree->rightPointer);
	//	}
	//}

	//void postOrder() 
	//{
	//	if (root == NULL)
	//	{
	//		cout << "empty RB tree\n";
	//	}
	//	else
	//	{
	//		postOrder(root);
	//	}
	//}

	//void postOrder(rbtNode<T>* tree) const
	//{
	//	if (tree != NULL) 
	//	{
	//		postOrder(tree->leftPointer);
	//		postOrder(tree->rightPointer);
	//		cout << tree->key << " ";
	//	}
	//}
};