#include "main.h"
//����ȫ�ֱ���
unsigned int Freq = 870;
//������־λ��ر���
bit FLAG_V_UP,FLAG_V_DOWN,FLAG_F_UP,FLAG_F_DOWN;
//�Զ��庯��
void KEY_SCAN(void);

void main()
{
    VOIDE_1 = VOIDE_2 = F_1 = F_2 = F_3 = 0;//�����й���������ܵĹ����˴��ڵ͵�ƽ
    QN8027_Init();
    QN8027SetFreq(Freq);
    while(1)
    {
        KEY_SCAN();//ɨ�谴���Ƿ񱻰���
        Display_Frequency(Freq);
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
    /*-------------SW3_F+��Ƶ�ʼӣ�------------------*/
    if(FLAG_F_UP == 0)
    {
        if(KEY_F_UP == 0)
        {
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_F_UP == 0)
            {
                FLAG_F_UP = 1;//�ı��־λ״̬
                if(Freq < 1080)
                {
                    Freq = Freq + 10;
                    //��������Ƶ��
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
                if(Freq > 870)
                {
                    Freq = Freq - 10;
                    //��������Ƶ��
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
            Delay_Ms_(5);//ȥ����ʱ5ms
            if(KEY_F_DOWN == 1)
            {FLAG_F_DOWN = 0;}//������ֱ�־λ
        }
    }
}
