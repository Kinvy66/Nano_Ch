# STM32_Nano中文显示

##  硬件

* 正点原子STM32F103_Nano开发板以及自制扩展板，0.96OLED(IIC)

  注：板子原来的flash芯片是W25Q16(2MB),容量不够，换成了W25Q64(8MB)



<img src="https://kinvy-images.oss-cn-beijing.aliyuncs.com/Images/IMG_1032.JPG" alt="IMG_1032" style="zoom:50%;" />





## 软件设计

* 使用STM32的USB功能，将flash芯片模拟成一个u盘，将数据线插在板子的USB_SLAVE接口，电脑的资源管理器就可以识别到flash
* 程序设计中使用了Fatfs文件系统，flash的4MB用做文件系统，第一次连接电脑需要将flash在电脑上格式化为Fat32格式
* 将工程文件下的font文件中的所有文件复制到flash中FONT文件夹下
* 程序会自动将字库文件更新到flash的后4MB空间中

说明：flash不要频繁的读写，否则flash易爆



## 程序完成度

OLED驱动，USB驱动，Fatfs文件系统移植调试成功，各模块单独测试OK，程序的主体逻辑和优化没有写







## 文件说明

font：汉字（GBK2312）点阵文件和Unicode编码，ASCII码点阵文件

