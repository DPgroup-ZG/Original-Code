// �����ҳ�洢����ʽģ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#define Bsize 4

using namespace std;

typedef struct BLOCK//����һ��������--���������
{
	int pagenum;//ҳ��
	int accessed;//�����ֶΣ���ֵ��ʾ���δ������

}BLOCK;

int pc;//�����������������¼ָ������
int n;//ȱҳ��������������¼ȱҳ�Ĵ���	
static int temp[320];//�����洢320�������

BLOCK block[Bsize]; //����һ��СΪ4�����������


void init();     //�����ʼ������
int findExist(int curpage);//������������Ƿ��и�ҳ��
int findSpace();//�����Ƿ��п��������
int findReplace();//����Ӧ���û���ҳ��
void display();//��ʾ
void suijishu();//����320�������,��ʾ���洢��temp[320]
void pagestring();//��ʾ���õ�ҳ�����
void OPT();//OPT�㷨
void LRU();// LRU�㷨
void FIFO();//FIFO�㷨


void init()
{
	for (int i = 0; i<Bsize; i++)
	{
		block[i].pagenum = -1;
		block[i].accessed = 0;
		pc = n = 0;
	}
}

int findExist(int curpage)
{

	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum == curpage)
			return i;//��⵽�ڴ����и�ҳ�棬����block�е�λ��
	}
	return -1;
}

int findSpace()
{
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum == -1)
			return i;//�ҵ����е�block������block�е�λ��
	}

	return -1;

}

int findReplace()
{
	int pos = 0;
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].accessed >block[pos].accessed)
			pos = i;//�ҵ�Ӧ���û�ҳ�棬����BLOCK��λ��
	}
	return pos;
}

void display()
{
	for (int i = 0; i<Bsize; i++)
	{
		if (block[i].pagenum != -1)
		{
			printf(" %02d", block[i].pagenum);
		}
	}
	cout << endl;
}

void suijishu()
{
	int flag = 0;
	cin >> pc;
	cout << "******����Ҫ�������320���������*******" << endl;
	for (int i = 0; i<320; i++)
	{
		temp[i] = pc;
		if (flag % 2 == 0) pc = ++pc % 320;
		if (flag == 1) pc = rand() % (pc - 1);
		if (flag == 3) pc = pc + 1 + (rand() % (320 - (pc + 1)));
		flag = ++flag % 4;
		printf(" %03d", temp[i]);
		if ((i + 1) % 10 == 0) cout << endl;
	}
}

void pagestring()
{
	for (int i = 0; i<320; i++)
	{
		printf(" %02d", temp[i] / 10);
		if ((i + 1) % 10 == 0) cout << endl;
	}

}

void OPT()
{
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		pc = temp[i];
		curpage = pc / 10;
		exist = findExist(curpage);
		if (exist == -1)
		{
			space = findSpace();
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
				n = n + 1;
			}
			else
			{
				for (int k = 0; k<Bsize; k++)
				{
					for (int j = i; j<320; j++)
					{
						if (block[k].pagenum != temp[j] / 10)
						{
							block[k].accessed = 1000;
						}//���������ã�����Ϊһ���ܴ���
						else
						{
							block[k].accessed = j;
							break;

						}
					}
				}
				position = findReplace();
				block[position].pagenum = curpage;
				display();
				n++;

			}
		}
	}
	cout << "ȱҳ����:" << n << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}

void LRU()
{
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		pc = temp[i];
		curpage = pc / 10;
		exist = findExist(curpage);
		if (exist == -1)
		{
			space = findSpace();
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
				n = n + 1;
			}
			else
			{
				position = findReplace();
				block[position].pagenum = curpage;
				display();
				n++;

			}
		}
		else block[exist].accessed = -1;//�ָ����ڵĲ��շ��ʹ���BLOCK��ҳ��accessedΪ-1
		for (int j = 0; j<4; j++)
		{
			block[j].accessed++;
		}

	}
	cout << "ȱҳ����:" << n << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}

void FIFO()
{
	int exist, space, position;
	int curpage;
	for (int i = 0; i<320; i++)
	{
		if (i % 100 == 0) getchar();
		pc = temp[i];
		curpage = pc / 10;

		exist = findExist(curpage);
		if (exist == -1)

		{
			space = findSpace();
			if (space != -1)
			{
				block[space].pagenum = curpage;
				display();
				n = n + 1;
			}
			else
			{
				position = findReplace();
				block[position].pagenum = curpage;
				display();
				n++;
				block[position].accessed--;
			}
		}
		for (int j = 0; j<Bsize; j++)
			block[j].accessed++;


	}
	cout << "ȱҳ����:" << n << endl;
	cout << "ȱҳ��:" << (n / 320.0) * 100 << "%" << endl;
}

void main()
{
	int  select;
	cout << "�������һ��ָ���(0~320)��";
	suijishu();
	cout << "*****��Ӧ�ĵ���ҳ�����*******" << endl;
	pagestring();
	do
	{
		cout << "****************************************" << endl;
		cout << "------1:OPT   2:LRU  3:FIFO  4:�˳�-----" << endl;
		cout << "****************************************" << endl;
		cout << "          ��ѡ��һ��ҳ���û��㷨:";
		cin >> select;
		cout << "****************************************" << endl;
		init();

		switch (select)
		{
		case 1:cout << "����û��㷨OPT:" << endl;
			cout << "*****************" << endl;
			OPT();
			break;
		case 2:cout << "������δʹ���û��㷨LRU:" << endl;
			cout << "**************************" << endl;
			LRU();
			break;
		case 3:cout << "�Ƚ��ȳ��û��㷨FIFO:" << endl;
			cout << "*********************" << endl;
			FIFO();
			break;

		default:;
		}

	} while (select != 4);
}//END



