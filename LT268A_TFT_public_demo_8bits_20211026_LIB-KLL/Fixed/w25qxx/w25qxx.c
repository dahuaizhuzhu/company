/*
 * w25qxx.c
 *
 *  Created on: 2019年5月13日
 *      Author: cjc59
 */

#include "w25qxx.h"

UINT8  Flash_Type = 0;	  	//Flash_Type = 0, 24bits地址的NorFlash
                          	//Flash_Type = 1, 32bits地址的NorFlash W25Q256 NorFlash的标志 ，用于识别到256的时候开启4Byte 地址
                          	//Flash_Type = 2, Nand Flash（W25N01GV）


void SPI1_Init(void)
{
	SPI->U32SPIGPIOCSR.SCMGPIOEN = 0x00;	//All for main funtion
	SPI->U32SPIGPIOCSR.SCMGPIODDR = 0x7F;

	SPI->SPIBR0 = 0x0002;	//4Mhz  //当CS_VARCLK_EN=0，fixed clock=72MHz/2(SPIBR0[15:0] + 1)
	//SPI->SPIBR0 = 0x0FFF;

	SPI->U32SPCR.CS_CLKP = 0;			//Active-high clock, msck idle low
	SPI->U32SPCR.DW = 0;				// 0 -- 8bits, 1 -- 16bits, 2 -- 24bits, 3 -- 32bits
	SPI->U32SPCR.CS_VARCLK_EN = 0;		//1 = SPI variable clock mode enabled
																	//0 = SPI fixed clock mode enabled
								//00 : SPI0F is set after every completed transfer
								//01 : SPI0F is set after every two completed transfers
								//10 : SPI0F is set after every three completed transfers
								//11 : SPI0F is set after every four completed transfers
	SPI->U32SPCR.ICNT1 = 0;
	//双通道发送时，STC=0由channel0控制发送，STC=1由channel1控制发送
	SPI->U32SPCR.STC = 1;	//0 = SPI channel-0 write fifo not empty will start data transfer
								//1 = SPI channel-1 write fifo not empty will start data transfer
	SPI->U32SPCR.SPBROE = 0;
	SPI->U32SPCR.SPLSBFE = 0;		//1 = SPI channel-0 LSB enabled
															//0 = SPI channel-0 MSB enabled
	SPI->U32SPCR.SPISS1 = 0;		//SS0 = 1

	SPI->U32SPCR.WFEMPTY1IE = 0;	//0 = SPI channel-0 write fifo empty interrupt Disabled

	SPI->U32SPCR.WCOL1IE = 0;	//0 = SPI channel-0 write fifo overrun interrupt Disabled

	SPI->U32SPCR.RCOL1IE = 0;		//0 = SPI channel-0 read fifo overrun interrupt Disabled

	SPI->U32SPCR.SP1IE = 0;	//0 = SPI channel-0 interrupt disabled

	SPI->U32SPIDMACR.RXDMAEN1 = 0;
	SPI->U32SPIDMACR.TXDMAEN1 = 0;

	SPI->U32SPCR.SP1E = 1;	//1 = SPI channel-0 enabled

	SPI->U32SPCR.GTCS = 0;

	SPI->U32SPCR.GT = 0;

	SPI->SPSR = 0xffffffff;

	Flash_SS_SET;
}

/**
 * @file   SPIx_ReadWriteByte
 * @brief  读写一个字节
 * @param  TxData:要写入的字节
 * @reV 读取到的字节
 */
UINT8 SPI1_ReadWriteByte(UINT8 TxData)
{
	unsigned char reV;
	SPI->SPSR = 0xffffffff;
	SPI->SPB1R = TxData;
	while((SPI->U32SPSR.SPI1F)==0);
	reV = SPI->SPB1R; //接收数据
	return reV;
}


//读取W25QXX的状态寄存器
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
UINT8 LT268_W25QXX_ReadSR(void)   //读取W25QXX的状态寄存器
{
	UINT8 byte=0;
	Flash_SS_RESET                            		//使能器件
	SPI1_ReadWriteByte(W25X_ReadStatusReg); 	//发送读取状态寄存器命令
	byte=SPI1_ReadWriteByte(0Xff);          	//读取一个字节
	Flash_SS_SET                            		//取消片选
	return byte;
}

//将WEL置位
void LT268_W25QXX_Write_Enable(void)   //W25QXX写使能
{
	Flash_SS_RESET                          			//使能器件
    SPI1_ReadWriteByte(W25X_WriteEnable); 	//发送写使能
	Flash_SS_SET                           		//取消片选
}

//将WEL清零
void LT268_W25QXX_Write_Disable(void)   //W25QXX写禁止
{
	Flash_SS_RESET                            		//使能器件
    SPI1_ReadWriteByte(W25X_WriteDisable); 	//发送写禁止指令
	Flash_SS_SET                            		//取消片选
}


void LT268_W25QXX_Wait_Busy(void)   		//等待空闲
{
	while((LT268_W25QXX_ReadSR()&0x01)==0x01);  		// 等待BUSY位清空
}


//读取芯片ID
//返回值如下:
//0XEF13,表示芯片型号为W25Q80
//0XEF14,表示芯片型号为W25Q16
//0XEF15,表示芯片型号为W25Q32
//0XEF16,表示芯片型号为W25Q64
//0XEF17,表示芯片型号为W25Q128
//0XEF18,表示芯片型号为W25Q256
UINT16 LT268_W25QXX_ReadID(void)
{
//	SPI->SPIBR0 = 0x0008;
	SPI->U32SPCR.STC = 1;

	UINT16 Temp = 0;
	Flash_SS_RESET
	SPI1_ReadWriteByte(0x90);//发送读取ID命令
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(0x00);
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;
	Temp|=SPI1_ReadWriteByte(0xFF);
	Flash_SS_SET
	return Temp;
	SPI->U32SPCR.STC = 0;
}


void LT268_W25QXX_4Byte_addr(void)
{
	Flash_SS_RESET;//nSS_Active();
	SPI1_ReadWriteByte(0xB7);
	Flash_SS_SET;//nSS_Inactive();
}


//读取SPI FLASH
//在指定地址开始读取指定长度的数据
//pBuffer:数据存储区
//ReadAddr:开始读取的地址(24bit)
//NumByteToRead:要读取的字节数(最大65535)
void LT268_W25QXX_Read(UINT8* pBuffer,UINT32 ReadAddr,UINT16 NumByteToRead)
{
//	SPI->SPIBR0 = 0x0001;
	SPI->U32SPCR.STC = 1;

	UINT16 i;
 	Flash_SS_RESET                            			//使能器件
    SPI1_ReadWriteByte(W25X_ReadData);         	//发送读取命令
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(ReadAddr>>24));    //发送32bit地址
    SPI1_ReadWriteByte((UINT8)((ReadAddr)>>16));  	//发送24bit地址
    SPI1_ReadWriteByte((UINT8)((ReadAddr)>>8));
    SPI1_ReadWriteByte((UINT8)ReadAddr);

    for(i=0;i<NumByteToRead;i++)
	{
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   	//循环读数
    }
    Flash_SS_SET
	SPI->U32SPCR.STC = 0;
}


//SPI在一页(0~65535)内写入少于256个字节的数据
//在指定地址开始写入最大256字节的数据
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大256),该数不应该超过该页的剩余字节数!!!
void LT268_W25QXX_Write_Page(UINT8* pBuffer,UINT32 WriteAddr,UINT16 NumByteToWrite)
{
	UINT16 i;
	LT268_W25QXX_Write_Enable();                  							//SET WEL
    Flash_SS_RESET                            							//使能器件
    SPI1_ReadWriteByte(W25X_PageProgram);      					//发送写页命令
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(WriteAddr>>24));    //发送32bit地址
    SPI1_ReadWriteByte((UINT8)((WriteAddr)>>16)); 					//发送24bit地址
    SPI1_ReadWriteByte((UINT8)((WriteAddr)>>8));
    SPI1_ReadWriteByte((UINT8)WriteAddr);

    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);	//循环写数
    Flash_SS_SET                            							//取消片选
    LT268_W25QXX_Wait_Busy();					   								//等待写入结束
}


//无检验写SPI FLASH
//必须确保所写的地址范围内的数据全部为0XFF,否则在非0XFF处写入的数据将失败!
//具有自动换页功能
//在指定地址开始写入指定长度的数据,但是要确保地址不越界!
//pBuffer:数据存储区
//WriteAddr:开始写入的地址(24bit)
//NumByteToWrite:要写入的字节数(最大65535)
//CHECK OK
void LT268_W25QXX_Write_NoCheck(UINT8* pBuffer,UINT32 WriteAddr,UINT16 NumByteToWrite)
{
	UINT16 pageremain;

//	SPI->SPIBR0 = 0x0001;
	SPI->U32SPCR.STC = 1;

	pageremain=256-WriteAddr%256; //单页剩余的字节数
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//不大于256个字节
	while(1)
	{
		LT268_W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//写入结束了
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;

			NumByteToWrite-=pageremain;			  //减去已经写入了的字节数
			if(NumByteToWrite>256)pageremain=256; //一次可以写入256个字节
			else pageremain=NumByteToWrite; 	  //不够256个字节了
		}
	}
	SPI->U32SPCR.STC = 0;
}


void LT268_W25QXX_BlockErase64KB(UINT32 addr)
{
	SPI->U32SPCR.STC = 1;

	addr*=65536;
	LT268_W25QXX_Write_Enable();                 	//SET WEL
	LT268_W25QXX_Wait_Busy();
	Flash_SS_RESET;                            	  	//使能器件
	SPI1_ReadWriteByte(W25X_BlockErase);   			//发送片擦除命令
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(addr>>24));    //发送32bit地址
    SPI1_ReadWriteByte((UINT8)((addr)>>16)); 			//发送24bit地址
    SPI1_ReadWriteByte((UINT8)((addr)>>8));
    SPI1_ReadWriteByte((UINT8)addr);
    Flash_SS_SET;                           	//取消片选
    LT268_W25QXX_Wait_Busy();   				   	//等待芯片擦除结束

	SPI->U32SPCR.STC = 0;
}


void LT268_W25QXX_SectorErase4KB(UINT32 addr)
{
	SPI->U32SPCR.STC = 1;

	addr*=4096;
	LT268_W25QXX_Write_Enable();                 	//SET WEL
	LT268_W25QXX_Wait_Busy();
	Flash_SS_RESET;                           	  	//使能器件
	SPI1_ReadWriteByte(W25X_SectorErase);   			//发送片擦除命令
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(addr>>24));    //发送32bit地址
    SPI1_ReadWriteByte((UINT8)((addr)>>16)); 			//发送24bit地址
    SPI1_ReadWriteByte((UINT8)((addr)>>8));
    SPI1_ReadWriteByte((UINT8)addr);
    Flash_SS_SET;                            	//取消片选
    LT268_W25QXX_Wait_Busy();   				   	//等待芯片擦除结束

	SPI->U32SPCR.STC = 0;
}


//擦除整个芯片
//等待时间超长...
void LT268_W25QXX_Erase_Chip(void)
{
	LT268_W25QXX_Write_Enable();                 	 	  //SET WEL
	LT268_W25QXX_Wait_Busy();
	Flash_SS_RESET;                            	  //使能器件
	SPI1_ReadWriteByte(W25X_ChipErase);   //发送片擦除命令
	Flash_SS_RESET;                           	//取消片选
	LT268_W25QXX_Wait_Busy();   				   		        //等待芯片擦除结束

}
