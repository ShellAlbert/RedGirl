#include "zmailnotify.h"
#include <SMTPLib/SmtpMime>
#include <QMessageBox>
#include <QDateTime>
#include <zconfiginfo.h>
ZMailNotify::ZMailNotify(QWidget *parent) :
    QFrame(parent)
{
    this->m_labelMailServer=new QLabel(tr("SMTP Mail Server"));
    //////////////////////////////////////////////
    this->m_labelSMTP=new QLabel(tr("SMTP Address"));
    this->m_lineEditSMTP=new QLineEdit;
    this->m_labelSender=new QLabel(tr("Sender"));
    this->m_lineEditSender=new QLineEdit;
    this->m_labelSendPass=new QLabel(tr("Password"));
    this->m_lineEditSendPass=new QLineEdit;
    this->m_lineEditSendPass->setEchoMode(QLineEdit::Password);
    this->m_btnTest=new QToolButton;
    this->m_btnTest->setText(tr("Test"));
    this->m_hLayoutMailServer=new QHBoxLayout;
    this->m_hLayoutMailServer->addWidget(this->m_labelSMTP);
    this->m_hLayoutMailServer->addWidget(this->m_lineEditSMTP);
    this->m_hLayoutMailServer->addWidget(this->m_labelSender);
    this->m_hLayoutMailServer->addWidget(this->m_lineEditSender);
    this->m_hLayoutMailServer->addWidget(this->m_labelSendPass);
    this->m_hLayoutMailServer->addWidget(this->m_lineEditSendPass);
    /////////////////////////////
    this->m_labelMailReceiver=new QLabel(tr("Receiver"));
    this->m_lineEditMailReceiver=new QLineEdit;
    this->m_hLayoutMailRecv=new QHBoxLayout;
    this->m_hLayoutMailRecv->addWidget(this->m_labelMailReceiver);
    this->m_hLayoutMailRecv->addWidget(this->m_lineEditMailReceiver);
    this->m_hLayoutMailRecv->addWidget(this->m_btnTest);
    ////////////////////////////
    this->m_labelNotify=new QLabel(tr("Feedback Notification"));
    this->m_checkBoxAlive=new QCheckBox(tr("Send alive email every 30 minutes"));
    this->m_checkBoxFeedBack=new QCheckBox(tr("Send post on/off result"));
    this->m_hLayoutNotify=new QHBoxLayout;
    this->m_hLayoutNotify->addWidget(this->m_checkBoxAlive);
    this->m_hLayoutNotify->addWidget(this->m_checkBoxFeedBack);
    ////////////////////////////
    this->m_vLayoutMain=new QVBoxLayout;
    this->m_vLayoutMain->addWidget(this->m_labelMailServer);
    this->m_vLayoutMain->addLayout(this->m_hLayoutMailServer);
    this->m_vLayoutMain->addLayout(this->m_hLayoutMailRecv);
    this->m_vLayoutMain->addWidget(this->m_labelNotify);
    this->m_vLayoutMain->addLayout(this->m_hLayoutNotify);
    this->setLayout(this->m_vLayoutMain);

    this->ZLoadConfigFile();

    connect(this->m_btnTest,SIGNAL(clicked()),this,SLOT(ZSlotSendTestEmail()));

    this->m_timer=new QTimer;
    connect(this->m_timer,SIGNAL(timeout()),this,SLOT(ZSlotTimeout1s()));
    this->m_timer->setInterval(1000);

    this->m_lineEditSMTP->setEnabled(false);
    this->m_lineEditSender->setEnabled(false);
    this->m_lineEditSendPass->setEnabled(false);
}
ZMailNotify::~ZMailNotify()
{
    delete this->m_labelMailServer;
    delete this->m_labelSMTP;
    delete this->m_lineEditSMTP;
    delete this->m_labelSender;
    delete this->m_lineEditSender;
    delete this->m_labelSendPass;
    delete this->m_lineEditSendPass;
    delete this->m_hLayoutMailServer;
    ///////////////
    delete this->m_labelMailReceiver;
    delete this->m_lineEditMailReceiver;
    delete this->m_btnTest;
    delete this->m_hLayoutMailRecv;
    //////////////////////////////
    delete this->m_labelNotify;
    delete this->m_checkBoxAlive;
    delete this->m_checkBoxFeedBack;
    delete this->m_hLayoutNotify;
    ////////////////////////
    delete this->m_vLayoutMain;
}
void ZMailNotify::ZLoadConfigFile()
{
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    this->m_lineEditSMTP->setText(pConfig->EmailSMTPAddr);
    this->m_lineEditSender->setText(pConfig->EmailSender);
    this->m_lineEditSendPass->setText(pConfig->EmailSenderPassword);
    this->m_checkBoxAlive->setChecked(pConfig->AliveEmailEnabled);
    this->m_checkBoxFeedBack->setChecked(pConfig->PostResultEnabled);
}
void ZMailNotify::ZSaveConfigFile()
{
    ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
    pConfig->EmailSMTPAddr=this->m_lineEditSMTP->text();
    pConfig->EmailSender=this->m_lineEditSender->text();
    pConfig->EmailSenderPassword=this->m_lineEditSendPass->text();
    pConfig->AliveEmailEnabled=this->m_checkBoxAlive->isChecked()?1:0;
    pConfig->PostResultEnabled=this->m_checkBoxFeedBack->isChecked()?1:0;
}
void ZMailNotify::ZSlotTimeout1s()
{
    this->m_aliveCounter++;
    qDebug()<<"MailNotify:"<<this->m_aliveCounter;
    if(this->m_aliveCounter>30*60)
    {
        qDebug()<<"send email to notify that I'm alive";
        //send email to tell that I'm alive.
        ZConfigInfo *pConfig=ZConfigInfo::ZGetInstance();
        QString subject(tr("OAKiller Alive Notification"));
        QString msgBody;
        msgBody+=tr("OA Server:")+pConfig->OAIPAddr+tr("\n");
        msgBody+=tr("UserName:")+pConfig->OAUserName+tr("\n");
        msgBody+=tr("Password:")+pConfig->OAPassword+tr("\n");
        msgBody+=tr("I'm alive!");
        qint32 retry=3;
        while(retry>0)
        {
            if(!this->ZSendEmail(subject,msgBody))
            {
                break;
            }
            retry--;
        }
        //reset counter.
        this->m_aliveCounter=0;
    }
}
void ZMailNotify::ZSlotStartService()
{
    //update current setting to config object.
    this->ZSaveConfigFile();
    //disable all componenets.
    this->m_lineEditSMTP->setEnabled(false);
    this->m_lineEditSender->setEnabled(false);
    this->m_lineEditSendPass->setEnabled(false);
    this->m_btnTest->setEnabled(false);
    this->m_checkBoxAlive->setEnabled(false);
    this->m_checkBoxFeedBack->setEnabled(false);
    //start schedule timer.
    this->m_aliveCounter=0;
    this->m_timer->start();
}
void ZMailNotify::ZSlotStopService()
{
    //enable all components.
    this->m_lineEditSMTP->setEnabled(true);
    this->m_lineEditSender->setEnabled(true);
    this->m_lineEditSendPass->setEnabled(true);
    this->m_btnTest->setEnabled(true);
    this->m_checkBoxAlive->setEnabled(true);
    this->m_checkBoxFeedBack->setEnabled(true);
    //stop schedule timer.
    this->m_timer->stop();
}
void ZMailNotify::ZSlotSendTestEmail()
{
    QString subjectMsg("OAKiller Email Test Notification");
    QString mailMsg;
    mailMsg+=tr("This is a test email.\n");
    mailMsg+=tr("It's used to test the capability of OAKiller email sending.\n");
    qint32 ret=this->ZSendEmail(subjectMsg,mailMsg);
    if(ret<0)
    {
        switch(ret)
        {
        case -1:
            QMessageBox::critical(this,tr("Error"),tr("Failed to connect to host!"));
            break;
        case -2:
            QMessageBox::critical(this,tr("Error"),tr("Failed to login!"));
            break;
        case -3:
            QMessageBox::critical(this,tr("Error"),tr("Failed to send mail!"));
            break;
        default:
            break;
        }
    }
    QMessageBox::information(this,tr("Success"),tr("Send test mail successfully!"));
}

qint32 ZMailNotify::ZSendEmail(QString subject,QString msgbody)
{
    qint32 ret=0;
    // First we need to create an SmtpClient object
    // We will use the Gmail's smtp server (smtp.163.com, port 465, ssl)
    SmtpClient smtp(this->m_lineEditSMTP->text(), 465, SmtpClient::SslConnection);

    // We need to set the username (your email address) and password
    // for smtp authentification.

    //smtp.setUser("13522296239@163.com");
    //smtp.setPassword("qwer1234");
    smtp.setUser(this->m_lineEditSender->text());
    smtp.setPassword(this->m_lineEditSendPass->text());

    // Now we create a MimeMessage object. This is the email.
    MimeMessage message;

    EmailAddress sender(this->m_lineEditSender->text(), this->m_lineEditSender->text());
    message.setSender(&sender);

    EmailAddress to(this->m_lineEditMailReceiver->text(), this->m_lineEditMailReceiver->text());
    message.addRecipient(&to);

    message.setSubject(subject);

    // Now add some text to the email.

    QString mailMsg;
    mailMsg+=msgbody;
    mailMsg+=tr("\n");
    mailMsg+=tr("Created on ")+QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss")+tr("\n");

    // First we create a MimeText object.
    MimeText text;
    text.setText(mailMsg);

    // Now add it to the mail
    message.addPart(&text);

    do{
        // Now we can send the mail
        if (!smtp.connectToHost()) {
            qDebug()<<"failed to connect to host!";
            ret=-1;
            break;
        }

        if (!smtp.login()) {
            qDebug()<<"failed to login.";
            ret=-2;
            break;
        }

        if (!smtp.sendMail(message)) {
            qDebug()<<"failed to send email.";
            ret=-3;
            break;
        }
    }while(0);
    smtp.quit();
    emit this->ZSignalEmailSended(ret);
    return ret;
}

void ZMailNotify::ZSlotEmailNotifyDutyOn(qint32 ret)
{
    if(this->m_checkBoxFeedBack->isChecked())
    {
        if(!ret)
        {
            this->ZSendEmail(tr("DutyOn"),tr("Success!"));
        }else{
            this->ZSendEmail(tr("DutyOn"),tr("Failed!"));
        }
    }
}
void ZMailNotify::ZSlotEmailNotifyDutyOff(qint32 ret)
{
    if(this->m_checkBoxFeedBack->isChecked())
    {
        if(!ret)
        {
            this->ZSendEmail(tr("DutyOff"),tr("Success!"));
        }else{
            this->ZSendEmail(tr("DutyOff"),tr("Failed!"));
        }
    }
}
