#include "queue.h"

#include <QDebug>
/*********************************************************************
 * @fn      Queue
 *
 * @brief   构造函数
 *
 * @param   QueueSize-->队列的数据长度
 *
 * 编写者    zyh
 *
 * 日  期    2016-12-25
 ********************************************************************/
Queue::Queue(AJB_U32 QueueSize)
{
    queue.Size          = QueueSize;
    queue.pReadSeat     = 0;
    queue.pWriteSeat    = 0;
    queue.DataSize      = 0;
    queue.EmptySize     = QueueSize;

    queue.Data = (char *)malloc(sizeof(char) * QueueSize );
}
/*********************************************************************
 * @fn      DelectDataFromQueue
 *
 * @brief   从当前队列中删除数据
 *
 * @param   Length-->删除数据的长度
 *
 * @return  实际删除Data的长度
 *
 * 编写者    zyh
 *
 * 日  期    2016-12-25
 ********************************************************************/
AJB_U32 Queue::DelectDataFromQueue(AJB_U32 Length)
{

    if( 0 == Length || 0 == queue.DataSize )  //当前队列为空或者读取的数据长度为零
    {
        return 0;
    }

    if( queue.DataSize < Length ) //核对最大可以删除的长度
    {
        Length = queue.DataSize ;
    }

    if( ( Length + queue.pReadSeat ) >=  queue.Size  )
    {
        queue.pReadSeat = Length + queue.pReadSeat - queue.Size ;
    }
    else
    {
        queue.pReadSeat += Length;
    }

    queue.EmptySize += Length;
    queue.DataSize -= Length;

    return Length;
}
/*********************************************************************
 * @fn      WriteDataToQueue
 *
 * @brief   写数据到队列中去
 *
 * @param   Data--->将要写人数据的指针
 *          Length-->将要写入数据的长度
 *
 * @return 实际写成功的数据长度
 *
 * 编写者    zyh
 *
 * 日  期    2016-12-25
 ********************************************************************/
AJB_U32 Queue::WriteDataToQueue(char *Data, AJB_U32 Length)
{
    if(0 == queue.EmptySize || NULL == Data )
    {
        return 0;
    }

    /*判断FIFO存储空间是否够*/
    if(Length > queue.EmptySize)
    {
        Length = queue.EmptySize;
    }

    if( ( queue.Size - queue.pWriteSeat) >= Length )//连续的空间足够
    {
        memcpy( &(queue.Data[queue.pWriteSeat]),Data,Length);
        queue.pWriteSeat += Length;
    }
    else
    {
        memcpy( &(queue.Data[queue.pWriteSeat]) ,Data ,queue.Size - queue.pWriteSeat );
        memcpy( &(queue.Data[0]) ,&(Data[queue.Size - queue.pWriteSeat]) ,Length + queue.pWriteSeat - queue.Size  );
        queue.pWriteSeat = Length + queue.pWriteSeat - queue.Size ;
    }

    queue.EmptySize -= Length;
    queue.DataSize += Length;

    return Length;   //返回成功写入成功的字节数
}

AJB_U32 Queue::WriteDataToQueue(QByteArray ByteData)
{
    char Data[1024];
    AJB_U32 Length = ByteData.count();

    if(0 == queue.EmptySize || 0 == Length )
    {
        return 0;
    }

    for(int i=0; i<Length; i++ )
    {
        Data[i] = ByteData[i];
    }

    /*判断FIFO存储空间是否够*/
    if(Length > queue.EmptySize)
    {
        Length = queue.EmptySize;
    }

    if( ( queue.Size - queue.pWriteSeat) >= Length )//连续的空间足够
    {
        memcpy( &(queue.Data[queue.pWriteSeat]),Data,Length);
        queue.pWriteSeat += Length;
    }
    else
    {
        memcpy( &(queue.Data[queue.pWriteSeat]) ,Data ,queue.Size - queue.pWriteSeat );
        memcpy( &(queue.Data[0]) ,&(Data[queue.Size - queue.pWriteSeat]) ,Length + queue.pWriteSeat - queue.Size  );
        queue.pWriteSeat = Length + queue.pWriteSeat - queue.Size ;
    }

    queue.EmptySize -= Length;
    queue.DataSize += Length;

    return Length;   //返回成功写入成功的字节数

}
/*********************************************************************
 * @fn      ReadDataFromQueue
 *
 * @brief   从当前队列中读取数据
 *
 * @param
 *          Offset-->从当前位置偏移量开始读数据
 *          Data--->读取后数据存放的空间
 *          Length-->读取数据的长度
 *
 * @return  实际读取到Data的长度
 *
 * 编写者    zyh
 *
 * 日  期    2016-12-25
 ********************************************************************/
AJB_U32 Queue::ReadDataFromQueue(AJB_U32 Offset, char *Data, AJB_U32 _Length)
{
   AJB_U32  Length =_Length;
    AJB_U32 TempReadSeat = 0;
    if( NULL == Data )
    {
        return 0;
    }

    if( 0 == queue.DataSize || 0 == Length )  //当前队列为空或者读取的数据长度为零
    {
        return 0;
    }

    if( Offset > ( queue.DataSize - 1 ) )   //偏移是否超过了范围
    {
        return 0;
    }

    if( Offset + queue.pReadSeat > queue.Size - 1 )//根据偏移量计算开始读取数据的位置
    {
      TempReadSeat = (Offset + queue.pReadSeat) - queue.Size ;  //计算出最小的值为0
    }
    else
    {
      TempReadSeat = queue.pReadSeat + Offset;  //计算出最大的值为 Queue->Size - 1
    }

    if( (queue.DataSize - Offset) < Length ) //核对最大可读取的数据长度
    {
        Length = queue.DataSize - Offset;
    }

    /* 判断空间是否是连续 */
    if( (queue.Size - TempReadSeat) >= Length )
    {
        memcpy(Data,&(queue.Data[TempReadSeat]),Length);
    }
    else
    {
        memcpy( Data,&(queue.Data[TempReadSeat]) , queue.Size - TempReadSeat );
        memcpy( &Data[queue.Size - TempReadSeat] , queue.Data , Length + TempReadSeat - queue.Size );
    }

    return Length;
}

/*********************************************************************
 * @fn      GetQueueDataSize
 *
 * @brief   获取当前队列的存储数据的大小
 *
 * @param   无
 *
 * @return  获取队列的内容长度
 *
 * 编写者    zyh
 *
 * 日  期    2016-12-25
 ********************************************************************/
AJB_U32 Queue::GetQueueEmptySize()
{
    return queue.EmptySize;
}
/*********************************************************************
 * @fn      GetQueueEmptySize
 *
 * @brief   获取当前队列空余容量的大小
 *
 * @param   无
 *
 * @return  获取队列的内容剩余空间的长度
 *
 * 编写者    zyh
 *
 * 日  期    2016-12-25
 ********************************************************************/
AJB_U32 Queue::GetQueueDataSize()
{
    return queue.DataSize;
}



