#include<iostream>
using namespace std;
#include"IEditor.h"


CString IEditor::getFileName()
{
	return fileName;
}

void IEditor::setFileName(const CString & fn)
{
	fileName = fn;
}


IEditor::~IEditor()
{
	if (head == nullptr)
	{
		return;
	}
	DNode<CString>* x = head;
	while (x != nullptr)
	{
		DNode<CString>* p = x;
		x = x->next;
		delete p;
	}
	head = nullptr;
}



void IEditor::start()
{
	head = currentLineRef = nullptr;
	linesCount = 0;
	currentLineNumber = 1;
	DNode<CString> a;
	cout << currentLineNumber << ">";
	a.info.input();
	DNode<CString> *addAtLast = nullptr;

	while (a.info != "_E")
	{
		if (a.info[0] == '_')
		{

			char b = a.info[1];   //    command L E U D  etc
			switch (b)
			{
			case 'L':    // list_all
			{
				if (head != nullptr)
				{
					DNode<CString> *p = head;
					int a = 1;
					while (p != nullptr)
					{
						cout << a << ">";
						cout << p->info << "\n";
						p = p->next;
						a = a + 1;

					}
					//cout << endl;
				}

				currentLineNumber = linesCount + 1;
				break;
			}


			case 'U':               // Move_UP
			{
				if (a.info.getLength() == 2)
				{
					currentLineRef = currentLineRef->prev;
					currentLineNumber = currentLineNumber - 1;
				}
				else
				{
					int goToLine = a.info[3] - '0';
					for (int i = 0; i < goToLine; i++)
					{
						currentLineRef = currentLineRef->prev;
					}
					currentLineNumber = currentLineNumber - goToLine;
				}
				break;
			}

			case 'D':   //  move down
			{
				if (a.info.getLength() == 2)
				{
					currentLineRef = currentLineRef->next;
					currentLineNumber = currentLineNumber + 1;
				}
				else
				{
					int goToLine = a.info[3] - '0';
					for (int i = 0; i < goToLine; i++)
					{
						currentLineRef = currentLineRef->next;
					}
					currentLineNumber = currentLineNumber + goToLine;
				}
				break;
			}
			case 'A':        //  append
			{
				DNode<CString> b(currentLineRef->info);
				cout << currentLineNumber << ">";
				b.info.input();



				DNode<CString> *x = new DNode<CString>(b);
				x->next = currentLineRef->next;
				x->prev = currentLineRef;
				if (currentLineRef->next != nullptr)
				{
					x->next->prev = x;
				}
				x->prev->next = x;

				currentLineRef = x;
				linesCount = linesCount + 1;
				currentLineNumber = currentLineNumber + 1;

				break;

			}
			case 'M':     //  modify
			{


				CString b;
				cout << currentLineNumber - 1 << ">";
				b.input();
				currentLineRef->info = b;
				break;
			}
			case 'R':    //  remove
			{
				// do nothing in my case 
			}

			}

		}
		else              //    add the node in currentLineRef 
		{

			if (head == nullptr)
			{
				head = new DNode<CString>(a);
				currentLineRef = head;
				linesCount = linesCount + 1;
				currentLineNumber = currentLineNumber + 1;
			}
			else
			{
				DNode<CString> *x = new DNode<CString>(a);
				x->next = currentLineRef->next;
				x->prev = currentLineRef;
				if (currentLineRef->next != nullptr)
				{
					x->next->prev = x;
				}
				currentLineRef->next = x;

				currentLineRef = x;
				linesCount = linesCount + 1;
				currentLineNumber = currentLineNumber + 1;
			}
		}

		a.info.~CString();
		cout << currentLineNumber << ">";
		a.info.input();

	}





}
