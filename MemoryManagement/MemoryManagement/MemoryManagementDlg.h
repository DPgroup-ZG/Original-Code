
// MemoryManagementDlg.h : ͷ�ļ�
//

#pragma once


//�ڴ�����ҵ�ķ���ṹ
typedef struct Node
{
	Node *pre;            //ǰ�����
	Node *next;           //��̽��	
	int size;	          //�������ڴ�ռ��С
	int address;	      //�����׵�ַ
	int workNo;		      //�÷������������ҵ���
};

class Memory
{
public:

	Memory(){TotalSize = 0;}//��ʼ������ռ�Ϊ0
	~Memory(){Free();}	//�ͷ�����ṹ
	
	BOOL FirstFit(int workNo, int size);	//�״���Ӧ�㷨
	BOOL BestFit(int workNo, int size);	    //�����Ӧ�㷨
	BOOL FreeMemory(int workNo);	        //���տռ��㷨
	void AllocateTotalSize(int tsize);	    //�����ڴ�ռ��ܴ�С
	Node* GetPartitionList(){ return PartitionList; }  //��ȡ��������
	void Free();	                        //�ͷ�����ȫ���ڴ�

private:
	int TotalSize;        //�ڴ�ռ���ܴ�С
	Node* PartitionList;  //��������
};


// CMemoryManagementDlg �Ի���
class CMemoryManagementDlg : public CDialogEx
{
	// ����
public:
	CMemoryManagementDlg(CWnd* pParent = NULL);	//��׼���캯��
	// �Ի�������
	enum { IDD = IDD_MEMORYMANAGEMENT_DIALOG };

	int	workNum;							//��ǰҪ�����ڴ�ռ����ҵ��
	int workSize;							//��ǰҪ������ڴ�ռ��С
	int	freeNum;							//��ǰҪ�ͷ��ڴ�ռ����ҵ��
	CString displayText;					//������Ϣչʾ��
	BOOL FirstFit_or_not;					//�Ƿ��״���Ӧ�㷨
	BOOL BestFit_or_not;					//�Ƿ������Ӧ�㷨

	afx_msg void OnBnClickedRadio1();//�״���Ӧ�㷨��ť
	afx_msg void OnBnClickedRadio2();//�����Ӧ�㷨��ť
	afx_msg void OnBnClickedButton1();//ȷ������ռ䰴ť
	afx_msg void OnBnClickedButton2();//ȷ���ͷſռ䰴ť
	afx_msg void OnBnClickedButton3();//��ʼ�Զ���ʾ��ť
	afx_msg void OnEnChangeEdit1();//������ҵ��
	afx_msg void OnEnChangeEdit2();//����ռ��С
	afx_msg void OnEnChangeEdit3();//�ͷ���ҵ��
	afx_msg void OnEnChangeEdit4();//չʾ��

private:
	void Display();	//��ʾ��ǰ������Ϣ
	void AllocateMemory(int workNo, int size);//�����ڴ�
	void FreeMemory(int workNo);//�ͷ��ڴ�

	int Step;//��¼�Զ���ʾ����ʾ����
	Memory Mem;//ʵ���ڴ涯̬�����������


protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
