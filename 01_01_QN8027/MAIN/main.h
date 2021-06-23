#ifndef _MAIN_H_
#define _MAIN_H_

#include <reg52.h>
#include "I2C.h"
#include "QN8027.h"
#include "NUMLED.h"
//定义四个按键
sbit KEY_V_UP = P1^0;
sbit KEY_V_DOWN = P1^1;
sbit KEY_F_UP = P1^2;
sbit KEY_F_DOWN = P1^3;

#endif
