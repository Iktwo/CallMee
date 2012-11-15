#include "autoanswer.h"

#include <QtDBus>
#include <QTimer>
#include <gq/gconfitem.h>

#define CSD_CALL_STATUS_IDLE			       0
#define CSD_CALL_STATUS_CREATE			       1
#define CSD_CALL_STATUS_COMING			       2
#define CSD_CALL_STATUS_PROCEEDING		       3
#define CSD_CALL_STATUS_MO_ALERTING		       4
#define CSD_CALL_STATUS_MT_ALERTING		       5
#define CSD_CALL_STATUS_WAITING			       6
#define CSD_CALL_STATUS_ANSWERED		       7
#define CSD_CALL_STATUS_ACTIVE			       8
#define CSD_CALL_STATUS_MO_RELEASE		       9
#define CSD_CALL_STATUS_MT_RELEASE		       10
#define CSD_CALL_STATUS_HOLD_INITIATED		   11
#define CSD_CALL_STATUS_HOLD			       12
#define CSD_CALL_STATUS_RETRIEVE_INITIATED	   13
#define CSD_CALL_STATUS_RECONNECT_PENDING	   14
#define CSD_CALL_STATUS_TERMINATED		       15
#define CSD_CALL_STATUS_SWAP_INITIATED		   16

#define SIP_CALL_DIALING                1
#define SIP_CALL_ACTIVE                 3
#define SIP_CALL_DEACTIVE               5

AutoAnswer::AutoAnswer() : autoAnswering(false),delayTime(0){

    activeKey = new GConfItem("/apps/Callmee/Active");
    autoAnswering = activeKey->value().toBool();

    delayKey = new GConfItem("/apps/Callmee/Delay");
    delayTime = delayKey->value().toInt();

    connect(activeKey,SIGNAL(valueChanged()),this,SLOT(updateActiveKeyValue()));
    connect(delayKey,SIGNAL(valueChanged()),this,SLOT(updateDelayKeyValue()));

    csdIface = new QDBusInterface("com.nokia.csd.Call","/com/nokia/csd/call/1","com.nokia.csd.Call.Instance",QDBusConnection::systemBus());

    connect(csdIface,SIGNAL(CallStatus(uint,uint,uint)),this,SLOT(csdStatusUpdate(uint,uint,uint)));
}

void AutoAnswer::updateActiveKeyValue()
{
    autoAnswering = activeKey->value().toBool();
}

void AutoAnswer::updateDelayKeyValue()
{
    delayTime = delayKey->value().toInt();
}

void AutoAnswer::csdStatusUpdate(uint status,uint b,uint c)
{
    if (autoAnswering && (status == CSD_CALL_STATUS_MT_ALERTING)){
        QTimer::singleShot(delayTime*1000, this, SLOT(takeCall()));
    }
}

void AutoAnswer::takeCall()
{
    //qDebug() << "Taking call";
    csdIface->call("Answer");
}
