#include "led.h"

/**
  * @brief LED Init
  *         
  * @param  None
  *         
  * @retval None
  */
void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);  
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  			
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed =	GPIO_Speed_50MHz;	
	GPIO_Init(GPIOC,&GPIO_InitStructure);				
	
	LED0 = 1;
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
}







