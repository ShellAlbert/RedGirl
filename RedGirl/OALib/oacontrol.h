#ifndef OACONTROL_H
#define OACONTROL_H
#include <QtGlobal>
#include <QString>
#include <string.h>

class MainWidget;
typedef struct
{
  char *buffer;
  unsigned int size;
} MemoryStruct;

//callback function to write data in memory.
extern int
WriteMemoryCallback (void *contents, size_t size, size_t nmemb, void *userp);
class OAControl
{
public:
    OAControl();
public:
    qint32
    postLoginInfoAndSaveCookie(QString username,QString password);
    qint32
    getLoginInfoAndSaveCookie(void);
    qint32
    getAttendanceTableAndSaveCookie(void);
    qint32
    postAttenanceOnAndSaveCookie(void);
    qint32
    postAttendanceOffAndSaveCookie(void);
};

#endif // OACONTROL_H
