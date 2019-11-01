#ifndef ZWEEKELEMENT_H
#define ZWEEKELEMENT_H

#include <QFrame>
#include <QLabel>
#include <QTimeEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <zconfiginfo.h>
#include <OALib/oacontrol.h>
#include <QTimer>
class ZWeekElement : public QFrame
{
    Q_OBJECT
public:
    explicit ZWeekElement(QWidget *parent = 0);
    ~ZWeekElement();

    void ZLoadConfigFile();
    void ZSaveConfigFile();
signals:
    void ZSignalErrMsg(QString errMsg);
    void ZSignalDutyOn(qint32 ret);
    void ZSignalDutyOff(qint32 ret);
public slots:
    void ZSlotEnableDayComponents(bool en);
    void ZSlotTimeout1s();
    void ZSlotStartService();
    void ZSlotStopService();
private:
    void ZPostDutyOn();
    void ZPostDutyOff();
private:
    QCheckBox *m_checkboxDayEnabled[7];
    QLabel *m_labelOn[7];
    QTimeEdit *m_timeOnTime[7];
    QCheckBox *m_checkBoxAutoExitOn[7];
    QLabel *m_labelOff[7];
    QTimeEdit *m_timeOffTime[7];
    QCheckBox *m_checkBoxAutoExitOff[7];
    QLabel *m_labelSplitLine[7];
    QGridLayout *m_gLayoutMain;
    /////////////////////////
    ////////////////////
    OAControl *m_OAObj;
    QTimer *m_timer;

};

#endif // ZWEEKELEMENT_H
