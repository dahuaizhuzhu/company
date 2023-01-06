#ifndef _tp_h
#define _tp_h
#include "LT268A.h"
#include "flash.h"
#include <math.h>
#include <stdlib.h>
#define CMD_RDX 0XD0
#define CMD_RDY 0X90
#define TP_PRES_DOWN 0x80  		//触屏被按下	  
#define TP_CATH_PRES 0x40  		//有按键按下了 
#define CT_MAX_TOUCH  5    		//电容屏支持的点数,固定为5点

//电阻/电容屏芯片连接引脚

#define TDIN	PWM0->U32PPCR.PDR2
#define TCLK	PWM1->U32PPCR.PDR2
#define TCS		PWM1->U32PPCR.PDR0


#define DOUT			((EPORT0->EPPDR)&0X02)
#define PEN			((EPORT1->EPPDR)&0X40)
//坐标计算
//x = px * xfac + xoff
//y = py * yfac + yoff

extern UINT8 Yp_Pulldown_Flag;
extern UINT8 RTP_read_Flag;
extern UINT16 RTP_time;

UINT8 LT_TpInit(void);
UINT8 LT_TpScan(void);
UINT8 LT_TpAdjust(void);
void LT_TpSaveAdjdata(void);
UINT8 LT_TpGetAdjdata(void);
UINT8 TP_Read_XY2(UINT16 *x,UINT16 *y) ;
UINT16 TP_Read_AD(UINT8 CMD);

UINT16 TP_Read_XOY(UINT8 xy);

//void Int05_Handler(void);
#endif
