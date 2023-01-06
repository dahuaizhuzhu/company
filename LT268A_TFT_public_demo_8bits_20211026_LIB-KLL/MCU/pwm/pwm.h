#ifndef _pwm_h
#define _pwm_h
#include "LT268A.h"
#include "type.h"


void LCD_BL_Init(UINT16 duty);

void LT_BacklightSet(UINT16 duty);

void LT_BuglePwmInit(void);
void LT_BuglePwmSet(UINT16 duty);

#endif
