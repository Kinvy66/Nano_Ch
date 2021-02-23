#include "smg.h"
#include "delay.h"



void LED_SMG_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO��ʼ��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);  
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);  //����JTAG
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;  			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_50MHz;	
	GPIO_Init(GPIOB,&GPIO_InitStructure);				//��ʼ��74HC595
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
	GPIO_Init(GPIOC,&GPIO_InitStructure);				//��ʼ��74HC138
	
	LED_DS   = 0;
	LED_LCLK = 1;
	LED_SCK	 = 0;
	
	LED_DS	 = 0;
	LED_LCLK = 0;
	LED_SCK	 = 0;
	
}

//74HC138����
//�����λѡ
//num:Ҫ��ʾ������ܱ�� 0-7(��8�������)
void LED_Wei(u8 num)
{
  LED_A0=num&0x01;
	LED_A1=(num&0x02)>>1;
	LED_A2=(num&0x04)>>2;
}
//74HC595����
//�������ʾ
//num:��ʾ����
//wei:Ҫ��ʾ������ܱ�� 0-7(��8�������)
void LED_Write_Data(u8 duan,u8 wei)
{
	u8 i;
//	duan = smg_num[num];
	for( i=0;i<8;i++)//���Ͷ�
	{
		LED_DS=(duan>>i)&0x01;
		LED_SCK=0;
		delay_us(5);
		LED_SCK=1;
	}
    LED_Wei(wei);//��ѡ��λ
}
//74HC595����
//�����ˢ����ʾ
void LED_Refresh(void)
{
	LED_LCLK=1;
	delay_us(5);
	LED_LCLK=0;
}





