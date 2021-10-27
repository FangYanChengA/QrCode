#include "ajb_socket.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QtEndian>
#include <QDateTime>
#include <QHostAddress>
#include <QMessageBox>

AJB_SocketControl::AJB_SocketControl(QWidget *parent)
{
    udpSocketInit();
    udpGetInfo = UDP_WAIT;
    udpPort = 9000;
    udpSocketbind(udpPort);
    msgid = 1;
    idreserve = 0;
}

AJB_SocketControl::~AJB_SocketControl()
{
    delete SocketUDPReadQueue;
    udpSocket.close();
}

void AJB_SocketControl::udpSocketInit()
{
   SocketUDPReadQueue = new Queue(1024*10);
}

void AJB_SocketControl::udpSocketbind(int port)
{
    udpSocket.bind(QHostAddress::AnyIPv4,port,QUdpSocket::ShareAddress);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(on_udpRecvMsgProc()));
}

void AJB_SocketControl::udpBroadRquest()
{
    char Data[1024]= {0};
    char packLen[12] = {0};
    int msgTopicAndMsgDataLen;
    int msgLen;
    QJsonObject jsonqrcode;
    jsonqrcode.insert("msg_id",msgid++);
    if(msgid >= 268435455)
        msgid = 1;
    QString topic ="/lan/gateway/qrcode\r\n";
    QJsonDocument jsonDoc(jsonqrcode);
    QByteArray bMsgData = jsonDoc.toJson(); //转换成文本

    QByteArray tp = topic.toLatin1();
    char* tpc = tp.data();
    msgTopicAndMsgDataLen = strlen(tpc) + bMsgData.size();

    msgLen = msgTopicAndMsgDataLen + 12;
    qDebug() << msgLen;
    qDebug() << "send data:" << bMsgData;
    msgTopicAndMsgDataLen = qToBigEndian(msgTopicAndMsgDataLen);
    memcpy( packLen,"PACKLEN:",8);
    memcpy( &packLen[8],&msgTopicAndMsgDataLen,4);
    memcpy(Data,packLen,12);
    memcpy(&Data[12],tpc,strlen(tpc));
    memcpy(&Data[12 +strlen(tpc)],bMsgData.data(),bMsgData.size());
    udpSocket.writeDatagram(Data,msgLen,QHostAddress::Broadcast,9000);
}

void AJB_SocketControl::udpBroadRquest(QString &senddata)
{
    //udpSocket.writeDatagram(senddata.data(),senddata.length(),QHostAddress::Broadcast,udpPort);
}

void AJB_SocketControl::on_udpRecvMsgProc()
{
    QByteArray datagram;
    QString tempGet;
    // 拥有等待的数据报
    while(udpSocket.hasPendingDatagrams())    //hasPendingDatagrams()判断是否还有等待的数据报
    {
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(udpSocket.pendingDatagramSize());//pendingDatagramSize() 当前数据包大小
        udpSocket.readDatagram(datagram.data(), datagram.size());//readDatagram将不大于指定长度的数据保存到datagram.data()
        // 接收数据报，将其存放到datagram中
        SocketUDPReadQueue->WriteDataToQueue(datagram.data(),datagram.size());
        qDebug() << " UDP datagram.size()" << datagram.size();
    }

    while(SocketUDPReadQueue->GetQueueDataSize() >0)
    {
       if(on_DecodeudpData())
       {
            if(udpGetInfo == UDP_ERROR)
            {
                QMessageBox msgBox;
                msgBox.setText("请停止打印并检查局域网段是否连接多个网关!");
                msgBox.setStandardButtons(QMessageBox::Ok);
                msgBox.exec();
                SocketUDPReadQueue->DelectDataFromQueue(SocketUDPReadQueue->GetQueueDataSize());
                break;
            }
            tempGet.clear();
            tempGet = qrcodeInfo;
            //udpGetInfo = UDP_GETDATA;
       }
    }
}

UdpState AJB_SocketControl::udpGetReady()
{
    return udpGetInfo;
}

void AJB_SocketControl::udpBackToWait()
{
    udpGetInfo = UDP_WAIT;
}

QString AJB_SocketControl::udpGetPart(QString info,char *sense,unsigned int sensenum)
{
    QString stemp;
    QString part;
    stemp=info;
    int pos;
    pos = stemp.indexOf(sense,0);
    stemp.remove(0,pos+sensenum+1);
    pos = stemp.indexOf("]",0);
    part = stemp.left(pos);
    return part;
}

bool AJB_SocketControl::on_DecodeudpData()
{
    char Head[14] = {0};
    char msgData[1024*2] = {0};
    char msgTopic[64] = {0};
    QJsonParseError json_error;
    char *jsonData;
    int i = 0;
    int tempid = 0;
    //开始数据解析
    if( SocketUDPReadQueue->GetQueueDataSize() > 12 )
    {
        unsigned int msgLen;
        SocketUDPReadQueue->ReadDataFromQueue(0,Head,14);
        if(  0 == memcmp(Head,"PACKLEN:",8) )
        {
            memcpy( &msgLen,&Head[8],4);
            msgLen = qToBigEndian(msgLen);
            qDebug() << "msgLen:" << msgLen;
            if( SocketUDPReadQueue->GetQueueDataSize() >= (12 + msgLen) )
            {
                unsigned int len =SocketUDPReadQueue->ReadDataFromQueue(12,msgData,msgLen);
                qDebug() << "get info:" << msgData;
                while( '\r' != msgData[i] && i<64 )
                {
                    msgTopic[i] = msgData[i];
                    i++;
                }
                if(strlen(msgTopic) >0 && 0 == strcmp("/lan/gateway/qrcode_reply",msgTopic))
                {
                    jsonData = msgData + strlen(msgTopic) + 2;
                    QJsonDocument  jsonDoc = QJsonDocument::fromJson( jsonData, &json_error );
                    QJsonObject severinfo= jsonDoc.object();
                    qrcodeInfo.clear();
                    //crcInfo.clear();
                    ethmac.clear();
                    wlanmac.clear();
                    QString tempStr;
                    tempStr = severinfo["qr_info"].toString();
                    if(tempStr.contains("qrinfo"))
                        qrcodeInfo = udpGetPart(tempStr,"qrinfo",6);
                    else
                        qrcodeInfo = tempStr;
                    //crcInfo = severinfo["crc"].toString();
                    ethmac = severinfo["mac_eth0"].toString();
                    wlanmac = severinfo["mac_wlan0"].toString();
                    tempid = severinfo["msg_id"].toInt();
                    qDebug() << "qrcodeInfo:" << qrcodeInfo;
                    //qDebug() << "crcInfo:" << crcInfo;
                    if(qrcodeInfo.size() > 0)
                    {
                        if(tempid == idreserve)
                        {
                            //udpGetInfo = UDP_ERROR;
                            udpGetInfo = UDP_GETDATA;
                        }
                        else
                        {
                            udpGetInfo = UDP_GETDATA;
                        }
                        idreserve = tempid;
                        SocketUDPReadQueue->DelectDataFromQueue(msgLen+12);
                        return true;
                    }
                    else
                    {
                        SocketUDPReadQueue->DelectDataFromQueue(msgLen+12);
                        return false;
                    }
                }
                else
                {
                    SocketUDPReadQueue->DelectDataFromQueue(msgLen+12);
                    return false;
                }
            }
        }
    }
    SocketUDPReadQueue->DelectDataFromQueue(1);
    return false;
}
