#include "zmainwidget.h"
#include <QApplication>
#include <QFile>
#include <zlogindialog.h>
#include <zqssname.h>
#include <zconfiginfo.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //load qss file.
    QFile qssFile(":/skin/resource/OASkin.txt");
    if(qssFile.open(QFile::ReadOnly))
    {
        QString qssStr=qssFile.readAll();
        a.setStyleSheet(qssStr);
    }
    ZLoginDialog loginDia;
    if(loginDia.exec()==QDialog::Rejected)
    {
        return -1;
    }
    //remember the UserName.
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    pConfig->OAUserName=loginDia.ZGetUserName();
    //use fixed sender & password.
    pConfig->EmailSender="13522296239@163.com";
    pConfig->EmailSenderPassword="qwer1234";
    ZMainWidget w;
    w.show();

    return a.exec();
}
