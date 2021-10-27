#include "uart.h"
#include <QMessageBox>
#include <QCryptographicHash>

uart::uart()
{
    connect = false;
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);
}

uart::~uart()
{

}

void uart::Uart_FindAllUart()
{
    namelist.clear();
    //使用foreach 获取到每一个串口信息
    foreach(const QSerialPortInfo &Info,QSerialPortInfo ::availablePorts())
    {
        QSerialPort CurrentPort;
        CurrentPort.setPort(Info);
        //if(CurrentPort.open(QIODevice::ReadWrite))
        {
            namelist.append( CurrentPort.portName() );
            qDebug() << "Info:" << Info.portName() << "CurrentPort：" << CurrentPort.portName();
            //CurrentPort.close();   //先开再关，把串口名称先导入
        }
    }
}

bool uart::Uart_Connect()
{
    if(connect == false)
    {
        serial.setPortName(serial_name);
        int buardnum = buard.toInt();
        qDebug() << "buard:" <<  buardnum;
        if(buardnum != 9600 && buardnum != 115200 && buardnum != 19200 && buardnum != 38400)
            return false;
        serial.setBaudRate(buardnum);
        if(serial.open(QIODevice::ReadWrite))
        {
            connect = true;
            return true;
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("open uart error!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.exec();
            return false;
        }
    }
    return false;
}

bool uart::Uart_Disconnect()
{
    if(connect == true)
    {
        serial.close();
        connect = false;
        return true;
    }
    return false;
}

unsigned int uart::Uart_Received(Queue* queuelist)
{
    QByteArray datagram;
    char temp[1024] = {0};
    long long res;
    //res = serial.read(temp,1024);
    //qDebug() << "res = " << res <<"read:" << temp;
    datagram.append(serial.readAll());
    //qDebug() << "get:" << datagram;
    return queuelist->WriteDataToQueue(datagram.data(),datagram.size());
}

#if 0
void Uart_Send(char *data,long long length)
{
    serial.writeData(data,length);
}
#endif

#define POLY        0x1021

unsigned short uart::Uart_Crc16(char *addr, int num )
{
    unsigned short crc = 0;
    int i,j;
    for (j = num; j > 0; j--)              /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << 8);     /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)             /* Prepare to rotate 8 bits */
        {
            if (crc & 0x8000)            /* b15 is set... */
                crc = (crc << 1) ^ POLY;    /* rotate and XOR with polynomic */
            else                          /* b15 is clear... */
                crc <<= 1;                  /* just rotate */
        }                             /* Loop for 8 bits */
        crc &= 0xFFFF;                  /* Ensure CRC remains 16-bit value */
    }                               /* Loop until num=0 */
    return(crc);                    /* Return updated CRC */
}

QString uart::Uart_GetPart(char *info,char *sense,unsigned int sensenum)
{
    QString stemp;
    QString part;
    stemp.append(info);
    int pos;
    pos = stemp.indexOf(sense,0);
    stemp.remove(0,pos+sensenum+1);
    pos = stemp.indexOf("]",0);
    part = stemp.left(pos);
    return part;
}

void uart::Uart_ParseGatewayInfo(char *info,unsigned int num)
{
    //uart_qrinfo.append(info);
    uart_qrinfo = Uart_GetPart(info,"qrinfo",6);
    uart_ethmac = Uart_GetPart(info,"ethmac",6);
    uart_wlanmac = Uart_GetPart(info,"wlanmac",7);
    int begin = uart_qrinfo.indexOf("%");
    int second = uart_qrinfo.indexOf("%",begin+1);
    uart_gwid = uart_qrinfo.mid(second+1,8);
}

bool uart::Uart_ParseInfo(char *info,unsigned int num)
{
    char szinfo[256] = {0};
    char szmd[64] = {0};
    char *readpos = info;
    char *codeendpos = NULL;
    int codelength = 0;
    int md5length = 0;
    QByteArray getmd;
    QByteArray calmd;

    uart_qrinfo.clear();
    uart_gwid.clear();
    uart_ethmac.clear();
    uart_wlanmac.clear();

    while(readpos[0] != '\0' && readpos-info < num -2)
    {
        if(readpos[0] == '*' && readpos[1] == '#')
        {
            readpos += 2;
            codeendpos = readpos;
            while(codeendpos[0] != '*' && codeendpos[1] != '#')
            {
                codeendpos++;
                if(codeendpos[0] == '\0')
                    break;
            }
            if(codeendpos[0] != '\0')
            {
                codelength = codeendpos - readpos;
                memcpy(szinfo,readpos,codelength);
                codeendpos+=4;
                if(codeendpos[0] == '\0')
                {
                    return false;
                }
                readpos = codeendpos;
                while(codeendpos[0] != '*' && codeendpos[1] != '#')
                {
                    codeendpos++;
                    if(codeendpos[0] == '\0')
                        break;
                }
                if(codeendpos[0] != '\0')
                {
                    md5length = codeendpos - readpos;
                    memcpy(szmd,readpos,md5length);
                    getmd.append(szmd);
                    QCryptographicHash hash(QCryptographicHash::Md5);
                    hash.addData(szinfo,strlen(szinfo));
                    calmd = hash.result();
                    calmd = calmd.toHex();
                    if(calmd == getmd)
                    {
                        Uart_ParseGatewayInfo(szinfo,codelength);
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else
        {
            readpos += 1;
        }
    }
    return false;
}
