// 9_1452810_郭梦晗.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>

//二叉排序树
using namespace std;

//树的节点信息
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
		cout << "1---建立二叉排序树" << endl;
		cout << "2---插入元素" << endl;
		cout << "3---查询元素" << endl;
		cout << "4---退出程序" << endl;
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
	//插入一个元素
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
	//打印树的信息
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
	//创建树
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
	//搜索元素
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