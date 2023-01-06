#include "pwm.h"


void LCD_BL_Init(UINT16 duty)
{
//	PWM0->U32PPCR.PDDR |= 1<<2;
//	PWM0->U32PPCR.PDR2 =1;

	PWM0->U32PCSR.CSR2 = 1;       // 时钟选择位  （设置1为分频4，即时钟为48/4=12Mhz)
	PWM0->U32PPR.CP1 = 0;         // 时钟预分频  （设置为0，即没分频，最终输出时钟还是为12Hhz）
	PWM0->U32PCR.CH2MOD = 1;      // 定时器输出反转开关（1：反转开       0：反转关）
	PWM0->PCNR2 = 900;            // 周期时间（12Mzh/120=100Khz，即输出为100Khz的频率）
	PWM0->PCMR2 = duty;             // 设置占空比，即最后的占空比为（60/120）*100% = 50%
	PWM0->U32PPCR.PDDR |= (1<<2); // 设置PWM02为输出
	PWM0->U32PCR.CH2EN = 1;       // 使能PWM02

}

void LT_BacklightSet(UINT16 duty)
{
	PWM0->PCMR2 = duty;
}


//------------PWM0[3]控制喇叭----------------
void LT_BuglePwmInit(void)
{
	PWM0->U32PCSR.CSR3 = 1;       // 时钟选择位  （设置1为分频4，即时钟为48/4=12Mhz)
	PWM0->U32PPR.CP1 = 0;         // 时钟预分频  （设置为0，即没分频，最终输出时钟还是为12Hhz）
	PWM0->U32PCR.CH3MOD = 1;      // 定时器输出反转开关（1：反转开       0：反转关）
	PWM0->PCNR3 = 512;            // 周期时间（12Mzh/120=100Khz，即输出为100Khz的频率）
	PWM0->PCMR3 = 256;             // 设置占空比，即最后的占空比为（60/120）*100% = 50%
	PWM0->U32PPCR.PDDR |= (1<<3); // 设置PWM03为输出
	PWM0->U32PCR.CH3EN = 1;       // 使能PWM03

}

void LT_BuglePwmSet(UINT16 duty)
{
	PWM0->PCMR3 = duty;
}


//________ pin10_init___________设为GPIO
/*
PWM0->U32PCR.CH1EN = 0;           		//禁用PWM
PWM0->U32PPCR.PULLUP_EN |= (1<<1);		//上拉
PWM0->U32PPCR.PDDR |= (1<<1);          	//输出
PWM0->U32PPCR.PDR1=0;			   		//写  0 or 1


PWM0->U32PPCR.PDDR&= ~(1<<1);         	  //输入
i=PWM0->U32PPCR.PDR1;                     //读
*/


