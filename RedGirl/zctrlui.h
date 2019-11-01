#ifndef ZCTRLUI_H
#define ZCTRLUI_H

#include <QFrame>
#include <QLabel>
#include <QToolButton>
#include <QGridLayout>
#include <QTimer>
class ZCtrlUI : public QFrame
{
    Q_OBJECT
public:
    explicit ZCtrlUI(QWidget *parent = 0);
    ~ZCtrlUI();
signals:
    void ZSignalStartService();
    void ZSignalStopService();
public slots:
    void ZSlotTimeout1s();
    void ZSlotStartService();
    void ZSlotStopService();
    void ZSlotExitApp();
    void ZSlotErrMsg(QString errMsg);
    ///////////////////
    void ZSlotUpdateDutyOnCounter(qint32 ret);
    void ZSlotUpdateDutyOffCounter(qint32 ret);
    void ZSlotUpdateEmailCounter(qint32 ret);
private:
    QLabel *m_labelCurTimeTip;
    QLabel *m_labelCurTime;
    QLabel *m_labelRunTimeTip;
    QLabel *m_labelRunTime;
    ////////////////////////////////
    QLabel *m_labelAMTotalTips;
    QLabel *m_labelAMTotal;
    QLabel *m_labelAMSuccessTips;
    QLabel *m_labelAMSuccess;
    /////////////////////////////////
    QLabel *m_labelPMTotalTips;
    QLabel *m_labelPMTotal;
    QLabel *m_labelPMSuccessTips;
    QLabel *m_labelPMSuccess;
    //////////////////////////////
    QLabel *m_labelAliveEmailTotalTips;
    QLabel *m_labelAliveEmailTotal;
    QLabel *m_labelAliveEmailSuccessTips;
    QLabel *m_labelAliveEmailSuccess;
    ///////////////////////////
    QToolButton *m_btnStart;
    QToolButton *m_btnExit;
    QGridLayout *m_gridLayout;
    ////////////
    QTimer *m_timer;
    qint32 m_runCounter;
    bool m_bCountRunTime;

    /////////////////////
    qint32 m_AMTotal;
    qint32 m_AMSuccess;
    qint32 m_PMTotal;
    qint32 m_PMSuccess;
    qint32 m_AliveEmailTotal;
    qint32 m_AliveEmailSuccess;
};

#endif // ZCTRLUI_H
