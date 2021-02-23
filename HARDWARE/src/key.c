#include "key.h"
#include "delay.h"
#include "led.h"


/**
  * @brief ������ʼ��
  *         
  * @param  None
  *         
  * @retval None
  */
void KEY_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE); //ʹ��GPIO��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			//WK_UP
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	//��������
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;	//KEY0  KEY1		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	//KEY2 		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//��������
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	

}

/**
  * @brief	��ȡ��������
  *         
  * @param  Mode, 0:�������¼���Ч  1:���������ɿ�����Ч
  *         
  * @retval 0,û�а�������  
	*					1,KEY0����
	*					2,KEY1����
	*					3,KEY2����
	*					4,WK_UP����
  */
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(WK_UP==1)return WKUP_PRES; 
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0)key_up=1; 	     
	return 0;// �ް�������
}





