/******************** COPYRIGHT  ********************
* Author             :Levetop Electronics
* Version            :V1.0
* Date                :2017-8-15
* Description     :
****************************************************/
#include "LT268A.h"
#include "delay.h"




void delay(volatile UINT32 time)
{
	while(time)
		time--;
}
void DelayMs(UINT32 t)
{
	UINT32 i;
	for(i=0;i<t;i++)
	{
		delay(3000);
	}
}

void Delay_us(UINT32 us)
{
	EPT->U32EPTRLD.RLD = SysFreq/1000000UL*us-1;
	EPT->U32EPTCSR.INTEN =0;
	EPT->U32EPTCSR.CLKSRC = 1;
	EPT->U32EPTCSR.CNTEN = 1;

	while(EPT->U32EPTCSR.CNTFLAG == 0)		asm("nop");

	EPT->U32EPTCSR.CNTEN = 0;
	EPT->EPTCNT = 0;
}

void Delay_ms(UINT32 ms)
{
	UINT8 nMs;
	UINT32 nMs100;

	nMs=ms%100;
	nMs100=ms/100;

	if(nMs100)
	{
		EPT->U32EPTRLD.RLD = SysFreq/10-1; 	//����ֵ
		EPT->U32EPTCSR.INTEN =0;						//EPT�ж�ʹ������
		EPT->U32EPTCSR.CLKSRC = 1;						//����ʱ��Դ���ڲ�ʱ��
		EPT->U32EPTCSR.CNTEN = 1;           			//������ʹ��

		do{
			while(EPT->U32EPTCSR.CNTFLAG == 0)		asm("nop");
			nMs100--;
		}while(nMs100);

		EPT->U32EPTCSR.CNTEN = 0;           		//��������ֹ
		EPT->EPTCNT = 0;                    					//��ռ�����
	}

	if(nMs)
	{
		EPT->U32EPTRLD.RLD = SysFreq/1000*nMs-1;
		EPT->U32EPTCSR.INTEN =0;
		EPT->U32EPTCSR.CLKSRC = 1;
		EPT->U32EPTCSR.CNTEN = 1;

		while(EPT->U32EPTCSR.CNTFLAG == 0)		asm("nop");

		EPT->U32EPTCSR.CNTEN = 0;
		EPT->EPTCNT = 0;
	}
}



void Delay_seconds(UINT32 s)
{
	while(s)
		{
			Delay_ms(1000);
			s--;
		}
}

