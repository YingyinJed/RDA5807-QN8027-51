#ifndef _MAIN_H_
#define _MAIN_H_

#include <reg52.h>
#include <stdio.h>
#include "UART.h"
#include "I2C.h"
#include "RDA5807.h"
#include "NUMLED.h"
//�����ĸ�����
sbit KEY_V_UP = P1^0;
sbit KEY_V_DOWN = P1^1;
sbit KEY_F_UP = P1^2;
sbit KEY_F_DOWN = P1^3;

#endif