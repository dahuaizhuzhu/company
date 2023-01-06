#include "rtc.h"
#include "LT268A.h"
//#include "uart_lib.h"
#include "delay.h"
struct DS1302DATA gRtcTime ={18,11,25,9,42,5,7};


  
static UINT8 LT_AsciiToBcd(UINT8 asciiData)
{  
	UINT8 bcdData = 0;
	bcdData = (((asciiData/10)<<4)|((asciiData%10)));  
	return bcdData;  
}  

UINT8 LT_BcdToAscii(UINT8 bcdData)
{  
	UINT8 asciiData = 0;
	asciiData = (((bcdData&0xf0)>>4)*10 + (bcdData&0x0f));  
	return asciiData;  
} 

UINT8 DS1302_DATIN(void)
{

			if(((EPORT0->EPPDR)&0X10))
				return 1;
			else
				return 0;

}

void LT_RtcInit(void)
{
	//RST  int0[5]
	EPORT0->EPDDR |= (1<<5);

	//CLK  int0[3]
	EPORT0->EPDDR |= (1<<3);

	//IO   int0[4]
	EPORT0->EPDDR |= (1<<4);

}
//��ȡһ���ֽڵ�ʱ��   Bit_RESET
UINT8 LT_Ds1302ReadByte(void)
{  
	UINT8 i = 0, dat = 0;
	DS1302_DAT_INPUT();
	Delay_us(5);
	for(i = 0; i <8; i++)  
	{  
		dat >>= 1;  
		if(DS1302_DATIN() == 1)dat |= 0x80;
		DS1302_CLK = 1;
		Delay_us(2);
		DS1302_CLK = 0;
		Delay_us(2);
	}  
	return dat;  
}  
  
//д��һ���ֽڵ�ʱ��  
void LT_Ds1302WriteByte(UINT8 dat)
{  
	UINT8 i = 0, data = dat;
	DS1302_DAT_OUTPUT();
	DS1302_CLK = 0;
	Delay_us(2);
	for(i = 0; i < 8; i++)  
	{  
		DS1302_DATOUT = data&0x01;
		Delay_us(2);
		DS1302_CLK = 1;
		Delay_us(2);
		DS1302_CLK = 0;
		data >>= 1;  
	}  
}  
  
//д��һ���Ĵ���  
void LT_Ds1302Write(UINT8 address,UINT8 dat)
{  
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	LT_Ds1302WriteByte(address);  
	LT_Ds1302WriteByte(dat);  
	DS1302_CLK = 1;
	DS1302_RST = 0;
}  

//��ȡһ���ֽ�  
UINT8 LT_Ds1302Read(UINT8 address)
{  
	UINT8 data = 0;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	LT_Ds1302WriteByte(address|0x01);
	data = LT_Ds1302ReadByte();  
	DS1302_CLK = 1;
	DS1302_RST = 0;
	return data;  
} 


//����д��ʱ��  
void LT_Ds1302WriteTimeSingel(UINT8 address,UINT8 dat)
{  
	LT_Ds1302Write(DS1302_CONTROL_REG,0x00);  //ȡ��д����  
	LT_Ds1302Write(address,dat);  
	LT_Ds1302Write(DS1302_CONTROL_REG,0x80);  //��д����  
}  
  
//һ���������ʱ�����  
//start��ǰʱ�����л���ֹͣ  
void LT_Ds1302WriteTimeAll(UINT8 start)
{  
	LT_Ds1302Write(DS1302_CONTROL_REG,0x00);                          //ȡ��д����  
		LT_Ds1302Write(DS1302_SEC_REG,(LT_AsciiToBcd(gRtcTime.sec)|start));
		LT_Ds1302Write(DS1302_MIN_REG,LT_AsciiToBcd(gRtcTime.min));
		LT_Ds1302Write(DS1302_HR_REG,LT_AsciiToBcd(gRtcTime.hour));
		LT_Ds1302Write(DS1302_DAY_REG,LT_AsciiToBcd(gRtcTime.week));
		LT_Ds1302Write(DS1302_DATE_REG,LT_AsciiToBcd(gRtcTime.day));
		LT_Ds1302Write(DS1302_MONTH_REG,LT_AsciiToBcd(gRtcTime.month));

		LT_Ds1302Write(DS1302_YEAR_REG,LT_AsciiToBcd(gRtcTime.year));
		LT_Ds1302Write(DS1302_CONTROL_REG,0x80);                           //��д����                      //��д����
}  

//��ȡʱ���ʱ��Ĭ����ʱ��������  
void LT_Ds1302Readtime(void)  
{  
	gRtcTime.sec   = LT_BcdToAscii(LT_Ds1302Read(DS1302_SEC_REG));    //��
		gRtcTime.min   = LT_BcdToAscii(LT_Ds1302Read(DS1302_MIN_REG));    //��
		gRtcTime.hour  = LT_BcdToAscii(LT_Ds1302Read(DS1302_HR_REG));     //Сʱ
		gRtcTime.week  = LT_BcdToAscii(LT_Ds1302Read(DS1302_DAY_REG));    //���ڼ�
		gRtcTime.day   = LT_BcdToAscii(LT_Ds1302Read(DS1302_DATE_REG));   //��
		gRtcTime.month = LT_BcdToAscii(LT_Ds1302Read(DS1302_MONTH_REG));  //��
		gRtcTime.year  = LT_BcdToAscii(LT_Ds1302Read(DS1302_YEAR_REG));   //��
		while(UART0->U8SCISR1.TC == 0){};
		LT_SingleByteToPc(gRtcTime.year);
		LT_SingleByteToPc(gRtcTime.month);
		LT_SingleByteToPc(gRtcTime.day);
		LT_SingleByteToPc(gRtcTime.hour);
		LT_SingleByteToPc(gRtcTime.min);
		LT_SingleByteToPc(gRtcTime.sec);
		LT_SingleByteToPc(gRtcTime.week);
} 




