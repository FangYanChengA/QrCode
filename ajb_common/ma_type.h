#ifndef MA_TYPE_H
#define MA_TYPE_H

#include<stddef.h>

    typedef unsigned char           AJB_U8;
    typedef unsigned short          AJB_U16;
    typedef unsigned int            AJB_U32;

    typedef signed char             AJB_S8;
    typedef short                   AJB_S16;
    typedef int                     AJB_S32;

    typedef long long               AJB_S64;
    typedef unsigned long long      AJB_U64;

    typedef float                   AJB_F32;
    typedef double                  AJB_F64;
    typedef bool                    AJB_BOOL;

    //typedef __int64                 AJB_U64;
    //typedef __int64                 AJB_S64;

    typedef char                    AJB_CHAR;
    #define AJB_VOID                 void



    #define ZNC_RTN_U16( BUFFER, i ) ( ( ( AJB_U16 ) (BUFFER)[ i ] << 8) |( ( AJB_U16 ) (BUFFER)[ i + 1 ] & 0xFF))
    #define ZNC_RTN_U32( BUFFER, i ) ( ( ( AJB_U32 ) (BUFFER)[ i ] << 24) |( ( AJB_U32 ) (BUFFER)[ i+1 ] << 16) | ( ( AJB_U32 ) (BUFFER)[ i+2 ] << 8) | ( ( AJB_U32 ) (BUFFER)[ i + 3 ] & 0xFF))


    #define ZNC1_RTN_U16( BUFFER, i ) ( ( ( AJB_U16 ) (BUFFER)[ i+1 ] << 8) |( ( AJB_U16 ) (BUFFER)[ i ] & 0xFF))

    #define ZNC1_RTN_U32( BUFFER, i ) ( ( ( AJB_U32 ) (BUFFER)[ i+3 ] << 24) |( ( AJB_U32 ) (BUFFER)[ i+2 ] << 16) | ( ( AJB_U32 ) (BUFFER)[ i+1 ] << 8) | ( ( AJB_U32 ) (BUFFER)[ i ] & 0xFF))

    #define U16_RTN_ZNC( BUFEER, i ,U16_Data )  BUFEER[i+1] = U16_Data; BUFEER[i] = (U16_Data>>8)
   // #define U16_RTN_ZNC( BUFEER, i ,U16_Data )  BUFEER[i] = U16_Data; BUFEER[i+1] = (U16_Data>>8)
    #define U32_RTN_ZNC( BUFEER, i ,U32_Data )  BUFEER[i+3] = U32_Data; BUFEER[i+2] = (U32_Data>>8);BUFEER[i+1] = (U32_Data>>16);BUFEER[i] = (U32_Data>>24)




#pragma pack(1)
    typedef enum
    {
        READ_BIT    = 0X01,
        READ_WORD   = 0X03,
        WRITE_BIT   = 0X0F,
        WRITE_WORD  = 0X10,
    }ModbusFunctionCode_e;    //功能码
    #define IS_MODBUS_FUNCTION_CODE_TYPE(ModbusFunctionCode)    ((ModbusFunctionCode == READ_BIT) || \
                                                                (ModbusFunctionCode == READ_WORD) || \
                                                                (ModbusFunctionCode == WRITE_BIT) || \
                                                                (ModbusFunctionCode == WRITE_WORD) )


    typedef enum
    {
        ANORMAL_DATA   = 0X03,   //数据异常
        ANORMAL_DEVICE = 0X04,   //从机通讯异常（设备不存在）
    }ModbusAnormalCodeType_e;

    //写请求帧
    typedef struct
    {
      //  AJB_U8                  DevieAddr;   //设备地址
     //   ModbusFunctionCode_e    ModbusFunctionCode;
        AJB_U16                 SourceAddr;
        AJB_U16                 DataLen;     //数据数量
        AJB_U8                  ByteLen;     //字节个数
        AJB_U8                  Data[128];
      //  AJB_U16                 Crc;
    }ModbusWriteRequstFrame_t;

    //读请求帧
    typedef struct
    {
      //  AJB_U8                  DevieAddr;   //设备地址
      //  ModbusFunctionCode_e    ModbusFunctionCode;
        AJB_U16                 SourceAddr;
        AJB_U16                 DataLen;
      //  AJB_U16                 Crc;
    }ModbusReadRequstFrame_t;


    //写响应帧
    typedef struct
    {
      //  AJB_U8                  DevieAddr;   //设备地址
      //  ModbusFunctionCode_e    ModbusFunctionCode;
        AJB_U16                 SourceAddr;
        AJB_U16                 DataLen;
      //  AJB_U16                 Crc;
    }ModbusWriteResponseFrame_t;

    // 读响应帧
    typedef struct
    {
       // AJB_U8                  DeviceAddr;
       // ModbusFunctionCode_e    ModbusFunctionCode;
        AJB_U8                  DataLen;
        AJB_U8                  Data[128];
       // AJB_U16                 Crc;
    }ModbusReadResponseFrame_t;

    typedef struct
    {
        ModbusAnormalCodeType_e ModbusAnormalCodeType;
    }ModebusAbnormalResponseFrame_t;

    typedef enum
    {
        MODBUS_WRITE_REQUST      = 1,
        MODBUS_READ_REQUST       = 2,
        MODBUS_WRITE_RESPONSE    = 3,
        MODBUS_READ_RESPONSE     = 4,
        MODBUS_ABNORMAL_RESPONSE = 5,  //异常码返回
    }ModbusFrameType_e;

    typedef union
    {
       ModbusWriteRequstFrame_t         WriteRequst;
       ModbusReadRequstFrame_t          ReadRequst;
       ModbusWriteResponseFrame_t       WriteResponse;
       ModbusReadResponseFrame_t        ReadResponse;
       ModebusAbnormalResponseFrame_t   ModebusAbnormalResponseFrame;
    }ModbusDataFrame_u;

    typedef struct
    {
        ModbusFrameType_e       FrameType;

        AJB_U8                  DeviceAddr;
        AJB_U8                  ModbusFunctionCode;

        ModbusDataFrame_u       FrameData;

        AJB_U16                 Crc;
    }ModbusFrameData_t;
#pragma pack()










#endif // MA_TYPE_H

