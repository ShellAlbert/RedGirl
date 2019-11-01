#ifndef ZMAILNOTIFY_H
#define ZMAILNOTIFY_H

#include <QFrame>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QToolButton>
#include <zconfiginfo.h>
#include <QTimer>
class ZMailNotify : public QFrame
{
    Q_OBJECT
public:
    explicit ZMailNotify(QWidget *parent = 0);
    ~ZMailNotify();

    void ZLoadConfigFile();
    void ZSaveConfigFile();
signals:
    void ZSignalErrMsg(QString errMsg);
    void ZSignalEmailSended(qint32 ret);
public slots:
    void ZSlotSendTestEmail();

    void ZSlotTimeout1s();
    void ZSlotStartService();
    void ZSlotStopService();

    void ZSlotEmailNotifyDutyOn(qint32 ret);
    void ZSlotEmailNotifyDutyOff(qint32 ret);
private:
    qint32 ZSendEmail(QString subject,QString message);
private:
    QLabel *m_labelMailServer;
    QLabel *m_labelSMTP;
    QLineEdit *m_lineEditSMTP;
    QLabel *m_labelSender;
    QLineEdit *m_lineEditSender;
    QLabel *m_labelSendPass;
    QLineEdit *m_lineEditSendPass;
    QToolButton *m_btnTest;
    QHBoxLayout *m_hLayoutMailServer;
    /////////////////////////////
    QLabel *m_labelMailReceiver;
    QLineEdit *m_lineEditMailReceiver;
    QHBoxLayout *m_hLayoutMailRecv;
    ////////////////////////////
    QLabel *m_labelNotify;
    QCheckBox *m_checkBoxAlive;
    QCheckBox *m_checkBoxFeedBack;
    QHBoxLayout *m_hLayoutNotify;
    ////////////////////////////
    QVBoxLayout *m_vLayoutMain;

    ////////////
    QTimer *m_timer;
    qint32 m_aliveCounter;
};

#endif // ZMAILNOTIFY_H
