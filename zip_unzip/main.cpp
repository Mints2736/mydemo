#include <QFile>
#include <QFile>
#include <QtCore> 
#include <QCoreApplication>
#include <QObject>

#include "zlib.h"
#include <stdio.h>
#include "quazip.h"
#include "quazipfile.h"
#include <QTextCodec>


#define QTCONSOLE 1
#include "gojobzip.h"

static inline QString UserLanguage()
{
     /////////////QSettings setter;
     QString languser,languagesistem,langqt; 
	QLocale loci = QLocale::system();
             languser = getenv("LANG");
             languser = languser.toLower();
             languagesistem = loci.name();
             languagesistem = languagesistem.toLower();
	     languagesistem = languagesistem.left(2);
     /* Window XP Prof MUI Multiuser == stay only "c" language && user setting setenv !!! */
     if (languagesistem == "c") { 
         if (languser.size() > 2 && languser.contains("_")) {
             languagesistem = languser.left(2);
         }
     }
  return languagesistem;
}


int main(int argc, char *argv[]) {

    /*
    QCoreApplication a( argc, argv );
    QString a1, a2 , a3 , la, dis, folderzip;
    const QString na = "press";
    la =  UserLanguage();
    QTextStream out(stdout);
    ////out.setFieldWidth(60);
    ////out.setPadChar('.');
    
    if (!argv[1]) {
      out <<  "Usage language " << la << ":\n";
      out <<  "GZ file\n";
      out <<  na << " gz filename\n";
      out <<  "\n";
      out <<  "ZIP dir\n";
      out <<  na << " zip /pathtozip/ /path_out_zipfile/\n";
      out <<  na << " zip /pathtozip/  ./  (to output zip on current folder.) \n";
      out <<  "zip file name take from folder name.\n";
      out <<  "UnZIP dir\n";
      out <<  na << " unzip zipfile.zip /pathout/\n";
      out <<  "\n";
      out << "\n";
      return 0;
    }
    
    a1 = argv[1];
    a2 = argv[2];
    a3 = argv[3];
    
    if (a1.size() > 1) {
        
        if (a1 == "gz") {
               out << "Start gz compress... on file .. " << a2 << " \n"; 
               bool s = MakeGzipOneFile(a2);
               if (s) {
               out << "File " << a2 << " is ready.\n"; 
               } else {
               out << "File " << a2 << " not found.\n";   
               }
        } else if (a1 == "unzip") {
               out << "Start unzip file... " << a2 << " \n";
               QDir check(a3);
                    check.mkpath(a3);
            
               if (check.exists() && is_file(a2)) {
                   dis = check.absolutePath();
                   if (!dis.endsWith("/")) {
                   dis.append("/");
                   }
                   bool uz = UnzipTo(a2,dis);
                       if (uz) {
                       out << "UnZip " << a2 << " is ready.\n"; 
                       } else {
                       out << "UnZip " << a2 << " file or dir not found.\n";   
                       }
               
               } else {
                       out << "UnZip " << a2 << " file or dir not found.\n"; 
               }                   
            
         } else if (a1 == "zip") {
                 out << "Start zip path..." << a2 << " zip file dest to " << a3 << " \n";
             
                  if (a3.size() > 0 ) {
                      QDir dest(a3);
                      QDir folder(a2);
                      dest.mkpath(a3);
                      dis = dest.absolutePath();
                         if (!dis.endsWith("/")) {
                           dis.append("/");
                         }
                         
                         if (folder.exists()) {
                             folderzip =  folder.absolutePath();
                             if (!folderzip.endsWith("/")) {
                             folderzip.append("/");
                             }
                             
                             PackZip ma;
                                     ma.SetJob(folderzip,dis);
                              return 0;
                         } else {
                         out <<  a2 << " path not exist!\n";  
                         out <<  "ZIP dir command:\n";
                         out <<  na << " zip /pathtozip/ /path_out_zipfile/\n";  
                         return 0;
                         }
                      
                      
                      
                      
                      
                  } else {
                      
                      out <<  "ZIP dir command:\n";
                      out <<  na << " zip /pathtozip/ /path_out_zipfile/\n"; 
                      return 0;
                  }
             
             
             
         }   else {
             
                  out <<  "Usage language " << la << ":\n";
                  out <<  "GZ file\n";
                  out <<  na << " gz filename\n";
                  out <<  "\n";
                  out <<  "ZIP dir\n";
                  out <<  na << " zip /pathtozip/ /pathzipout/\n";
                  out <<  "\n";
                  out <<  "UnZIP dir\n";
                  out <<  na << " unzip zipfile.zip /pathout/\n";
                  out <<  "\n";
                  out << "\n";
                  return 0;
             
         }
    }

    
    
    
    */

QString a2("E:/tmp/11.zip");
  QString a3("E:/tmp");
  QString dis;
    qDebug()<< "Start unzip file... " << a2 << " \n";
    QDir check(a3);
         check.mkpath(a3);

    if (check.exists() && is_file(a2)) {
        dis = check.absolutePath();
        if (!dis.endsWith("/")) {
        dis.append("/");
        }
        bool uz = UnzipTo(a2,dis);
            if (uz) {
           qDebug()<< "UnZip " << a2 << " is ready.\n";
            } else {
           qDebug()<< "UnZip " << a2 << " file or dir not found.\n";
            }

    } else {
           qDebug()<< "UnZip " << a2 << " file or dir not found.\n";
    }
    
    
    return 0;
}



