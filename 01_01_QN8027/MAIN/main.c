#include "main.h"
//定义全局变量
unsigned int Freq = 870;
//按键标志位相关变量
bit FLAG_V_UP,FLAG_V_DOWN,FLAG_F_UP,FLAG_F_DOWN;
//自定义函数
void KEY_SCAN(void);

void main()
{
    VOIDE_1 = VOIDE_2 = F_1 = F_2 = F_3 = 0;//让所有共阳极数码管的公共端处于低电平
    QN8027_Init();
    QN8027SetFreq(Freq);
    while(1)
    {
        KEY_SCAN();//扫描按键是否被按下
        Display_Frequency(Freq);
    }
}
/*******************************************************************************
* 函数名         :KEY_SCAN()
* 函数功能     	 :扫描四个按键是哪个被按下
* 输入           :无
* 输出           :无
*******************************************************************************/
void KEY_SCAN(void)
{
    /*-------------SW3_F+（频率加）------------------*/
    if(FLAG_F_UP == 0)
    {
        if(KEY_F_UP == 0)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_F_UP == 0)
            {
                FLAG_F_UP = 1;//改变标志位状态
                if(Freq < 1080)
                {
                    Freq = Freq + 10;
                    //重新设置频率
                    QN8027SetFreq(Freq);
                }
                else if(Freq >=1080)
                {Freq = 1080;}
            }
        }
    }
    else
    {
        if(KEY_F_UP == 1)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_F_UP == 1)
            {FLAG_F_UP = 0;}//清除松手标志位
        }
    }
    /*-------------SW4_F-（频率减）------------------*/
    if(FLAG_F_DOWN == 0)
    {
        if(KEY_F_DOWN == 0)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_F_DOWN == 0)
            {
                FLAG_F_DOWN = 1;//改变标志位状态
                if(Freq > 870)
                {
                    Freq = Freq - 10;
                    //重新设置频率
                    QN8027SetFreq(Freq);
                }
                else if(Freq <= 870)
                {Freq = 870;}
            }
        }
    }
    else
    {
        if(KEY_F_DOWN == 1)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_F_DOWN == 1)
            {FLAG_F_DOWN = 0;}//清除松手标志位
        }
    }
}
