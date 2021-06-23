//影隐劫
/*该文件需要依赖于之前编写的I2C文件和Delay文件*/
#ifndef _RDA5807_H_
#define _RDA5807_H_

#define READ	        1   
#define WRITE	        0

#define ADRW 	        0x20	//RDA5807P写寄存器地址
#define ADRR 	        0x21	//RDA5807P读寄存器地址

//#define                 _SHARE_CRYSTAL_24MHz_   //共用24MHz晶振，请打开此宏
//#define                 _SHARE_CRYSTAL_12MHz_   //共用12MHz晶振，请打开此宏
#define                 _SHARE_CRYSTAL_32KHz_   //共用32KHz晶振，请打开此宏
//#define                 _FM_STEP_50K_           //50K步进，请打开此宏

#include <string.h>
#include <stdio.h>
#include "I2C.h"
#include "Delay.h"
//初始化RDA5807P
bit RDA5807P_Intialization(void);
//设置RDA5807的频率
void RDA5807P_SetFreq(int curFreq);
//获得RDA5807当前的信号强度
unsigned int RDA5807P_GetSigLvl(void);
//设置RDA5807的输出音量
void RDA5807P_SetVolumeLevel(unsigned char level);

#endif