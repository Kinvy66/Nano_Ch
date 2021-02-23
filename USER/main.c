#include "sys_api.h"
#include "file_api.h"

void FatFs_Test()
{
	FIL fil;
	u8 res;
	UINT bww;
	char buf[] = "fatfs test\r\n";
	
	u8 i = 0;
	res = f_open(&fil,"0:/test.txt",FA_READ|FA_WRITE|FA_OPEN_ALWAYS);
	res = f_write(&fil,buf,sizeof(buf)/sizeof(char),&bww);
	res = f_read(&fil,buf,50,&bww);

	f_close(&fil);
}




int main(void)
{	 
	Sys_Init();
	Font_Init();
	test01();
	
	while(1);
}
















