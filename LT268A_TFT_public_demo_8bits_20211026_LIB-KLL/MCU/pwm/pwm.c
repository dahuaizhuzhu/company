#include "pwm.h"


void LCD_BL_Init(UINT16 duty)
{
//	PWM0->U32PPCR.PDDR |= 1<<2;
//	PWM0->U32PPCR.PDR2 =1;

	PWM0->U32PCSR.CSR2 = 1;       // ʱ��ѡ��λ  ������1Ϊ��Ƶ4����ʱ��Ϊ48/4=12Mhz)
	PWM0->U32PPR.CP1 = 0;         // ʱ��Ԥ��Ƶ  ������Ϊ0����û��Ƶ���������ʱ�ӻ���Ϊ12Hhz��
	PWM0->U32PCR.CH2MOD = 1;      // ��ʱ�������ת���أ�1����ת��       0����ת�أ�
	PWM0->PCNR2 = 900;            // ����ʱ�䣨12Mzh/120=100Khz�������Ϊ100Khz��Ƶ�ʣ�
	PWM0->PCMR2 = duty;             // ����ռ�ձȣ�������ռ�ձ�Ϊ��60/120��*100% = 50%
	PWM0->U32PPCR.PDDR |= (1<<2); // ����PWM02Ϊ���
	PWM0->U32PCR.CH2EN = 1;       // ʹ��PWM02

}

void LT_BacklightSet(UINT16 duty)
{
	PWM0->PCMR2 = duty;
}


//------------PWM0[3]��������----------------
void LT_BuglePwmInit(void)
{
	PWM0->U32PCSR.CSR3 = 1;       // ʱ��ѡ��λ  ������1Ϊ��Ƶ4����ʱ��Ϊ48/4=12Mhz)
	PWM0->U32PPR.CP1 = 0;         // ʱ��Ԥ��Ƶ  ������Ϊ0����û��Ƶ���������ʱ�ӻ���Ϊ12Hhz��
	PWM0->U32PCR.CH3MOD = 1;      // ��ʱ�������ת���أ�1����ת��       0����ת�أ�
	PWM0->PCNR3 = 512;            // ����ʱ�䣨12Mzh/120=100Khz�������Ϊ100Khz��Ƶ�ʣ�
	PWM0->PCMR3 = 256;             // ����ռ�ձȣ�������ռ�ձ�Ϊ��60/120��*100% = 50%
	PWM0->U32PPCR.PDDR |= (1<<3); // ����PWM03Ϊ���
	PWM0->U32PCR.CH3EN = 1;       // ʹ��PWM03

}

void LT_BuglePwmSet(UINT16 duty)
{
	PWM0->PCMR3 = duty;
}


//________ pin10_init___________��ΪGPIO
/*
PWM0->U32PCR.CH1EN = 0;           		//����PWM
PWM0->U32PPCR.PULLUP_EN |= (1<<1);		//����
PWM0->U32PPCR.PDDR |= (1<<1);          	//���
PWM0->U32PPCR.PDR1=0;			   		//д  0 or 1


PWM0->U32PPCR.PDDR&= ~(1<<1);         	  //����
i=PWM0->U32PPCR.PDR1;                     //��
*/


