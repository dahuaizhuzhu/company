/*
 * dma.c
 *
 *  Created on: 2016年3月30日
 *      Author: Administrator
 */
#include "LT268A.h"
#include "dma.h"
#include "function.h"

#define TURE  1
#define ERROR 0
#define DATA_NUM   32

//extern UINT8 dma_int_index;

//UINT16 TX_BUFF[DATA_NUM] = {0};
//UINT16 RX_BUFF[DATA_NUM] = {0};

//UINT8 TX1_BUFF[DATA_NUM];
//UINT8 RX1_BUFF[DATA_NUM];

void SPI_LDMA_Rx_Init(UINT32 Rx_Addr,UINT8 Count)
{
	LDMA->U32LDMACR1.START1 = 0;   // 关闭LDMA

	//LDMA->LDMAMBAR1 = Rx_Addr;     // 内存基地址
	//LDMA->LDMABCR1 = Count;        // 发送的字节数

	LDMA->U32LDMACR1.LBFE1 = 0;    // 右字节开始传输
	LDMA->U32LDMACR1.PTS1 = 2;     // 1- byte,0-word,2 -- halfword
	LDMA->U32LDMACR1.PS1 = 0;      // SPI写
	LDMA->U32LDMACR1.TD1 = 1;      // 外设到内存
	LDMA->U32LDMACR1.MINC1 = 1;    // 内存递增
	LDMA->U32LDMACR1.CIRC1 = 0;    // 禁止循环模式

	while(LDMA->U32LDMACR1.CE1);   // 检查LDMA配置
}

void SPI_LDMA_Rx_Start(UINT32 Rx_Addr,UINT8 Count)
{
	LDMA->LDMAMBAR1 = Rx_Addr;     // 内存基地址
	LDMA->LDMABCR1 = Count;        // 发送的字节数
	while(LDMA->U32LDMACR1.CE1);   // 检查LDMA配置
	LDMA->U32LDMACR1.START1 = 1;   // 使能LDMA
}

void SPI_LDMA_Tx_Init(UINT32 Tx_Addr,UINT8 Count)
{
	LDMA->U32LDMACR2.START2 = 0;   // 关闭LDMA

	//LDMA->LDMAMBAR2 = Tx_Addr;     // 内存基地址
	//LDMA->LDMABCR2 = Count;        // 发送的字节数

	LDMA->U32LDMACR2.LBFE2 = 0;    // 右字节开始传输
	LDMA->U32LDMACR2.PTS2 = 2;     // 1- byte,0-word,2 -- halfword
	LDMA->U32LDMACR2.PS2 = 0;      // SPI读
	LDMA->U32LDMACR2.TD2 = 0;      // 内存到外设
	LDMA->U32LDMACR2.MINC2 = 1;    // 内存递增
	LDMA->U32LDMACR2.CIRC2 = 0;    // 禁止循环模式

	LDMA->U32LDMACR2.TCIE2 = 1;    // 打开SPI DMA读中断

	EIC->IER|=0x0020;                   // 使能DMA中断

	while(LDMA->U32LDMACR2.CE2);   // 检查LDMA配置
}

void SPI_LDMA_Tx_Start(UINT32 Tx_Addr,UINT8 Count)
{
	LDMA->LDMAMBAR2 = Tx_Addr;     // 内存基地址
	LDMA->LDMABCR2 = Count;        // 发送的字节数
	while(LDMA->U32LDMACR2.CE2);   // 检查LDMA配置
	LDMA->U32LDMACR2.START2 = 1;   // 使能LDMA
}
//--------------------------------------------------------------------------------------------
void SPI_1_LDMA_Rx_Init(UINT32 Rx_Addr,UINT16 Count)
{
	LDMA->U32LDMACR3.START3 = 0;   // 关闭LDMA

//	LDMA->LDMAMBAR3 = Rx_Addr;     // 内存基地址
//	LDMA->LDMABCR3 = Count;        // 发送的字节数

	LDMA->U32LDMACR3.LBFE3 = 0;    // 右字节开始传输
	LDMA->U32LDMACR3.PTS3 = 1;     // 以字节传输
	LDMA->U32LDMACR3.PS3 = 0;      // SPI写
	LDMA->U32LDMACR3.TD3 = 1;      // 外设到内存
	LDMA->U32LDMACR3.MINC3 = 1;    // 内存递增
	LDMA->U32LDMACR3.CIRC3 = 0;    // 禁止循环模式
	LDMA->U32LDMACR3.TCIE3 = 1;		// 打开SPI DMA读中断

//	while(LDMA->U32LDMACR3.CE3);   // 检查LDMA配置
}

void SPI_1_LDMA_Rx_Start(UINT32 Rx_Addr,UINT16 Count)
{
	LDMA->LDMAMBAR3 = Rx_Addr;     // 内存基地址
	LDMA->LDMABCR3 = Count;        // 发送的字节数
	while(LDMA->U32LDMACR3.CE3);   // 检查LDMA配置
	LDMA->U32LDMACR3.START3 = 1;   // 使能LDMA
}

void SPI_1_LDMA_Tx_Init(UINT32 Tx_Addr,UINT16 Count)
{
	LDMA->U32LDMACR4.START4 = 0;   // 关闭LDMA

	//LDMA->LDMAMBAR4 = Tx_Addr;     // 内存基地址
	//LDMA->LDMABCR4 = Count;        // 发送的字节数

	LDMA->U32LDMACR4.LBFE4 = 0;    // 右字节开始传输
	LDMA->U32LDMACR4.PTS4 = 1;     // 以字节传输
	LDMA->U32LDMACR4.PS4 = 0;      // SPI读
	LDMA->U32LDMACR4.TD4 = 0;      // 内存到外设
	LDMA->U32LDMACR4.MINC4 = 1;    // 内存递增
	LDMA->U32LDMACR4.CIRC4 = 0;    // 禁止循环模式

	LDMA->U32LDMACR4.TCIE4 = 1;    // 打开SPI DMA读中断

	//EIC->IER|=0x0020;                   // 使能DMA中断

	//while(LDMA->U32LDMACR4.CE4);   // 检查LDMA配置
}

void SPI_1_LDMA_Tx_Start(UINT32 Tx_Addr,UINT16 Count)
{

	//LTPrintf("Tx_Addr = 0x%x\n",Tx_Addr);

	LDMA->LDMAMBAR4 = Tx_Addr;     // 内存基地址
	LDMA->LDMABCR4 = Count;        // 发送的字节数
	while(LDMA->U32LDMACR4.CE4);   // 检查LDMA配置
	LDMA->U32LDMACR4.START4 = 1;   // 使能LDMA
}

//UINT8 Compare_DATA(void)
//{
//	UINT8 i = 0;
//	for(i = 0 ; i < DATA_NUM ; i++)
//	{
//		if(TX_BUFF[i] != RX_BUFF[i])
//		{
//			return ERROR;
//		}
//	}
//	return TURE;
//}

//void Printf_RXBUFF(void)
//{
//	UINT8 i = 0;
//	for(i = 0 ; i < DATA_NUM ; i++)
//	{
//		LTPrintf("0x%x ",RX_BUFF[i]);
//	}
//}

void Printf_RXBUFF1(void)
{
	UINT8 i = 0;
	for(i = 0 ; i < 512 ; i++)
	{
		//LTPrintf("0x%x ",DMA_SPI_rxbuf[i]);
	}
}


void LDMA_Handler(void)
{
	if(LDMA->U32LDMASR.TCIF3 == 1)
	{
		LDMA->U32LDMASR.TCIF3 = 1; // 清除中断标志位
//		Printf_RXBUFF1();
		//dma_int_index = 0;
		//
	}
}


