#include "zoaset.h"

ZOASet::ZOASet(QWidget *parent) :
    QFrame(parent)
{
    this->m_labelHeadOA=new QLabel(tr("OA Server Settings"));
    this->m_labelOAIP=new QLabel(tr("IP Address:"));
    this->m_lineEditOAIP=new QLineEdit;
    this->m_labelUserName=new QLabel(tr("UserName:"));
    this->m_lineEditUserName=new QLineEdit;
    this->m_lineEditUserName->setEnabled(false);
    this->m_labelUserPass=new QLabel(tr("Password:"));
    this->m_lineEditUserPass=new QLineEdit;
    this->m_lineEditUserPass->setEchoMode(QLineEdit::Password);
    this->m_gLayoutServer=new QGridLayout;
    this->m_gLayoutServer->addWidget(this->m_labelOAIP,0,0,1,1);
    this->m_gLayoutServer->addWidget(this->m_lineEditOAIP,0,1,1,1);
    this->m_gLayoutServer->addWidget(this->m_labelUserName,1,0,1,1);
    this->m_gLayoutServer->addWidget(this->m_lineEditUserName,1,1,1,1);
    this->m_gLayoutServer->addWidget(this->m_labelUserPass,1,2,1,1);
    this->m_gLayoutServer->addWidget(this->m_lineEditUserPass,1,3,1,1);
    /////////////////////////////////////////////////////////
    this->m_labelHeadSet=new QLabel(tr("Exhanced Options"));
    this->m_labelPostOnTimes=new QLabel(tr("PostOnTimes:"));
    this->m_spinBoxPostOnTimes=new QSpinBox;
    this->m_labelPostOffTimes=new QLabel(tr("PostOffTimes:"));
    this->m_spinBoxPostOffTimes=new QSpinBox;
    this->m_gLayoutOption=new QGridLayout;
    this->m_gLayoutOption->addWidget(this->m_labelPostOnTimes,0,0,1,1);
    this->m_gLayoutOption->addWidget(this->m_spinBoxPostOnTimes,0,1,1,1);
    this->m_gLayoutOption->addWidget(this->m_labelPostOffTimes,0,2,1,1);
    this->m_gLayoutOption->addWidget(this->m_spinBoxPostOffTimes,0,3,1,1);

    /////////////////////////
    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addWidget(this->m_labelHeadOA);
    this->m_vLayoutMain->addLayout(this->m_gLayoutServer);
    this->m_vLayoutMain->addWidget(this->m_labelHeadSet);
    this->m_vLayoutMain->addLayout(this->m_gLayoutOption);
    this->m_vLayoutMain->addStretch(1);
    this->setLayout(this->m_vLayoutMain);

    this->ZLoadConfigFile();

    ////////////////////////////
}
ZOASet::~ZOASet()
{
    delete this->m_labelHeadOA;
    delete this->m_labelOAIP;
    delete this->m_lineEditOAIP;
    delete this->m_labelUserName;
    delete this->m_lineEditUserName;
    delete this->m_labelUserPass;
    delete this->m_lineEditUserPass;
    delete this->m_gLayoutServer;
    delete this->m_labelHeadSet;
    delete this->m_labelPostOnTimes;
    delete this->m_spinBoxPostOnTimes;
    delete this->m_labelPostOffTimes;
    delete this->m_spinBoxPostOffTimes;
    delete this->m_gLayoutOption;
    ////////////
}
void ZOASet::ZLoadConfigFile()
{
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    this->m_lineEditOAIP->setText(pConfig->OAIPAddr);
    this->m_lineEditUserName->setText(pConfig->OAUserName);
    this->m_lineEditUserPass->setText(pConfig->OAPassword);
    this->m_spinBoxPostOnTimes->setValue(pConfig->OAPostOnTimes);
    this->m_spinBoxPostOffTimes->setValue(pConfig->OAPostOffTimes);
}
void ZOASet::ZSaveConfigFile()
{
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    pConfig->OAIPAddr=this->m_lineEditOAIP->text();
    pConfig->OAUserName=this->m_lineEditUserName->text();
    pConfig->OAPassword=this->m_lineEditUserPass->text();
    pConfig->OAPostOnTimes=this->m_spinBoxPostOnTimes->value();
    pConfig->OAPostOffTimes=this->m_spinBoxPostOffTimes->value();
}
void ZOASet::ZSlotStartService()
{
    //update current setting to config object.
    this->ZSaveConfigFile();

    //disable all components.
    this->m_lineEditOAIP->setEnabled(false);
    this->m_lineEditUserName->setEnabled(false);
    this->m_lineEditUserPass->setEnabled(false);
    this->m_spinBoxPostOnTimes->setEnabled(false);
    this->m_spinBoxPostOffTimes->setEnabled(false);
    //start schedule timer.

}
void ZOASet::ZSlotStopService()
{
    //enable all components.
    this->m_lineEditOAIP->setEnabled(true);
    this->m_lineEditUserName->setEnabled(true);
    this->m_lineEditUserPass->setEnabled(true);
    this->m_spinBoxPostOnTimes->setEnabled(true);
    this->m_spinBoxPostOffTimes->setEnabled(true);
    //stop schedule timer.
}
