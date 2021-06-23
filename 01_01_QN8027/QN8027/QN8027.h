#ifndef _QN8027_H_
#define _QN8027_H_

#include "I2C.h"
#include "Delay.h"

void QN8027_Init();//初始化QN8027
void QN8027SetFreq(unsigned int freq);//设置QN8027发射频率
#endif