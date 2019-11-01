#include "zctrlui.h"
#include <QDateTime>
#include <QMessageBox>
#include <QApplication>
ZCtrlUI::ZCtrlUI(QWidget *parent) :
    QFrame(parent)
{
    this->m_labelCurTimeTip=new QLabel(tr("Current Time:"));
    this->m_labelCurTime=new QLabel;
    this->m_labelCurTime->setText(tr("00:00:00"));
    this->m_labelRunTimeTip=new QLabel(tr("Run Time:"));
    this->m_labelRunTime=new QLabel;
    this->m_labelRunTime->setText(tr("00:00:00"));
    /////////////////////////////////////////////////////
    this->m_labelAMTotalTips=new QLabel(tr("AM Total:"));
    this->m_labelAMTotal=new QLabel(tr("0"));
    this->m_labelAMSuccessTips=new QLabel(tr("Success:"));
    this->m_labelAMSuccess=new QLabel(tr("0"));
    /////////////////////////////////
    this->m_labelPMTotalTips=new QLabel(tr("PM Total:"));
    this->m_labelPMTotal=new QLabel(tr("0"));
    this->m_labelPMSuccessTips=new QLabel(tr("Success:"));
    this->m_labelPMSuccess=new QLabel(tr("0"));
    ////////////////////////////////////////////
    this->m_labelAliveEmailTotalTips=new QLabel(tr("Email Total"));
    this->m_labelAliveEmailTotal=new QLabel(tr("0"));
    this->m_labelAliveEmailSuccessTips=new QLabel(tr("Success"));
    this->m_labelAliveEmailSuccess=new QLabel(tr("0"));
    ////////////////////////////////////////////
    this->m_btnStart=new QToolButton;
    this->m_btnStart->setText(tr("Start"));
    this->m_btnExit=new QToolButton;
    this->m_btnExit->setText(tr("Exit"));
    this->m_gridLayout=new QGridLayout;
    //line 1.
    this->m_gridLayout->addWidget(this->m_labelCurTimeTip,0,0,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelCurTime,0,1,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelRunTimeTip,0,2,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelRunTime,0,3,Qt::AlignCenter);
    //line 2.
    this->m_gridLayout->addWidget(this->m_labelAMTotalTips,1,0,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelAMTotal,1,1,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelAMSuccessTips,1,2,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelAMSuccess,1,3,Qt::AlignCenter);
    //line 3.
    this->m_gridLayout->addWidget(this->m_labelPMTotalTips,2,0,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelPMTotal,2,1,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelPMSuccessTips,2,2,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelPMSuccess,2,3,Qt::AlignCenter);
    //line 4.
    this->m_gridLayout->addWidget(this->m_labelAliveEmailTotalTips,3,0,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelAliveEmailTotal,3,1,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelAliveEmailSuccessTips,3,2,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_labelAliveEmailSuccess,3,3,Qt::AlignCenter);
    //line 5.
    this->m_gridLayout->addWidget(this->m_btnStart,4,2,Qt::AlignCenter);
    this->m_gridLayout->addWidget(this->m_btnExit,4,3,Qt::AlignCenter);
    this->setLayout(this->m_gridLayout);

    this->m_timer=new QTimer;
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(ZSlotTimeout1s()));
    this->m_timer->start(1000);
    this->m_runCounter=0;
    this->m_bCountRunTime=false;

    ///////////////////////////////////////
    connect(this->m_btnStart,SIGNAL(clicked()),this,SLOT(ZSlotStartService()));
    connect(this->m_btnExit,SIGNAL(clicked()),this,SLOT(ZSlotExitApp()));

    //initial counter.
    this->m_AMTotal=0;
    this->m_AMSuccess=0;
    this->m_PMTotal=0;
    this->m_PMSuccess=0;
}
ZCtrlUI::~ZCtrlUI()
{
    delete this->m_labelCurTimeTip;
    delete this->m_labelCurTime;
    delete this->m_labelRunTimeTip;
    delete this->m_labelRunTime;
    ////////////////
    delete this->m_labelAMTotalTips;
    delete this->m_labelAMTotal;
    delete this->m_labelAMSuccessTips;
    delete this->m_labelAMSuccess;
    ///////////////
    delete this->m_labelPMTotalTips;
    delete this->m_labelPMTotal;
    delete this->m_labelPMSuccessTips;
    delete this->m_labelPMSuccess;
    ///////////////////////////////
    delete this->m_labelAliveEmailTotalTips;
    delete this->m_labelAliveEmailTotal;
    delete this->m_labelAliveEmailSuccessTips;
    delete this->m_labelAliveEmailSuccess;
    /////////////////////////
    delete this->m_btnStart;
    delete this->m_btnExit;
    delete this->m_gridLayout;

    delete this->m_timer;
}
void ZCtrlUI::ZSlotTimeout1s()
{
    //update current time.
    this->m_labelCurTime->setText(QTime::currentTime().toString("HH:mm:ss"));
    if(this->m_bCountRunTime)
    {
        this->m_runCounter++;
        qint32 tHour=this->m_runCounter/3600;
        qint32 tMinute=(this->m_runCounter-tHour*3600)/60;
        qint32 tSecond=(this->m_runCounter-tHour*3600-tMinute*60);
        QString tRunTimeStr;
        tRunTimeStr.sprintf("%02d:%02d:%02d",tHour,tMinute,tSecond);
        this->m_labelRunTime->setText(tRunTimeStr);
    }
}
void ZCtrlUI::ZSlotStartService()
{
    disconnect(this->m_btnStart,SIGNAL(clicked()),this,SLOT(ZSlotStartService()));
    this->m_btnStart->setText(tr("Stop"));
    connect(this->m_btnStart,SIGNAL(clicked()),this,SLOT(ZSlotStopService()));

    //start run time counter.
    this->m_runCounter=0;
    this->m_bCountRunTime=true;

    //start service code.
    emit this->ZSignalStartService();

}
void ZCtrlUI::ZSlotStopService()
{
    disconnect(this->m_btnStart,SIGNAL(clicked()),this,SLOT(ZSlotStopService()));
    this->m_btnStart->setText(tr("Start"));
    connect(this->m_btnStart,SIGNAL(clicked()),this,SLOT(ZSlotStartService()));
    //stop run time counter.
    this->m_bCountRunTime=false;

    //stop service code.
    emit this->ZSignalStopService();
}
void ZCtrlUI::ZSlotExitApp()
{
    qApp->exit();
}
void ZCtrlUI::ZSlotErrMsg(QString errMsg)
{
    QMessageBox::critical(this,tr("Error"),errMsg);
    this->ZSlotStopService();
    return;
}
void ZCtrlUI::ZSlotUpdateDutyOnCounter(qint32 ret)
{
    this->m_AMTotal++;
    if(!ret)
    {
        this->m_AMSuccess++;
    }
    this->m_labelAMTotal->setText(QString("%1").arg(this->m_AMTotal));
    this->m_labelAMSuccess->setText(QString("%1").arg(this->m_AMSuccess));
}
void ZCtrlUI::ZSlotUpdateDutyOffCounter(qint32 ret)
{
    this->m_PMTotal++;
    if(!ret)
    {
        this->m_PMSuccess++;
    }
    this->m_labelPMTotal->setText(QString("%1").arg(this->m_PMTotal));
    this->m_labelPMSuccess->setText(QString("%1").arg(this->m_PMSuccess));
}
void ZCtrlUI::ZSlotUpdateEmailCounter(qint32 ret)
{
    this->m_AliveEmailTotal++;
    if(!ret)
    {
        this->m_AliveEmailSuccess++;
    }
    this->m_labelAliveEmailTotal->setText(QString("%1").arg(this->m_AliveEmailTotal));
    this->m_labelAliveEmailSuccess->setText(QString("%1").arg(this->m_AliveEmailSuccess));
}
