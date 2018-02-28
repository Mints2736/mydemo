// FileEditToolDlg.cpp : ʵ���ļ�
//
/**
** ���ߣ�pengweizhi
** http://blog.csdn.net/toshiba689
** ���䣺toshiba689@sina.com
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

// CFileEditToolDlg �Ի���


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


// CFileEditToolDlg ��Ϣ�������

BOOL CFileEditToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	m_List1.InsertColumn(1, _T("�ļ�"),   LVCFMT_LEFT, 350);
	m_List1.InsertColumn(1, _T("����"),   LVCFMT_LEFT, 100);

	GetDlgItem(IDC_EDIT_FILTER_TYPES)->SetWindowText(DEFAULT_FILTER_STR);

	((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(m_bIgnoreEmptyLines);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFileEditToolDlg::OnDestroy()
{
	CDialog::OnDestroy();

    ClearFiles();
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFileEditToolDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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



//���Ŀ¼����ļ�
void CFileEditToolDlg::OnBnClickedButtonAddDir()
{
	CString strDir;
	GetDlgItem(IDC_EDIT_DIR_PATH)->GetWindowText(strDir);
    if(strDir.IsEmpty())
	{
		MessageBox(_T("Ŀ¼·��ûָ��"),  _T("��ʾ"), MB_OK|MB_ICONWARNING);
		return;
	}

	ClearFiles();
	m_List1.DeleteAllItems();

	m_strCurrentDir = strDir;

	m_bIgnoreEmptyLines = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck(); //�Ƿ���Ե�����

	AddDir(strDir);
}


//���Ŀ¼����ļ�����֧�ֵ���ɨ����Ŀ¼�ļ���
void  CFileEditToolDlg::AddDir(LPCTSTR tszDir)
{
	//��ȡ���˵��ļ������б�����".h", ".cpp"��

	m_lstFilterTypes.clear();

	CString strArry;
	GetDlgItem(IDC_EDIT_FILTER_TYPES)->GetWindowText(strArry);

	if(strArry.Find(";") == -1)
	{
       MessageBox( _T("����Ĺ����ļ�����֮�����÷ֺŸ��������磺.h;.hpp;.cpp��ע��ÿ������ǰ����'.'��ͷ"), _T("��ʾ"), MB_OK|MB_ICONWARNING);
	}

	//���ֺ���ȡ���ַ���
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
	    MessageBox(_T("��δ��������ļ����ͣ�"), _T("��ʾ"), MB_OK|MB_ICONWARNING);
		return;
	}
	else if(m_lstFilterTypes.size() == 0)
	{
		MessageBox( _T("������Ĺ����ļ����Ͳ��Ϸ���"), _T("��ʾ"), MB_OK|MB_ICONWARNING);
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

//�ֶ�ѡ���ļ����
void CFileEditToolDlg::OnBnClickedButtonAddFile()
{
	//��ȡ���˵��ļ������б�����".h", ".cpp"��

	m_lstFilterTypes.clear();

	CString strArry;
	GetDlgItem(IDC_EDIT_FILTER_TYPES)->GetWindowText(strArry);

	if(strArry.Find(";") == -1)
	{
       MessageBox( _T("����Ĺ����ļ�����֮�����÷ֺŸ��������磺.h;.hpp;.cpp��ע��ÿ������ǰ����'.'��ͷ"), _T("��ʾ"), MB_OK|MB_ICONWARNING);
	}

	//���ֺ���ȡ���ַ���
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
	    MessageBox( _T("��δ��������ļ����ͣ�"), _T("��ʾ"), MB_OK|MB_ICONWARNING);
		return;
	}
	else if(m_lstFilterTypes.size() == 0)
	{
		MessageBox(_T("������Ĺ����ļ����Ͳ��Ϸ���"), _T("��ʾ"), MB_OK|MB_ICONWARNING);
		return;
	}

	m_bIgnoreEmptyLines = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck(); //�Ƿ���Ե����У����ΪFalse���򽫿�����һ�д��룬���ΪTrue����ͳ�ƿ��еĸ������ܴ�������

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

		while( pos ) //��Ӷ���ļ�
		{
			szPath = dlg.GetNextPathName(pos);

			strDir = szPath.Left(szPath.ReverseFind('\\'));

			AddFile(szPath);

		}//while( pos )

		//::SetCurrentDirectory(strDir); //���õ�ǰĿ¼Ϊ�ϴ�ѡ���·��
	}
	delete[] buf;
}

//��������ļ�
void CFileEditToolDlg::OnBnClickedButtonClear()
{
    ClearFiles();
	m_List1.DeleteAllItems();
}


BOOL CFileEditToolDlg::AddFile(CString strPath)
{
    CString strDir = _T(".");
    int pos = -1;
	CString strFileExt; //�ļ���չ��

	pos = strPath.ReverseFind('\\');
	if(pos >= 0)
	{
		strDir = strPath.Left(pos); //���Դ�ļ����ڵ�Ŀ¼
	}

	pos = strPath.ReverseFind('.');
	if(pos == -1)
		return FALSE;

	strFileExt = strPath.Mid(pos); //�ļ���չ��

	//�����ļ��Ƿ�Ϊ����Ĺ������ͣ������������
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

	while( file.ReadString(line)!= FALSE ) //��ȡ�ַ�����ֱ���������з�
	{
		i++;

		if(line.IsEmpty()) //����
		{
			if(!m_bIgnoreEmptyLines) //�����Կ���
			{
			   nLines++;
			}
		}
		else //���ǿ���
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

//�ļ������Ƿ��ڹ����б�����
bool CFileEditToolDlg::IsInFilterType(CString strExt)
{
	//strExt.MakeLower(); //תΪСд��ĸ

	list<CString>::iterator it;
	for(it = m_lstFilterTypes.begin(); it != m_lstFilterTypes.end(); ++it)
	{
		if(strExt.CompareNoCase(*it) == 0) //�����ִ�Сд�Ƚ�
		{
			return true;
		}
	}
	return false;
}

//ͳ�ƴ�������
void CFileEditToolDlg::OnBnClickedButtonCalcLines()
{
	int nTotalLines = GetTotalLineNum();

	if(nTotalLines == 0 && m_lstFiles.size() == 0)
	{
		MessageBox(_T("��δ����κ��ļ�"),  _T("��ʾ"), MB_OK|MB_ICONWARNING);
		return;
	}


	CString str;
	str.Format(_T("����������%d"), nTotalLines);

    MessageBox(str, _T("��ʾ"), MB_OK);
}

