 
#ifndef _FunctionsUtils
#define _FunctionsUtils


BOOL     FileExist( LPCTSTR   pszFileName); //����ļ��Ƿ����

CString  GetAppDir(); //���Ӧ�ó���ĵ�ǰĿ¼·��

BOOL    IsFileType(LPCTSTR lpsz, LPCTSTR lpszType); //����ļ��Ƿ�Ϊָ�����ͣ�lpszTypeΪ��׺����

ULONG   GetFileSize(LPCTSTR lpszPath); //����ļ���С

//int     GetFileList(LPCTSTR lpszDir,  LPCTSTR lpszType, CList<CString, CString &> & lst); //��Ŀ¼�л�ȡ����ΪlpszType���ļ��б�

BOOL    ReadFileData(LPCTSTR lpszFile, BYTE* pData, UINT & len ); //��ȡ�ļ�����

CString  FileNameFromPath(CString strPath); //���ļ�·����ȡ�ļ�����

CString   UIntToString(UINT value);

INT       StringToInt(CString & str);

CString   IntToString(INT value);

INT       HexToInt(const char * szHex, int len);

COLORREF  StringToRGB(CString & str);

CString   RGBToString(COLORREF color);

 #endif