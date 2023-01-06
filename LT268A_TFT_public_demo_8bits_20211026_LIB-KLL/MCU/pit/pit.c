#include "pit.h"
#include "iostring.h"
#include "bsp.h"
#include "pwm.h"
#include "data.h"
#include "tp.h"


//void PIT0_Handler(void)
//{
//
//	UINT32 rdVal;
//	if(wbuf_select==1)					//ѡ��Buf0
//	{
//		if(wbuf0_Stat)					//Buf0����׼���õı�־
//		{
//			rdVal = wavBuf0[bufPos++];	//��ȡBuf0������
//			//8bits����Ƶ����д��16bits��PWM��Ƶ�Ĵ�����Ҫ�Ƶ���8λ
//			rdVal = rdVal<<8;
//
//			//PCM�����Ƿ�Ϊ����
//			if((rdVal&0x8000)==0x8000)
//			{
//				rdVal = (0xFF00-rdVal)&0xFF00;		//����תPWM����
//				//H_PWM_VAL�� PWM��������ֵ
//				rdVal = (H_PWM_VAL*rdVal)/32767;
//				//PCM����ת�ɵ�PWMռ�ձ�д��Ĵ���
//				PWM0->PCMR3 = (H_PWM_VAL - rdVal);
//			}
//			else
//			{
//				//H_PWM_VAL�� PWM��������ֵ
//				rdVal = (H_PWM_VAL*rdVal)/32767;
//				//PCM����ת�ɵ�PWMռ�ձ�д��Ĵ���
//			PWM0->PCMR3 = (H_PWM_VAL + rdVal);
//			}
//			if(bufPos>=256)
//			{
//				wbuf_select = 2;	//Buf0���ݶ�ȡ��������־ָ��Buf1
//				bufPos = 0;			//Buf����־����
//				wbuf0_Stat = 0;		//Buf0����׼���õı�־����
//			}
//		}
//	}
//
//	if(wbuf_select==2)				//ѡ��Buf1
//	{
//			if(wbuf1_Stat)			//Buf1����׼���õı�־
//			{
//				rdVal = wavBuf1[bufPos++];
//				rdVal = rdVal<<8;
//
//				if((rdVal&0x8000)==0x8000)
//				{
//						rdVal = (0xFF00-rdVal)&0xFF00;
//						rdVal = (H_PWM_VAL*rdVal)/32767;
//						PWM0->PCMR3 = (H_PWM_VAL - rdVal);
//				}
//				else
//				{
//					rdVal = (H_PWM_VAL*rdVal)/32767;
//					PWM0->PCMR3 = (H_PWM_VAL + rdVal);
//				}
//
//				if(bufPos>=256)
//				{
//					wbuf_select = 1;
//					bufPos = 0;
//					wbuf1_Stat = 0;
//				}
//			}
//	}
//	PIT0->U16PCSR.PIF =1;		// 4.clear PIF interrupt flag
//
//}

void PIT0_Handler(void)
{
	if(RS485_Handle.RxCount > 25)
	{
		RS485_Handle.RxEndFlag++;
	}

	PIT0->U16PCSR.PIF =1;		// 4.clear PIF interrupt flag
}

UINT8 LT_PlayWav(void)
{
#if MODULE_B8_B9
	if(gWavState == 1)
	{
		gWavState = 0;
		gTempWavFlashAddr = gWavFlashAddr;
		gWavState = 0;
		//��ȡ���ݵ� Buf0
		LT_ReadFlash(wavBuf0,gTempWavFlashAddr,256);
		gTempWavFlashAddr += 256;
		wbuf0_Stat = 1;//Buf0 ����׼����
		//��ȡ���ݵ� Buf1
		LT_ReadFlash(wavBuf1,gTempWavFlashAddr,256);
		gTempWavFlashAddr += 256;
		wbuf1_Stat = 1;//Buf1 ����׼����
		wbuf_select = 1;//ѡ�� Buf0
		LT_BuglePwmInit();		//����
		PIT0_Init();

		Set_GPIO_A_In_Out(0x00);
		Write_GPIO_A_7_0(0x00);
		//LTPrintf("wbuf0_Stat:%d\n",wbuf0_Stat);
	}
	if(wbuf0_Stat==0)//Buf0 ���ݿ�
	{
		LT_ReadFlash(wavBuf0,gTempWavFlashAddr,256);
		gTempWavFlashAddr += 256;
		wbuf0_Stat = 1;
		//��ȡ���ݵ�ַ���� WAV �ļ����ȣ� ��ַ����
		if(gTempWavFlashAddr>=gWavLen)
		{
			gTempWavFlashAddr = gWavFlashAddr;
			//�ж��Ƿ�ֻ����һ��
			if(gWavType == 0)
			{
				gWavFlag = 0;
				gWavState = 0;
				//TIM_Cmd(TIM3, DISABLE);
				//TIM_Cmd(TIM2, DISABLE);
				PIT2->U16PCSR.EN=0;
				Write_GPIO_A_7_0(0xff);
				//Set_GPIO_A_In_Out(0xff);
			}
		}
	}
	if(wbuf1_Stat==0)//Buf1 ���ݿ�
	{
		LT_ReadFlash(wavBuf1,gTempWavFlashAddr,256);
		gTempWavFlashAddr += 256;
		wbuf1_Stat = 1;
		//��ȡ���ݵ�ַ���� WAV �ļ����ȣ� ��ַ����
		if(gTempWavFlashAddr>=gWavLen)
		{
			gTempWavFlashAddr = gWavFlashAddr;
			//�ж��Ƿ�ֻ����һ��
			if(gWavType == 0)
			{
				close_wav();
			}
		}
	}
#endif
	return OK;
}

void close_wav(void)
{
#if MODULE_B8_B9
	gWavFlag = 0;
	gWavState = 0;
	PIT2->U16PCSR.EN=0;
//	Write_GPIO_A_7_0(0xff); 																										//�ص�Դ
#endif
}

//��ֹ��ʱ��14
void LT_UsartTimeDisable(void)
{
	PIT1->U16PCSR.PIE=0;
	PIT1->U16PCSR.EN=0;
}

//ʹ�ܶ�ʱ��14
void LT_UsartTimeEnable(void)
{
//	gRxfist = 0;
	PIT1->U16PCSR.PIE=1;
	PIT1->U16PCSR.EN=1;
}

//���ö�ʱ��14װ��ֵ
void LT_UsartTimeSetCounter(UINT32 Counter)
{
	PIT1->PMR = Counter;//
	PIT1->U16PCSR.PIF =1;
	LT_UsartTimeEnable();
}

void PIT1_Handler(void)
{
	UINT8 buf[2];
	LT_UsartTimeDisable();
	PIT1->U16PCSR.PIF =1;
	if(busyflag == 0)
	{
		gUsartRx.Flag = 1;
	}
	else
	{
		gRxFlag = 0;
		gUsartRx.Count=0;
		buf[0] = 0x55;
		LT_DataToPc(buf,1);																														//��ʱʱ�䵽��æʱ����0xA5
	}
}

void PIT3_Handler(void)
{

#if   MODULE_81
			if(gOpen81==1)
			{
				gTurnFlag = 1;
			}
#endif

#if   MODULE_86_87
			if(gOpenTP==1)
			{
					gTPFlag = 1;
			}
#endif

#if   MODULE_88
			if(gOpen88==1)
			{
					gGifFlag = 1;
			}
#endif

#if   MODULE_8B
			if(RTP_read_Flag==1)
			{
				RTP_time++;
				if(RTP_time>5)
				{
					RTP_read_Flag=0;
					RTP_time=0;
				}
			}
#endif

#if MODULE_D8
			if(gOpenD8==1)
			{
					rool_one_flag = 1;
			}
#endif

#if  MODULE_D9
			if(gOpenD9==1)
			{
					RollFlag = 1;
			}
#endif

	//����ʱ��δ���յ�BMS�ظ�
	if(RS485_Handle.cmdFlatN==0)
	{
		RS485_Handle.E_Cnt+=1;
	}
	else
	{
		RS485_Handle.E_Cnt=0;
	}

	//�쳣״̬����
	if(show_flag==2)
	{
		RS485_Handle.TempCount+=1;
	}
	else
	{
		RS485_Handle.TempCount=0;
	}
	//
	PIT3->U16PCSR.PIF =1;		// 4.clear PIF interrupt flag

}

void PIT0_Init(void)
{
	PIT0->U16PCSR.EN=0;//����ENλ
	PIT0->PMR = 450000;//1ms
	PIT0->U16PCSR.PRE= 4;	//72mhz/16
	PIT0->U16PCSR.PIE=1;//�ж�ʹ��PIE
	PIT0->U16PCSR.RLD=1;//��װλRLD
	PIT0->U16PCSR.EN=1;//PITʹ��EN

	EIC->IER|=IRQ(9); //enable pit0 interrupt

}

void PIT1_Init(void)
{
	PIT1->PMR = 16874;//15ms
	PIT1->U16PCSR.PRE= 6;	//72mhz/64
	PIT1->U16PCSR.OVW=1;//
	PIT1->U16PCSR.RLD=1;//��װλRLD
	PIT1->U16PCSR.PIE=0;//�ж�ȡ��PIE
	PIT1->U16PCSR.EN=0;//PITȡ��EN

	EIC->IER|=IRQ(10); //enable pit0 interrupt
}


void PIT3_Init(void)
{
	PIT3->U16PCSR.EN=0;//����ENλ

	PIT3->PMR = 45000;//10ms
	PIT3->U16PCSR.PRE= 4;	//72/16
	PIT3->U16PCSR.PIE=1;//�ж�ʹ��PIE
	PIT3->U16PCSR.RLD=1;//��װλRLD
	PIT3->U16PCSR.EN=1;//PITʹ��EN

	EIC->IER|=IRQ(12); //enable pit3 interrupt
}


