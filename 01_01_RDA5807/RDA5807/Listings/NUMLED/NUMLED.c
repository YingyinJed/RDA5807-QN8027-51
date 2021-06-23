#include "NUMLED.h"
unsigned char leddata[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
                        //"0"  "1"  "2"  "3"  "4"  "5"  "6"  "7"  "8"  "9"  
/*******************************************************************************
* 函数名         :Display_Voide(unsigned char NUM)
* 函数功能     	 :在音量显示的数码管上显示当前的音量
* 输入           :音量的值
* 输出           :无
*******************************************************************************/
void Display_Voide(unsigned char NUM)
{
    unsigned char NUM_GE,NUM_SHI;//GE，SHI分别代表各位和十位
    NUM_GE  = NUM % 10;
    NUM_SHI = NUM / 10;
    
    P0 = leddata[NUM_GE];//先输入个位的数形码
    VOIDE_2 = 1;//点亮音量的第一根数码管
    Delay_Ms_(1);//延时1ms后关掉
    VOIDE_2 = 0;
    
    P0 = leddata[NUM_SHI];//输入十位的数形码
    VOIDE_1 = 1;//点亮音量的第二根数码管
    Delay_Ms_(1);//延时1ms后关掉
    VOIDE_1 = 0;
}
/*******************************************************************************
* 函数名         :Display_Frequency(int NUM)
* 函数功能     	 :在音量显示的数码管上显示当前的频率
* 输入           :频率的值
* 输出           :无
*******************************************************************************/
void Display_Frequency(int NUM)
{
    unsigned char NUM_GE,NUM_SHI,NUM_BAI;//分别表示MHz的个，十，百位
    NUM_BAI = NUM / 10000;
    NUM_SHI = (NUM % 10000) / 1000;
    NUM_GE  = (NUM % 1000) / 100;
    
    P0 = leddata[NUM_BAI];//输入百位的数形码
    F_1 = 1;//点亮频率显示的第一根数码管
    Delay_Ms_(1);//延时1ms后关掉
    F_1 = 0; 
    
    P0 = leddata[NUM_SHI];//输入十位的数形码
    F_2 = 1;//点亮频率显示的第二根数码管
    Delay_Ms_(1);//延时1ms后关掉
    F_2 = 0;
    
    P0 = leddata[NUM_GE];//输入个位的数形码
    F_3 = 1;//点亮频率显示的第三根数码管
    Delay_Ms_(1);//延时1ms后关掉
    F_3 = 0;
}