/*
 * w25qxx.h
 *
 *  Created on: 2019年5月13日
 *      Author: cjc59
 */

#ifndef W25QXX_H_
#define W25QXX_H_

#include "LT268A.h"


#define Flash_SS_RESET SPI->U32SPCR.SPISS1 = 0;
#define Flash_SS_SET   SPI->U32SPCR.SPISS1 = 1;

extern UINT8  Flash_Type;
//------------------------------------------------------- 操作W25QXX -------------------------------------------------------------
//指令表
#define W25X_WriteEnable		0x06
#define W25X_WriteDisable		0x04
#define W25X_ReadStatusReg		0x05
#define W25X_WriteStatusReg		0x01
#define W25X_ReadData			0x03
#define W25X_FastReadData		0x0B
#define W25X_FastReadDual		0x3B
#define W25X_PageProgram		0x02
#define W25X_BlockErase			0xD8
#define W25X_SectorErase		0x20
#define W25X_ChipErase			0xC7
#define W25X_PowerDown			0xB9
#define W25X_ReleasePowerDown	0xAB
#define W25X_DeviceID			0xAB
#define W25X_ManufactDeviceID	0x90
#define W25X_JedecDeviceID		0x9F


void SPI1_Init(void);
UINT8 SPI1_ReadWriteByte(UINT8 TxData);
UINT8 LT268_W25QXX_ReadSR(void);
UINT16 LT268_W25QXX_ReadID(void);
void LT268_W25QXX_4Byte_addr(void);
void LT268_W25QXX_Read(UINT8* pBuffer,UINT32 ReadAddr,UINT16 NumByteToRead);
void LT268_W25QXX_Write_Page(UINT8* pBuffer,UINT32 WriteAddr,UINT16 NumByteToWrite);
void LT268_W25QXX_Write_NoCheck(UINT8* pBuffer,UINT32 WriteAddr,UINT16 NumByteToWrite);
void LT268_W25QXX_BlockErase64KB(UINT32 addr);
void LT268_W25QXX_SectorErase4KB(UINT32 addr);
void LT268_W25QXX_Erase_Chip(void);


#endif /* W25QXX_H_ */
