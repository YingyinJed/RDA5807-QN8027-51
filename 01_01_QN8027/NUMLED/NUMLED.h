#ifndef _NUMLED_H_
#define _NUMLED_H_

#include "reg52.h"
#include "Delay.h"
//音量显示
sbit VOIDE_1 = P2^7;
sbit VOIDE_2 = P2^6;
//频率显示
sbit F_1 = P2^5;
sbit F_2 = P2^4;
sbit F_3 = P2^3;
//自定义函数
void Display_Voide(unsigned char NUM);//用于显示音量
void Display_Frequency(unsigned int NUM);//用于显示频率

#endif