#include "data.h"

#define H_PWM_VAL 256

UINT8 DMA_SPI_rxbuf1[DMA_LEN];
UINT8 DMA_SPI_rxbuf2[DMA_LEN];
UINT8 DMA_SPI_txbuf[DMA_LEN*2];
//UINT8 Table_color[512];

UINT8 First_press=0;
UINT16 First_pressX,First_pressY;

UINT16 bufPos;
UINT8  wbuf_select,wbuf0_Stat,wbuf1_Stat;
UINT8  wavBuf0[256];
UINT8  wavBuf1[256];                   			//用来控制喇叭的全局变量
UINT32 gWavFlashAddr = 0;
UINT32 gTempWavFlashAddr = 0;
UINT32 gWavLen = 0;
UINT8  gWavFlag = 0;
UINT8  gWavState = 0;
UINT8  gWavType = 0;
UINT8  gWavOpen = 0;
UINT16  gWavLast = 0;


UINT8 gRxFlag ;
UINT8 busyflag ;
UINT16 gControlDuty=400;
TP_INFO gTpInfo;

TP_TEST gTptest;
TP_xfac gTpxfac;
TP_xoff gTpxoff;
TP_yfac gTpyfac;
TP_yoff gTpyoff;

USART_RX_INFO gUsartRx;

