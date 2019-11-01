#include "zweekelement.h"
#include <QMessageBox>
#include <QDebug>
#include <QApplication>
ZWeekElement::ZWeekElement(QWidget *parent) :
    QFrame(parent)
{
    this->m_gLayoutMain=new QGridLayout;
    for(qint32 i=0;i<7;i++)
    {
        this->m_checkboxDayEnabled[i]=new QCheckBox;
        connect(this->m_checkboxDayEnabled[i],SIGNAL(clicked(bool)),this,SLOT(ZSlotEnableDayComponents(bool)));

        switch(i)
        {
        case 0:
            this->m_checkboxDayEnabled[i]->setText(tr("Monday"));
            break;
        case 1:
            this->m_checkboxDayEnabled[i]->setText(tr("Tuesday"));
            break;
        case 2:
            this->m_checkboxDayEnabled[i]->setText(tr("Wednesday"));
            break;
        case 3:
            this->m_checkboxDayEnabled[i]->setText(tr("Thursday"));
            break;
        case 4:
            this->m_checkboxDayEnabled[i]->setText(tr("Friday"));
            break;
        case 5:
            this->m_checkboxDayEnabled[i]->setText(tr("Saturday"));
            break;
        case 6:
            this->m_checkboxDayEnabled[i]->setText(tr("Sunday"));
            break;
        default:
            break;
        }

        this->m_labelOn[i]=new QLabel(tr("ON:"));
        this->m_timeOnTime[i]=new QTimeEdit;
        this->m_timeOnTime[i]->setDisplayFormat("hh:mm:ss");
        this->m_timeOnTime[i]->setTimeRange(QTime(6,0,0),QTime(10,0,0));
        this->m_checkBoxAutoExitOn[i]=new QCheckBox(tr("AutoExit"));
        this->m_labelOff[i]=new QLabel(tr("OFF:"));
        this->m_timeOffTime[i]=new QTimeEdit;
        this->m_timeOffTime[i]->setDisplayFormat("hh:mm:ss");
        this->m_timeOffTime[i]->setTimeRange(QTime(14,0,0),QTime(20,0,0));
        this->m_checkBoxAutoExitOff[i]=new QCheckBox(tr("AutoExit"));
    }

    this->m_gLayoutMain=new QGridLayout;
    for(qint32 i=0;i<7;i++)
    {
        this->m_gLayoutMain->addWidget(this->m_checkboxDayEnabled[i],i,0,Qt::AlignLeft|Qt::AlignVCenter);
        this->m_gLayoutMain->addWidget(this->m_labelOn[i],i,1,Qt::AlignCenter);
        this->m_gLayoutMain->addWidget(this->m_timeOnTime[i],i,2,Qt::AlignCenter);
        this->m_gLayoutMain->addWidget(this->m_checkBoxAutoExitOn[i],i,3,Qt::AlignCenter);
        this->m_gLayoutMain->addWidget(this->m_labelOff[i],i,4,Qt::AlignCenter);
        this->m_gLayoutMain->addWidget(this->m_timeOffTime[i],i,5,Qt::AlignCenter);
        this->m_gLayoutMain->addWidget(this->m_checkBoxAutoExitOff[i],i,6,Qt::AlignCenter);
    }
    this->setLayout(this->m_gLayoutMain);
    ////////////////////////
    this->ZLoadConfigFile();
    //////////////////
    this->m_OAObj=new OAControl;
    this->m_timer=new QTimer;
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(ZSlotTimeout1s()));
    this->m_timer->setInterval(1000);
}
ZWeekElement::~ZWeekElement()
{
    for(qint32 i=0;i<7;i++)
    {
        delete this->m_checkboxDayEnabled[i];
        this->m_checkboxDayEnabled[i]=NULL;

        delete this->m_labelOn[i];
        this->m_labelOn[i]=NULL;

        delete this->m_timeOnTime[i];
        this->m_timeOnTime[i]=NULL;

        delete this->m_checkBoxAutoExitOn[i];
        this->m_checkBoxAutoExitOn[i]=NULL;

        delete this->m_labelOff[i];
        this->m_labelOff[i]=NULL;

        delete this->m_timeOffTime[i];
        this->m_timeOffTime[i]=NULL;

        delete this->m_checkBoxAutoExitOff[i];
        this->m_checkBoxAutoExitOff[i]=NULL;
    }
    delete this->m_gLayoutMain;

    delete this->m_timer;
    delete this->m_OAObj;
}
void ZWeekElement::ZLoadConfigFile()
{
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    for(qint32 i=0;i<7;i++)
    {
        this->m_checkboxDayEnabled[i]->setChecked(pConfig->DayEnabled[i]?true:false);
        emit this->m_checkboxDayEnabled[i]->clicked(pConfig->DayEnabled[i]?true:false);
        this->m_timeOnTime[i]->setTime(QTime::fromString(pConfig->OnTime[i],"hh:mm:ss"));
        this->m_checkBoxAutoExitOn[i]->setChecked(pConfig->AutoExitAfterOn[i]);
        this->m_timeOffTime[i]->setTime(QTime::fromString(pConfig->OffTime[i],"hh:mm:ss"));
        this->m_checkBoxAutoExitOff[i]->setChecked(pConfig->AutoExitAfterOff[i]);
    }
}
void ZWeekElement::ZSaveConfigFile()
{
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    for(qint32 i=0;i<7;i++)
    {
        pConfig->DayEnabled[i]=this->m_checkboxDayEnabled[i]->isChecked()?1:0;
        pConfig->OnTime[i]=this->m_timeOnTime[i]->text();
        pConfig->AutoExitAfterOn[i]=this->m_checkBoxAutoExitOn[i]->isChecked()?1:0;
        pConfig->OffTime[i]=this->m_timeOffTime[i]->text();
        pConfig->AutoExitAfterOff[i]=this->m_checkBoxAutoExitOff[i]->isChecked()?1:0;
    }
}
void ZWeekElement::ZSlotEnableDayComponents(bool en)
{
    QCheckBox *checkBox=qobject_cast<QCheckBox*>(sender());
       if(!checkBox->text().compare("Monday"))
       {
           this->m_labelOn[0]->setEnabled(en);
           this->m_timeOnTime[0]->setEnabled(en);
           this->m_checkBoxAutoExitOn[0]->setEnabled(en);
           this->m_labelOff[0]->setEnabled(en);
           this->m_timeOffTime[0]->setEnabled(en);
           this->m_checkBoxAutoExitOff[0]->setEnabled(en);
       }else if(!checkBox->text().compare("Tuesday"))
       {
           this->m_labelOn[1]->setEnabled(en);
           this->m_timeOnTime[1]->setEnabled(en);
           this->m_checkBoxAutoExitOn[1]->setEnabled(en);
           this->m_labelOff[1]->setEnabled(en);
           this->m_timeOffTime[1]->setEnabled(en);
           this->m_checkBoxAutoExitOff[1]->setEnabled(en);
       }else if(!checkBox->text().compare("Wednesday"))
       {
           this->m_labelOn[2]->setEnabled(en);
           this->m_timeOnTime[2]->setEnabled(en);
           this->m_checkBoxAutoExitOn[2]->setEnabled(en);
           this->m_labelOff[2]->setEnabled(en);
           this->m_timeOffTime[2]->setEnabled(en);
           this->m_checkBoxAutoExitOff[2]->setEnabled(en);
       }else if(!checkBox->text().compare("Thursday"))
       {
           this->m_labelOn[3]->setEnabled(en);
           this->m_timeOnTime[3]->setEnabled(en);
           this->m_checkBoxAutoExitOn[3]->setEnabled(en);
           this->m_labelOff[3]->setEnabled(en);
           this->m_timeOffTime[3]->setEnabled(en);
           this->m_checkBoxAutoExitOff[3]->setEnabled(en);
       }else if(!checkBox->text().compare("Friday"))
       {
           this->m_labelOn[4]->setEnabled(en);
           this->m_timeOnTime[4]->setEnabled(en);
           this->m_checkBoxAutoExitOn[4]->setEnabled(en);
           this->m_labelOff[4]->setEnabled(en);
           this->m_timeOffTime[4]->setEnabled(en);
           this->m_checkBoxAutoExitOff[4]->setEnabled(en);
       }else if(!checkBox->text().compare("Saturday"))
       {
           this->m_labelOn[5]->setEnabled(en);
           this->m_timeOnTime[5]->setEnabled(en);
           this->m_checkBoxAutoExitOn[5]->setEnabled(en);
           this->m_labelOff[5]->setEnabled(en);
           this->m_timeOffTime[5]->setEnabled(en);
           this->m_checkBoxAutoExitOff[5]->setEnabled(en);
       }else if(!checkBox->text().compare("Sunday"))
       {
           this->m_labelOn[6]->setEnabled(en);
           this->m_timeOnTime[6]->setEnabled(en);
           this->m_checkBoxAutoExitOn[6]->setEnabled(en);
           this->m_labelOff[6]->setEnabled(en);
           this->m_timeOffTime[6]->setEnabled(en);
           this->m_checkBoxAutoExitOff[6]->setEnabled(en);
       }
}
void ZWeekElement::ZSlotTimeout1s()
{
    QDateTime dateTime=QDateTime::currentDateTime();
    int cur_hour=dateTime.time().hour();
    int cur_minute=dateTime.time().minute();
    int cur_second=dateTime.time().second();
    int weekday=dateTime.date().dayOfWeek();
    if(this->m_checkboxDayEnabled[weekday-1]->checkState()==Qt::Checked)
    {
        //on
        int on_hour=this->m_timeOnTime[weekday-1]->time().hour();
        int on_minute=this->m_timeOnTime[weekday-1]->time().minute();
        int on_second=this->m_timeOnTime[weekday-1]->time().second();
        if(on_hour==cur_hour && on_minute==cur_minute && on_second==cur_second)
        {
            //qDebug()<<"attendance on now!";
            this->ZPostDutyOn();
            if(this->m_checkBoxAutoExitOn[weekday-1]->isChecked())
            {
                qApp->exit(0);
            }
        }

        //off
        int off_hour=this->m_timeOffTime[weekday-1]->time().hour();
        int off_minute=this->m_timeOffTime[weekday-1]->time().minute();
        int off_second=this->m_timeOffTime[weekday-1]->time().second();
        if(off_hour==cur_hour&&off_minute==cur_minute&&off_second==cur_second)
        {
            //qDebug()<<"attendance off now!";
            this->ZPostDutyOff();
            if(this->m_checkBoxAutoExitOff[weekday-1]->isChecked())
            {
                qApp->exit(0);
            }
        }
    }
}
void ZWeekElement::ZSlotStartService()
{
    //update current setting to config object.
    this->ZSaveConfigFile();
    ////////////////////
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    //verify username & password.
    if(this->m_OAObj->postLoginInfoAndSaveCookie(pConfig->OAUserName,pConfig->OAPassword)<0)
    {
        emit this->ZSignalErrMsg(tr("Error when login!\nCheck your username and password!"));
        return;
    }
    //disable all components.
    for(qint32 i=0;i<7;i++)
    {
        this->m_checkboxDayEnabled[i]->setEnabled(false);
        this->m_timeOnTime[i]->setEnabled(false);
        this->m_checkBoxAutoExitOn[i]->setEnabled(false);
        this->m_timeOffTime[i]->setEnabled(false);
        this->m_checkBoxAutoExitOff[i]->setEnabled(false);
    }
    //start schedule timer.
    this->m_timer->start();
}
void ZWeekElement::ZSlotStopService()
{
    //enable all components.
    for(qint32 i=0;i<7;i++)
    {
        this->m_checkboxDayEnabled[i]->setEnabled(true);
        this->m_timeOnTime[i]->setEnabled(true);
        this->m_checkBoxAutoExitOn[i]->setEnabled(true);
        this->m_timeOffTime[i]->setEnabled(true);
        this->m_checkBoxAutoExitOff[i]->setEnabled(true);
    }
    //stop schedule timer.
    this->m_timer->stop();
}
void ZWeekElement::ZPostDutyOn()
{
    qint32 ret=0;
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    for(qint32 i=0;i<pConfig->OAPostOnTimes;i++)
    {
        do{
            //verify username & password.
            if(this->m_OAObj->postLoginInfoAndSaveCookie(pConfig->OAUserName,pConfig->OAPassword)<0)
            {
                ret=-1;
                break;
            }
            //get login info
            if(this->m_OAObj->getLoginInfoAndSaveCookie()<0)
            {
                ret=-2;
                break;
            }
            //get attendance table.
            if(this->m_OAObj->getAttendanceTableAndSaveCookie()<0)
            {
                ret=-3;
                break;
            }
            //duty on.
            if(this->m_OAObj->postAttenanceOnAndSaveCookie()<0)
            {
                ret=-4;
                break;
            }
        }while(0);
    }
    emit this->ZSignalDutyOn(ret);
}
void ZWeekElement::ZPostDutyOff()
{
    qint32 ret=0;
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    for(qint32 i=0;i<pConfig->OAPostOnTimes;i++)
    {
        do{
            //verify username & password.
            if(this->m_OAObj->postLoginInfoAndSaveCookie(pConfig->OAUserName,pConfig->OAPassword)<0)
            {
                ret=-1;
                break;
            }
            //get login info
            if(this->m_OAObj->getLoginInfoAndSaveCookie()<0)
            {
                ret=-2;
                break;
            }
            //get attendance table.
            if(this->m_OAObj->getAttendanceTableAndSaveCookie()<0)
            {
                ret=-3;
                break;
            }
            //duty off.
            if(this->m_OAObj->postAttendanceOffAndSaveCookie()<0)
            {
                ret=-4;
                break;
            }
        }while(0);
    }
    emit this->ZSignalDutyOff(ret);
}
