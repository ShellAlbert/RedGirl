#ifndef ZLOGINDIALOG_H
#define ZLOGINDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QToolButton>
#include <QLineEdit>
#include <QGridLayout>
class ZLoginDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ZLoginDialog(QWidget *parent = 0);
    ~ZLoginDialog();
    QString ZGetUserName();
signals:

public slots:
    void ZSlotVerifyMagicKey();
private:
    QLabel *m_labelLoginBanner;
    QLabel *m_labelPenguin;
    QLineEdit *m_lineEditUser;
    QLineEdit *m_lineEditPass;
    QGridLayout *m_gridLayout;
    QToolButton *m_btnLogin;
    QToolButton *m_btnExit;
    QHBoxLayout *m_hLayoutBtn;
    QVBoxLayout *m_vLayoutMain;
};

#endif // ZLOGINDIALOG_H
