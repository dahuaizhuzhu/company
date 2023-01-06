#ifndef _data_h
#define _data_h
#include "LT268A.h"
#include "type.h"
//#include "module_select.h"

//图片
#define DMA_LEN  256
extern UINT8 DMA_SPI_rxbuf1[DMA_LEN];
extern UINT8 DMA_SPI_rxbuf2[DMA_LEN];
extern UINT8 DMA_SPI_txbuf[DMA_LEN*2];
//extern UINT8 Table_color[512];

extern UINT8 First_press;										//tp
extern UINT16  First_pressX,First_pressY;

#define WAV_ADDR 0x00001700
#define RX_SIZE (1024+2)					//用来控制USART接收数据的宏


#if   MODULE_B8_B9
#define H_PWM_VAL 256

extern UINT16 bufPos;
extern UINT8  wbuf_select,wbuf0_Stat,wbuf1_Stat;
extern UINT8  wavBuf0[256];
extern UINT8  wavBuf1[256]; 													//用来控制喇叭的全局变量

extern UINT32 gWavFlashAddr;
extern UINT32 gTempWavFlashAddr ;
extern UINT32 gWavLen;
extern UINT8  gWavFlag;
extern UINT8  gWavState;
extern UINT8  gWavType;
extern UINT8  gWavOpen;
extern UINT16  gWavLast;
#endif

extern UINT8 gRxFlag ;
extern UINT8 busyflag ;
typedef struct
{
	UINT8  Flag;
	UINT8  Buf[RX_SIZE];
	UINT16 Len;
	UINT16 Count;
}USART_RX_INFO;
extern USART_RX_INFO gUsartRx;


#define 		TP_PRES_DOWN 0x80  										//触屏被按下
#define 		TP_CATH_PRES 0x40  										//有按键按下了
#define 		CT_MAX_TOUCH  5    										//电容屏支持的点数,固定为5点
typedef struct
{
	UINT8 (*scan)(void);				  											//扫描触摸屏.0,屏幕扫描;1,物理坐标;
	UINT8   sta;  																			//状态标志  0：未按下    1：被按下   2：按下后，未被释放
	UINT16  x[CT_MAX_TOUCH];    												//屏坐标
	UINT16  y[CT_MAX_TOUCH];    												//屏坐标
	UINT16  px;   																			//物理坐标
	UINT16  py;   																			//物理坐标

	UINT32     flag; 																			//从flash中读取得到，当值为0x5a，则表示flash里存有4个参数
	float     xfac;
	float     yfac;
	float     xoff;
	float     yoff;
}TP_INFO;

typedef union {

	 float x;
       char s[4];
}TP_TEST;

typedef union {

	 float xfac;
       char s[4];
}TP_xfac;

typedef union {

	 float xoff;
       char s[4];
}TP_xoff;

typedef union {

	 float yfac;
       char s[4];
}TP_yfac;

typedef union {

	 float yoff;
       char s[4];
}TP_yoff;
extern TP_xfac gTpxfac;
extern TP_xoff gTpxoff;
extern TP_yfac gTpyfac;
extern TP_yoff gTpyoff;

extern TP_TEST gTptest;
extern TP_INFO gTpInfo;														//电容屏所需相关参数
extern UINT16 gControlDuty;

#endif
