#ifndef QUEUE_H
#define QUEUE_H

#include "ma_type.h"
#include <malloc.h>
#include <cstring>
#include <QByteArray>

#pragma pack(1)
typedef struct
{
    AJB_U32	 pReadSeat;   		//存放数据队列的位置
    AJB_U32	 pWriteSeat;		//获取数据队列的位置
    AJB_U32  Size;  		    //队列总容量的大小
    AJB_U32	 DataSize;	        //当前队列中数据容量的大小
    AJB_U32  EmptySize;
    char	 *Data;      		//队列数据存放地址
}Queue_t;//队列结构体
#pragma pack()

class Queue
{
public:
    Queue( AJB_U32 QueueSize );
    AJB_U32 DelectDataFromQueue( AJB_U32 Length );
    AJB_U32 WriteDataToQueue(char *Data, AJB_U32 Length );
    AJB_U32 WriteDataToQueue(QByteArray ByteData);
    AJB_U32 ReadDataFromQueue( AJB_U32 Offset,char *Data,AJB_U32 _Length );
    AJB_U32 GetQueueDataSize( AJB_VOID );
private:
    AJB_U32 GetQueueEmptySize( AJB_VOID );

    Queue_t queue;

};

#endif // QUEUE_H
