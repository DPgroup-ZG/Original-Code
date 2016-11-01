
// MemoryManagementDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MemoryManagement.h"
#include "MemoryManagementDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


/* ******************************CMemoryManagementDlg �Ի���********* ��ʼ ******************* */



CMemoryManagementDlg::CMemoryManagementDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CMemoryManagementDlg::IDD, pParent)
{
	// ��ʼ���������ֵ
	//{{AFX_DATA_INIT(CAllocMemoryDlg)
	workNum = 0;
	workSize = 0;
	freeNum = 0;
	displayText = "";
	//}}AFX_DATA_INIT
	FirstFit_or_not = TRUE; //δѡ�������£�Ĭ�����״���Ӧ�㷨
	BestFit_or_not = FALSE;
	Step = 0;
	Mem.AllocateTotalSize(640);	// ����640KB���ڴ�ռ�

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

//ͨ��UpdateData�������ô˺������������ˢ��
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


// CMemoryManagementDlg ��Ϣ�������

BOOL CMemoryManagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	((CButton *)GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);//���״���Ӧ�㷨�İ�ť��ΪĬ�ϰ���״̬

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMemoryManagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMemoryManagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�״���Ӧ�㷨��ť
void CMemoryManagementDlg::OnBnClickedRadio1()
{
	FirstFit_or_not = TRUE;
	BestFit_or_not = FALSE;
}

//�����Ӧ�㷨��ť
void CMemoryManagementDlg::OnBnClickedRadio2()
{
	FirstFit_or_not = FALSE;
	BestFit_or_not = TRUE;
}

//ȷ������ռ䰴ť
void CMemoryManagementDlg::OnBnClickedButton1()
{
	UpdateData();	//���ݿؼ�ֵ���±���
	if (workSize <= 640)
	{
		AllocateMemory(workNum, workSize);
	}
	else
	{
		AfxMessageBox("�����ڴ�ʧ��!");
	}
}

//ȷ���ͷſռ䰴ť
void CMemoryManagementDlg::OnBnClickedButton2()
{
	UpdateData();//���ݿؼ�ֵ���±���
	FreeMemory(freeNum);
}

//��ʼ�Զ���ʾ��ť
void CMemoryManagementDlg::OnBnClickedButton3()
{
	switch (Step)
	{
	case 0:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(1, 130);
			  break;
	}
	case 1:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(2, 60);
			  break;
	}
	case 2:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(3, 100);
			  break;
	}
	case 3:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  FreeMemory(2);
			  break;
	}
	case 4:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(4, 200);
			  break;
	}
	case 5:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  FreeMemory(3);
			  break;
	}
	case 6:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  FreeMemory(1);
			  break;
	}
	case 7:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(5, 140);
			  break;
	}
	case 8:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(6, 60);
			  break;
	}
	case 9:
	{
			  SetDlgItemText(IDC_BUTTON4, "��һ��");
			  AllocateMemory(7, 50);
			  break;
	}
	case 10:
	{
			   SetDlgItemText(IDC_BUTTON4, "��ʼ");
			   FreeMemory(6);

			   //��ʾ�����ͷ��ڴ沢���·���
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

void CMemoryManagementDlg::OnEnChangeEdit1()//������ҵ��
{}
void CMemoryManagementDlg::OnEnChangeEdit2()//����ռ��С
{}
void CMemoryManagementDlg::OnEnChangeEdit3()//�ͷ���ҵ��
{}
void CMemoryManagementDlg::OnEnChangeEdit4()//չʾ��
{
}

//��ĳ����ҵ�����ڴ沢��ʾ��չʾ����
void CMemoryManagementDlg::AllocateMemory(int workNo, int size)
{
	if (FirstFit_or_not==TRUE)
	{	
		Mem.FirstFit(workNo, size);// �״���Ӧ�㷨
	}
	else if (BestFit_or_not==TRUE)
	{
		Mem.BestFit(workNo, size);// �����Ӧ�㷨
	}
	Display();
}

//�ͷ�ĳ����ҵ���ڴ�
void CMemoryManagementDlg::FreeMemory(int workNo)
{
	Mem.FreeMemory(workNo);
	Display();
}

//չʾ
void CMemoryManagementDlg::Display() 
{
	Node* p = Mem.GetPartitionList();//pΪͷ��㣬�޾�����Ϣ
	displayText = "��ǰ���з����������\r\n";
	displayText = displayText + "ʼĩ��ַ(KB)\t������С(KB)\t״̬\t��ҵ��\r\n";
	Node* current = p->next;//p->next���ǵ�һ���о�����Ϣ�Ľ��
	while (current != NULL)
	{
		// ��ҵ��Ϊ0�ķ����������ǿ��з���
		if (current->workNo == 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t����\t--\r\n", current->address, current->size + current->address, current->size);
			displayText = displayText + str;
		}
		// ��ҵ�ŷ�0�ķ������Ƿǿ��з���
		if (current->workNo != 0 && current->size>0)
		{
			CString str;
			str.Format("%d--%d\t\t%d\t\t����\t��ҵ%d\r\n", current->address, current->size + current->address, current->size, current->workNo);
			displayText = displayText + str;
		}
		current = current->next;
	}
	UpdateData(FALSE);				// ���ݱ���ֵ���¿ؼ�
}


/* ****************************** CMemoryManagementDlg �Ի��� ************ ���� ********************** */

/* *************************************** Memory �ڴ� ****************** ��ʼ *********************** */


// �����ڴ�ռ��ܴ�С����TotalSize��
void Memory::AllocateTotalSize(int tsize)	
{
	TotalSize = tsize;
	// ����һ����ͷ���ķ�������
	PartitionList = new Node;//���������ͷ���
	PartitionList->next = NULL;
	PartitionList->pre = NULL;

	// ����һ���½���¼��ǰ�Ŀ��з�����Ϣ
	Node* p = new Node;
	p->size = TotalSize;			//�½��Ĵ�С��Ϊ�ڴ���ܴ�С		
	p->address = 0;					//�½�����ʼ��ַ��Ϊ0
	p->workNo = 0;					//�½����������Ϊ0��0��ʾ�÷����ǿ��з���
	p->next = PartitionList->next;	//��̽����ΪNULL
	p->pre = PartitionList;			//ǰ�����ָ��ͷ���
	PartitionList->next = p;	    //ͷ���ĺ�̽��ָ���½��
}

//�״���Ӧ�㷨
BOOL Memory::FirstFit(int workNo, int size)
{
	Node* target = PartitionList->next;	//targetָ��ָ�򼴽�����ֵķ���
	Node* current = NULL;

	//���ҵ�һ������Ҫ��Ŀ��з���
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	if (target != NULL)
	{		
		Node* p = new Node;//�½�p��㣬ָ�򼴽��������ҵ�ķ������                          
		p->size = size;//�ӿ��÷����л���size��С���ڴ�ռ�
		p->address = target->address;//ָʾ�ý��ĵ�ַΪ��ǰ���з�������ʼ��ַ
		target->size = target->size - size;//��ǰ���з����Ĵ�С����size
		target->address = target->address + size;//��ǰ���з�������ʼ��ַ����ƫ��size

		//���·���Ľ�������н���ǰ��
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("�����ڴ�ʧ��!");
		return FALSE;
	}
}

//�����Ӧ�㷨
BOOL Memory::BestFit(int workNo, int size)	
{
	Node* target = PartitionList->next;	//targetָ�򼴽�����ֵķ���
	Node* current = NULL;

	//���ҵ�һ�����з���
	current = PartitionList->next;
	while (current != NULL && (current->workNo != 0 || current->size < size))
	{
		current = current->next;
	}
	target = current;

	//���ҳ����з���Ҫ�������ڴ���С�Ŀ��з���
	while (current != NULL)
	{
		if (size< current->size && current->size< target->size && current->workNo == 0)
		{
			target = current;
		}
		current = current->next;
	}

	if (target != NULL)  //������δ������״���Ӧ�㷨һ��
	{
		
		Node* p = new Node;//�½�p��㣬ָʾ�����������ҵ�ķ������                   
		p->size = size;//�ӿ��÷����л���size��С���ڴ�ռ� 	
		p->address = target->address;//ָʾ�ý��ĵ�ַΪ��ǰ���з�������ʼ��ַ		
		target->size = target->size - size;//��ǰ���з����Ĵ�С����size		
		target->address = target->address + size;//��ǰ���з�������ʼ��ַ����ƫ��size

		// ���·���Ľ�������н���ǰ��
		p->pre = target->pre;
		p->next = target;
		target->pre->next = p;
		target->pre = p;

		p->workNo = workNo;
		return TRUE;
	}
	else
	{
		AfxMessageBox("�����ڴ�ʧ��!");
		return FALSE;
	}
}

//���տռ��㷨
BOOL Memory::FreeMemory(int workNo)	
{
	Node* current;
	//�ҵ�Ҫ�ͷſռ����ҵ
	current = PartitionList->next;
	while (current != NULL && current->workNo != workNo)
	{
		current = current->next;
	}

	//�ͷŸ���ҵ���ڴ�
	if (current)
	{
		// ���1������Ҫ�ͷ��ڴ�ķ���ǰ���ǿ��з���ʱ���������������ϲ�
		if (current->pre != PartitionList && current->pre->workNo == 0)	
		{
			if (current->next != NULL && current->next->workNo == 0)
			{
				// ���ͷ��ڴ�ķ��������Ŀ��з����ϲ�
				current->size = current->size + current->next->size;
				current->workNo = 0;
				if (current->next->next != NULL)
				{
					current->next->next->pre = current;
				}
				current->next = current->next->next;
			}

			// ���ղźϲ���ķ���������ǰ��Ŀ��з����ٴκϲ���ʵ�����������ϲ�
			current->pre->size = current->pre->size + current->size;
			current->pre->next = current->next;
			if (current->next != NULL)
			{
				current->next->pre = current->pre;
			}
		}
		// ���2�������ǰ������Ƿǿ��з����������ķ����ǿ��з��������������ķ����ϲ�
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
		// ���3����ǰ��û�п��з���������ͷű�����ڴ�
		else
		{
			current->workNo = 0;
		}
		return TRUE;
	}
	else
	{
		AfxMessageBox("�ͷ��ڴ�ʧ��!");
		return FALSE;
	}
}

//�ͷ�����ȫ���ڴ�
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

/* *************************************** Memory �ڴ� ******************* ���� *********************** */