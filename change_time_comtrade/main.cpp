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
    //�ļ����  
    long   hFile = 0;


#if defined(_WIN32)||defined(_WIN64)
	
	// windows���ҳ�ָ��·���µ��ļ����ļ���

    //�ļ���Ϣ  
    struct _finddata_t fileinfo;  //�����õ��ļ���Ϣ��ȡ�ṹ
    string p;  //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib &  _A_SUBDIR))  //�ж��Ƿ�Ϊ�ļ���
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                {
					files.push_back(p.assign(path).append("/").append(fileinfo.name));//�����ļ�������
                    getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//�ݹ鵱ǰ�ļ���
                }
            }
            else    //�ļ�����
            {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));//�ļ���
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
        _findclose(hFile);
    }

#else

	// linux���ҳ�ָ��·���µ��ļ����ļ���

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
		
	//	��ȡϵͳʱ�� 
	time_t t = time( 0 );  
    char tmpBuf[BUFLEN] , tmpBuf1[BUFLEN];
	
    strftime(tmpBuf, BUFLEN, "%d/%m/%Y,%H:%M:%S.00000", localtime(&t));
	strftime(tmpBuf1, BUFLEN, "%Y%m%d_%H%M%S_000", localtime(&t));

#ifdef _DEBUG
	printf("time is %s \n",tmpBuf);  
	printf("time is %s \n",tmpBuf1);  
#endif


 /***********************************************************************
 *��������:     _getcwd
 *����ԭ��:     char * _cdecl _getcwd(char *_DstBuf,int _SizeInBytes)
 *��������:     �õ���ǰ·������
 *��������:     ָ��dir��ָ��
 *����˵��:     _DstBuf-·���ַ���;_SizeInBytes-·����󳤶�
 *ͷ �� ��:     <direct.h>
 *************************************************************************/
	char buff[1000];

#if defined(_WIN32)||defined(_WIN64)	
	
	_getcwd(buff, 1000);

#else
	
	getcwd(buff, 1000);

#endif

     cout << "��ǰ�ļ���·���ǣ�" << buff << endl << endl;


	string DATA_DIR = buff;
    vector<string> files;

    // ��ǰĿ¼�µ������ļ����Լ��ļ��ľ���·��
    getAllFiles(DATA_DIR, files);

 /***********************************************************************
 ****  ��ָ��·���������ļ����ļ��е�·���������txt�ļ���
 *************************************************************************/
	/*
	char * DistAll = "AllFiles.txt";
    ofstream ofn(DistAll);  //����ļ���
    int size = files.size();
    int  FaiNum = 0;
    ofn << size << endl;
    for (int i = 0; i<size; i++)
    {
        ofn << files[i] << endl;
    }
    ofn.close(); // �ر��ļ�
	*/

	string	m_strpath;
	int end;
	string  m_filetime;
	string	dat_Extensions = ".dat";
	string	cfg_Extensions = ".cfg";

	//	�õ�����������ѭ����ѡ��ָ�����ļ�
    for (vector<string>::iterator it_file = files.begin(); it_file != files.end(); ++it_file)
	{
	//	cout << *it_file<< endl;
		m_strpath = *it_file; // ÿ��ѭ��Ҫ���¸�ֵ

		//�������ָʾ�� ���Բ��� ��������ָʾ������TEST����Ϊ��.cfg����ʽ  
        if ((it_file->find("����ָʾ��") != string::npos) && (it_file->find("TEST") != string::npos) && (it_file->find(".cfg") != string::npos))
        {
			
			cout << "��ǰ�ļ�ȫ·��Ϊ·��" << m_strpath << endl << endl;	
			
			// ���ļ�
			ifstream myfile(m_strpath.c_str());
			
			//	���ļ����е�vector<string>��
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
			
			//	�õ�����������ѭ�����滻ָ�����ַ���
			for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it)
			{
				
				if ((it->find("/") != string::npos) && (it->find(":") != string::npos))
				{
					*it = tmpBuf;
					cout << "modify the cfg time ok" << endl<< endl;
				}
			}
		
			// д���ļ�
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

			lines.clear(); // ÿ��ѭ��������Ҫ���lines������������ۼ������棬�����ظ�

			// �޸��ļ���
			end = m_strpath.find("TEST01_0001_") + 12;
			m_filetime = tmpBuf1; 
			
			m_fimename_new = m_strpath.substr(0, end)+m_filetime + cfg_Extensions; 
			
			cout << " m_fimename_new is :" <<  m_fimename_new << endl;
			
			// �޸�cfg�ļ���
			if (!rename(m_strpath.c_str(), m_fimename_new.c_str()))  
			{  
				std::cout << "rename  the cfg file success "<< std::endl << endl;  
			}  
			else  
			{  
				std::cout << "rename  the cfg file error "<< std::endl;  
			}  			
			
		 }

		if ((it_file->find("����ָʾ��") != string::npos) && (it_file->find("TEST") != string::npos) && (it_file->find(".dat") != string::npos))
		{
			// �޸��ļ���
			
			end = m_strpath.find("TEST01_0001_") + 12;

			m_filetime = tmpBuf1; 


			m_fimename_new = m_strpath.substr(0, end)+m_filetime + dat_Extensions; 

			cout << " m_fimename_new is :" <<  m_fimename_new << endl;

			// �޸�dat�ļ���
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