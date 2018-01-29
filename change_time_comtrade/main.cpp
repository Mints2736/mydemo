#define BUFLEN 255  

#include <stdio.h>  
#include <time.h>
#include <iostream>
#include <fstream>

#include <vector>

#if defined(_WIN32)||defined(_WIN64)

#include <direct.h>
#include <io.h>
#include <string>

#else

#include <unistd.h>
#include <dirent.h>
#include <string.h>

#endif

using namespace std;

void getAllFiles(string path, vector<string>& files)
{
    //文件句柄  
    long   hFile = 0;


#if defined(_WIN32)||defined(_WIN64)
	
	// windows下找出指定路径下的文件与文件夹

    //文件信息  
    struct _finddata_t fileinfo;  //很少用的文件信息读取结构
    string p;  //string类很有意思的一个赋值函数:assign()，有很多重载版本
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib &  _A_SUBDIR))  //判断是否为文件夹
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
					files.push_back(p.assign(path).append("/").append(fileinfo.name));//保存文件夹名字
                    getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//递归当前文件夹
                }
            }
            else    //文件处理
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));//文件名
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }

#else

	// linux下找出指定路径下的文件与文件夹

	DIR *dir;  
    struct dirent *ptr;  
    char base[1000];  
   
    if ((dir=opendir(path.c_str())) == NULL)  
        {  
		   perror("Open dir error...");  
        }  
   
    while ((ptr=readdir(dir)) != NULL)  
    {  
        if(strcmp(ptr->d_name,".")==0 || strcmp(ptr->d_name,"..")==0)    ///current dir OR parrent dir  
                continue;  
        else if(ptr->d_type == 8)    ///file  
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);  
            files.push_back(ptr->d_name);  
        else if(ptr->d_type == 10)    ///link file  
            //printf("d_name:%s/%s\n",basePath,ptr->d_name);  
            continue;  
        else if(ptr->d_type == 4)    ///dir  
        {  
            files.push_back(ptr->d_name);  
            /* 
                memset(base,'\0',sizeof(base)); 
                strcpy(base,basePath); 
                strcat(base,"/"); 
                strcat(base,ptr->d_nSame); 
                readFileList(base); 
            */  
        }  
    }  
    closedir(dir);  

#endif  
}

int main(int argc, const char * argv[]) 
{
    string line;
	vector<string> lines;

	string filename;
	string m_fimename_new;
		
	//	获取系统时间 
	time_t t = time( 0 );  
    char tmpBuf[BUFLEN] , tmpBuf1[BUFLEN];
	
    strftime(tmpBuf, BUFLEN, "%d/%m/%Y,%H:%M:%S.00000", localtime(&t));
	strftime(tmpBuf1, BUFLEN, "%Y%m%d_%H%M%S_000", localtime(&t));

#ifdef _DEBUG
	printf("time is %s \n",tmpBuf);  
	printf("time is %s \n",tmpBuf1);  
#endif


 /***********************************************************************
 *函数名称:     _getcwd
 *函数原型:     char * _cdecl _getcwd(char *_DstBuf,int _SizeInBytes)
 *函数功能:     得到当前路径名称
 *函数返回:     指向dir的指针
 *参数说明:     _DstBuf-路径字符串;_SizeInBytes-路径最大长度
 *头 文 件:     <direct.h>
 *************************************************************************/
	char buff[1000];

#if defined(_WIN32)||defined(_WIN64)	
	
	_getcwd(buff, 1000);

#else
	
	getcwd(buff, 1000);

#endif

     cout << "当前文件夹路径是：" << buff << endl << endl;


	string DATA_DIR = buff;
    vector<string> files;

    // 当前目录下的所有文件夹以及文件的绝对路径
    getAllFiles(DATA_DIR, files);

 /***********************************************************************
 ****  把指定路径的所有文件与文件夹的路径都输出到txt文件里
 *************************************************************************/
	/*
	char * DistAll = "AllFiles.txt";
    ofstream ofn(DistAll);  //输出文件流
    int size = files.size();
    int  FaiNum = 0;
    ofn << size << endl;
    for (int i = 0; i<size; i++)
    {
        ofn << files[i] << endl;
    }
    ofn.close(); // 关闭文件
	*/

	string	m_strpath;
	int end;
	string  m_filetime;
	string	dat_Extensions = ".dat";
	string	cfg_Extensions = ".cfg";

	//	用迭代器来进行循环并选择指定的文件
    for (vector<string>::iterator it_file = files.begin(); it_file != files.end(); ++it_file)
	{
	//	cout << *it_file<< endl;
		m_strpath = *it_file; // 每次循环要重新赋值

		//处理故障指示器 测试波形 带“故障指示器”“TEST”且为“.cfg”格式  
        if ((it_file->find("故障指示器") != string::npos) && (it_file->find("TEST") != string::npos) && (it_file->find(".cfg") != string::npos))
        {
			
			cout << "当前文件全路径为路径" << m_strpath << endl << endl;	
			
			// 打开文件
			ifstream myfile(m_strpath.c_str());
			
			//	读文件各行到vector<string>中
			if (myfile.is_open())
			{
				while (getline(myfile, line))
				{
					lines.push_back(line);
				}
				myfile.close();
			}
			else
			{
				cout << "open file failed." << endl;
			}
			
			//	用迭代器来进行循环并替换指定的字符串
			for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				
				if ((it->find("/") != string::npos) && (it->find(":") != string::npos))
				{
					*it = tmpBuf;
					cout << "modify the cfg time ok" << endl<< endl;
				}
			}
		
			// 写入文件
			ofstream myfileOut(m_strpath.c_str());
			if (myfileOut.is_open())
			{
				for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
				{
					myfileOut << *it << endl;
				}
				myfileOut.close();
			}
			
			else
				cout << "Unable to open file";

			lines.clear(); // 每个循环结束需要清空lines向量，否则会累计在里面，导致重复

			// 修改文件名
			end = m_strpath.find("TEST01_0001_") + 12;
			m_filetime = tmpBuf1; 
			
			m_fimename_new = m_strpath.substr(0, end)+m_filetime + cfg_Extensions; 
			
			cout << " m_fimename_new is :" <<  m_fimename_new << endl;
			
			// 修改cfg文件名
			if (!rename(m_strpath.c_str(), m_fimename_new.c_str()))  
			{  
				std::cout << "rename  the cfg file success "<< std::endl << endl;  
			}  
			else  
			{  
				std::cout << "rename  the cfg file error "<< std::endl;  
			}  			
			
		 }

		if ((it_file->find("故障指示器") != string::npos) && (it_file->find("TEST") != string::npos) && (it_file->find(".dat") != string::npos))
		{
			// 修改文件名
			
			end = m_strpath.find("TEST01_0001_") + 12;

			m_filetime = tmpBuf1; 


			m_fimename_new = m_strpath.substr(0, end)+m_filetime + dat_Extensions; 

			cout << " m_fimename_new is :" <<  m_fimename_new << endl;

			// 修改dat文件名
			if (!rename(m_strpath.c_str(), m_fimename_new.c_str()))  
			{  
				std::cout << "rename  the dat file success "<< std::endl;  
			}  
			else  
			{  
				std::cout << "rename  the dat file error "<< std::endl;  
			}  

		}
    }
	
	cout << "\n***************************************\n" << "replace the comtrade files`time  ok" << "\n***************************************\n"<< endl;
    return 0;
}