#ifndef __CTOUCH_H
#define __CTOUCH_H

#include "LT268A.h"
#include "delay.h"
#include "uart.h"
#include <math.h>
#include "bsp.h"



/************************错误代码*****************************/
#define CT_COM_OK               (0)
#define CT_ACK_FAIL             (1)
 
#define FT6X06_ID               (0x6206)
#define CT_IC                   (FT6X06_ID)              //使用的控制IC
#define CT_ADDR                 (0x70)                  //器件地址
#define CT_WRITE_MASK           (0x00)
#define CT_READ_MASK            (0x01)
 
#define CT_CACK_TIMEOUT         (3000)                  //等待ACK超时时间

void TP_Port_Init(void);
UINT8 TP_Get_INT(void);
UINT8 CTI2C_write_byte(const UINT8 s);
UINT8 CTI2C_read_byte(UINT8 ack);
UINT8 CT_Write_Nbyte(const UINT8 sla_add,const UINT8 add,UINT16 n,const UINT8 *s);
UINT8 CT_Read_Nbyte(const UINT8 sla_add,const UINT8 add,UINT16 n,UINT8 *s);
void TP_read_XY(void);
//UINT8 FT5216_Scan(UINT8 tp);
UINT8 FT5216_Scan(void);
void CTP_Init(void);
 
#endif
