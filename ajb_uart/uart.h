#ifndef UART_H
#define UART_H
#include <QSerialPort>           //提供访问串口的功能
#include <QSerialPortInfo>    //提供系统中存在的串口的信息
#include <QVector>
#include <QObject>
#include <QDebug>
#include "ajb_common/queue.h"

class uart
{
public:
    uart();
    ~uart();
    QSerialPort serial;
    QString buard;
    QString serial_name;
    QVector<QString> namelist;
    bool connect;

    // parse info
    QString uart_qrinfo;
    QString uart_gwid;
    QString uart_ethmac;
    QString uart_wlanmac;

public:
    //QString Uart_Getcomm(int index, QString keyorvalue);
    void Uart_FindAllUart();
    bool Uart_Connect();
    bool Uart_Disconnect();
    unsigned int Uart_Received(Queue* queuelist);
    //void Uart_Send(char *data,long long length);

    unsigned short Uart_Crc16(char *addr, int num );
    bool Uart_ParseInfo(char *info,unsigned int num);

private:
    QString Uart_GetPart(char *info,char *sense,unsigned int sensenum);
    void Uart_ParseGatewayInfo(char *info,unsigned int num);
};

#endif // UART_H
