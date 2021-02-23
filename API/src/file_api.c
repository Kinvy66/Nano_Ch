#include "file_api.h"
#include "usb_prop.h"

u8 FileSys_Init()
{
//	extern u16 SPI_FLASH_TYPE;
	u8 res;
	u8 err= 0;
		
	SPI_Flash_Init();
	err = exfuns_init();
	if(err)
	{
		printf("RAM err\r\n");
	}
	
	if(SPI_FLASH_TYPE == W25Q32 ||
		SPI_FLASH_TYPE == W25Q64 ||
		SPI_FLASH_TYPE == W25Q128) 		//TODO:添加4MB和16MB的flash兼容
	{
		printf("flash SIZE: 8MB\r\n");
		res=f_mount(fs[0],"0:",1); 		//挂载FLASH.	
		if(res==FR_NO_FILESYSTEM)	//FLASH磁盘,FAT文件系统错误,重新格式化FLASH
		{
			printf("Flash Disk Formatting...\r\n");
			res=f_mkfs("0:",1,4096);	//格式化FLASH,0,  盘符0,不需要引导区,8个扇区为1个簇
			if(res==FR_OK) 
			{
				f_setlabel((const TCHAR *)"0:Kinvy");	//设置Flash磁盘的名字为：
				printf("Flash Disk Format Finish\r\n");
			}
			else
			{
				printf("Flash Disk Format Error\r\n");
			}
			delay_ms(1000);
		}
	}
	else	//没有flash
	{
		//TODO:
		
	}
	
	if(SD_Initialize()) 	//没有SD
	{
		printf("SD Error!\r\n");
		
	}
	else		//SD卡
	{
		
	}
		
	return 0;
}

void USB_Connecte()
{
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA; 
	
	static bool connete = 0;

	if(SPI_FLASH_TYPE!=W25Q64)
	{
		printf("flash Error!\r\n");
	}
	else //SPI FLASH 正常
	{   															  
 	   	Mass_Memory_Size[0]=4*1024*1024;//前4M字节
	    Mass_Block_Size[0] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
		printf("SPI FLASH Size:4096KB\r\n");
	}

	if(SD_Initialize()) 
	{
		printf("SD Card Error!\r\n");
		Max_Lun = 0;
	}
	else //SD 卡正常
	{   															  
// 	    Mass_Memory_Size[1]=(long long)SD_GetSectorCount()*512;//得到SD卡容量（字节），当SD卡容量超过4G的时候,需要用到两个u32来表示
//	    Mass_Block_Size[1] =512;//因为我们在Init里面设置了SD卡的操作字节为512个,所以这里一定是512个字节.
//	    Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[0];
 	}
	
  	delay_ms(1800);
	if(!connete)
	{
		USB_Port_Set(0); 	//USB先断开
	}
	delay_ms(300);
   	USB_Port_Set(1);	//USB再次连接   
	printf("USB Connecting...\r\n");
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//为USB数据缓存区申请内存
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//申请内存
 	//USB配置
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	    
//	while(1)
//	{	
//		delay_ms(1);				  
//		if(USB_STA!=USB_STATUS_REG)//状态改变了 
//		{	 						   
//			if(USB_STATUS_REG&0x01)//正在写		  
//			{
//				printf("USB Writing...\r\n");
//			}
//			if(USB_STATUS_REG&0x02)//正在读
//			{
//				printf("USB Reading...\r\n");				
//			}	 										  
//			if(USB_STATUS_REG&0x04)
//			{
//				printf("USB Write Err\r\n");	
//			}
//			else 
//			{
////				LCD_Fill(60,210,240,210+16,WHITE);//清除显示	 
//			}				
//			if(USB_STATUS_REG&0x08)
//			{
//				printf("USB Read Err\r\n");	
//			}
//			else 
//			{
////				LCD_Fill(60,230,240,230+16,WHITE);//清除显示    
//			}
//				
//			USB_STA=USB_STATUS_REG;//记录最后的状态
//		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED) 
			{ 
				printf("USB Connected\r\n");
				connete = 1;
			} 
			else 
			{ 
				printf("USB DisConnected\r\n"); 
			} 
			Divece_STA=bDeviceState;
		}
//		tct++;
//		if(tct==200)
//		{
//			tct=0;
//			LED0=!LED0;//提示系统在运行
//			if(USB_STATUS_REG&0x10)
//			{
//				offline_cnt=0;//USB连接了,则清除offline计数器
//				bDeviceState=CONFIGURED;
//			}else//没有得到轮询 
//			{
//				offline_cnt++;  
//				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s内没收到在线标记,代表USB被拔出了
//			}
//			USB_STATUS_REG=0;
//		}
//	};  										    			    

}















