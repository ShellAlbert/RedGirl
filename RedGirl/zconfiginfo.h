#ifndef ZCONFIGINFO_H
#define ZCONFIGINFO_H
#include <QString>
class ZConfigInfo
{
public:
    static ZConfigInfo* ZGetInstance()
    {
        if(m_pInstance==NULL)
        {
            m_pInstance=new ZConfigInfo;
            m_pInstance->ZReadConfigFile();
        }
        return m_pInstance;
    }

public:
    qint32 ZWriteConfigFile();
    qint32 ZReadConfigFile();
public:
    QString OAIPAddr;
    QString OAUserName;
    QString OAPassword;
    qint32 OAPostOnTimes;
    qint32 OAPostOffTimes;
    ////////////////////
    qint32 DayEnabled[7];
    QString OnTime[7];
    qint32 AutoExitAfterOn[7];
    QString OffTime[7];
    qint32 AutoExitAfterOff[7];
    ////////////////////////
    QString EmailSMTPAddr;
    QString EmailSender;
    QString EmailSenderPassword;
    qint32 AliveEmailEnabled;
    qint32 PostResultEnabled;
private:
    static ZConfigInfo* m_pInstance;
};

#endif // ZCONFIGINFO_H
