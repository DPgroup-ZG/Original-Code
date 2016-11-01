// 9_1452810_������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <string>

//����������
using namespace std;

//���Ľڵ���Ϣ
struct Node
{
	int value;
	Node *left;
	Node *right;
};

class SortTree
{
private:
	Node *root;
public:
	SortTree()
	{
		root = NULL;
	}
	void printMenu()
	{
		cout << "1---��������������" << endl;
		cout << "2---����Ԫ��" << endl;
		cout << "3---��ѯԪ��" << endl;
		cout << "4---�˳�����" << endl;
		cout << "=======================" << endl;

		while (1)
		{
			switch (getchoose())
			{
			case 1:
				createTree();
				break;
			case 2:
			{
					  int n = 0;

					  cout << "Please input key which inserted: ";
					  cin >> n;

					  Node *tmp = new Node();

					  tmp->value = n;
					  tmp->left = NULL;
					  tmp->right = NULL;

					  insertElement(tmp);
					  break;
			}

			case 3:
			{
					  int n = 0;

					  cout << "Please input key which searched: ";
					  cin >> n;
					  if (searchElement(root, n) == 0)
					  {
						  cout << n << " not exist!" << endl;
					  }
					  else
					  {
						  cout << "search success!" << endl;
					  }
					  break;
			}

			case 4:
				return;
			default:
				break;
			}
		}

	}

	int getchoose()
	{
		int t;

		cout << "Please select: ";
		cin >> t;
		return t;
	}
	//����һ��Ԫ��
	void insertElement(Node *newnode)
	{
		if (root == NULL)
		{
			root = newnode;
		}
		else
		{
			Node *ptr = root;
			while (1)
			{
				if (newnode->value < ptr->value)
				{
					if (ptr->left == NULL)
					{
						ptr->left = newnode;
						break;
					}
					else
					{
						ptr = ptr->left;
					}
				}
				else if (newnode->value > ptr->value)
				{
					if (ptr->right == NULL)
					{
						ptr->right = newnode;
						break;
					}
					else
					{
						ptr = ptr->right;
					}
				}
				else
				{
					cout << "The input key(" << newnode->value << ") iS have in!" << endl;
					delete newnode;
					break;
				}
			}
		}
		printTree(root);
		cout << endl;
	}
	//��ӡ������Ϣ
	void printTree(Node *r)
	{
		if (r == NULL)
		{
			return;
		}

		printTree(r->left);

		cout << r->value << "->";

		printTree(r->right);

	}
	//������
	void createTree()
	{
		int a[1000] = { 0 };

		cout << "Please input key to create Bsort_Tree:" << endl;

		for (int i = 0; i < 1000; i++)
		{
			cin >> a[i];

			if (a[i] == 0)
			{
				break;
			}
		}
		Node *tmp;
		for (int i = 0; i < 1000 && a[i] != 0; i++)
		{
			tmp = new Node();

			tmp->value = a[i];
			tmp->left = NULL;
			tmp->right = NULL;

			insertElement(tmp);
		}
		printTree(root);
		cout << endl;
	}
	//����Ԫ��
	int searchElement(Node *root, int value)
	{
		if (root == NULL)
		{
			return 0;
		}
		else if (root->value == value)
		{
			return 1;
		}
		else if (root->value > value)
		{
			return searchElement(root->left, value);
		}
		else
		{
			return searchElement(root->right, value);
		}

		return 0;
	}
};

int main()
{
	SortTree test;

	test.printMenu();
	return 0;
}