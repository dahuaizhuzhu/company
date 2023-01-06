/*
 * TFTLCD.h
 *
 *  Created on: 2019Äê5ÔÂ9ÈÕ
 *      Author: cjc59
 */

#ifndef TFTLCD_H_
#define TFTLCD_H_

#include "LT268A.h"



//#define LCD_RESET 	EPORT1->U8EPDR.int5 = 0
//#define LCD_SET 		EPORT1->U8EPDR.int5 = 1

#define LCD_RESET 	EPORT0->U8EPDR.int0 = 0
#define LCD_SET 	EPORT0->U8EPDR.int0 = 1

//#define WriteCommand_A0 	I2C->U8I2CPDR.SDA = 0
//#define WriteData_A0 	I2C->U8I2CPDR.SDA = 1

#define WriteCommand_A0 	PWM1->U32PPCR.PDR0=0
#define WriteData_A0 		PWM1->U32PPCR.PDR0=1

#define CS_RESET    SPI->U32SPCR.SPISS0 = 0;
#define CS_SET      SPI->U32SPCR.SPISS0 = 1;

#define Data_8_RD_RESET		PWM1->U32PPCR.PDR2 = 0
#define Data_8_RD_SET		PWM1->U32PPCR.PDR2 = 1

#define Data_8_WR_RESET		PWM1->U32PPCR.PDR1 = 0
#define Data_8_WR_SET		PWM1->U32PPCR.PDR1 = 1

#define Data_8_CS_RESET		PWM0->U32PPCR.PDR3 = 0
#define Data_8_CS_SET		PWM0->U32PPCR.PDR3 = 1


void SPI0_ReadWriteByte(UINT8 TxData);
void TFT_CommandWrite(UINT8 cmd);
void TFT_DataWrite(UINT8 data);
void LCD_TFT_Init(void);
void LT268_TFT_SetWindows(UINT16 XStar,UINT16 yStar,UINT16 Width,UINT16 High);

#endif /* TFTLCD_H_ */
