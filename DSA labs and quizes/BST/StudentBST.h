#ifndef STUDENT_BST_H
#define STUDENT_BST_H


template<typename T>
struct BTNode
{
	T info;
	BTNode*left;
	BTNode*right;
	BTNode()
	{
		left = right = nullptr;
	}
	BTNode(T val)
	{
		info = val;
		left = right = nullptr;
	}

};

template<typename T>
class BST
{
	BTNode<T>*root;
	enum Degree { degZero, degOne, degTwo };

	Degree checkDegree(BTNode<T>* node)
	{
		if (node->left == nullptr&&node->right == nullptr)
		{
			return degZero;
		}
		else if (node->left != nullptr&&node->right != nullptr)
		{
			return degTwo;
		}
		else
		{
			return degOne;
		}
	}
	void LVR(BTNode<T>*node)   //  inorder
	{
		if (node->left)
		{
			LVR(node->left);
		}
		cout << node->info << ", ";

		if (node->right)
		{
			LVR(node->right);
		}
	}
public:
	BST()
	{
		root = nullptr;
	}
	void insert(T val)
	{
		if (search(val))
		{
			return;
		}


		if (root == nullptr)
		{
			root = new BTNode<T>(val);
			return;
		}
		else
		{
			BTNode<T>* p = root;
			while (p != nullptr)
			{
				if (p->info <= val)
				{
					if (p->right == nullptr)
					{

						p->right = new BTNode<T>(val);
						return;
					}
					else
					{
						p = p->right;
					}
				}
				else
				{
					if (p->left == nullptr)
					{
						p->left = new BTNode<T>(val);
						return;
					}
					else
					{
						p = p->left;
					}
				}
			}
		}

	}
	void remove(T val)
	{
		BTNode<T>* current = root;
		BTNode<T>* previous = root;
		bool leftTree = false;
		if (root == nullptr)
		{
			return;
		}
		else if (root->info == val && checkDegree(root) == degZero)
		{
			delete root;
			root = nullptr;
			return;
		}
		else if ((root->info == val && checkDegree(root) == degOne))
		{
			if (root->left != nullptr)
			{
				root = root->left;
				delete current;
			}
			else
			{
				root = root->right;
				delete current;
			}
			return;
		}
		while (current != nullptr)
		{
			if (current->info == val)
			{
				if (checkDegree(current) == degZero)
				{
					delete current;
					if (leftTree)
					{
						previous->left = nullptr;
					}
					else
					{
						previous->right = nullptr;
					}
					current = nullptr;

				}
				else if (checkDegree(current) == degOne)
				{
					if (current->left == nullptr)
					{
						if (leftTree)
						{
							previous->left = current->right;
							delete current;
							current = previous->left;
						}
						else
						{
							previous->right = current->right;
							delete current;
							current = previous->right;
						}
					}
					else
					{
						if (leftTree)
						{
							previous->left = current->left;
							delete current;
							current = previous->left;
						}
						else
						{
							previous->right = current->left;
							delete current;
							current = previous->right;
						}
					}

				}
				else
				{
					BTNode<T>* p = current->right;
					BTNode<T>* parent = current->right;


					while (p->left != nullptr)
					{
						parent = p;
						p = p->left;
					}
					if (p == current->right)
					{
						current->info = p->info;
						current->right = p->right;
						delete p;
					}
					else
					{
						current->info = p->info;
						delete p;
						parent->left = nullptr;
					}



				}
			}
			else
			{
				if (val < current->info)
				{
					previous = current;
					current = current->left;
					leftTree = true;
				}
				else
				{
					previous = current;
					current = current->right;
					leftTree = false;
				}
			}
		}

	}
	bool search(T val)
	{

		BTNode<T>* p = root;
		while (p != nullptr)
		{
			if (p->info == val)
			{
				return true;
			}
			else
			{
				if (val < p->info)
				{
					p = p->left;
				}
				else
				{
					p = p->right;
				}
			}
		}
		return false;
	}
	void displayAsLVR()
	{
		LVR(root);
	}
	~BST()
	{
		while (root != nullptr)
		{
			remove(root->info);
		}
	}
};

#endif


