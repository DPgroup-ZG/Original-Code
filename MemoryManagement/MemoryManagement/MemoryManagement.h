
// MemoryManagement.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMemoryManagementApp: 
// �йش����ʵ�֣������ MemoryManagement.cpp
//

class CMemoryManagementApp : public CWinApp
{
public:
	CMemoryManagementApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMemoryManagementApp theApp;