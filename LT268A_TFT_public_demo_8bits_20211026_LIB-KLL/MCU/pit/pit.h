
#ifndef PIT_H_
#define PIT_H_

#include "LT268A.h"

//#include "misc.h"



extern void PIT0_Handler(void);
extern void PIT1_Handler(void);
extern void PIT2_Handler(void);
extern void PIT3_Handler(void);
extern void LT_UsartTimeEnable(void);
extern void LT_UsartTimeDisable(void);
extern void LT_UsartTimeSetCounter(UINT32 Counter);
extern void PIT0_Init(void);
extern void PIT1_Init(void);
extern void PIT2_Init(void);
extern void PIT3_Init(void);
extern UINT8 LT_PlayWav(void);
extern void close_wav(void);

#endif /* PIT_H_ */
