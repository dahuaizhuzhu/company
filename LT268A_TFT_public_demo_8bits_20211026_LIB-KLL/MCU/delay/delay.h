/******************** COPYRIGHT  ********************
* Author             :Levetop Electronics
* Version            :V1.0
* Date                :2017-8-15
* Description     :
****************************************************/
#ifndef DELAY_H_
#define DELAY_H_

#include "type.h"




extern void delay(volatile UINT32 time);
extern void DelayMs(UINT32 t);
void Delay_us(UINT32 us);
void Delay_ms(UINT32 ms);
void Delay_seconds(UINT32 s);

#endif /* TIMER_H_ */
