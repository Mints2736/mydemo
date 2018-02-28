 
#ifndef _FunctionsUtils
#define _FunctionsUtils


BOOL     FileExist( LPCTSTR   pszFileName); //检查文件是否存在

CString  GetAppDir(); //获得应用程序的当前目录路径

BOOL    IsFileType(LPCTSTR lpsz, LPCTSTR lpszType); //检查文件是否为指定类型（lpszType为后缀名）

ULONG   GetFileSize(LPCTSTR lpszPath); //获得文件大小

//int     GetFileList(LPCTSTR lpszDir,  LPCTSTR lpszType, CList<CString, CString &> & lst); //在目录中获取类型为lpszType的文件列表

BOOL    ReadFileData(LPCTSTR lpszFile, BYTE* pData, UINT & len ); //读取文件数据

CString  FileNameFromPath(CString strPath); //从文件路径提取文件名称

CString   UIntToString(UINT value);

INT       StringToInt(CString & str);

CString   IntToString(INT value);

INT       HexToInt(const char * szHex, int len);

COLORREF  StringToRGB(CString & str);

CString   RGBToString(COLORREF color);

 #endif