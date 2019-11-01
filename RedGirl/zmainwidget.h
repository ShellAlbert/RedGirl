#ifndef ZMAINWIDGET_H
#define ZMAINWIDGET_H

#include <QWidget>
#include <zctrlui.h>
#include <zoaset.h>
#include <zweekelement.h>
#include <zmailnotify.h>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QMovie>
class ZMainWidget : public QWidget
{
    Q_OBJECT

public:
    ZMainWidget(QWidget *parent = 0);
    ~ZMainWidget();
protected:
    void closeEvent(QCloseEvent *);
private:
    QLabel *m_labelBanner;
    QMovie *m_movieGif;
    ZCtrlUI *m_ctrl;
    ZOASet *m_oa;
    ZWeekElement *m_week;
    ZMailNotify *m_mail;
    QTabWidget *m_tab;
    QVBoxLayout *m_vLayoutMain;
};

#endif // ZMAINWIDGET_H
