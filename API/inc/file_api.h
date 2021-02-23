#ifndef __FILE_API_H
#define __FILE_API_H
#include "sys_api.h"

//´íÎó´úÂë
//#define FILE_ERR_CODE 0

typedef enum 
{
	FILE_OK=0,
} FILE_ERR_CODE;


u8 FileSys_Init();
void USB_Connecte();


#endif


