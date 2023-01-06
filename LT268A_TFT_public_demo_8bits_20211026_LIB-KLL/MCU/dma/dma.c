/*
 * dma.c
 *
 *  Created on: 2016��3��30��
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
	LDMA->U32LDMACR1.START1 = 0;   // �ر�LDMA

	//LDMA->LDMAMBAR1 = Rx_Addr;     // �ڴ����ַ
	//LDMA->LDMABCR1 = Count;        // ���͵��ֽ���

	LDMA->U32LDMACR1.LBFE1 = 0;    // ���ֽڿ�ʼ����
	LDMA->U32LDMACR1.PTS1 = 2;     // 1- byte,0-word,2 -- halfword
	LDMA->U32LDMACR1.PS1 = 0;      // SPIд
	LDMA->U32LDMACR1.TD1 = 1;      // ���赽�ڴ�
	LDMA->U32LDMACR1.MINC1 = 1;    // �ڴ����
	LDMA->U32LDMACR1.CIRC1 = 0;    // ��ֹѭ��ģʽ

	while(LDMA->U32LDMACR1.CE1);   // ���LDMA����
}

void SPI_LDMA_Rx_Start(UINT32 Rx_Addr,UINT8 Count)
{
	LDMA->LDMAMBAR1 = Rx_Addr;     // �ڴ����ַ
	LDMA->LDMABCR1 = Count;        // ���͵��ֽ���
	while(LDMA->U32LDMACR1.CE1);   // ���LDMA����
	LDMA->U32LDMACR1.START1 = 1;   // ʹ��LDMA
}

void SPI_LDMA_Tx_Init(UINT32 Tx_Addr,UINT8 Count)
{
	LDMA->U32LDMACR2.START2 = 0;   // �ر�LDMA

	//LDMA->LDMAMBAR2 = Tx_Addr;     // �ڴ����ַ
	//LDMA->LDMABCR2 = Count;        // ���͵��ֽ���

	LDMA->U32LDMACR2.LBFE2 = 0;    // ���ֽڿ�ʼ����
	LDMA->U32LDMACR2.PTS2 = 2;     // 1- byte,0-word,2 -- halfword
	LDMA->U32LDMACR2.PS2 = 0;      // SPI��
	LDMA->U32LDMACR2.TD2 = 0;      // �ڴ浽����
	LDMA->U32LDMACR2.MINC2 = 1;    // �ڴ����
	LDMA->U32LDMACR2.CIRC2 = 0;    // ��ֹѭ��ģʽ

	LDMA->U32LDMACR2.TCIE2 = 1;    // ��SPI DMA���ж�

	EIC->IER|=0x0020;                   // ʹ��DMA�ж�

	while(LDMA->U32LDMACR2.CE2);   // ���LDMA����
}

void SPI_LDMA_Tx_Start(UINT32 Tx_Addr,UINT8 Count)
{
	LDMA->LDMAMBAR2 = Tx_Addr;     // �ڴ����ַ
	LDMA->LDMABCR2 = Count;        // ���͵��ֽ���
	while(LDMA->U32LDMACR2.CE2);   // ���LDMA����
	LDMA->U32LDMACR2.START2 = 1;   // ʹ��LDMA
}
//--------------------------------------------------------------------------------------------
void SPI_1_LDMA_Rx_Init(UINT32 Rx_Addr,UINT16 Count)
{
	LDMA->U32LDMACR3.START3 = 0;   // �ر�LDMA

//	LDMA->LDMAMBAR3 = Rx_Addr;     // �ڴ����ַ
//	LDMA->LDMABCR3 = Count;        // ���͵��ֽ���

	LDMA->U32LDMACR3.LBFE3 = 0;    // ���ֽڿ�ʼ����
	LDMA->U32LDMACR3.PTS3 = 1;     // ���ֽڴ���
	LDMA->U32LDMACR3.PS3 = 0;      // SPIд
	LDMA->U32LDMACR3.TD3 = 1;      // ���赽�ڴ�
	LDMA->U32LDMACR3.MINC3 = 1;    // �ڴ����
	LDMA->U32LDMACR3.CIRC3 = 0;    // ��ֹѭ��ģʽ
	LDMA->U32LDMACR3.TCIE3 = 1;		// ��SPI DMA���ж�

//	while(LDMA->U32LDMACR3.CE3);   // ���LDMA����
}

void SPI_1_LDMA_Rx_Start(UINT32 Rx_Addr,UINT16 Count)
{
	LDMA->LDMAMBAR3 = Rx_Addr;     // �ڴ����ַ
	LDMA->LDMABCR3 = Count;        // ���͵��ֽ���
	while(LDMA->U32LDMACR3.CE3);   // ���LDMA����
	LDMA->U32LDMACR3.START3 = 1;   // ʹ��LDMA
}

void SPI_1_LDMA_Tx_Init(UINT32 Tx_Addr,UINT16 Count)
{
	LDMA->U32LDMACR4.START4 = 0;   // �ر�LDMA

	//LDMA->LDMAMBAR4 = Tx_Addr;     // �ڴ����ַ
	//LDMA->LDMABCR4 = Count;        // ���͵��ֽ���

	LDMA->U32LDMACR4.LBFE4 = 0;    // ���ֽڿ�ʼ����
	LDMA->U32LDMACR4.PTS4 = 1;     // ���ֽڴ���
	LDMA->U32LDMACR4.PS4 = 0;      // SPI��
	LDMA->U32LDMACR4.TD4 = 0;      // �ڴ浽����
	LDMA->U32LDMACR4.MINC4 = 1;    // �ڴ����
	LDMA->U32LDMACR4.CIRC4 = 0;    // ��ֹѭ��ģʽ

	LDMA->U32LDMACR4.TCIE4 = 1;    // ��SPI DMA���ж�

	//EIC->IER|=0x0020;                   // ʹ��DMA�ж�

	//while(LDMA->U32LDMACR4.CE4);   // ���LDMA����
}

void SPI_1_LDMA_Tx_Start(UINT32 Tx_Addr,UINT16 Count)
{

	//LTPrintf("Tx_Addr = 0x%x\n",Tx_Addr);

	LDMA->LDMAMBAR4 = Tx_Addr;     // �ڴ����ַ
	LDMA->LDMABCR4 = Count;        // ���͵��ֽ���
	while(LDMA->U32LDMACR4.CE4);   // ���LDMA����
	LDMA->U32LDMACR4.START4 = 1;   // ʹ��LDMA
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
		LDMA->U32LDMASR.TCIF3 = 1; // ����жϱ�־λ
//		Printf_RXBUFF1();
		//dma_int_index = 0;
		//
	}
}


