#ifndef AJB_SOCKET_H
#define AJB_SOCKET_H

#include <QWidget>
#include <QTcpSocket>
#include <QUdpSocket>
#include "ajb_common/queue.h"

enum UdpState {
    UDP_WAIT,
    UDP_GETDATA,
    UDP_ERROR,
};

class AJB_SocketControl:public QWidget
{
    Q_OBJECT

public:
    explicit AJB_SocketControl(QWidget *parent = 0);
    ~AJB_SocketControl();
    QUdpSocket udpSocket;
    Queue* SocketUDPReadQueue;
    int udpPort;
    QString qrcodeInfo;
    QString crcInfo;
    QString ethmac;
    QString wlanmac;
    UdpState udpGetInfo;
    int msgid;
    int idreserve;
public:
    void udpSocketbind(int port);

    void udpSocketInit();

    void udpBroadRquest();

    void udpBroadRquest(QString &senddata);

    UdpState udpGetReady();

    void udpBackToWait();
signals:

private slots:
    void on_udpRecvMsgProc();

private:
    QString udpGetPart(QString info,char *sense,unsigned int sensenum);
    bool on_DecodeudpData();
};

#endif
