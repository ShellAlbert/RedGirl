#-------------------------------------------------
#
# Project created by QtCreator 2016-02-04T14:38:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OAKiller
TEMPLATE = app


SOURCES += main.cpp\
        zmainwidget.cpp \
    zweekelement.cpp \
    zctrlui.cpp \
    zmailnotify.cpp \
    zoaset.cpp \
    zconfiginfo.cpp \
    SMTPLib/emailaddress.cpp \
    SMTPLib/mimeattachment.cpp \
    SMTPLib/mimecontentformatter.cpp \
    SMTPLib/mimefile.cpp \
    SMTPLib/mimehtml.cpp \
    SMTPLib/mimeinlinefile.cpp \
    SMTPLib/mimemessage.cpp \
    SMTPLib/mimemultipart.cpp \
    SMTPLib/mimepart.cpp \
    SMTPLib/mimetext.cpp \
    SMTPLib/quotedprintable.cpp \
    SMTPLib/smtpclient.cpp \
    OALib/oacontrol.cpp \
    zlogindialog.cpp

HEADERS  += zmainwidget.h \
    zweekelement.h \
    zctrlui.h \
    zmailnotify.h \
    zqssname.h \
    zoaset.h \
    zconfiginfo.h \
    SMTPLib/emailaddress.h \
    SMTPLib/mimeattachment.h \
    SMTPLib/mimecontentformatter.h \
    SMTPLib/mimefile.h \
    SMTPLib/mimehtml.h \
    SMTPLib/mimeinlinefile.h \
    SMTPLib/mimemessage.h \
    SMTPLib/mimemultipart.h \
    SMTPLib/mimepart.h \
    SMTPLib/mimetext.h \
    SMTPLib/quotedprintable.h \
    SMTPLib/smtpclient.h \
    SMTPLib/smtpexports.h \
    OALib/oa_parameter.h \
    OALib/oacontrol.h \
    zlogindialog.h

RESOURCES += \
    OARes.qrc



OTHER_FILES += \
    resource/OASkin.txt

RC_FILE += OAKiller.rc



win32: LIBS += -L$$PWD/../libcurl/lib/ -lcurl

INCLUDEPATH += $$PWD/../libcurl/include
DEPENDPATH += $$PWD/../libcurl/include

