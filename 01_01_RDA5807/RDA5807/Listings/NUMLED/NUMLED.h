#ifndef _NUMLED_H_
#define _NUMLED_H_

#include "reg52.h"
#include "Delay.h"
//������ʾ
sbit VOIDE_1 = P2^7;
sbit VOIDE_2 = P2^6;
//Ƶ����ʾ
sbit F_1 = P2^5;
sbit F_2 = P2^4;
sbit F_3 = P2^3;
//�Զ��庯��
void Display_Voide(unsigned char NUM);//������ʾ����
void Display_Frequency(int NUM);//������ʾƵ��

#endif