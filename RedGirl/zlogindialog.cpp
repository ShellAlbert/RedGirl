#include "zlogindialog.h"
#include <QMessageBox>
#include <QCryptographicHash>
#include <QDebug>
ZLoginDialog::ZLoginDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle(tr("QQ空间挂级V1.0"));
    this->m_labelLoginBanner=new QLabel;
    this->m_labelLoginBanner->setObjectName("LoginBanner");
    this->m_labelLoginBanner->setFixedSize(300,60);
    ///////////////////////////////
    this->m_labelPenguin=new QLabel;
    this->m_labelPenguin->setObjectName("Penguin");
    this->m_labelPenguin->setFixedSize(72,72);
    this->m_lineEditUser=new QLineEdit;
    this->m_lineEditPass=new QLineEdit;
    this->m_gridLayout=new QGridLayout;
    this->m_gridLayout->addWidget(this->m_labelPenguin,0,0,2,1);
    this->m_gridLayout->addWidget(this->m_lineEditUser,0,1,1,1);
    this->m_gridLayout->addWidget(this->m_lineEditPass,1,1,1,1);
    this->m_gridLayout->setColumnStretch(0,1);
    this->m_gridLayout->setColumnStretch(1,0);
    ////////////////
    this->m_btnLogin=new QToolButton;
    this->m_btnLogin->setText(tr("登录"));
    this->m_btnExit=new QToolButton;
    this->m_btnExit->setText(tr("退出"));
    this->m_hLayoutBtn=new QHBoxLayout;
    this->m_hLayoutBtn->addStretch(1);
    this->m_hLayoutBtn->addWidget(this->m_btnLogin);
    this->m_hLayoutBtn->addWidget(this->m_btnExit);

    /////////////////
    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->setContentsMargins(0,0,0,6);
    this->m_vLayoutMain->addWidget(this->m_labelLoginBanner);
    this->m_vLayoutMain->addLayout(this->m_gridLayout);
    this->m_vLayoutMain->addLayout(this->m_hLayoutBtn);
    this->setLayout(this->m_vLayoutMain);

    connect(this->m_btnLogin,SIGNAL(clicked()),this,SLOT(ZSlotVerifyMagicKey()));
    connect(this->m_btnExit,SIGNAL(clicked()),this,SLOT(reject()));
}
ZLoginDialog::~ZLoginDialog()
{
    delete this->m_labelLoginBanner;
    delete this->m_labelPenguin;
    delete this->m_lineEditUser;
    delete this->m_lineEditPass;
    delete this->m_gridLayout;
    delete this->m_btnLogin;
    delete this->m_btnExit;
    delete this->m_hLayoutBtn;
    delete this->m_vLayoutMain;
}
void ZLoginDialog::ZSlotVerifyMagicKey()
{
    if(this->m_lineEditUser->text().isEmpty())
    {
        QMessageBox::critical(this,tr("Error"),tr("Missing UserName!"));
        return;
    }
    if(this->m_lineEditPass->text().isEmpty())
    {
        QMessageBox::critical(this,tr("Error"),tr("Missing MagicKey!"));
        return;
    }

    //calculate md5 value.
    QString ming=QString("YanTai$$ZhangShaoYan")+this->m_lineEditUser->text();
    QByteArray bb=QCryptographicHash::hash (ming.toUtf8(), QCryptographicHash::Md5 );
    qDebug()<<bb.toHex();
    if(this->m_lineEditPass->text()!=QString(bb.toHex()))
    {
        QMessageBox::critical(this,tr("Error"),tr("Invalid MagicKey!"));
        return;
    }
    this->accept();
}
QString ZLoginDialog::ZGetUserName()
{
    return this->m_lineEditUser->text();
}
