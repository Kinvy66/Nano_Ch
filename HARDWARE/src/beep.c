#include "beep.h"

/**
  * @brief	������IO��ʼ��
  *         
  * @param  None
  *         
  * @retval None
  */
void BEEP_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;  //����GPIO��ʼ��ʼ���ṹ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  //ʹ��GPIOC��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  			//LED����������PC13
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//GPIO��ģʽΪ�������
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_50MHz;	//������ٶ�Ϊ50MHz
	GPIO_Init(GPIOB,&GPIO_InitStructure);				//��ʼ��PC13
	
	BEEP = 1;
	
}



