#ifndef __SYSTEM_API_H
#define __SYSTEM_API_H
#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "sys.h"
#include "led.h"
#include "beep.h"
#include "oled.h"
#include "key.h"

//flash and SD
#include "spi.h"
#include "flash.h"
#include "mmc_sd.h"

//RAM 
#include "malloc.h"

//USB
#include "mass_mal.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "memory.h"	    
#include "usb_bot.h"

//FatFs
#include "ff.h"  
#include "exfuns.h" 

//TEXT
#include "text.h"
#include "fontupd.h"

#include "file_api.h"

u8 Sys_Init();
u8 Font_Init();

#endif


