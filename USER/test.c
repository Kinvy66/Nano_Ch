#include "test.h"

const u8 TEXT_Buffer[]={"SPI TEST"};
u8 Hz[32] = {0};
#define SIZE sizeof(TEXT_Buffer)
	
//void System_Init()
//{
//	delay_init();	    	 //��ʱ������ʼ��	  
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
//	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
//	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
//	KEY_Init();				//������ʼ��
////	mem_init();				//�ڴ�س�ʼ��
//	OLED_Init();	 
//	SPI_Flash_Init();			//W25QXX��ʼ��
//	
//}
	
void show_Hz(int i)
{
	u8 Hz[32] = {0};
	OLED_Clear();
 	OLED_ShowString(0,0,"Start Read.... ",16,1);
	SPI_Flash_Read(Hz,0xB000+((701+i)*32),32);					//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
	OLED_ShowChinese(0,17,Hz,16,1);
	//OLED_ShowString(0,17,datatemp,16,1);//��ʾ�������ַ���
	OLED_Refresh();
}

void SPI_Test()
{
	u8 key;
	u32 FLASH_SIZE; 
	u32 hz_num = 0;
	u16 i = 0;
	
	SPI_Flash_Init();			//W25QXX��ʼ��

	while(SPI_Flash_ReadID()!=W25Q64)								//��ⲻ��W25Q128
	{
		printf("W25Q64 Check Failed!");
		OLED_ShowString(0, 0, "Flash Failed!",16,1);
		delay_ms(500);
		OLED_ShowString(0, 0, "Please Check!",16,1);
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
	printf("Flash Ready!");
	OLED_ShowString(0, 0, "Flash Ready!",16,1);
	OLED_Refresh();
	FLASH_SIZE=64*1024*1024;	//FLASH ��СΪ8M�ֽ�
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)	//KEY1����,д��W25QXX
		{
			OLED_Clear();
 			OLED_ShowString(0,0,"Start Write....",16,1); 
			SPI_Flash_Write((u8*)TEXT_Buffer,FLASH_SIZE-100,SIZE);			//�ӵ�����100����ַ����ʼ,д��SIZE���ȵ�����
			OLED_ShowString(0,17,"Write Finished!",16,1);	//��ʾ�������
			OLED_Refresh();
		}
		if(key==KEY0_PRES)	//KEY0����,��ȡ�ַ�������ʾ
		{
//			OLED_Clear();
// 			OLED_ShowString(0,0,"Start Read.... ",16,1);
//			W25QXX_Read(datatemp,FLASH_SIZE-100,SIZE);					//�ӵ�����100����ַ����ʼ,����SIZE���ֽ�
//			OLED_ShowString(0,17,datatemp,16,1);//��ʾ�������ַ���
//			OLED_Refresh();
			show_Hz(hz_num);
			hz_num++;
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED0=!LED0;//��ʾϵͳ��������	
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
	u8 paddr[18];			        //���P Addr:+p��ַ��ASCIIֵ 
	
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
		key=KEY_Scan(0);//��֧������	
		switch(key)
		{
			case 0:		//û�а�������	
				break;
			case KEY0_PRES:	 //KEY0����
				p=mymalloc(2048);//����2K�ֽ�
				if(p!=NULL)sprintf((char*)p,"Memory Malloc Test%03d",i);//��pд��һЩ����
				break;
			case KEY1_PRES:	 //KEY1����	   
				if(p!=NULL)
				{
					sprintf((char*)p,"Memory Malloc Test%03d",i);//������ʾ���� 	 
					printf("%s\r\n",p);//��ʾP������
				}
				break;
			case KEY2_PRES:	//KEY2����	  
				myfree(p);	//�ͷ��ڴ�
				p=0;		//ָ��յ�ַ
				break; 
		}
		if(tp!=p)
		{
			tp=p;
			printf("\r\nSRAM USED:%d%%\r\n",mem_perused());//��ʾ�ڴ�ʹ����
			sprintf((char*)paddr,"P Addr:0X%08X",(u32)tp);
			printf("%s\r\n",paddr);//��ʾp�ĵ�ַ
			if(p) printf("%s\r\n",p);//��ʾP������
		}
		delay_ms(10);   
		i++;
		if((i%20)==0)//DS0��˸.
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
   
	
//	POINT_COLOR=RED;	//��������Ϊ��ɫ	   
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"USB Card Reader TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/15");	
// 	SPI_Flash_Init();
	if(SD_Initialize()) 
	{
//		LCD_ShowString(60,130,200,16,16,"SD Card Error!");	//���SD������
		printf("SD Card Error!\r\n");
	}
	else //SD ������
	{   															  
//		LCD_ShowString(60,130,200,16,16,"SD Card Size:     MB");
 	    Mass_Memory_Size[0]=(long long)SD_GetSectorCount()*512;//�õ�SD���������ֽڣ�����SD����������4G��ʱ��,��Ҫ�õ�����u32����ʾ
	    Mass_Block_Size[0] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
	    Mass_Block_Count[0]=Mass_Memory_Size[0]/Mass_Block_Size[0];
// 		LCD_ShowNum(164,130,Mass_Memory_Size[0]>>20,5,16);	//��ʾSD������
 	}
	if(SPI_FLASH_TYPE!=W25Q64)
	{
//		LCD_ShowString(60,130,200,16,16,"W25Q64 Error!");	//���SD������
		printf("W25Q64 Error!\r\n");
	}
	else //SPI FLASH ����
	{   															  
 	   	Mass_Memory_Size[1]=4096*1024;//ǰ4.8M�ֽ�
	    Mass_Block_Size[1] =512;//��Ϊ������Init����������SD���Ĳ����ֽ�Ϊ512��,��������һ����512���ֽ�.
	    Mass_Block_Count[1]=Mass_Memory_Size[1]/Mass_Block_Size[1];
//		LCD_ShowString(60,150,200,16,16,"SPI FLASH Size:4916KB");	 
		printf("SPI FLASH Size:4096KB\r\n");
	}
  	delay_ms(1800);
 	USB_Port_Set(0); 	//USB�ȶϿ�
	delay_ms(300);
   	USB_Port_Set(1);	//USB�ٴ�����   
// 	LCD_ShowString(60,170,200,16,16,"USB Connecting...");//��ʾSD���Ѿ�׼����	
	printf("USB Connecting...\r\n");
	Data_Buffer=mymalloc(BULK_MAX_PACKET_SIZE*2*4);	//ΪUSB���ݻ����������ڴ�
	Bulk_Data_Buff=mymalloc(BULK_MAX_PACKET_SIZE);	//�����ڴ�
 	//USB����
 	USB_Interrupts_Config();    
 	Set_USBClock();   
 	USB_Init();	    
	delay_ms(1800);	   	    
	while(1)
	{	
		delay_ms(1);				  
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
//			LCD_Fill(60,190,240,190+16,WHITE);//�����ʾ			  	   
			if(USB_STATUS_REG&0x01)//����д		  
			{
//				LCD_ShowString(60,190,200,16,16,"USB Writing...");//��ʾUSB����д������	 
				printf("USB Writing...\r\n");
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
//				LCD_ShowString(60,190,200,16,16,"USB Reading...");//��ʾUSB���ڶ������� 
				printf("USB Reading...\r\n");				
			}	 										  
			if(USB_STATUS_REG&0x04)
			{
//				LCD_ShowString(60,210,200,16,16,"USB Write Err ");//��ʾд�����
				printf("USB Write Err\r\n");	
			}
			else 
			{
//				LCD_Fill(60,210,240,210+16,WHITE);//�����ʾ	 
			}				
			if(USB_STATUS_REG&0x08)
			{
//				LCD_ShowString(60,230,200,16,16,"USB Read  Err ");//��ʾ��������
				printf("USB Read Err\r\n");	
			}
			else 
			{
//				LCD_Fill(60,230,240,230+16,WHITE);//�����ʾ    
			}
				
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==CONFIGURED) 
			{ 
			printf("USB Connected\r\n");	
			} //LCD_ShowString(60,170,200,16,16,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else 
			{ 
				printf("USB DisConnected\r\n"); 
			} //LCD_ShowString(60,170,200,16,16,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		tct++;
		if(tct==200)
		{
			tct=0;
			LED0=!LED0;//��ʾϵͳ������
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=CONFIGURED;
			}else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=UNCONNECTED;//2s��û�յ����߱��,����USB���γ���
			}
			USB_STATUS_REG=0;
		}
	};  										    			    

}



void SD_Read_Sectorx(u32 sec)
{
	u8 *buf;
	u16 i;
	buf=mymalloc(512);				//�����ڴ�
	if(SD_ReadDisk(buf,sec,1)==0)	//��ȡ0����������
	{	
//		LCD_ShowString(60,190,200,16,16,"USART1 Sending Data...");
		printf("SECTOR 0 DATA:\r\n");
		for(i=0;i<512;i++)printf("%x ",buf[i]);//��ӡsec��������    	   
		printf("\r\nDATA ENDED\r\n");
//		LCD_ShowString(60,190,200,16,16,"USART1 Send Data Over!");
	}
	myfree(buf);//�ͷ��ڴ�	
}

void SD_Test()
{
	u8 key;		 
	u32 sd_size;
	u8 t=0;	 
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600
	LED_Init();		  		//��ʼ����LED���ӵ�Ӳ���ӿ�
//	LCD_Init();			   	//��ʼ��LCD	
 	KEY_Init();				//������ʼ��  
 	mem_init();				//��ʼ���ڴ��	 
// 	POINT_COLOR=RED;//��������Ϊ��ɫ 
//	LCD_ShowString(60,50,200,16,16,"Mini STM32");	
//	LCD_ShowString(60,70,200,16,16,"SD CARD TEST");	
//	LCD_ShowString(60,90,200,16,16,"ATOM@ALIENTEK");
//	LCD_ShowString(60,110,200,16,16,"2014/3/13");  
//	LCD_ShowString(60,130,200,16,16,"KEY0:Read Sector 0");	   
 	while(SD_Initialize())//��ⲻ��SD��
	{
//		LCD_ShowString(60,150,200,16,16,"SD Card Error!");
		printf("SD Card Error!\r\n");
		delay_ms(500);					
//		LCD_ShowString(60,150,200,16,16,"Please Check! ");
		printf("Please Check!\r\n");
		delay_ms(500);
		LED0=!LED0;//DS0��˸
	}
// 	POINT_COLOR=BLUE;//��������Ϊ��ɫ 
//	//���SD���ɹ� 											    
//	LCD_ShowString(60,150,200,16,16,"SD Card OK    ");
//	LCD_ShowString(60,170,200,16,16,"SD Card Size:     MB");
	printf("SD Card OK   \r\n");
	sd_size=SD_GetSectorCount();//�õ�������
	printf("SD Card Size: %dMB\r\n",sd_size>>11);
//	LCD_ShowNum(164,170,sd_size>>11,5,16);//��ʾSD������
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY0_PRES)SD_Read_Sectorx(0);//KEY0��,��ȡSD������0������
		t++;
		delay_ms(10);
		if(t==20)
		{
			LED0=!LED0;
			t=0;
		}
	}    	   

}