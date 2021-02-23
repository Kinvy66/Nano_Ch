#include "sys_api.h"

u8 Sys_Init()
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
	KEY_Init();				//������ʼ��
	OLED_Init();	 
//	SPI_Flash_Init();			//W25QXX��ʼ��
	mem_init();				//�ڴ�س�ʼ��
	
	return 0;
}

u8 Font_Init()
{
	u8 key,t;
	FileSys_Init();		//��ʼ���ļ�ϵͳ��׼�������ļ�
	if(font_init())		//����ֿ�,û���ֿ⣬�����ֿ��ļ�
	{
		key=update_font();//�����ֿ�
		if(key)	//����ʧ��
		{
			printf("FONT update failed!\r\n");
			printf("err:%d\r\n",key);
		}
		else 
		{
			printf("FONT update successfully!\r\n");
		}
	}
	else
	{
		return 0;
	}
}