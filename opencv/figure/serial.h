#ifndef __SERIAL_H
#define __SERIAL_H

//串口相关的头文件
#include "stdint.h"
#include <errno.h>  /*错误号定义*/
#include <fcntl.h>  /*文件控制定义*/
#include <stdio.h>  /*标准输入输出定义*/
#include <stdlib.h> /*标准函数库定义*/
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h> /*PPSIX 终端控制定义*/
#include <unistd.h>  /*Unix 标准函数定义*/

#define BAUDRATE 115200
#define UART_DEVICE "/dev/ttyUSB0"

#define ECHOFLAGS (ECHO | ECHOE | ECHOK | ECHONL)

// Used when calling a serial port
#define FALSE -1
#define TRUE 0
#define TIMEOUT_SEC(buflen, baud) (buflen * 20 / baud + 2)  //接收超时
#define TIMEOUT_USEC 0

// 联合体解析数据
typedef union {
    float         f;
    unsigned char c[4];
} float2uchar;

typedef union {
    unsigned char c[4];
    float         f;
} char2float;

typedef union {
    char    c[2];
    int16_t f;
} uint2int16;

//--发送数据
typedef struct
{
    unsigned char start;
    unsigned char Direction;  ///<路径修正转向
    unsigned char Turn;       ///< 是否开始90度转向
    unsigned char Number;     ///< 是否开始90度转向

    unsigned char end;
} HostComputerData;

////--接受数据
typedef struct
{
    uint8_t     color;
    float2uchar gain_yaw;
    float2uchar gain_pitch;
} GroundChassisData;

class Uart
{
public:
    Uart(int speed = 115200);
    int     Init_serial(int& fdcom, int baud_speed);
    void    set_speed(int fd, speed_t speed);
    int     set_Parity(int fd, int databits, int stopbits, int parity);
    void    close_serial(int fd);
    void    GetMode(int& fd, GroundChassisData& data);
    void    TransformTarPos(int& fd, const HostComputerData& data);
    uint8_t crc8_check(uint8_t* addr, int len);

private:
    int fd;
    int speed;
};
#endif  //__SERIAL_H
