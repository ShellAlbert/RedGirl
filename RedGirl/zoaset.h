#ifndef ZOASET_H
#define ZOASET_H

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTreeWidget>
#include <zconfiginfo.h>
class ZOASet : public QFrame
{
    Q_OBJECT
public:
    explicit ZOASet(QWidget *parent = 0);
    ~ZOASet();

    void ZLoadConfigFile();
    void ZSaveConfigFile();
signals:

public slots:
    void ZSlotStartService();
    void ZSlotStopService();
private:
    QLabel *m_labelHeadOA;
    QLabel *m_labelOAIP;
    QLineEdit *m_lineEditOAIP;
    QLabel *m_labelUserName;
    QLineEdit *m_lineEditUserName;
    QLabel *m_labelUserPass;
    QLineEdit *m_lineEditUserPass;
    QGridLayout *m_gLayoutServer;
    /////////////////////////
    QLabel *m_labelHeadSet;
    QLabel *m_labelPostOnTimes;
    QSpinBox *m_spinBoxPostOnTimes;
    QLabel *m_labelPostOffTimes;
    QSpinBox *m_spinBoxPostOffTimes;
    QGridLayout *m_gLayoutOption;
    /////////////////////////
    QVBoxLayout *m_vLayoutMain;


};

#endif // ZOASET_H
