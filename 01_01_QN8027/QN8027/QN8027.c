#include "QN8027.h"
/*******************************************************************************
* 函数名         :QN8027Write1Byte(unsigned char Reg,Vaule)
* 函数功能     	 :向QN8027写一个字节的信号
* 输入           :Reg寄存器地址，Value数据值
* 输出           :I2C应答信号
*******************************************************************************/
bit QN8027Write1Byte(unsigned char Reg,Vaule)
{
    bit ACK_Return;//设置一个变量用于检测应答信号
    IIC_Start();
    ACK_Return = IIC_Write_Byte(0X58);//要向QN8027写东西要先发0x58
    if(ACK_Return == 0)
    {
        ACK_Return = IIC_Write_Byte(Reg);//在有应答后写入需要发送数据的地址
        if(ACK_Return == 0)
        {
            ACK_Return = IIC_Write_Byte(Vaule);//获得应答后写入该地址对应的数字
        }
    }
    IIC_Stop();
    return !ACK_Return;
}
/*******************************************************************************
* 函数名         :QN8027SetReg(unsigned char Regis_Addr,Data)
* 函数功能     	 :向QN8027特地的寄存器写一个字节的信号
* 输入           :Regis_Addr寄存器地址，Data数据值
* 输出           :I2C应答信号
*******************************************************************************/
bit QN8027SetReg(unsigned char Regis_Addr,Data)
{
    unsigned count = 8;
    while(--count)
    {
        if(QN8027Write1Byte(Regis_Addr,Data)) break;
    }
    if(!count)return 0;
    else return 1;
}
/*******************************************************************************
* 函数名         :QN8027_Init()
* 函数功能     	 :初始化QN8027
* 输入           :无
* 输出           :无
*******************************************************************************/
void QN8027_Init()
{
    QN8027SetReg(0x00,0x81);//复位所有寄存器的值
    Delay_Ms_(20);
    QN8027SetReg(0x03,0x10);//在XTL1和XTL2上接入时钟
    QN8027SetReg(0x04,0x34);//选择12MHz晶振，选择1dB的TX数字增益，输入阻抗选用40KΩ
    QN8027SetReg(0x00,0x41);//FSM重置
    QN8027SetReg(0x00,0x01);
    Delay_Ms_(20);
    QN8027SetReg(0x01,0x7e);//设置发射频率
    QN8027SetReg(0x02,0xA9);//设置TX导频增益
    QN8027SetReg(0x00,0x22);//设置QN8027开始发射频率
    Delay_Ms_(20);
}
/*******************************************************************************
* 函数名         :QN8027_Init()
* 函数功能     	 :初始化QN8027
* 输入           :无
* 输出           :无
*******************************************************************************/
void QN8027SetFreq(unsigned int freq)
{
    unsigned int a;
    unsigned char b,c;
    a = (freq - 760)*2;
    c = ((unsigned char *)&a)[1];
    
    b = 0x20|0x04|((unsigned char *)&a)[0];
    Delay_Ms_(20);
    QN8027SetReg(0x00,b);
    QN8027SetReg(0x01,c);
    Delay_Ms_(20);
}