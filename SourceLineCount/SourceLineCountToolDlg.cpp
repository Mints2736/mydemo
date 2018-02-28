// FileEditToolDlg.cpp : 实现文件
//
/**
** 作者：pengweizhi
** http://blog.csdn.net/toshiba689
** 邮箱：toshiba689@sina.com
**/

#include "stdafx.h"
#include "SourceLineCountTool.h"
#include "SourceLineCountToolDlg.h"
#include "FuncUtils.h"
#include "StdioFileEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define DEFAULT_FILTER_STR    _T(".h;.cpp")

// CFileEditToolDlg 对话框


CFileEditToolDlg::CFileEditToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileEditToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bIgnoreEmptyLines = FALSE;
}

void CFileEditToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_List1);

}

BEGIN_MESSAGE_MAP(CFileEditToolDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CFileEditToolDlg::OnNMRClickList1)
	ON_COMMAND(IDM_LIST_REMOVE_WORD, &CFileEditToolDlg::OnListRemoveWord)
	ON_COMMAND(IDM_LIST_REMOVE_ALL_WORD, &CFileEditToolDlg::OnListRemoveAllWord)
	ON_BN_CLICKED(IDC_BUTTON_REFRESH, &CFileEditToolDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_IMPORT, &CFileEditToolDlg::OnBnClickedButtonAddDir)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CFileEditToolDlg::OnBnClickedButtonAddFile)
	ON_BN_CLICKED(IDC_BUTTON_CALC_LINES, &CFileEditToolDlg::OnBnClickedButtonCalcLines)
END_MESSAGE_MAP()


// CFileEditToolDlg 消息处理程序

BOOL CFileEditToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_List1.InsertColumn(1, _T("文件"),   LVCFMT_LEFT, 350);
	m_List1.InsertColumn(1, _T("类型"),   LVCFMT_LEFT, 100);

	GetDlgItem(IDC_EDIT_FILTER_TYPES)->SetWindowText(DEFAULT_FILTER_STR);

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(m_bIgnoreEmptyLines);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFileEditToolDlg::OnDestroy()
{
	CDialog::OnDestroy();

    ClearFiles();
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFileEditToolDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CFileEditToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


SourceFileInfo * CFileEditToolDlg:: FindFile(CString strFile)
{
	list<SourceFileInfo*>::iterator it;
	for(it = m_lstFiles.begin(); it != m_lstFiles.end(); it++)
	{
        SourceFileInfo * pFileItem = *it;
		if(pFileItem->strFilePath == strFile)
			return pFileItem;
	}
	return NULL;
}


bool  CFileEditToolDlg::RemoveFile(SourceFileInfo * pFileIn)
{
	list<SourceFileInfo*>::iterator it;

	for(it = m_lstFiles.begin(); it != m_lstFiles.end(); it++)
	{
      SourceFileInfo * pFileItem = *it;

	  if(pFileItem == pFileIn)
	  {
         delete pFileItem;
		 m_lstFiles.erase(it);
		 return true;
		// break;
	  }
	}
	return false;
}
	

void CFileEditToolDlg::ClearFiles()
{
	list<SourceFileInfo*>::iterator it;
	for(it = m_lstFiles.begin(); it != m_lstFiles.end(); it++)
	{
      SourceFileInfo * pFileItem = *it;
	  delete pFileItem;
	}
	m_lstFiles.clear();
}

int   CFileEditToolDlg::GetLineNum(CString strFilePath)
{
	SourceFileInfo * pFileItem = FindFile(strFilePath);
    if(pFileItem == NULL)
		return -1;

	return pFileItem->nLineCount;
}

int  CFileEditToolDlg::GetTotalLineNum()
{
	int nTotal = 0;
	list<SourceFileInfo*>::iterator it;

	for(it = m_lstFiles.begin(); it != m_lstFiles.end(); ++it)
	{
		SourceFileInfo * pFileItem = *it;
		nTotal += pFileItem->nLineCount;
	}	
	
	return nTotal;
}

void CFileEditToolDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<NMITEMACTIVATE*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	int nItem = pNMItemActivate->iItem;
	if(nItem == -1) return;
	
	CMenu dMenu;
	if(!dMenu.LoadMenu(IDR_MENU1))
		AfxThrowResourceException();

	CMenu* pPopMenu=dMenu.GetSubMenu(0);
	ASSERT(pPopMenu!=NULL);
	POINT pt;
	::GetCursorPos(&pt);

	pPopMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,pt.x,pt.y, AfxGetMainWnd());
}

void CFileEditToolDlg::OnListRemoveWord()
{
    int nItem = m_List1.GetSelectionMark();
	if(nItem < 0)
		return;

	SourceFileInfo * pFileItem = (SourceFileInfo*)m_List1.GetItemData(nItem);
	if(pFileItem != NULL)
	{
	   if(RemoveFile(pFileItem))
	   {
		   m_List1.DeleteItem(nItem);
	   }
	}

}

void CFileEditToolDlg::OnListRemoveAllWord()
{
   ClearFiles();
   m_List1.DeleteAllItems();
}



//添加目录里的文件
void CFileEditToolDlg::OnBnClickedButtonAddDir()
{
	CString strDir;
	GetDlgItem(IDC_EDIT_DIR_PATH)->GetWindowText(strDir);
    if(strDir.IsEmpty())
	{
		MessageBox(_T("目录路径没指定"),  _T("提示"), MB_OK|MB_ICONWARNING);
		return;
	}

	ClearFiles();
	m_List1.DeleteAllItems();

	m_strCurrentDir = strDir;

	m_bIgnoreEmptyLines = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck(); //是否忽略掉空行

	AddDir(strDir);
}


//添加目录里的文件（不支持迭代扫描子目录文件）
void  CFileEditToolDlg::AddDir(LPCTSTR tszDir)
{
	//获取过滤的文件类型列表（比如".h", ".cpp"）

	m_lstFilterTypes.clear();

	CString strArry;
	GetDlgItem(IDC_EDIT_FILTER_TYPES)->GetWindowText(strArry);

	if(strArry.Find(";") == -1)
	{
       MessageBox( _T("输入的过滤文件类型之间请用分号隔开，例如：.h;.hpp;.cpp，注意每个类型前面以'.'开头"), _T("提示"), MB_OK|MB_ICONWARNING);
	}

	//按分号提取子字符串
	int i = 0;
	CString strGet;
	while (AfxExtractSubString(strGet, strArry, i++, _T(';')))
	{
		strGet.Trim();

		if(strGet.GetAt(0) != '.')
			continue;

		m_lstFilterTypes.push_back(strGet);
	}

	if(strArry.IsEmpty())
	{
	    MessageBox(_T("你未输入过滤文件类型！"), _T("提示"), MB_OK|MB_ICONWARNING);
		return;
	}
	else if(m_lstFilterTypes.size() == 0)
	{
		MessageBox( _T("你输入的过滤文件类型不合法！"), _T("提示"), MB_OK|MB_ICONWARNING);
		return;
	}

	///////////////////////////////////////////////

    WIN32_FIND_DATA wfd;

    TCHAR  szFile[MAX_PATH]   = {0};
	TCHAR  szFolder[MAX_PATH] = {0};

	_tcscpy(szFolder, tszDir);

	if(szFolder[_tcslen(tszDir)-1] != '\\')
	{
		_tcscat(szFolder, _T("\\"));
	}

	TCHAR szTemp[MAX_PATH] = {0};
	_tcscat(szTemp, szFolder);
	_tcscat(szTemp, _T("*.*"));

	HANDLE hFind = ::FindFirstFile(szTemp, &wfd);
	if ( hFind != INVALID_HANDLE_VALUE )
	{
		do 
		{
			if (_tcscmp(wfd.cFileName, _T(".")) != 0 &&
				(_tcscmp(wfd.cFileName, _T("..")) != 0) )
			{
				_tcscpy(szFile, szFolder);
				_tcscat(szFile, wfd.cFileName);

				if(wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{
					//AddDir(szFile);
				}
				else
				{
				   AddFile(szFile);
				}
	
			}
		} while(::FindNextFile(hFind, &wfd));
		FindClose(hFind);
	}
}

//手动选择文件添加
void CFileEditToolDlg::OnBnClickedButtonAddFile()
{
	//获取过滤的文件类型列表（比如".h", ".cpp"）

	m_lstFilterTypes.clear();

	CString strArry;
	GetDlgItem(IDC_EDIT_FILTER_TYPES)->GetWindowText(strArry);

	if(strArry.Find(";") == -1)
	{
       MessageBox( _T("输入的过滤文件类型之间请用分号隔开，例如：.h;.hpp;.cpp，注意每个类型前面以'.'开头"), _T("提示"), MB_OK|MB_ICONWARNING);
	}

	//按分号提取子字符串
	int i = 0;
	CString strGet;
	while (AfxExtractSubString(strGet, strArry, i++, _T(';')))
	{
		strGet.Trim();

		if(strGet.GetAt(0) != '.')
			continue;

		m_lstFilterTypes.push_back(strGet);
	}

	if(strArry.IsEmpty())
	{
	    MessageBox( _T("你未输入过滤文件类型！"), _T("提示"), MB_OK|MB_ICONWARNING);
		return;
	}
	else if(m_lstFilterTypes.size() == 0)
	{
		MessageBox(_T("你输入的过滤文件类型不合法！"), _T("提示"), MB_OK|MB_ICONWARNING);
		return;
	}

	m_bIgnoreEmptyLines = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck(); //是否忽略掉空行，如果为False，则将空行算一行代码，如果为True，则不统计空行的个数到总代码行数

	////////////////////////////////////////////////////

	CString    strFilter;
    strFilter = _T("Source File (*.h);(*.cpp);|*.h;*.cpp|");
	strFilter += _T("All Files (*.*)|*.*|");

	//CList<CString, CString&> cList;

	CFileDialog dlg(TRUE, NULL, NULL, OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, strFilter, this);
	DWORD  MAXFILE   =   100*1024;   //   allocate   enough   memory   space   
	dlg.m_ofn.nMaxFile  =   MAXFILE;   //   set   the   buffer   size   
	TCHAR * buf  =   new  TCHAR[MAXFILE];   
	dlg.m_ofn.lpstrFile    =  buf;   
	dlg.m_ofn.lpstrFile[0] = NULL;  

	if (IDOK == dlg.DoModal()) 
	{
		CString strDir;
		CString szPath;
		POSITION pos;
		pos = dlg.GetStartPosition();

		while( pos ) //添加多个文件
		{
			szPath = dlg.GetNextPathName(pos);

			strDir = szPath.Left(szPath.ReverseFind('\\'));

			AddFile(szPath);

		}//while( pos )

		//::SetCurrentDirectory(strDir); //设置当前目录为上次选择的路径
	}
	delete[] buf;
}

//清除所有文件
void CFileEditToolDlg::OnBnClickedButtonClear()
{
    ClearFiles();
	m_List1.DeleteAllItems();
}


BOOL CFileEditToolDlg::AddFile(CString strPath)
{
    CString strDir = _T(".");
    int pos = -1;
	CString strFileExt; //文件扩展名

	pos = strPath.ReverseFind('\\');
	if(pos >= 0)
	{
		strDir = strPath.Left(pos); //获得源文件所在的目录
	}

	pos = strPath.ReverseFind('.');
	if(pos == -1)
		return FALSE;

	strFileExt = strPath.Mid(pos); //文件扩展名

	//检查该文件是否为定义的过滤类型，如果否，则跳过
	if(!IsInFilterType(strFileExt))
	{
        return FALSE;
	}

   /////////////////////////////////////
	int nItem = m_List1.GetItemCount();
	m_List1.InsertItem(nItem, strPath);

	
	m_List1.SetItemText(nItem, 1, strFileExt);
	
    /////////////////////////////////////

	int i = 0;
    CString line;
	int nLines = 0;

	CStdioFileEx file;
	if( !file.Open(strPath, CFile::modeRead | CFile::typeText) )
	   return FALSE;

	while( file.ReadString(line)!= FALSE ) //读取字符串，直到遇到换行符
	{
		i++;

		if(line.IsEmpty()) //空行
		{
			if(!m_bIgnoreEmptyLines) //不忽略空行
			{
			   nLines++;
			}
		}
		else //不是空行
		{
			 nLines++;
		}

		line.Empty();
	}
	file.Close();

	SourceFileInfo * pFileItem = AddSourceFile(strFileExt, strPath, nLines);

	if(pFileItem != NULL)
	{
	   m_List1.SetItemData(nItem, (UINT_PTR)pFileItem);
	}

	return TRUE;
}

SourceFileInfo * CFileEditToolDlg::AddSourceFile(CString strFileType, CString strFilePath, int nLineCount)
{
	SourceFileInfo * pFileItem = new  SourceFileInfo();

	pFileItem->strFileType = strFileType;
	pFileItem->strFilePath = strFilePath;
	pFileItem->nLineCount = nLineCount;

	m_lstFiles.push_back(pFileItem);

	return pFileItem;
}

//文件类型是否在过滤列表里面
bool CFileEditToolDlg::IsInFilterType(CString strExt)
{
	//strExt.MakeLower(); //转为小写字母

	list<CString>::iterator it;
	for(it = m_lstFilterTypes.begin(); it != m_lstFilterTypes.end(); ++it)
	{
		if(strExt.CompareNoCase(*it) == 0) //不区分大小写比较
		{
			return true;
		}
	}
	return false;
}

//统计代码行数
void CFileEditToolDlg::OnBnClickedButtonCalcLines()
{
	int nTotalLines = GetTotalLineNum();

	if(nTotalLines == 0 && m_lstFiles.size() == 0)
	{
		MessageBox(_T("你未添加任何文件"),  _T("提示"), MB_OK|MB_ICONWARNING);
		return;
	}


	CString str;
	str.Format(_T("代码行数：%d"), nTotalLines);

    MessageBox(str, _T("提示"), MB_OK);
}

