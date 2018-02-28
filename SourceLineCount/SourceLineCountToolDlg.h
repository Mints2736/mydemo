// FileEditToolDlg.h : ͷ�ļ�
//
/**
** ���ߣ�pengweizhi
** http://blog.csdn.net/toshiba689
** ���䣺toshiba689@sina.com
**/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFileEditToolDlg �Ի���
class CFileEditToolDlg : public CDialog
{
// ����
public:
	CFileEditToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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

	void  AddDir(LPCTSTR tszDir); //���Ŀ¼��Ĵ����ļ�����֧�ֵ���ɨ����Ŀ¼�ļ�
	BOOL  AddFile(CString strFilePath); //���һ�������ļ�
	bool  RemoveFile(SourceFileInfo * pFile); //���б���ɾ�������ļ�

	int   GetLineNum(CString strFilePath); //��ȡָ���ļ��Ĵ�������
	int   GetTotalLineNum(); //��ȡ�����ļ��Ĵ�������

	SourceFileInfo *  AddSourceFile(CString strFileType, CString strFilePath, int nLineCount); //����ļ�����Ϣ���б�

    bool              IsInFilterType(CString strExt); //������ļ������Ƿ��ڹ����б�����



protected:
	CListCtrl m_List1;

	CString m_strCurrentDir; //����Ŀ¼·��

	list<SourceFileInfo*> m_lstFiles; //����Դ�����ļ����б�

	list<CString> m_lstFilterTypes; //��¼���˵��ļ���׺������".h", ".cpp"

	BOOL m_bIgnoreEmptyLines; //�Ƿ���Ե�����(���ΪFalse���򽫿�����һ�д��룬���ΪTrue����ͳ�ƿ��еĸ������ܴ�������)
};
