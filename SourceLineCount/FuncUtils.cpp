
#include "stdafx.h"
//#include "afx.h"
#include "FuncUtils.h"

BOOL   FileExist( LPCTSTR   pszFileName)
{
  if(GetFileAttributes(pszFileName) == -1)   
  {   
     return FALSE;  
  }
   return TRUE;
}



CString  GetAppDir()
{
	TCHAR szLocalPath[MAX_PATH]; 
	GetModuleFileName( 0, szLocalPath, MAX_PATH );
    CString strTemp;
	strTemp  = szLocalPath;
	strTemp = strTemp.Left(strTemp.ReverseFind('\\'));
	return strTemp;
}

BOOL IsFileType(LPCTSTR lpsz, LPCTSTR lpszType)
{
	CString strType = lpszType;
	CString str = lpsz;
	if ( str.GetLength() >= 5 ){
		int nFind = str.ReverseFind('.');
		if ( nFind != -1 ) {

			str = str.Right(str.GetLength() - nFind );
			str.MakeLower();

			if (str == strType){
				return TRUE;
			}

		}
	}
	return FALSE;
}

 ULONG     GetFileSize(LPCTSTR lpszPath)
 {
  
	CFile file;
	if(!file.Open(lpszPath, CFile::modeRead | CFile::shareDenyNone))
		return -1;
	ULONG size = (ULONG)file.GetLength();
	file.Close();

	return size;
 }



 BOOL  ReadFileData(LPCTSTR lpszFile, BYTE* pData, UINT  & len )
{
 // 	TCHAR buffer[MAX_PATH]; 
	//GetModuleFileName( 0, buffer, MAX_PATH );
	//LPTSTR pos=_tcsrchr(buffer, '\\');
	//if (pos)
	//	*++pos=0;

	//_tcscat(buffer, _T("FileList.xml"));

	CFile file;
	if(!file.Open(lpszFile, CFile::modeRead | CFile::shareDenyWrite))
	{
      return FALSE;
	}

		
	long length = (long)file.GetLength();
	if(length <= 0)
	{
	   file.Close();
	   return FALSE;
	}

	if(len < (UINT)length)
	{
		file.Close();
	    return FALSE;
	}

	len = length;


    int bytes = file.Read(pData, length);
	if(bytes < 0)
	{
		file.Close();
        return FALSE;
	}


	file.Close();
    return TRUE;
}

  CString  FileNameFromPath(CString strPath)
 {
    CString filename;

	int pos = strPath.ReverseFind('\\');
	if(pos == -1)
		return strPath;

	filename = strPath.Mid(pos+1);
	return filename;
 }

  CString   UIntToString(UINT value)
{
   CString str;
   str.Format(_T("%u"), value);
   return str;
}

INT    StringToInt(CString & str)
{
     return _tstoi(str);
}

CString   IntToString(INT value)
{
   CString str;
   str.Format(_T("%d"), value);
   return str;
}

 INT   HexToInt(const TCHAR * szHex, int len)
 {
   int sum = 0;
   

   for(int i = 0; i<len; i++)
   {
     TCHAR c = szHex[len-1-i];
#ifdef _UNICODE
	 c = towupper(c);
#else
	 c = ::toupper(c);
#endif

     switch(c)
     {
     case 'A':
        sum += 10*(1<<(4*i));
        break;
     case 'B':
        sum += 11*(1<<(4*i));
        break;
     case 'C':
        sum += 12*(1<<(4*i));
        break;
     case 'D':
        sum += 13*(1<<(4*i));
        break;
     case 'E':
        sum += 14*(1<<(4*i));
        break;
     case 'F':
        sum += 15*(1<<(4*i));
        break;
     default:
        sum += ((int)(c-48))*(1<<(4*i));
     }
    }//for
   return sum;
 }

 COLORREF  StringToRGB(CString & str)
 {
	 str.Trim();

	 int i = 0;
	 int len = str.GetLength();
	 if(len != 7)
		 return RGB(255, 255, 255);

	 UINT r, g, b;

	 if(str.Left(1) == _T("#"))
		 str = str.Mid(1);

     CString  tmp; 

	 tmp = str.Mid(0, 2);
	 r = HexToInt(tmp, 2);

	 tmp = str.Mid(2, 2);
	 g = HexToInt(tmp, 2);

	 tmp = str.Mid(4, 2);
	 b = HexToInt(tmp, 2);
	 
	 COLORREF rgb = RGB(r, g, b);
	 return rgb;
 }

 CString  RGBToString(COLORREF color)
 {
	CString str;
	str.Format(_T("#%02x%02x%02x"), GetRValue(color), GetGValue(color), GetBValue(color));
	return str;
 }