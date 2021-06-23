#include "main.h"

//����ȫ�ֱ���
//RDA5807��������ر���
int FRE_RDA5807 = 8700;//����Ƶ��
unsigned int RSSI_RDA5807 = 0;//��ȡ�ź�ǿ��
unsigned char VOL_RDA5807 = 5;//��������
//������־λ��ر���
bit FLAG_V_UP,FLAG_V_DOWN,FLAG_F_UP,FLAG_F_DOWN;

//�Զ��庯��
void KEY_SCAN(void);//ɨ�谴��״̬

//������
void main()
{
    VOIDE_1 = VOIDE_2 = F_1 = F_2 = F_3 = 0;//�����й���������ܵĹ����˴��ڵ͵�ƽ
    Uart_init();//��ʼ������
    TI = 1;//TI��Ϊ1��Ϊ����printf������������
    //��ʼ��RDA5807
    if(RDA5807P_Intialization())
    {
        printf("FM Init OK!\n");
        Delay_Ms_(600);
        Delay_Ms_(600);
    }
    else//��ʼ��ʧ���򴮿���ʾʧ�ܺ�����ܲ���ʾ
    {
        printf("FM Init Fail!\n");
        while(1);
    }
    //���ó�ʼƵ��
	RDA5807P_SetFreq(FRE_RDA5807);
    printf("FM_FRE = %d\n",FRE_RDA5807);
    //���õ�ǰƵ���ź�ǿ��
    RSSI_RDA5807 = RDA5807P_GetSigLvl();
    printf("FM_RSSI = %d\n",RSSI_RDA5807);
    //���õ�ǰ����ֵ
    RDA5807P_SetVolumeLevel(VOL_RDA5807);
    printf("FM_VOL = %X\n",VOL_RDA5807);
    //��ʼ��ͨ�������ѭ��
    while(1)
    {        
        Display_Voide(VOL_RDA5807);//��ʾ����
        Display_Frequency(FRE_RDA5807);//��ʾƵ��
        KEY_SCAN();//ɨ�谴���Ƿ񱻰���
    }
}
/*******************************************************************************
* ������         :KEY_SCAN()
* ��������     	 :ɨ���ĸ��������ĸ�������
* ����           :��
* ���           :��
*******************************************************************************/
void KEY_SCAN(void)
{
    /*-------------SW1_V+�������ӣ�------------------*/
    if(FLAG_V_UP == 0)//���ֱ�־λΪ0˵���Ѿ�����
    {
        if(KEY_V_UP == 0)//�������������
        {
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_V_UP == 0)
            {
                FLAG_V_UP = 1;//�ı��־λ״̬
                if(VOL_RDA5807 < 15)
                {                    
                    VOL_RDA5807++;
                    //�������õ�ǰ����ֵ
                    RDA5807P_SetVolumeLevel(VOL_RDA5807);
                }
                else if(VOL_RDA5807 >=15)
                {VOL_RDA5807 = 15;}//���������ֵΪ15
                
            }
        }
    }
    else //���ֱ�־λλ1˵����δ����
    {
        if(KEY_V_UP == 1) //˵�������Ѿ�����
        {
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_V_UP == 1)
            { FLAG_V_UP = 0; }//������ֱ�־λ
        }
    }
    /*-------------SW2_V-����������------------------*/
    if(FLAG_V_DOWN == 0)
    {
        if(KEY_V_DOWN == 0)
        {
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_V_DOWN == 0)
            {
                FLAG_V_DOWN = 1;//�ı��־λ״̬
                if(VOL_RDA5807 > 0)
                {
                    VOL_RDA5807--;
                    //�������õ�ǰ����ֵ
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
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_V_DOWN == 1)
            {FLAG_V_DOWN = 0;}//������ֱ�־λ
        }
    }
    /*-------------SW3_F+��Ƶ�ʼӣ�------------------*/
    if(FLAG_F_UP == 0)
    {
        if(KEY_F_UP == 0)
        {
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_F_UP == 0)
            {
                FLAG_F_UP = 1;//�ı��־λ״̬
                if(FRE_RDA5807 < 10800)
                {
                    FRE_RDA5807 = FRE_RDA5807 + 100;
                    //��������Ƶ��
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
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_F_UP == 1)
            {FLAG_F_UP = 0;}//������ֱ�־λ
        }
    }
    /*-------------SW4_F-��Ƶ�ʼ���------------------*/
    if(FLAG_F_DOWN == 0)
    {
        if(KEY_F_DOWN == 0)
        {
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_F_DOWN == 0)
            {
                FLAG_F_DOWN = 1;//�ı��־λ״̬
                if(FRE_RDA5807 > 8700)
                {
                    FRE_RDA5807 = FRE_RDA5807 - 100;
                    //��������Ƶ��
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
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_F_DOWN == 1)
            {FLAG_F_DOWN = 0;}//������ֱ�־λ
        }
    }
}