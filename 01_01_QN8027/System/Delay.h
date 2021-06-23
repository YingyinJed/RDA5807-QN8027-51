//影隐劫(ZGT)
#ifndef _DELAY_H_
#define _DELAY_H_

#include <reg52.h>
#include <intrins.h>

#ifndef Main_Fosc
#define Main_Fosc	 11059200UL		//定义主时钟的HZ，用于延时
#endif

void Delay_Ms_(unsigned int ms);//毫秒级延时
//void Delay_5us_(void);//延时5us
#endif
