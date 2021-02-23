#include "sys_api.h"

u8 Sys_Init()
{
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
	KEY_Init();				//按键初始化
	OLED_Init();	 
//	SPI_Flash_Init();			//W25QXX初始化
	mem_init();				//内存池初始化
	
	return 0;
}

u8 Font_Init()
{
	u8 key,t;
	FileSys_Init();		//初始化文件系统，准备复制文件
	if(font_init())		//检查字库,没有字库，更新字库文件
	{
		key=update_font();//更新字库
		if(key)	//更新失败
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