// FileEditToolDlg.h : 头文件
//
/**
** 作者：pengweizhi
** http://blog.csdn.net/toshiba689
** 邮箱：toshiba689@sina.com
**/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFileEditToolDlg 对话框
class CFileEditToolDlg : public CDialog
{
// 构造
public:
	CFileEditToolDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonAddDir();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnListRemoveWord();
	afx_msg void OnListRemoveAllWord();
  	afx_msg void OnBnClickedButtonAddFile();
    afx_msg void OnBnClickedButtonCalcLines();

	void  ClearFiles();

	SourceFileInfo *  FindFile(CString strFile);

	void  AddDir(LPCTSTR tszDir); //添加目录里的代码文件，不支持迭代扫描子目录文件
	BOOL  AddFile(CString strFilePath); //添加一个代码文件
	bool  RemoveFile(SourceFileInfo * pFile); //从列表中删除代码文件

	int   GetLineNum(CString strFilePath); //获取指定文件的代码行数
	int   GetTotalLineNum(); //获取所有文件的代码行数

	SourceFileInfo *  AddSourceFile(CString strFileType, CString strFilePath, int nLineCount); //添加文件的信息到列表

    bool              IsInFilterType(CString strExt); //输入的文件类型是否在过滤列表里面



protected:
	CListCtrl m_List1;

	CString m_strCurrentDir; //工程目录路径

	list<SourceFileInfo*> m_lstFiles; //所有源代码文件的列表

	list<CString> m_lstFilterTypes; //记录过滤的文件后缀，比如".h", ".cpp"

	BOOL m_bIgnoreEmptyLines; //是否忽略掉空行(如果为False，则将空行算一行代码，如果为True，则不统计空行的个数到总代码行数)
};
