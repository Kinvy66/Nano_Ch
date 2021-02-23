#ifndef __SMG_H
#define __SMG_H

#include "sys.h"

////74HC138������
#define LED_A0 PCout(10) //A0��ַ��
#define LED_A1 PCout(11) //A1��ַ��
#define LED_A2 PCout(12) //A2��ַ��

////74HC595������
#define LED_DS		PBout(3) //������
#define LED_LCLK	PBout(4) //����ʱ����
#define LED_SCK		PBout(5) //ʱ����

//u8 smg_num[]={0xfc,0x60,0xda,0xf2,0x66,0xb6,0xbe,0xe0,0xfe,
//							0xf6,0xee,0x3e,0x9c,0x7a,0x9e,0x8e,0x01,0x00};


void LED_SMG_Init(void);
void LED_Refresh(void);
void LED_Write_Data(u8 duan,u8 wei);

#endif




