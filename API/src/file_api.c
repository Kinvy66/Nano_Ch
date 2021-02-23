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
		SPI_FLASH_TYPE == W25Q128) 		//TODO:���4MB��16MB��flash����
	{
		printf("flash SIZE: 8MB\r\n");
		res=f_mount(fs[0],"0:",1); 		//����FLASH.	
		if(res==FR_NO_FILESYSTEM)	//FLASH����,FAT�ļ�ϵͳ����,���¸�ʽ��FLASH
		{
			printf("Flash Disk Formatting...\r\n");
			res=f_mkfs("0:",1,4096);	//��ʽ��FLASH,0,  �̷�0,����Ҫ������,8������Ϊ1����
			if(res==FR_OK) 
			{
				f_setlabel((const TCHAR *)"0:Kinvy");	//����Flash���̵�����Ϊ��
				printf("Flash Disk Format Finish\r\n");
			}
			else
			{
				printf("Flash Disk Format Error\r\n");
			}
			delay_ms(1000);
		}
	}
	else	//û��flash
	{
		//TODO:
		
	}
	
	if(SD_Initialize()) 	//û��SD
	{
		printf("SD Error!\r\n");
		
	}
	else		//SD��
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
	else //SPI FLASH ����
	{   															  
 	   	Mass_Memory_Size[0]=4*1024*1024;//ǰ4M�ֽ�
	    Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
		printf("SPI FLASH Size:4096KB\r\n");
	}

	if(SD_Initialize()) 
	{
		printf("SD Card Error!\r\n");
		Max_Lun = 0;
	}
	else //SD ������
	{   															  
// 	    Mass_Memory_Size[1]=(long long)SD_GetSectorCount()*512;//�õ�SD���������ֽڣ�����SD����������4G��ʱ��,��Ҫ�õ�����u32����ʾ
//	    Mass_Block_Size[1] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
//	    Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[0];
 	}
	
  	delay_ms(1800);
	if(!connete)
	{
		USB_Port_Set(0); 	//USB�ȶϿ�
	}
	delay_ms(300);
   	USB_Port_Set(1);	//USB�ٴ�����   
	printf("USB Connecting...\r\n");
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//�����ڴ�
 	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	    
//	while(1)
//	{	
//		delay_ms(1);				  
//		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
//		{	 						   
//			if(USB_STATUS_REG&0x01)//����д		  
//			{
//				printf("USB Writing...\r\n");
//			}
//			if(USB_STATUS_REG&0x02)//���ڶ�
//			{
//				printf("USB Reading...\r\n");				
//			}	 										  
//			if(USB_STATUS_REG&0x04)
//			{
//				printf("USB Write Err\r\n");	
//			}
//			else 
//			{
////				LCD_Fill(60,210,240,210+16,WHITE);//�����ʾ	 
//			}				
//			if(USB_STATUS_REG&0x08)
//			{
//				printf("USB Read Err\r\n");	
//			}
//			else 
//			{
////				LCD_Fill(60,230,240,230+16,WHITE);//�����ʾ    
//			}
//				
//			USB_STA=USB_STATUS_REG;//��¼����״̬
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
//			LED0=!LED0;//��ʾϵͳ������
//			if(USB_STATUS_REG&0x10)
//			{
//				offline_cnt=0;//USB������,�����offline������
//				bDeviceState=CONFIGURED;
//			}else//û�еõ���ѯ 
//			{
//				offline_cnt++;  
//				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
//			}
//			USB_STATUS_REG=0;
//		}
//	};  										    			    

}















