/*
 * TFTLCD.c
 *
 *  Created on: 2019年5月9日
 *      Author: cjc59
 */
#include "TFTLCD.h"
#include "delay.h"
#include "module_select.h"

UINT8 SPIx_ReadWriteByte(UINT8 TxData)
{
	unsigned char reV;
	SPI->SPSR = 0xffffffff;
	SPI->SPB0R = TxData;
	while((SPI->U32SPSR.SPI0F)==0);
	reV = SPI->SPB0R; //接收数据
	return reV;

}

UINT32 TFT_ReadID(void)
{
	UINT32 temp=0;
	WriteCommand_A0;
	CS_RESET;
	SPIx_ReadWriteByte(0x04);
	Delay_us(100);

	temp|=SPIx_ReadWriteByte(0xFF)<<16;
	temp|=SPIx_ReadWriteByte(0xFF)<<8;
	temp|=SPIx_ReadWriteByte(0xFF);
	CS_SET;
	return temp;
}

UINT8 TFT_ReadParameter(UINT8 TxData)
{
	UINT8 temp=0;
	WriteCommand_A0;
	CS_RESET;
	SPIx_ReadWriteByte(TxData);
	Delay_us(100);

	temp=SPIx_ReadWriteByte(0xFF);
	CS_SET;
	return temp;
}

void Reset_Init(void)
{
//	EPORT1->EPDDR |= (1<<1);	//GPIO输出
//	EPORT1->U8EPDR.int1 = 1;
	EFM->U16CCR.CCRTEST=1;
	EFM->U16CCR.CCRTEST=2;
	EFM->U16CCR.CCRTEST=3;
	EFM->U16CCR.SWDDIS=1;

	EPORT0->EPDDR |= (1<<0);	//GPIO输出
	EPORT0->EPPUE |= (1<<0);
	EPORT0->U8EPDR.int0 = 1;
}

//#if	LT268A_SPI
void A0_Init(void)
{
	PWM1->U32PPCR.PDDR |= (1<<0);		//GPIO输出
	PWM1->U32PPCR.PDR0=0;
}

/**
 * @file   SPI0_ReadWriteByte
 * @brief  读写一个字节
 * @param  TxData:要写入的字节
 * @reV 读取到的字节
 */
void SPI0_ReadWriteByte(UINT8 TxData)
{
//	unsigned char reV;
	SPI->SPSR = 0xffffffff;
	SPI->SPB0R = TxData;
	while((SPI->U32SPSR.SPI0F)==0);
//	reV = SPI->SPB0R; //接收数据
	//return reV;
}
//#endif

//#if	LT268A_Data_8
void Data_8_Port_Init(void)
{
	/*DB7--DB0数据线*/
	EFM->U16CCR.CCRTEST=1;		//寄存器写入的解锁
	EFM->U16CCR.CCRTEST=2;
	EFM->U16CCR.CCRTEST=3;

	EFM->U16CCR.EXTALDIS=1;		//xtal  配置为int1[7]功能
	EFM->U16CCR.RSTOUTDIS=1;	//rstout配置为int1[6]功能
	EFM->U16CCR.CLKOUTDIS=1;	//clkout配置为int1[0]功能

	CLOCK->U32LOSCCSR.LOSCCSTEST = 1;
	CLOCK->U32LOSCCSR.LOSCCSTEST = 2;
	CLOCK->U32LOSCCSR.LOSCCSTEST = 3;
	CLOCK->U32LOSCCSR.SXOSCEN = 0;	//32K_IO配置为int1[3]、int1[2]功能

	EPORT1->EPDDR =0xFF;		//DB[7:0]数据线配置为输出


	PWM1->U32PCR.CH2EN = 0;
	PWM1->U32PCR.CH1EN = 0;
	PWM1->U32PCR.CH0EN = 0;
	PWM0->U32PCR.CH3EN = 0;
	/*控制线*/
	PWM1->U32PPCR.PDDR |= (1<<2)|(1<<1)|(1<<0);	//RD、WR、RS配置为输出
	PWM1->U32PPCR.PDR2 = 1;
	PWM1->U32PPCR.PDR1 = 1;
	PWM1->U32PPCR.PDR0 = 1;

	PWM0->U32PPCR.PDDR |= (1<<3);	//CS配置为输出
	PWM0->U32PPCR.PDR3 = 1;

	EPORT1->EPDDR |= (1<<1);

	EPORT1->EPDDR |= (1<<4);
	EPORT1->EPDDR |= (1<<5);
}

//#endif


void TFT_CommandWrite(UINT8 cmd)
{
#if	LT268A_SPI
	WriteCommand_A0;
	CS_RESET;
	SPI0_ReadWriteByte(cmd);
	CS_SET;
#endif

#if	LT268A_Data_8
	Data_8_RD_SET;

	WriteCommand_A0;
	Data_8_CS_RESET;

	EPORT1->EPDR =cmd;

	Data_8_WR_RESET;
	Data_8_WR_SET;

	Data_8_CS_SET;

#endif
}

void TFT_DataWrite(UINT8 data)
{
#if	LT268A_SPI
	WriteData_A0;
	CS_RESET;
	SPI0_ReadWriteByte(data);
	CS_SET;
#endif

#if	LT268A_Data_8
	Data_8_RD_SET;

	WriteData_A0;
	Data_8_CS_RESET;

	EPORT1->EPDR =data;
	Data_8_WR_RESET;
	Data_8_WR_SET;

	Data_8_CS_SET;
#endif
}

//---------------------------TFT 初始化---------------------------
void LCD_TFT_Init(void)
{
	Reset_Init();

#if	LT268A_SPI
	A0_Init();
#endif

#if	LT268A_Data_8
	Data_8_Port_Init();
#endif

	LCD_SET;        //TFT_Reset
	Delay_ms(50);
	LCD_RESET;
	Delay_ms(50);
	LCD_SET;
	Delay_ms(120); //Delay 120ms

/*屏的初始化代码部分，Horizontal_screen部分为设置横竖屏，此处需根据实际情况调整*/
#if 1

	TFT_CommandWrite(0x11);
	Delay_ms(120);

	TFT_CommandWrite(0x36);

#if Horizontal_screen
//	TFT_DataWrite(0x60);
	TFT_DataWrite(0xA0);
#else
	TFT_DataWrite(0x00);
#endif

	TFT_CommandWrite(0x3A);
	TFT_DataWrite(0x55);

	TFT_CommandWrite(0xB2);
	TFT_DataWrite(0x0C);   //porch setting, back porch
	TFT_DataWrite(0x0C);   //front portch
	TFT_DataWrite(0x00);
	TFT_DataWrite(0x33);
	TFT_DataWrite(0x33);

	TFT_CommandWrite(0xB7);
	TFT_DataWrite(0x75);   //VGH=15V, VGL=-10.43

	TFT_CommandWrite(0xBB);
	TFT_DataWrite(0x2B);   //Vcom  16

	TFT_CommandWrite(0xC0);
	TFT_DataWrite(0x2C);

	TFT_CommandWrite(0xC2);
	TFT_DataWrite(0x01);

	TFT_CommandWrite(0xC3);
	TFT_DataWrite(0x14);   //GVDD=4.55v,

	TFT_CommandWrite(0xC4);
	TFT_DataWrite(0x20);   //VDV, 0x20:0v

	TFT_CommandWrite(0xC6);
	TFT_DataWrite(0x0F);   //60Hz

	TFT_CommandWrite(0xD0);
	TFT_DataWrite(0xA4);
	TFT_DataWrite(0xA1);

	TFT_CommandWrite(0xE0);
	TFT_DataWrite(0xD0);   //V63[7-4] & V0[3-0]
	TFT_DataWrite(0x0D);   //V1[5-0]
	TFT_DataWrite(0x14);   //V2[5-0]
	TFT_DataWrite(0x0D);   //V4[4-0]
	TFT_DataWrite(0x0D);   //V6[4-0]
	TFT_DataWrite(0x18);   //J0[5-4] & V13[3-0]
	TFT_DataWrite(0x39);   //V20[6-0]
	TFT_DataWrite(0x43);   //V36[6-4] & V27[2-0]
	TFT_DataWrite(0x48);   //V43[6-0]
	TFT_DataWrite(0x2A);   //J1[5-4] & V50[3-0]
	TFT_DataWrite(0x16);   //V57[4-0]
	TFT_DataWrite(0x14);   //V59[4-0]
	TFT_DataWrite(0x1A);   //V61[5-0]
	TFT_DataWrite(0x1D);   //V62[5-0]

	TFT_CommandWrite(0xE1);
	TFT_DataWrite(0xD0);   //V63[7-4] & V0[3-0]
	TFT_DataWrite(0x0D);   //V1[5-0]
	TFT_DataWrite(0x15);   //V2[5-0]
	TFT_DataWrite(0x0D);   //V4[4-0]
	TFT_DataWrite(0x0D);   //V6[4-0]
	TFT_DataWrite(0x09);   //J0[5-4] & V13[3-0]
	TFT_DataWrite(0x38);   //V20[6-0]
	TFT_DataWrite(0x44);   //V36[6-4] & V27[2-0]
	TFT_DataWrite(0x48);   //V43[6-0]
	TFT_DataWrite(0x2A);   //J1[5-4] & V50[3-0]
	TFT_DataWrite(0x15);   //V57[4-0]
	TFT_DataWrite(0x14);   //V59[4-0]
	TFT_DataWrite(0x1A);   //V61[5-0]
	TFT_DataWrite(0x1E);   //V62[5-0]

	TFT_CommandWrite(0x21);

	TFT_CommandWrite(0x29);
#else

	TFT_CommandWrite(0x11);
	Delay_ms(120); //Delay 120ms
	//------------------------------display and color format setting--------------------------------//
	TFT_CommandWrite(0x36);
	TFT_DataWrite(0x00);
	TFT_CommandWrite(0x3a);
	TFT_DataWrite(0x06);
	//--------------------------------ST7789V Frame rate setting----------------------------------//
	TFT_CommandWrite(0xb2);
	TFT_DataWrite(0x0c);
	TFT_DataWrite(0x0c);
	TFT_DataWrite(0x00);
	TFT_DataWrite(0x33);
	TFT_DataWrite(0x33);
	TFT_CommandWrite(0xb7);
	TFT_DataWrite(0x35);
	//---------------------------------ST7789V Power setting--------------------------------------//
	TFT_CommandWrite(0xbb);
	TFT_DataWrite(0x28);
	TFT_CommandWrite(0xc0);
	TFT_DataWrite(0x2c);
	TFT_CommandWrite(0xc2);
	TFT_DataWrite(0x01);
	TFT_CommandWrite(0xc3);
	TFT_DataWrite(0x0b);
	TFT_CommandWrite(0xc4);

	TFT_DataWrite(0x20);
	TFT_CommandWrite(0xc6);
	TFT_DataWrite(0x0f);
	TFT_CommandWrite(0xd0);
	TFT_DataWrite(0xa4);
	TFT_DataWrite(0xa1);
	//--------------------------------ST7789V gamma setting---------------------------------------//
	TFT_CommandWrite(0xe0);
	TFT_DataWrite(0xd0);
	TFT_DataWrite(0x01);
	TFT_DataWrite(0x08);
	TFT_DataWrite(0x0f);
	TFT_DataWrite(0x11);
	TFT_DataWrite(0x2a);
	TFT_DataWrite(0x36);
	TFT_DataWrite(0x55);
	TFT_DataWrite(0x44);
	TFT_DataWrite(0x3a);
	TFT_DataWrite(0x0b);
	TFT_DataWrite(0x06);
	TFT_DataWrite(0x11);
	TFT_DataWrite(0x20);
	TFT_CommandWrite(0xe1);
	TFT_DataWrite(0xd0);
	TFT_DataWrite(0x02);
	TFT_DataWrite(0x07);
	TFT_DataWrite(0x0a);
	TFT_DataWrite(0x0b);
	TFT_DataWrite(0x18);
	TFT_DataWrite(0x34);
	TFT_DataWrite(0x43);
	TFT_DataWrite(0x4a);
	TFT_DataWrite(0x2b);
	TFT_DataWrite(0x1b);
	TFT_DataWrite(0x1c);
	TFT_DataWrite(0x22);
	TFT_DataWrite(0x1f);
	TFT_CommandWrite(0x29);

//	TFT_CommandWrite( 0x11);
//	Delay_ms(120); //Delay 120ms
//		//--------------------------------------Display Setting------------------------------------------//
//		TFT_CommandWrite( 0x36);
//		TFT_DataWrite(0xA0);
//		TFT_CommandWrite( 0x3a);
//		TFT_DataWrite(0x06);
//		//--------------------------------ST7789V Frame rate setting----------------------------------//
//		TFT_CommandWrite( 0xb2);
//		TFT_DataWrite(0x0c);
//		TFT_DataWrite(0x0c);
//		TFT_DataWrite(0x00);
//		TFT_DataWrite(0x33);
//		TFT_DataWrite(0x33);
//		TFT_CommandWrite( 0xb7);
//		TFT_DataWrite(0x35);
//		//---------------------------------ST7789V Power setting--------------------------------------//
//		TFT_CommandWrite( 0xbb);
//		TFT_DataWrite(0x2b);
//		TFT_CommandWrite( 0xc0);
//		TFT_DataWrite(0x2c);
//		TFT_CommandWrite( 0xc2);
//		TFT_DataWrite(0x01);
//		TFT_CommandWrite( 0xc3);
//		TFT_DataWrite(0x11);
//		TFT_CommandWrite( 0xc4);
//
//		TFT_DataWrite(0x20);
//		TFT_CommandWrite( 0xc6);
//		TFT_DataWrite(0x0f);
//		TFT_CommandWrite( 0xd0);
//		TFT_DataWrite(0xa4);
//		TFT_DataWrite(0xa1);
//		//--------------------------------ST7789V gamma setting---------------------------------------//
//		TFT_CommandWrite( 0xe0);
//		TFT_DataWrite(0xd0);
//		TFT_DataWrite(0x00);
//		TFT_DataWrite(0x05);
//		TFT_DataWrite(0x0e);
//		TFT_DataWrite(0x15);
//		TFT_DataWrite(0x0d);
//		TFT_DataWrite(0x37);
//		TFT_DataWrite(0x43);
//		TFT_DataWrite(0x47);
//		TFT_DataWrite(0x09);
//		TFT_DataWrite(0x15);
//		TFT_DataWrite(0x12);
//		TFT_DataWrite(0x16);
//		TFT_DataWrite(0x19);
//		TFT_CommandWrite( 0xe1);
//		TFT_DataWrite(0xd0);
//		TFT_DataWrite(0x00);
//		TFT_DataWrite(0x05);
//		TFT_DataWrite(0x0d);
//		TFT_DataWrite(0x0c);
//		TFT_DataWrite(0x06);
//		TFT_DataWrite(0x2d);
//		TFT_DataWrite(0x44);
//		TFT_DataWrite(0x40);
//		TFT_DataWrite(0x0e);
//		TFT_DataWrite(0x1c);
//		TFT_DataWrite(0x18);
//		TFT_DataWrite(0x16);
//		TFT_DataWrite(0x19);
//		TFT_CommandWrite( 0x29);


//	TFT_CommandWrite(0x11);
//	Delay_ms(120);                                              //Delay 120ms
//		TFT_CommandWrite(0x36);
//		TFT_DataWrite(0x00);
//		TFT_CommandWrite(0x3a);
//		TFT_DataWrite(0x05);
//		TFT_CommandWrite(0xb2);
//		TFT_DataWrite(0x0c);
//		TFT_DataWrite(0x0c);
//		TFT_DataWrite(0x00);
//		TFT_DataWrite(0x33);
//		TFT_DataWrite(0x33);
//		TFT_CommandWrite(0xb7);
//		TFT_DataWrite(0x35);
//		TFT_CommandWrite(0xbb);
//		TFT_DataWrite(0x19);
//		TFT_CommandWrite(0xc0);
//		TFT_DataWrite(0x2c);
//		TFT_CommandWrite(0xc2);
//		TFT_DataWrite(0x01);
//		TFT_CommandWrite(0xc3);
//		TFT_DataWrite(0x0d); //GVDD=4.2V
//		TFT_CommandWrite(0xc4);
//		TFT_DataWrite(0x20);
//		TFT_CommandWrite(0xc6);
//		TFT_DataWrite(0x0f); //Frame=60Hz
//		TFT_CommandWrite(0xd0);
//		TFT_DataWrite(0xa4);
//		TFT_DataWrite(0xa1);
//		TFT_CommandWrite(0xe0);
//		TFT_DataWrite(0xd0);
//		TFT_DataWrite(0x00);
//		TFT_DataWrite(0x05);
//		TFT_DataWrite(0x0f);
//		TFT_DataWrite(0x10);
//		TFT_DataWrite(0x28);
//		TFT_DataWrite(0x34);
//		TFT_DataWrite(0x50);
//		TFT_DataWrite(0x44);
//		TFT_DataWrite(0x3a);
//		TFT_DataWrite(0x0b);
//		TFT_DataWrite(0x06);
//		TFT_DataWrite(0x11);
//		TFT_DataWrite(0x20);
//		TFT_CommandWrite(0xe1);
//		TFT_DataWrite(0xd0);
//		TFT_DataWrite(0x00);
//		TFT_DataWrite(0x05);
//		TFT_DataWrite(0x0a);
//		TFT_DataWrite(0x0b);
//		TFT_DataWrite(0x16);
//		TFT_DataWrite(0x32);
//		TFT_DataWrite(0x40);
//		TFT_DataWrite(0x4a);
//		TFT_DataWrite(0x2b);
//		TFT_DataWrite(0x1b);
//		TFT_DataWrite(0x1c);
//		TFT_DataWrite(0x22);
//		TFT_DataWrite(0x1f);
//		TFT_CommandWrite(0x29);
#endif
}

//--------------------------设定窗口-----------------------------------
#define XSoff	 	0       		//X轴： XSoff = 起始偏移  ，XSoff = 终点偏移
#define XEoff 		0
#define YSoff	    0				//Y轴： YSoff = 起始偏移  ，YEoff = 终点偏移
#define YEoff 		0

void LT268_TFT_SetWindows(UINT16 XStar,UINT16 yStar,UINT16 Width,UINT16 High)
{
	UINT16 XS,XE,YS,YE;
	XS=XStar+XSoff;  	XE=XStar+XEoff+Width-1;
	YS=yStar+YSoff;  	YE=yStar+YEoff+High-1;

	/*-适用驱动IC : ST7789、ILI9341、、、等 -*/
			TFT_CommandWrite(0x2A);
			TFT_DataWrite(XS>>8);
			TFT_DataWrite(XS);
			TFT_DataWrite(XE>>8);
			TFT_DataWrite(XE);

			TFT_CommandWrite(0x2B);
			TFT_DataWrite(YS>>8);
			TFT_DataWrite(YS);
			TFT_DataWrite(YE>>8);
			TFT_DataWrite(YE);

			TFT_CommandWrite(0x2c);

//	/*-适用驱动IC : HX8347 、、等-*/
//			TFT_CommandWrite(0x02);
//			TFT_DataWrite(XS>>8);
//			TFT_CommandWrite(0x03);
//			TFT_DataWrite(XS); //Column Start
//
//			TFT_CommandWrite(0x04);
//			TFT_DataWrite(XE>>8);
//			TFT_CommandWrite(0x05);
//			TFT_DataWrite(XE); //Column End
//
//			TFT_CommandWrite(0x06);
//			TFT_DataWrite(YS>>8);
//			TFT_CommandWrite(0x07);
//			TFT_DataWrite(YS); //Row Start
//
//			TFT_CommandWrite(0x08);
//			TFT_DataWrite(YE>>8);
//			TFT_CommandWrite(0x09);
//			TFT_DataWrite(YE); //Row End
//
//			TFT_CommandWrite(0x22);

}


//void disp_Picture(UINT32 Addr)
//{
//	int i,j;
//	UINT8 pBuffer[4]={0};
//
//
//	for(j=0;j<240*320*2/4;j++)
//	{
//		LT268_W25QXX_Read(pBuffer,Addr,4);
//		Addr+=4;
//
//		SPI->SPIBR0 = 0x0000;
//		SPI->U32SPCR.STC = 0;
//		CS_RESET;
//		WriteData_A0;
//		SPI0_ReadWriteByte(pBuffer[1]);
//		SPI0_ReadWriteByte(pBuffer[0]);
//		SPI0_ReadWriteByte(pBuffer[3]);
//		SPI0_ReadWriteByte(pBuffer[2]);
//		CS_SET;
//	}
//}

//---------------------TFT Sleep Mode----------------------

void ST7789VPanelSleepInMode(void)
{
	TFT_CommandWrite(0x28);
	TFT_CommandWrite(0x10);
	Delay_ms(120);
}

//---------------------TFT Sleep Out----------------------
void ST7789VPanelSleepOutMode(void)
{
	TFT_CommandWrite(0x11);
	Delay_ms(120);
	TFT_CommandWrite(0x29);
}

