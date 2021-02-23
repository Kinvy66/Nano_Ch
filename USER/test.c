#include "test.h"

const u8 TEXT_Buffer[]={"SPI TEST"};
u8 Hz[32] = {0};
#define SIZE sizeof(TEXT_Buffer)
	
//void System_Init()
//{
//	delay_init();	    	 //延时函数初始化	  
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//	uart_init(9600);	 	//串口初始化为9600
//	LED_Init();		  		//初始化与LED连接的硬件接口
//	KEY_Init();				//按键初始化
////	mem_init();				//内存池初始化
//	OLED_Init();	 
//	SPI_Flash_Init();			//W25QXX初始化
//	
//}
	
void show_Hz(int i)
{
	u8 Hz[32] = {0};
	OLED_Clear();
 	OLED_ShowString(0,0,"Start Read.... ",16,1);
	SPI_Flash_Read(Hz,0xB000+((701+i)*32),32);					//从倒数第100个地址处开始,读出SIZE个字节
	OLED_ShowChinese(0,17,Hz,16,1);
	//OLED_ShowString(0,17,datatemp,16,1);//显示读到的字符串
	OLED_Refresh();
}

void SPI_Test()
{
	u8 key;
	u32 FLASH_SIZE; 
	u32 hz_num = 0;
	u16 i = 0;
	
	SPI_Flash_Init();			//W25QXX初始化

	while(SPI_Flash_ReadID()!=W25Q64)								//检测不到W25Q128
	{
		printf("W25Q64 Check Failed!");
		OLED_ShowString(0, 0, "Flash Failed!",16,1);
		delay_ms(500);
		OLED_ShowString(0, 0, "Please Check!",16,1);
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
	printf("Flash Ready!");
	OLED_ShowString(0, 0, "Flash Ready!",16,1);
	OLED_Refresh();
	FLASH_SIZE=64*1024*1024;	//FLASH 大小为8M字节
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1按下,写入W25QXX
		{
			OLED_Clear();
 			OLED_ShowString(0,0,"Start Write....",16,1); 
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);			//从倒数第100个地址处开始,写入SIZE长度的数据
			OLED_ShowString(0,17,"Write Finished!",16,1);	//提示传送完成
			OLED_Refresh();
		}
		if(key==KEY0_PRES)	//KEY0按下,读取字符串并显示
		{
//			OLED_Clear();
// 			OLED_ShowString(0,0,"Start Read.... ",16,1);
//			W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//从倒数第100个地址处开始,读出SIZE个字节
//			OLED_ShowString(0,17,datatemp,16,1);//显示读到的字符串
//			OLED_Refresh();
			show_Hz(hz_num);
			hz_num++;
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}

void Mem_Test()
{
	u8 key;		 
 	u8 i=0;	    
	u8 *p=0;
	u8 *tp=0;
	u8 paddr[18];			        //存放P Addr:+p地址的ASCII值 
	
	printf("NANO STM32\r\n");
	printf("MALLOC TEST\r\n");
    printf("KEY0:Malloc\r\n");
    printf("KEY1:Write Data\r\n");
	printf("KEY2:Free\r\n");
	OLED_Clear();
	OLED_ShowString(0,0,"MALLOC TEST",16,0);
	OLED_Refresh();
	while(1)
	{
		key=KEY_Scan(0);//不支持连按	
		switch(key)
		{
			case 0:		//没有按键按下	
				break;
			case KEY0_PRES:	 //KEY0按下
				p=mymalloc(2048);//申请2K字节
				if(p!=NULL)sprintf((char*)p,"Memory Malloc Test%03d",i);//向p写入一些内容
				break;
			case KEY1_PRES:	 //KEY1按下	   
				if(p!=NULL)
				{
					sprintf((char*)p,"Memory Malloc Test%03d",i);//更新显示内容 	 
					printf("%s\r\n",p);//显示P的内容
				}
				break;
			case KEY2_PRES:	//KEY2按下	  
				myfree(p);	//释放内存
				p=0;		//指向空地址
				break; 
		}
		if(tp!=p)
		{
			tp=p;
			printf("\r\nSRAM USED:%d%%\r\n",mem_perused());//显示内存使用率
			sprintf((char*)paddr,"P Addr:0X%08X",(u32)tp);
			printf("%s\r\n",paddr);//显示p的地址
			if(p) printf("%s\r\n",p);//显示P的内容
		}
		delay_ms(10);   
		i++;
		if((i%20)==0)//DS0闪烁.
		{
 			LED0=!LED0;
 		}
	} 
}

void USB_Test()
{
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA; 
   
	
//	POINT_COLOR=RED;	//设置字体为红色	   
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"USB Card Reader TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
// 	SPI_Flash_Init();
	if(SD_Initialize()) 
	{
//		LCD_ShowString(60,130,200,16,16,"SD Card Error!");	//检测SD卡错误
		printf("SD Card Error!\r\n");
	}
	else //SD 卡正常
	{   															  
//		LCD_ShowString(60,130,200,16,16,"SD Card Size:     MB");
 	    Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;//得到SD卡容量（字节），当SD卡容量超过4G的时候,需要用到两个u32来表示
	    Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
// 		LCD_ShowNum(164,130,Mass_Memory_Size[0]>>20,5,16);	//显示SD卡容量
 	}
	if(SPI_FLASH_TYPE!=W25Q64)
	{
//		LCD_ShowString(60,130,200,16,16,"W25Q64 Error!");	//检测SD卡错误
		printf("W25Q64 Error!\r\n");
	}
	else //SPI FLASH 正常
	{   															  
 	   	Mass_Memory_Size[1]=4096*1024;//前4.8M字节
	    Mass_Block_Size[1] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	    Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[1];
//		LCD_ShowString(60,150,200,16,16,"SPI FLASH Size:4916KB");	 
		printf("SPI FLASH Size:4096KB\r\n");
	}
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB先断开
	delay_ms(300);
   	USB_Port_Set(1);	//USB再次连接   
// 	LCD_ShowString(60,170,200,16,16,"USB Connecting...");//提示SD卡已经准备了	
	printf("USB Connecting...\r\n");
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//申请内存
 	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	   	    
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
//			LCD_Fill(60,190,240,190+16,WHITE);//清除显示			  	   
			if(USB_STATUS_REG&0x01)//正在写		  
			{
//				LCD_ShowString(60,190,200,16,16,"USB Writing...");//提示USB正在写入数据	 
				printf("USB Writing...\r\n");
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
//				LCD_ShowString(60,190,200,16,16,"USB Reading...");//提示USB正在读出数据 
				printf("USB Reading...\r\n");				
			}	 										  
			if(USB_STATUS_REG&0x04)
			{
//				LCD_ShowString(60,210,200,16,16,"USB Write Err ");//提示写入错误
				printf("USB Write Err\r\n");	
			}
			else 
			{
//				LCD_Fill(60,210,240,210+16,WHITE);//清除显示	 
			}				
			if(USB_STATUS_REG&0x08)
			{
//				LCD_ShowString(60,230,200,16,16,"USB Read  Err ");//提示读出错误
				printf("USB Read Err\r\n");	
			}
			else 
			{
//				LCD_Fill(60,230,240,230+16,WHITE);//清除显示    
			}
				
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED) 
			{ 
			printf("USB Connected\r\n");	
			} //LCD_ShowString(60,170,200,16,16,"USB Connected    ");//提示USB连接已经建立
			else 
			{ 
				printf("USB DisConnected\r\n"); 
			} //LCD_ShowString(60,170,200,16,16,"USB DisConnected ");//提示USB被拔出了
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//提示系统在运行
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=CONFIGURED;
			}else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
			}
			USB_STATUS_REG=0;
		}
	};  										    			    

}



void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//申请内存
	if(SD_ReadDisk(buf,sec,1)==0)	//读取0扇区的内容
	{	
//		LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//打印sec扇区数据    	   
		printf("\r\nDATA ENDED\r\n");
//		LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
	}
	myfree(buf);//释放内存	
}

void SD_Test()
{
	u8 key;		 
	u32 sd_size;
	u8 t=0;	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	  
	uart_init(9600);	 	//串口初始化为9600
	LED_Init();		  		//初始化与LED连接的硬件接口
//	LCD_Init();			   	//初始化LCD	
 	KEY_Init();				//按键初始化  
 	mem_init();				//初始化内存池	 
// 	POINT_COLOR=RED;//设置字体为红色 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"SD CARD TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/13");  
//	LCD_ShowString(60,130,200,16,16,"KEY0:Read Sector 0");	   
 	while(SD_Initialize())//检测不到SD卡
	{
//		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		printf("SD Card Error!\r\n");
		delay_ms(500);					
//		LCD_ShowString(60,150,200,16,16,"Please Check! ");
		printf("Please Check!\r\n");
		delay_ms(500);
		LED0=!LED0;//DS0闪烁
	}
// 	POINT_COLOR=BLUE;//设置字体为蓝色 
//	//检测SD卡成功 											    
//	LCD_ShowString(60,150,200,16,16,"SD Card OK    ");
//	LCD_ShowString(60,170,200,16,16,"SD Card Size:     MB");
	printf("SD Card OK   \r\n");
	sd_size=SD_GetSectorCount();//得到扇区数
	printf("SD Card Size: %dMB\r\n",sd_size>>11);
//	LCD_ShowNum(164,170,sd_size>>11,5,16);//显示SD卡容量
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)SD_Read_Sectorx(0);//KEY0按,读取SD卡扇区0的内容
		t++;
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;
			t=0;
		}
	}    	   

}