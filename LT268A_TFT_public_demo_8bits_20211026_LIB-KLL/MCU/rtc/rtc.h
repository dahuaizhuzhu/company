#ifndef _rtc_h
#define _rtc_h
#include "LT268A.h"
#include "uart.h"


typedef struct DS1302DATA  
{  
	UINT8 year;    //年
	UINT8 month;   //月
	UINT8 day;     //日
	UINT8 hour;    //时
	UINT8 min;     //分
	UINT8 sec;     //秒
	UINT8 week;    //周
}DS1302DATA;
extern struct DS1302DATA gRtcTime;

//#define DS1302_RST_RESET  	(EPORT0->U8EPDR.int5=0)
//#define DS1302_RST_SET  	(EPORT0->U8EPDR.int5=1)
//#define DS1302_CLK_RESET    (EPORT0->U8EPDR.int3=0)
//#define DS1302_CLK_SET  	(EPORT0->U8EPDR.int3=1)
//#define DS1302_DATOUT_RESET (EPORT0->U8EPDR.int4=0)
//#define DS1302_DATOUT_SET	(EPORT0->U8EPDR.int4=1)

#define  DS1302_CLK		(EPORT0->U8EPDR.int3)
#define  DS1302_RST		(EPORT0->U8EPDR.int5)
#define  DS1302_DATOUT	(EPORT0->U8EPDR.int4)
#define DS1302_DAT_INPUT()	EPORT0->EPDDR &=~(1<<4);
#define DS1302_DAT_OUTPUT()	EPORT0->EPDDR |= (1<<4);

//芯片寄存器地址定义 定义的写地址，读需要+1  
#define DS1302_SEC_REG          0x80        //秒数据地址  
#define DS1302_MIN_REG          0x82        //分数据地址  
#define DS1302_HR_REG           0x84        //时数据地址  
#define DS1302_DATE_REG         0x86        //日数据地址  
#define DS1302_MONTH_REG        0x88        //月数据地址  
#define DS1302_DAY_REG          0x8a        //星期几数据地址  
#define DS1302_YEAR_REG         0x8c        //年数据地址  
#define DS1302_CONTROL_REG      0x8e        //写保护寄存器地址  
#define DS1302_CHARGER_REG      0x90        //涓流充电寄存器              
#define DS1302_CLKBURST_REG     0xbe        //脉冲串寄存器  
#define DS1302_RAM_BASE         0X30        //RAM基础地址 

#define CLOCKSTOP               0X80  
#define CLOCKSTART              0X00  

void LT_RtcInit(void);
void LT_Ds1302Write(UINT8 address,UINT8 dat);
void LT_Ds1302WriteTimeAll(UINT8 start);
void LT_Ds1302Readtime(void);

#endif
