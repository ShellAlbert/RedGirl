#include "zmainwidget.h"
#include <QDebug>
ZMainWidget::ZMainWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("Monkey Spring Festival Special Edition"));
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->m_labelBanner=new QLabel;
    this->m_labelBanner->setObjectName("Banner");
    this->m_movieGif=new QMovie(":/resource/images/banner.gif");
    //this->m_labelBanner->setMovie(this->m_movieGif);
    this->m_movieGif->start();
    //the gif banner is 728x90,so here,we restrict the width of main widget.
    this->setMaximumWidth(728);
    ///////////////////////////////////////
    this->m_ctrl=new ZCtrlUI;
    this->m_oa=new ZOASet;
    this->m_week=new ZWeekElement;
    this->m_mail=new ZMailNotify;
    this->m_tab=new QTabWidget;
    this->m_tab->addTab(this->m_ctrl,QIcon(":/resource/images/service_control.png"),tr("Service Control"));
    this->m_tab->addTab(this->m_oa,QIcon(":/resource/images/oa_settings.png"),tr("OA Settings"));
    this->m_tab->addTab(this->m_week,QIcon(":/resource/images/time_settings.png"),tr("Time Settings"));
    this->m_tab->addTab(this->m_mail,QIcon(":/resource/images/email_notify.png"),tr("Email Notification"));
    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addWidget(this->m_labelBanner);
    this->m_vLayoutMain->addWidget(this->m_tab);
    this->m_vLayoutMain->setSpacing(0);
    this->m_vLayoutMain->setContentsMargins(0,0,0,0);
    this->setLayout(this->m_vLayoutMain);
    /////////////////
    connect(this->m_ctrl,SIGNAL(ZSignalStartService()),this->m_oa,SLOT(ZSlotStartService()));
    connect(this->m_ctrl,SIGNAL(ZSignalStopService()),this->m_oa,SLOT(ZSlotStopService()));
    //////////////
    connect(this->m_ctrl,SIGNAL(ZSignalStartService()),this->m_week,SLOT(ZSlotStartService()));
    connect(this->m_ctrl,SIGNAL(ZSignalStopService()),this->m_week,SLOT(ZSlotStopService()));
    //////////////
    connect(this->m_ctrl,SIGNAL(ZSignalStartService()),this->m_mail,SLOT(ZSlotStartService()));
    connect(this->m_ctrl,SIGNAL(ZSignalStopService()),this->m_mail,SLOT(ZSlotStopService()));
    /////////////////////////////
    connect(this->m_week,SIGNAL(ZSignalErrMsg(QString)),this->m_ctrl,SLOT(ZSlotErrMsg(QString)));
    connect(this->m_mail,SIGNAL(ZSignalErrMsg(QString)),this->m_ctrl,SLOT(ZSlotErrMsg(QString)));
    ////////////////////////////////
    connect(this->m_week,SIGNAL(ZSignalDutyOn(qint32)),this->m_ctrl,SLOT(ZSlotUpdateDutyOnCounter(qint32)));
    connect(this->m_week,SIGNAL(ZSignalDutyOff(qint32)),this->m_ctrl,SLOT(ZSlotUpdateDutyOffCounter(qint32)));
    connect(this->m_mail,SIGNAL(ZSignalEmailSended(qint32)),this->m_ctrl,SLOT(ZSlotUpdateEmailCounter(qint32)));

    connect(this->m_week,SIGNAL(ZSignalDutyOn(qint32)),this->m_mail,SLOT(ZSlotEmailNotifyDutyOn(qint32)));
    connect(this->m_week,SIGNAL(ZSignalDutyOff(qint32)),this->m_mail,SLOT(ZSlotEmailNotifyDutyOff(qint32)));
}

ZMainWidget::~ZMainWidget()
{
    delete this->m_movieGif;
    delete this->m_labelBanner;
    delete this->m_ctrl;
    delete this->m_oa;
    delete this->m_week;
    delete this->m_mail;
    delete this->m_tab;
    delete this->m_vLayoutMain;
}
void ZMainWidget::closeEvent(QCloseEvent *)
{
    this->m_oa->ZSaveConfigFile();
    this->m_week->ZSaveConfigFile();
    this->m_mail->ZSaveConfigFile();
    ZConfigInfo::ZGetInstance()->ZWriteConfigFile();
    qDebug()<<"closeEvent";
}
