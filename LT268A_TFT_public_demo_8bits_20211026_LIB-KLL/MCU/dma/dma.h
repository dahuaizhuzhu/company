/*
 * dma.h
 *
 *  Created on: 2016Äê3ÔÂ30ÈÕ
 *      Author: Administrator
 */

#ifndef INC_DMA_H_
#define INC_DMA_H_


//#include "iostring.h"

#define DATA_NUM   32

//extern UINT16 TX_BUFF[DATA_NUM];
//extern UINT16 RX_BUFF[DATA_NUM];
//extern UINT8 TX1_BUFF[DATA_NUM];
//extern UINT8 RX1_BUFF[DATA_NUM];


void SPI_LDMA_Tx_Init(UINT32 Tx_Addr,UINT8 Count);
void SPI_LDMA_Rx_Init(UINT32 Rx_Addr,UINT8 Count);
void SPI_LDMA_Tx_Start(UINT32 Tx_Addr,UINT8 Count);
void SPI_LDMA_Rx_Start(UINT32 Rx_Addr,UINT8 Count);


void SPI_1_LDMA_Tx_Init(UINT32 Tx_Addr,UINT16 Count);
void SPI_1_LDMA_Rx_Init(UINT32 Rx_Addr,UINT16 Count);
void SPI_1_LDMA_Tx_Start(UINT32 Tx_Addr,UINT16 Count);
void SPI_1_LDMA_Rx_Start(UINT32 Rx_Addr,UINT16 Count);

void LDMA_Handler(void);

#endif /* INC_DMA_H_ */
