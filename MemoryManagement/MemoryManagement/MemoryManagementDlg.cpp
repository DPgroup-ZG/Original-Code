
// MemoryManagementDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MemoryManagement.h"
#include "MemoryManagementDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{


	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


/* ******************************CMemoryManagementDlg 对话框********* 开始 ******************* */



CMemoryManagementDlg::CMemoryManagementDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMemoryManagementDlg::IDD, pParent)
{
	// 初始化各项变量值
	//{{AFX_DATA_INIT(CAllocMemoryDlg)
	workNum = 0;
	workSize = 0;
	freeNum = 0;
	displayText = "";
	//}}AFX_DATA_INIT
	FirstFit_or_not = TRUE; //未选择的情况下，默认是首次适应算法
	BestFit_or_not = FALSE;
	Step = 0;
	Mem.AllocateTotalSize(640);	// 分配640KB的内存空间

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//通过UpdateData函数调用此函数，完成数据刷新
void CMemoryManagementDlg::DoDataExchange(CDataExchange* pDX)  
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT2, workSize);
	DDV_MinMaxLong(pDX, workSize, 0, 640);
	DDX_Text(pDX, IDC_EDIT3, freeNum);
	DDX_Text(pDX, IDC_EDIT1, workNum);
	DDX_Text(pDX, IDC_EDIT4, displayText);

}

BEGIN_MESSAGE_MAP(CMemoryManagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_RADIO1, &CMemoryManagementDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CMemoryManagementDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMemoryManagementDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMemoryManagementDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CMemoryManagementDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CMemoryManagementDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMemoryManagementDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMemoryManagementDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMemoryManagementDlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CMemoryManagementDlg 消息处理程序

BOOL CMemoryManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//把首次适应算法的按钮设为默认按下状态

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMemoryManagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMemoryManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMemoryManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//首次适应算法按钮
void CMemoryManagementDlg::OnBnClickedRadio1()
{
	FirstFit_or_not = TRUE;
	BestFit_or_not = FALSE;
}

//最佳适应算法按钮
void CMemoryManagementDlg::OnBnClickedRadio2()
{
	FirstFit_or_not = FALSE;
	BestFit_or_not = TRUE;
}

//确认申请空间按钮
void CMemoryManagementDlg::OnBnClickedButton1()
{
	UpdateData();	//根据控件值更新变量
	if (workSize <= 640)
	{
		AllocateMemory(workNum, workSize);
	}
	else
	{
		AfxMessageBox("申请内存失败!");
	}
}

//确认释放空间按钮
void CMemoryManagementDlg::OnBnClickedButton2()
{
	UpdateData();//根据控件值更新变量
	FreeMemory(freeNum);
}

//开始自动演示按钮
void CMemoryManagementDlg::OnBnClickedButton3()
{
	switch (Step)
	{
	case 0:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(1, 130);
			  break;
	}
	case 1:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(2, 60);
			  break;
	}
	case 2:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(3, 100);
			  break;
	}
	case 3:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  FreeMemory(2);
			  break;
	}
	case 4:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(4, 200);
			  break;
	}
	case 5:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  FreeMemory(3);
			  break;
	}
	case 6:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  FreeMemory(1);
			  break;
	}
	case 7:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(5, 140);
			  break;
	}
	case 8:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(6, 60);
			  break;
	}
	case 9:
	{
			  SetDlgItemText(IDC_BUTTON4, "下一步");
			  AllocateMemory(7, 50);
			  break;
	}
	case 10:
	{
			   SetDlgItemText(IDC_BUTTON4, "开始");
			   FreeMemory(6);

			   //演示结束释放内存并重新分配
			   Mem.Free();
			   Mem.AllocateTotalSize(640);
			   break;
	}
	default:
	{
			   break;
	}
	}
	Step = (Step + 1) % 11;

}

void CMemoryManagementDlg::OnEnChangeEdit1()//申请作业号
{}
void CMemoryManagementDlg::OnEnChangeEdit2()//申请空间大小
{}
void CMemoryManagementDlg::OnEnChangeEdit3()//释放作业号
{}
void CMemoryManagementDlg::OnEnChangeEdit4()//展示区
{
}

//给某个作业分配内存并显示在展示区中
void CMemoryManagementDlg::AllocateMemory(int workNo, int size)
{
	if (FirstFit_or_not==TRUE)
	{	
		Mem.FirstFit(workNo, size);// 首次适应算法
	}
	else if (BestFit_or_not==TRUE)
	{
		Mem.BestFit(workNo, size);// 最佳适应算法
	}
	Display();
}

//释放某个作业的内存
void CMemoryManagementDlg::FreeMemory(int workNo)
{
	Mem.FreeMemory(workNo);
	Display();
}

//展示
void CMemoryManagementDlg::Display() 
{
	Node* p = Mem.GetPartitionList();//p为头结点，无具体信息
	displayText = "当前空闲分区链情况：\r\n";
	displayText = displayText + "始末地址(KB)\t分区大小(KB)\t状态\t作业名\r\n";
	Node* current = p->next;//p->next才是第一个有具体信息的结点
	while (current != NULL)
	{
		// 作业号为0的分区，表明是空闲分区
		if (current->workNo == 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t空闲\t--\r\n", current->address, current->size + current->address, current->size);
			displayText = displayText + str;
		}
		// 作业号非0的分区，是非空闲分区
		if (current->workNo != 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t已用\t作业%d\r\n", current->address, current->size + current->address, current->size, current->workNo);
			displayText = displayText + str;
		}
		current = current->next;
	}
	UpdateData(FALSE);				// 根据变量值更新控件
}


/* ****************************** CMemoryManagementDlg 对话框 ************ 结束 ********************** */

/* *************************************** Memory 内存 ****************** 开始 *********************** */


// 设置内存空间总大小（即TotalSize）
void Memory::AllocateTotalSize(int tsize)	
{
	TotalSize = tsize;
	// 建立一个带头结点的分区链表
	PartitionList = new Node;//分区链表的头结点
	PartitionList->next = NULL;
	PartitionList->pre = NULL;

	// 生成一个新结点记录当前的空闲分区信息
	Node* p = new Node;
	p->size = TotalSize;			//新结点的大小设为内存的总大小		
	p->address = 0;					//新结点的起始地址设为0
	p->workNo = 0;					//新结点的任务号设为0，0表示该分区是空闲分区
	p->next = PartitionList->next;	//后继结点设为NULL
	p->pre = PartitionList;			//前趋结点指向头结点
	PartitionList->next = p;	    //头结点的后继结点指向新结点
}

//首次适应算法
BOOL Memory::FirstFit(int workNo, int size)
{
	Node* target = PartitionList->next;	//target指针指向即将被拆分的分区
	Node* current = NULL;

	//查找第一个满足要求的空闲分区
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	if (target != NULL)
	{		
		Node* p = new Node;//新建p结点，指向即将分配给作业的分区结点                          
		p->size = size;//从可用分区中划出size大小的内存空间
		p->address = target->address;//指示该结点的地址为当前空闲分区的起始地址
		target->size = target->size - size;//当前空闲分区的大小减少size
		target->address = target->address + size;//当前空闲分区的起始地址往后偏移size

		//将新分配的结点插向空闲结点的前面
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("申请内存失败!");
		return FALSE;
	}
}

//最佳适应算法
BOOL Memory::BestFit(int workNo, int size)	
{
	Node* target = PartitionList->next;	//target指向即将被拆分的分区
	Node* current = NULL;

	//查找第一个空闲分区
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	//查找出所有符合要求结点中内存最小的空闲分区
	while (current != NULL)
	{
		if (size< current->size && current->size< target->size && current->workNo == 0)
		{
			target = current;
		}
		current = current->next;
	}

	if (target != NULL)  //下面这段代码与首次适应算法一样
	{
		
		Node* p = new Node;//新建p结点，指示即将分配给作业的分区结点                   
		p->size = size;//从可用分区中划出size大小的内存空间 	
		p->address = target->address;//指示该结点的地址为当前空闲分区的起始地址		
		target->size = target->size - size;//当前空闲分区的大小减少size		
		target->address = target->address + size;//当前空闲分区的起始地址往后偏移size

		// 将新分配的结点插向空闲结点的前面
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("申请内存失败!");
		return FALSE;
	}
}

//回收空间算法
BOOL Memory::FreeMemory(int workNo)	
{
	Node* current;
	//找到要释放空间的作业
	current = PartitionList->next;
	while (current != NULL && current->workNo != workNo)
	{
		current = current->next;
	}

	//释放该作业的内存
	if (current)
	{
		// 情况1：当需要释放内存的分区前后都是空闲分区时，将这三个分区合并
		if (current->pre != PartitionList && current->pre->workNo == 0)	
		{
			if (current->next != NULL && current->next->workNo == 0)
			{
				// 将释放内存的分区与其后的空闲分区合并
				current->size = current->size + current->next->size;
				current->workNo = 0;
				if (current->next->next != NULL)
				{
					current->next->next->pre = current;
				}
				current->next = current->next->next;
			}

			// 将刚才合并后的分区，与其前面的空闲分区再次合并，实现三个分区合并
			current->pre->size = current->pre->size + current->size;
			current->pre->next = current->next;
			if (current->next != NULL)
			{
				current->next->pre = current->pre;
			}
		}
		// 情况2：如果其前面分区是非空闲分区，而其后的分区是空闲分区，则将其与后面的分区合并
		else if (current->pre->workNo != 0 && current->next != NULL && current->next->workNo == 0)
		{
			current->workNo = 0;
			current->size = current->size + current->next->size;
			if (current->next->next != NULL)
			{
				current->next->next->pre = current;
			}
			current->next = current->next->next;
		}
		// 情况3：其前后没有空闲分区，则仅释放本身的内存
		else
		{
			current->workNo = 0;
		}
		return TRUE;
	}
	else
	{
		AfxMessageBox("释放内存失败!");
		return FALSE;
	}
}

//释放链表全部内存
void Memory::Free()	
{
	Node* current = PartitionList->next;
	while (current != NULL)
	{
		Node* p = current;
		current = current->next;
		delete p;
	}
	delete PartitionList;
}

/* *************************************** Memory 内存 ******************* 结束 *********************** */