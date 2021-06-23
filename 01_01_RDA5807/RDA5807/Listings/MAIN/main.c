#include "main.h"

//定义全局变量
//RDA5807的设置相关变量
int FRE_RDA5807 = 8700;//设置频率
unsigned int RSSI_RDA5807 = 0;//读取信号强度
unsigned char VOL_RDA5807 = 5;//设置音量
//按键标志位相关变量
bit FLAG_V_UP,FLAG_V_DOWN,FLAG_F_UP,FLAG_F_DOWN;

//自定义函数
void KEY_SCAN(void);//扫描按键状态

//主函数
void main()
{
    VOIDE_1 = VOIDE_2 = F_1 = F_2 = F_3 = 0;//让所有共阳极数码管的公共端处于低电平
    Uart_init();//初始化串口
    TI = 1;//TI设为1是为了让printf函数正常运行
    //初始化RDA5807
    if(RDA5807P_Intialization())
    {
        printf("FM Init OK!\n");
        Delay_Ms_(600);
        Delay_Ms_(600);
    }
    else//初始化失败则串口提示失败后数码管不显示
    {
        printf("FM Init Fail!\n");
        while(1);
    }
    //设置初始频率
	RDA5807P_SetFreq(FRE_RDA5807);
    printf("FM_FRE = %d\n",FRE_RDA5807);
    //设置当前频率信号强度
    RSSI_RDA5807 = RDA5807P_GetSigLvl();
    printf("FM_RSSI = %d\n",RSSI_RDA5807);
    //设置当前音量值
    RDA5807P_SetVolumeLevel(VOL_RDA5807);
    printf("FM_VOL = %X\n",VOL_RDA5807);
    //初始化通过进入大循环
    while(1)
    {        
        Display_Voide(VOL_RDA5807);//显示音量
        Display_Frequency(FRE_RDA5807);//显示频率
        KEY_SCAN();//扫描按键是否被按下
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
    /*-------------SW1_V+（音量加）------------------*/
    if(FLAG_V_UP == 0)//松手标志位为0说明已经松手
    {
        if(KEY_V_UP == 0)//如果按键被按下
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_V_UP == 0)
            {
                FLAG_V_UP = 1;//改变标志位状态
                if(VOL_RDA5807 < 15)
                {                    
                    VOL_RDA5807++;
                    //重新设置当前音量值
                    RDA5807P_SetVolumeLevel(VOL_RDA5807);
                }
                else if(VOL_RDA5807 >=15)
                {VOL_RDA5807 = 15;}//音量的最大值为15
                
            }
        }
    }
    else //松手标志位位1说明还未松手
    {
        if(KEY_V_UP == 1) //说明按键已经松手
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_V_UP == 1)
            { FLAG_V_UP = 0; }//清除松手标志位
        }
    }
    /*-------------SW2_V-（音量减）------------------*/
    if(FLAG_V_DOWN == 0)
    {
        if(KEY_V_DOWN == 0)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_V_DOWN == 0)
            {
                FLAG_V_DOWN = 1;//改变标志位状态
                if(VOL_RDA5807 > 0)
                {
                    VOL_RDA5807--;
                    //重新设置当前音量值
                    RDA5807P_SetVolumeLevel(VOL_RDA5807);
                }
                else if(VOL_RDA5807 == 0)
                {VOL_RDA5807 = 0;}
            }
        }
    }
    else
    {
        if(KEY_V_DOWN == 1)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_V_DOWN == 1)
            {FLAG_V_DOWN = 0;}//清除松手标志位
        }
    }
    /*-------------SW3_F+（频率加）------------------*/
    if(FLAG_F_UP == 0)
    {
        if(KEY_F_UP == 0)
        {
            Delay_Ms_(5);//去抖延时5ms
            if(KEY_F_UP == 0)
            {
                FLAG_F_UP = 1;//改变标志位状态
                if(FRE_RDA5807 < 10800)
                {
                    FRE_RDA5807 = FRE_RDA5807 + 100;
                    //重新设置频率
                    RDA5807P_SetFreq(FRE_RDA5807);
                }
                else if(FRE_RDA5807 >=10800)
                {FRE_RDA5807 = 10800;}
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
                if(FRE_RDA5807 > 8700)
                {
                    FRE_RDA5807 = FRE_RDA5807 - 100;
                    //重新设置频率
                    RDA5807P_SetFreq(FRE_RDA5807);
                }
                else if(FRE_RDA5807 <= 8700)
                {FRE_RDA5807 = 8700;}
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