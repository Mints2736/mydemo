// SourceLineCountTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSourceLineCountToolApp:
// �йش����ʵ�֣������ SourceLineCountTool.cpp
//

class CSourceLineCountToolApp : public CWinApp
{
public:
	CSourceLineCountToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSourceLineCountToolApp theApp;
