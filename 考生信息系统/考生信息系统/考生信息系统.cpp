// ������Ϣϵͳ.cpp : �������̨Ӧ�ó������ڵ㡣
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
	bool IsEmpty(Exam& e);               //�ж�ѭ�������Ƿ�Ϊ��
	void makeEmpty(Exam& e);             //�������
	void Create(Exam& e);                //����������Ϣϵͳ
	bool Insert(Exam& e);                //����
	bool Remove(Exam& e);                //ɾ��
	bool Search(Exam& e);                //��ѯ
	bool Modify(Exam& e);                //�޸�
	void Output(Exam& e);                //���
	bool Statistics(Exam& e);            //ͳ��

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


//������������ϵͳ
void Exam::Create(Exam& e)
{
	cout << "�����뿼������:";
	int n;
	cin >> n;
	if (n <= 0)
	{
		cout << "���������뿼������:";
		cin >> n;
	}

	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
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

//����������
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

//�����¿���
bool Exam::Insert(Exam& e)
{
	cout << "��������Ҫ����Ŀ�����λ��:";
	int n;
	cin >> n;
	LinkNode *p0;
	while ((n <= 0) || (n > (e.length(e) + 1)))
	{
		cout << "�������λ�ò�����,���������룺";
		cin >> n;
	}

	cout << "����������Ҫ����Ŀ����Ŀ���,����,�Ա�,���估�������!" << endl;
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

//ɾ��ĳһ����
bool Exam::Remove(Exam& e)
{
	cout << "������Ҫɾ���Ŀ����Ŀ���:";
	int num0;
	cin >> num0;
	LinkNode *p = first;
	LinkNode *current = first;

	while ((current->num != num0) && current != NULL)
	{
		current = current->link;
		if (p->link != current)
		{
			p = p->link;    //ʹp->link==current
		}
	}
	if (current == NULL)  //Ҫɾ���Ŀ��Ų�����
	{
		cout << "��Ҫɾ���Ŀ��Ų�����!" << endl;
	}
	else if (current == first)    //Ҫɾ���Ŀ�������
	{
		e.first = p->link;

		cout << "��ɾ���Ŀ�����Ϣ��:";
		cout << left;
		cout << setw(10) << current->num;
		cout << setw(10) << current->name;
		cout << setw(10) << current->sex;
		cout << setw(10) << current->age;
		cout << setw(10) << current->category;
		cout << endl;
		delete current;
	}

	else if (current->link == NULL)    //Ҫɾ���Ŀ�����β
	{
		p->link = NULL;

		cout << "��ɾ���Ŀ�����Ϣ��:";
		cout << left;
		cout << setw(10) << current->num;
		cout << setw(10) << current->name;
		cout << setw(10) << current->sex;
		cout << setw(10) << current->age;
		cout << setw(10) << current->category;
		cout << endl;

		delete current;
	}
	else          //Ҫɾ���Ŀ������м�
	{
		p->link = current->link;

		cout << "��ɾ���Ŀ�����Ϣ��:";
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

//��ѧ�Ų���ĳһ������Ϣ
bool Exam::Search(Exam& e)
{
	cout << "������Ҫ���ҵĿ����Ŀ���:";
	int num0;
	cin >> num0;
	LinkNode *current = first;
	while (current)
	{
		if (current->num == num0)
		{
			cout << "�����ҵĿ�����Ϣ�ǣ�";
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
		cout << "�������ҵ�ѧ�Ų����ڣ����������룡" << endl;
		e.Search(e);
	}
	return true;
}

//�޸�ĳһ������Ϣ
bool Exam::Modify(Exam& e)
{
	cout << "������Ҫ�޸ĵĿ����Ŀ���:";
	int num0;
	cin >> num0;
	LinkNode *current = first;
	int arrangement = 1;   //�����ƿ��ء�
	while (arrangement)
	{
		if (current->num == num0)
		{
			cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
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
		cout << "����Ҫ�޸ĵ�ѧ�Ų����ڣ�" << endl;
	}
	return true;
}

//���ȫ��������Ϣ
void Exam::Output(Exam& e)
{
	for (int m = 0; m < 32; m++)
	{
		cout << "*";
	}
	cout << " ȫ��������Ϣ ";
	for (int m = 0; m < 33; m++)
	{
		cout << "*";
	}
	cout << endl;
	LinkNode *current;
	cout << left;
	cout << setw(15) << "����";
	cout << setw(15) << "����";
	cout << setw(15) << "�Ա�";
	cout << setw(15) << "����";
	cout << setw(15) << "��������";
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

//ͳ����Ϣ
bool Exam::Statistics(Exam& e)
{
	cout << "����" << e.length(e) << "���˱���������������£�" << endl;
	e.Output(e);
	cout << "��������Ҫͳ�Ƶı���������ƣ�";
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
	cout << "����" << cate << "�Ŀ�����" << total << "��" << endl;
	return true;
}

int main()
{
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	Exam exam;
	exam.Create(exam);
	exam.Output(exam);
	while (1)
	{
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������";
		cout << "��ѡ����Ҫ���еĲ���:";
		int n;
		cin >> n;
		switch (n)
		{
		case 0:
		{
			cout << "ллʹ�ÿ��Ա���ϵͳ��" << endl;
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
			cout << "�ò��������ڣ����������룡" << endl;
			break;
		}
		}
	}
	system("pause");
	return 0;
}

