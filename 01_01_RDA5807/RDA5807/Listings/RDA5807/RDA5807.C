//影隐劫
#include "RDA5807.h"

unsigned int gChipID = 0;			//芯片ID号
unsigned char  RDA5807P_REGW[10];	//寄存器

unsigned char code RDA5807N_initialization_reg[]={
#if defined(_SHARE_CRYSTAL_24MHz_)
    0xC0, 0x51, //02H:
#elif defined(_SHARE_CRYSTAL_12MHz_)
    0xC0, 0x11, //02H:
#elif defined(_SHARE_CRYSTAL_32KHz_)
    0xC0, 0x01, //02H:			//02H寄存器第10位必须为1
	//0xD0, 0x01, //02H:	//开启增强低音
#else
    0xC0, 0x01,
#endif
    0x00, 0x00,
    0x04, 0x00,
    0xC6, 0xad, //05h
    0x60, 0x00,
    0x42, 0xC6,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,  //0x0ah
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,
    0x00, 0x00,  //0x10h
    0x00, 0x19,
    0x2a, 0x11,
    0xB0, 0x42,  
    0x2A, 0x11,  
    0xb8, 0x31,  //0x15h 
    0xc0, 0x00,
    0x2a, 0x91,
    0x94, 0x00,
    0x00, 0xa8,
    0xc4, 0x00,  //0x1ah
    0xF7, 0xcF,   
    0x2A, 0xDC,  //0x1ch
    0x80, 0x6F, 
    0x46, 0x08,
    0x00, 0x86,
    0x06, 0x61, //0x20H
    0x00, 0x00,
    0x10, 0x9E,
    0x23, 0xC8,
    0x04, 0x06,
    0x0E, 0x1C, //0x25H
};

/*******************************************************************************
* 函数名         :OperationRDAFM_2w()[内部使用]
* 函数功能     	 :读或者写数据到RDA5807
* 输入           :operation   —— 功能选择"读READ/写WRITE"
                  datas       —— 读或写的数据指针"
                  numBytes    —— 需要读或写numBytes个字节
* 输出           :无
*******************************************************************************/
unsigned char OperationRDAFM_2w(unsigned char operation,unsigned char *datas,unsigned char numBytes)
{
    unsigned char j;
	unsigned char acknowledge = 0;
    IIC_Start();
    if(operation == READ)
    { acknowledge = IIC_Write_Byte(ADRR);}//写IIC读地址
	else
    {acknowledge = IIC_Write_Byte(ADRW);}//写IIC写地址
    for(j = 0; j < numBytes; j++, datas++)
    {
        if(operation == READ){
			if(j == (numBytes -1))
			{ *datas = IIC_Read_Byte(IIC_NACK); } 
			else
			{*datas = IIC_Read_Byte(IIC_ACK);} 
		}
        else
        { acknowledge = IIC_Write_Byte(*datas); }
    }
    IIC_Stop();
	return acknowledge;
}
/*******************************************************************************
* 函数名         :RDA5807P_Intialization()
* 函数功能     	 :初始化RDA5807
* 输入           :无
* 输出           :无
*******************************************************************************/
bit RDA5807P_Intialization(void)
{
    unsigned char error_ind = 0;
	unsigned char RDA5807P_REGR[10]={0x0};
    unsigned char i = 0;      

    RDA5807P_REGW[0] = 0x00;//软件复位指令
    RDA5807P_REGW[1] = 0x02;    
    //写入复位信号
    error_ind = OperationRDAFM_2w(WRITE, (unsigned char *)&RDA5807P_REGW[0], 2);
    Delay_Ms_(50);
    //复位后读取寄存器信息
    error_ind = OperationRDAFM_2w(READ, (unsigned char *)&RDA5807P_REGR[0], 10);
    Delay_Ms_(50);
    //通过移位完全获得芯片号
    gChipID = RDA5807P_REGR[8];
    gChipID = ((gChipID << 8) | RDA5807P_REGR[9]);
    printf("-----gChipID = %x-----\n",gChipID);
    if(gChipID == 0x5808){  //RDA5807N
        for (i = 0; i < 8; i++){
            RDA5807P_REGW[i] = RDA5807N_initialization_reg[i];
		}
        error_ind = OperationRDAFM_2w(WRITE, (unsigned char *)&RDA5807N_initialization_reg[0], 2);
        Delay_Ms_(600); 
	    error_ind = OperationRDAFM_2w(WRITE, (unsigned char *)&RDA5807N_initialization_reg[0], sizeof(RDA5807N_initialization_reg));
    }
    Delay_Ms_(50);
    if(error_ind){	//ACK=0, NACK=1
	   return 0;
	}
	else{
	   return 1;
	}
}
/*******************************************************************************
* 函数名         :RDA5807P_FreqToChan()[内部使用]
* 函数功能     	 :把频率值转换成信道值,例如：频率107.3MHz，frequency = 10730，转换成信道值为203
* 输入           :需要转化的频率值
* 输出           :对应的信道值
*******************************************************************************/
unsigned int RDA5807P_FreqToChan(unsigned int frequency) 
{
	unsigned char channelSpacing;
	unsigned int bottomOfBand;
	unsigned int channel;

	if ((RDA5807P_REGW[3] & 0x0c) == 0x00){ //03H寄存器低八位第2、3位都为0，波段选择 = 87~108MHz
		bottomOfBand = 8700;
	}
	else if ((RDA5807P_REGW[3] & 0x0c) == 0x04){
		bottomOfBand = 7600;
	}
	else if ((RDA5807P_REGW[3] & 0x0c) == 0x08){
		bottomOfBand = 7600;	
	}
	if ((RDA5807P_REGW[3] & 0x03) == 0x00){ //03H寄存器低八位第0、1位都为0，频率间距 = 100KHz
		channelSpacing = 10;
	}
	else if ((RDA5807P_REGW[3] & 0x03) == 0x01){
		channelSpacing = 10;
	}
	else if ((RDA5807P_REGW[3] & 0x03) == 0x02){ 
		channelSpacing = 5;
	}
	channel = (frequency - bottomOfBand) / channelSpacing;
	return (channel);
}
/*******************************************************************************
* 函数名         :RDA5807P_SetFreq(int curFreq)
* 函数功能     	 :设置频率
* 输入           :需要设置的频率值
* 输出           :无
*******************************************************************************/
void RDA5807P_SetFreq(int curFreq)
{   
	unsigned int curChan;
	
	curChan = RDA5807P_FreqToChan(curFreq);
	
	//SetNoMute
	RDA5807P_REGW[0] |=	1 << 7;
	RDA5807P_REGW[2] = curChan >> 2;
	RDA5807P_REGW[3] = (((curChan & 0x0003) << 6) | 0x10) | (RDA5807P_REGW[3] & 0x0f);	//调谐启用
	
	OperationRDAFM_2w(WRITE, &(RDA5807P_REGW[0]), 4);
	Delay_Ms_(50);     //Delay 50 ms
}
/*******************************************************************************
* 函数名         :unsigned int RDA5807P_GetSigLvl(void)
* 函数功能     	 :返回当前信号强度
* 输入           :无
* 输出           :当前信号强度，0~127
*******************************************************************************/
unsigned int RDA5807P_GetSigLvl(void)
{    
    unsigned char RDA5807P_reg_data[4]={0};	
	unsigned int rssi;
	
	OperationRDAFM_2w(READ, &(RDA5807P_reg_data[0]), 4);
	Delay_Ms_(50);    //Dealy 50 ms
	
	rssi = (RDA5807P_reg_data[2] >> 1) & 0x7F;
    return rssi;  //返回RSSI
}
/*******************************************************************************
* 函数名         :void RDA5807P_SetVolumeLevel(unsigned char level)
* 函数功能     	 :设置FM音量，0~15
* 输入           :需要设置的音量值0~15
* 输出           :无
*******************************************************************************/
void RDA5807P_SetVolumeLevel(unsigned char level)
{
    unsigned char RDA5807P_reg_data[8];
    unsigned char i = 0;
	//uint16 temp;

    for(i = 0; i < 8; i++){
        RDA5807P_reg_data[i] = RDA5807P_REGW[i];
	}

    RDA5807P_reg_data[7] = (( RDA5807P_reg_data[7] & 0xf0 ) | (level & 0x0f)); 
    
    RDA5807P_reg_data[3] &= (~(0x10));

	OperationRDAFM_2w(WRITE, &(RDA5807P_reg_data[0]), 8);
    Delay_Ms_(50);    //Dealy 50 ms
}