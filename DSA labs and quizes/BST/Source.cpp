#include<iostream>
using namespace std;

#include"StudentBST.h"
#include<string>

class StudentBST;
class StudentNode
{
	friend class StudentBST;
private:
	int rollNo; // Studentís roll number (must be unique)
	string name; // Studentís name
	double cgpa; // Studentís CGPA
	StudentNode *left; // Pointer to the left subtree of a node
	StudentNode *right; // Pointer to the right subtree of a node

public:
	StudentNode()
	{
		left = right = nullptr;
	}
	StudentNode(int r, string n, double c)
	{
		rollNo = r;
		name = n;
		cgpa = c;

		left = right = nullptr;
	}

};

class StudentBST {
private:
	StudentNode *root; // Pointer to the root node of the BST

	

	int checkDegree(StudentNode* node)
	{
		if (node->left == nullptr  &&  node->right == nullptr)
		{
			return 0;
		}
		else if (node->left != nullptr&&node->right != nullptr)
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}


	//  Task # 2
	void inOrder(StudentNode* s)
	{
		if (root == nullptr)
		{
			return;
		}
		if (s->left)
		{
			inOrder(s->left);
		}

		
		cout << "Student roll number:   " << s->rollNo << "\n";
		cout << "Student name:   " << s->name << "\n";
		cout << "Student cgpa:   " << s->cgpa << "\n\n";

		if (s->right)
		{
			inOrder(s->right);
		}
	}

	
	bool searchIfAlreadyExist(int rn)
	{

		StudentNode* p = root;
		while (p != nullptr)
		{
			if (p->rollNo == rn)
			{
				return true;
			}
			else
			{
				if (rn < p->rollNo)
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

	// Task # 3
	void destroy(StudentNode* s)
	{
		StudentNode* current = root;
		StudentNode* previous = root;
		bool leftTree = false;
		if (root == nullptr)
		{
			return;
		}
		else if (root->rollNo == s->rollNo && checkDegree(root) == 0)
		{
			delete root;
			root = nullptr;
			return;
		}
		else if ((root->rollNo == s->rollNo && checkDegree(root) == 1))
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
			if (current->rollNo == s->rollNo)
			{
				if (checkDegree(current) == 0)
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
				else if (checkDegree(current) == 1)
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
					StudentNode* p = current->right;
					StudentNode* parent = current->right;


					while (p->left != nullptr)
					{
						parent = p;
						p = p->left;
					}
					if (p == current->right)
					{
						current->rollNo = p->rollNo;
						current->right = p->right;
						delete p;
					}
					else
					{
						current->rollNo = p->rollNo;
						delete p;
						parent->left = nullptr;
					}



				}
			}
			else
			{
				if (s->rollNo < current->rollNo)
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

public:
	StudentBST() // Default constructor
	{
		root = nullptr;
	}


	//Task # 1
	bool insert(int rn, string n, double c)
	{
		if (searchIfAlreadyExist(rn))     //   search if node already exist
		{
			return false;
		}

		if (root == nullptr)               
		{
			root = new StudentNode(rn,n,c);
			return  true;
		}

		else
		{
			StudentNode* p = root;
			while (p != nullptr)
			{
				if (p->rollNo <= rn)
				{
					if (p->right == nullptr)
					{

						p->right = new StudentNode(rn, n, c);
						return  true;
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
						p->left = new StudentNode(rn, n, c);
						return  true;
					}
					else
					{
						p = p->left;
					}
				}
			}
		}

	}

	bool search(int rn)
	{

		StudentNode* p = root;
		while (p != nullptr)
		{
			if (p->rollNo == rn)
			{
				cout << "\nStudent roll number: " << p->rollNo << "\n";
				cout << "Student name: " << p->name << "\n";
				cout << "Student cgpa: " << p->cgpa << "\n\n";
				return true;
			}
			else
			{
				if (rn < p->rollNo)
				{
					p = p->left;
				}
				else
				{
					p = p->right;
				}
			}
		}
		cout << "\nStudent does not exist";
		return false;
	}


	//Task # 2
	void inOredre()
	{
		inOrder(root);
	}

	//Task # 3
	~StudentBST()
	{
		while (root != nullptr)
		{
			destroy(root);
		}
	}


};



 
int main()                     // menu-based driver function 
{
	StudentBST obj;
	int choice=0;

	while (choice != 4)
	{
		cout << "\n\n";
		cout << "1. Insert a new student\n";
		cout << "2. Search for a student\n";
		cout << "3. See the list of all students(sorted)\n";
		cout << "4. Quit\n";
		cout << "Enter your choice :";
		cin >> choice;

		if (choice == 1)
		{
			int roll;
			string name;
			double cgpa;
			cout << "\nEnter Student roll number:";
			cin >> roll;
			cin.ignore();
			cout << "Enter Student name:";
			getline(cin, name);
			cout << "Enter Student cgpa:";
			cin >> cgpa;
			
			obj.insert(roll, name, cgpa);

		}
		else if (choice ==2)
		{
			int searchRoll;
			cout << "Enter Student roll number:";
			cin >> searchRoll;
			obj.search(searchRoll);
		}
		else if (choice == 3)
		{
			cout << "\nlist of all students\n\n";
			obj.inOredre();

		}
		//   in case of choice 4 while loop terminate and program ends
	}
	
	cout << "\nProgram Quit";

		
	
		
		




	return 0;
}