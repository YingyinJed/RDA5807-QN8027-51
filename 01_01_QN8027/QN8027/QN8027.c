#include "QN8027.h"
/*******************************************************************************
* ������         :QN8027Write1Byte(unsigned char Reg,Vaule)
* ��������     	 :��QN8027дһ���ֽڵ��ź�
* ����           :Reg�Ĵ�����ַ��Value����ֵ
* ���           :I2CӦ���ź�
*******************************************************************************/
bit QN8027Write1Byte(unsigned char Reg,Vaule)
{
    bit ACK_Return;//����һ���������ڼ��Ӧ���ź�
    IIC_Start();
    ACK_Return = IIC_Write_Byte(0X58);//Ҫ��QN8027д����Ҫ�ȷ�0x58
    if(ACK_Return == 0)
    {
        ACK_Return = IIC_Write_Byte(Reg);//����Ӧ���д����Ҫ�������ݵĵ�ַ
        if(ACK_Return == 0)
        {
            ACK_Return = IIC_Write_Byte(Vaule);//���Ӧ���д��õ�ַ��Ӧ������
        }
    }
    IIC_Stop();
    return !ACK_Return;
}
/*******************************************************************************
* ������         :QN8027SetReg(unsigned char Regis_Addr,Data)
* ��������     	 :��QN8027�صصļĴ���дһ���ֽڵ��ź�
* ����           :Regis_Addr�Ĵ�����ַ��Data����ֵ
* ���           :I2CӦ���ź�
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
* ������         :QN8027_Init()
* ��������     	 :��ʼ��QN8027
* ����           :��
* ���           :��
*******************************************************************************/
void QN8027_Init()
{
    QN8027SetReg(0x00,0x81);//��λ���мĴ�����ֵ
    Delay_Ms_(20);
    QN8027SetReg(0x03,0x10);//��XTL1��XTL2�Ͻ���ʱ��
    QN8027SetReg(0x04,0x34);//ѡ��12MHz����ѡ��1dB��TX�������棬�����迹ѡ��40K��
    QN8027SetReg(0x00,0x41);//FSM����
    QN8027SetReg(0x00,0x01);
    Delay_Ms_(20);
    QN8027SetReg(0x01,0x7e);//���÷���Ƶ��
    QN8027SetReg(0x02,0xA9);//����TX��Ƶ����
    QN8027SetReg(0x00,0x22);//����QN8027��ʼ����Ƶ��
    Delay_Ms_(20);
}
/*******************************************************************************
* ������         :QN8027_Init()
* ��������     	 :��ʼ��QN8027
* ����           :��
* ���           :��
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