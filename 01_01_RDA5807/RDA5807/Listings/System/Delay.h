//Ӱ����(ZGT)
#ifndef _DELAY_H_
#define _DELAY_H_

#include <reg52.h>
#include <intrins.h>

#ifndef Main_Fosc
#define Main_Fosc	 11059200UL		//������ʱ�ӵ�HZ��������ʱ
#endif

void Delay_Ms_(unsigned int ms);//���뼶��ʱ
//void Delay_5us_(void);//��ʱ5us
#endif
