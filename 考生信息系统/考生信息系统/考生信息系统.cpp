// 考生信息系统.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iomanip"
#include "iostream"
#include "string"


using namespace std;

class Exam;

class LinkNode
{
	friend class Exam;
public:
	LinkNode();

	int num;
	int age;
	string name;
	string sex;
	string category;

	LinkNode *link;
};
class Exam
{
public:
	Exam();
	int length(Exam& e);
	bool IsEmpty(Exam& e);               //判断循环链表是否为空
	void makeEmpty(Exam& e);             //清空链表
	void Create(Exam& e);                //建立考生信息系统
	bool Insert(Exam& e);                //插入
	bool Remove(Exam& e);                //删除
	bool Search(Exam& e);                //查询
	bool Modify(Exam& e);                //修改
	void Output(Exam& e);                //输出
	bool Statistics(Exam& e);            //统计

private:
	LinkNode *first;
};
LinkNode::LinkNode()
{
	num = 0;
	age = 0;
	name = "";
	sex = "";
	category = "";
	link = NULL;
}

Exam::Exam()
{
	first = NULL;
}

bool Exam::IsEmpty(Exam& e)
{
	int l = length(e);
	return l == 0 ? true : false;
}

void Exam::makeEmpty(Exam& e)
{
	LinkNode *p;
	while (!IsEmpty(e))
	{
		p = first->link;
		first->link = p->link;
		delete p;
	}
}


//创建考生报名系统
void Exam::Create(Exam& e)
{
	cout << "请输入考生人数:";
	int n;
	cin >> n;
	if (n <= 0)
	{
		cout << "请重新输入考生人数:";
		cin >> n;
	}

	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	LinkNode *p1, *p2;
	p2 = new LinkNode;

	for (int i = 0; i < n; i++)
	{
		p1 = new LinkNode;
		cin >> p1->num >> p1->name >> p1->sex >> p1->age >> p1->category;
		if (i == 0)
		{
			e.first = p1;
			p2 = e.first;
		}
		else
		{
			p2->link = p1;
			p2 = p1;
		}
	}
	p2->link = NULL;
}

//返回链表长度
int Exam::length(Exam& e)
{
	LinkNode *p;
	p = e.first;
	int count = 1;
	while (p->link != NULL)
	{
		count++;
		p = p->link;
	}
	return count;
}

//插入新考生
bool Exam::Insert(Exam& e)
{
	cout << "请输入你要插入的考生的位置:";
	int n;
	cin >> n;
	LinkNode *p0;
	while ((n <= 0) || (n > (e.length(e) + 1)))
	{
		cout << "您输入的位置不存在,请重新输入：";
		cin >> n;
	}

	cout << "请依次输入要插入的考生的考号,姓名,性别,年龄及报考类别!" << endl;
	p0 = new LinkNode;
	cin >> p0->num >> p0->name >> p0->sex >> p0->age >> p0->category;

	if (n == 1)
	{
		p0->link = e.first;
		e.first = p0;
	}
	else if (n == e.length(e) + 1)
	{
		LinkNode *current;
		current = e.first;
		int count = 1;
		while (current->link != NULL)
		{
			count++;
			current = current->link;
		}
		current->link = p0;
		p0->link = NULL;
	}
	else
	{
		LinkNode *current;
		current = e.first;
		int count = 1;
		while (count != (n - 1))
		{
			count++;
			current = current->link;
		}
		p0->link = current->link;
		current->link = p0;
	}

	e.Output(e);
	return true;
}

//删除某一考生
bool Exam::Remove(Exam& e)
{
	cout << "请输入要删除的考生的考号:";
	int num0;
	cin >> num0;
	LinkNode *p = first;
	LinkNode *current = first;

	while ((current->num != num0) && current != NULL)
	{
		current = current->link;
		if (p->link != current)
		{
			p = p->link;    //使p->link==current
		}
	}
	if (current == NULL)  //要删除的考号不存在
	{
		cout << "您要删除的考号不存在!" << endl;
	}
	else if (current == first)    //要删除的考号在首
	{
		e.first = p->link;

		cout << "你删除的考生信息是:";
		cout << left;
		cout << setw(10) << current->num;
		cout << setw(10) << current->name;
		cout << setw(10) << current->sex;
		cout << setw(10) << current->age;
		cout << setw(10) << current->category;
		cout << endl;
		delete current;
	}

	else if (current->link == NULL)    //要删除的考号在尾
	{
		p->link = NULL;

		cout << "你删除的考生信息是:";
		cout << left;
		cout << setw(10) << current->num;
		cout << setw(10) << current->name;
		cout << setw(10) << current->sex;
		cout << setw(10) << current->age;
		cout << setw(10) << current->category;
		cout << endl;

		delete current;
	}
	else          //要删除的考号在中间
	{
		p->link = current->link;

		cout << "你删除的考生信息是:";
		cout << left;
		cout << setw(10) << current->num;
		cout << setw(10) << current->name;
		cout << setw(10) << current->sex;
		cout << setw(10) << current->age;
		cout << setw(10) << current->category;
		cout << endl;

		delete current;
	}
	e.Output(e);
	return true;
}

//按学号查找某一考生信息
bool Exam::Search(Exam& e)
{
	cout << "请输入要查找的考生的考号:";
	int num0;
	cin >> num0;
	LinkNode *current = first;
	while (current)
	{
		if (current->num == num0)
		{
			cout << "您查找的考生信息是：";
			cout << left;
			cout << setw(10) << current->num;
			cout << setw(10) << current->name;
			cout << setw(10) << current->sex;
			cout << setw(10) << current->age;
			cout << setw(10) << current->category;
			cout << endl;
			break;
		}
		else
		{
			current = current->link;
		}
	}
	if (current == NULL)
	{
		cout << "您所查找的学号不存在，请重新输入！" << endl;
		e.Search(e);
	}
	return true;
}

//修改某一考生信息
bool Exam::Modify(Exam& e)
{
	cout << "请输入要修改的考生的考号:";
	int num0;
	cin >> num0;
	LinkNode *current = first;
	int arrangement = 1;   //“控制开关”
	while (arrangement)
	{
		if (current->num == num0)
		{
			cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
			cin >> current->num >> current->name >> current->sex >> current->age >> current->category;
			e.Output(e);
			arrangement = 0;
		}
		else
		{
			current = current->link;
		}
	}
	if (current == NULL)
	{
		cout << "您所要修改的学号不存在！" << endl;
	}
	return true;
}

//输出全部考生信息
void Exam::Output(Exam& e)
{
	for (int m = 0; m < 32; m++)
	{
		cout << "*";
	}
	cout << " 全部考生信息 ";
	for (int m = 0; m < 33; m++)
	{
		cout << "*";
	}
	cout << endl;
	LinkNode *current;
	cout << left;
	cout << setw(15) << "考号";
	cout << setw(15) << "姓名";
	cout << setw(15) << "性别";
	cout << setw(15) << "年龄";
	cout << setw(15) << "报考类型";
	cout << endl;
	int i;
	for (i = 0, current = e.first; i < e.length(e); i++, current = current->link)
	{
		cout << left;
		cout << setw(15) << current->num;
		cout << setw(15) << current->name;
		cout << setw(15) << current->sex;
		cout << setw(15) << current->age;
		cout << setw(15) << current->category;
		cout << endl;
	}
	for (int m = 0; m < 79; m++)
	{
		cout << "*";
	}
	cout << endl;
}

//统计信息
bool Exam::Statistics(Exam& e)
{
	cout << "共有" << e.length(e) << "个人报名，具体情况如下：" << endl;
	e.Output(e);
	cout << "请输入需要统计的报考类别名称：";
	string cate;
	cin >> cate;
	LinkNode *current = first;
	int total = 0;
	while (current)
	{
		if (current->category == cate)
		{
			total++;
			current = current->link;
		}
		else
		{
			current = current->link;
		}
	}
	cout << "报考" << cate << "的考生共" << total << "人" << endl;
	return true;
}

int main()
{
	cout << "首先请建立考生信息系统！" << endl;
	Exam exam;
	exam.Create(exam);
	exam.Output(exam);
	while (1)
	{
		cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）";
		cout << "请选择您要进行的操作:";
		int n;
		cin >> n;
		switch (n)
		{
		case 0:
		{
			cout << "谢谢使用考试报名系统！" << endl;
			system("pause");
			return 0;
		}
		case 1:
		{
			exam.Insert(exam);
			break;
		}
		case 2:
		{
			exam.Remove(exam);
			break;
		}
		case 3:
		{
			exam.Search(exam);
			break;
		}
		case 4:
		{
			exam.Modify(exam);
			break;
		}
		case 5:
		{
			exam.Statistics(exam);
			break;
		}
		default:
		{
			cout << "该操作不存在，请重新输入！" << endl;
			break;
		}
		}
	}
	system("pause");
	return 0;
}

