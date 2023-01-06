#ifndef _data_h
#define _data_h
#include "LT268A.h"
#include "type.h"
//#include "module_select.h"

//ͼƬ
#define DMA_LEN  256
extern UINT8 DMA_SPI_rxbuf1[DMA_LEN];
extern UINT8 DMA_SPI_rxbuf2[DMA_LEN];
extern UINT8 DMA_SPI_txbuf[DMA_LEN*2];
//extern UINT8 Table_color[512];

extern UINT8 First_press;										//tp
extern UINT16  First_pressX,First_pressY;

#define WAV_ADDR 0x00001700
#define RX_SIZE (1024+2)					//��������USART�������ݵĺ�


#if   MODULE_B8_B9
#define H_PWM_VAL 256

extern UINT16 bufPos;
extern UINT8  wbuf_select,wbuf0_Stat,wbuf1_Stat;
extern UINT8  wavBuf0[256];
extern UINT8  wavBuf1[256]; 													//�����������ȵ�ȫ�ֱ���

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


#define 		TP_PRES_DOWN 0x80  										//����������
#define 		TP_CATH_PRES 0x40  										//�а���������
#define 		CT_MAX_TOUCH  5    										//������֧�ֵĵ���,�̶�Ϊ5��
typedef struct
{
	UINT8 (*scan)(void);				  											//ɨ�败����.0,��Ļɨ��;1,��������;
	UINT8   sta;  																			//״̬��־  0��δ����    1��������   2�����º�δ���ͷ�
	UINT16  x[CT_MAX_TOUCH];    												//������
	UINT16  y[CT_MAX_TOUCH];    												//������
	UINT16  px;   																			//��������
	UINT16  py;   																			//��������

	UINT32     flag; 																			//��flash�ж�ȡ�õ�����ֵΪ0x5a�����ʾflash�����4������
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
extern TP_INFO gTpInfo;														//������������ز���
extern UINT16 gControlDuty;

#endif
