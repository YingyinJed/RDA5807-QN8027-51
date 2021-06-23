//影隐劫（ZGT）
#ifndef _I2C_H
#define _I2C_H

#include <reg52.h>
#include <intrins.h>

#define  IIC_ACK     0
#define  IIC_NACK    1

#ifndef Main_Fosc
#define Main_Fosc	 11059200UL		//定义主时钟的HZ							
#endif

sbit SDA = P2^0;	//这一个数据线和一个时钟线根据实际电路设置
sbit SCL = P2^1;	//实验板中采用的是P2^0和P2^1

void IIC_Start(void);//发送起始信号
void IIC_Stop(void);//发送停止信号
void IIC_Send_ACK(bit ack);//由主机向从机发送应答信号
bit IIC_Get_ACK(void);//主机获得来自从机的应答信号
bit IIC_Write_Byte(unsigned char dat);//通过IIC写一个字节的数据发送
unsigned char IIC_Read_Byte(bit ack);//通过IIC读取一个字节的数据
#endif
