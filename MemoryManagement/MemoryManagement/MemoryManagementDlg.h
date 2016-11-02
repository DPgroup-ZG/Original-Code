
// MemoryManagementDlg.h : 头文件
//

#pragma once


//内存中作业的分配结构
typedef struct Node
{
	Node *pre;            //前趋结点
	Node *next;           //后继结点	
	int size;	          //分区的内存空间大小
	int address;	      //分区首地址
	int workNo;		      //该分区分配给的作业编号
};

class Memory
{
public:

	Memory(){TotalSize = 0;}//初始化虚拟空间为0
	~Memory(){Free();}	//释放链表结构
	
	BOOL FirstFit(int workNo, int size);	//首次适应算法
	BOOL BestFit(int workNo, int size);	    //最佳适应算法
	BOOL FreeMemory(int workNo);	        //回收空间算法
	void AllocateTotalSize(int tsize);	    //设置内存空间总大小
	Node* GetPartitionList(){ return PartitionList; }  //获取分区链表
	void Free();	                        //释放链表全部内存

private:
	int TotalSize;        //内存空间的总大小
	Node* PartitionList;  //分区链表
};


// CMemoryManagementDlg 对话框
class CMemoryManagementDlg : public CDialogEx
{
	// 构造
public:
	CMemoryManagementDlg(CWnd* pParent = NULL);	//标准构造函数
	// 对话框数据
	enum { IDD = IDD_MEMORYMANAGEMENT_DIALOG };

	int	workNum;							//当前要申请内存空间的作业号
	int workSize;							//当前要申请的内存空间大小
	int	freeNum;							//当前要释放内存空间的作业号
	CString displayText;					//分区信息展示区
	BOOL FirstFit_or_not;					//是否首次适应算法
	BOOL BestFit_or_not;					//是否最佳适应算法

	afx_msg void OnBnClickedRadio1();//首次适应算法按钮
	afx_msg void OnBnClickedRadio2();//最佳适应算法按钮
	afx_msg void OnBnClickedButton1();//确认申请空间按钮
	afx_msg void OnBnClickedButton2();//确认释放空间按钮
	afx_msg void OnBnClickedButton3();//开始自动演示按钮
	afx_msg void OnEnChangeEdit1();//申请作业号
	afx_msg void OnEnChangeEdit2();//申请空间大小
	afx_msg void OnEnChangeEdit3();//释放作业号
	afx_msg void OnEnChangeEdit4();//展示区

private:
	void Display();	//显示当前分区信息
	void AllocateMemory(int workNo, int size);//分配内存
	void FreeMemory(int workNo);//释放内存

	int Step;//记录自动演示的演示步骤
	Memory Mem;//实现内存动态分区分配的类


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
