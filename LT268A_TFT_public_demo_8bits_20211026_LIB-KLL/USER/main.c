#include "iostring.h"
#include "delay.h"
#include "uart.h"
#include "LT268A.h"
#include "pwm.h"
#include "TFTLCD.h"
#include "w25qxx.h"
#include "function.h"
#include "module_select.h"
#include "flash.h"
#include "bsp.h"
#include "pit.h"
#include "tp.h"

UINT8 init_ok_flag = 0;

void InitialChip(void)
{
	EIC->IER=0;						//disable interrupt
	//WDT->WMR =0x0;				//CLOSE WDT------
	//WDT->WCR =0x0;
	EFM->U32EFMCR.WS=2;

	EFM->U16PVDC.PVDTEST = 1;
	EFM->U16PVDC.PVDTEST = 2;
	EFM->U16PVDC.PVDTEST = 3;
	EFM->U16PVDC.PVDC = 2;	//VCC less than 2.48V reset
	EFM->U16PVDC.PVDPORRE = 1;


	CLOCK->U32SYNCR.SYNCTEST = 1;
	CLOCK->U32SYNCR.SYNCTEST = 2;
	CLOCK->U32SYNCR.SYNCTEST = 3;

	CLOCK->U32SYNCR.SYSDIV=MCU_SYSDIV-1;
	CLOCK->U32SYNCR.IPSDIV=MCU_IPSDIV-1;
	CLOCK->U32SYNCR.ADCDIV=MCU_ADCDIV-1;
}

int main(void)
{
	UINT8 buff_9A[3],buff_80[3];
	uint8_t i=0;

	InitialChip();
	Delay_ms(50);

	SPI_Init();         																	//外部Flash SPI初始化
	LT_ReadParam();																			//Flash info
	Uart_Init();        																	//Uart Init
	LTPrintf("  Uart_Init_succeed!       \r\n");
	LTPrintf("  Flash_Type=%d  LCD= %d x %d   \r\n",Flash_Type,LCD_XSIZE_TFT,LCD_YSIZE_TFT);

	LCD_TFT_Init();
//	LCD_XSIZE_TFT=240;  LCD_YSIZE_TFT=320; LCD_BL_Init(400);
//	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,Red);Delay_ms(1500);
//	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,Green);Delay_ms(1500);
//	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,Blue);Delay_ms(1500);
//	 disp_V_Gray();  while(1); 	//RGB display(TFT test)
	//LCD_XSIZE_TFT=240;  LCD_YSIZE_TFT=320;
	PIT0_Init();
	PIT3_Init();                															//PIT

#if R_TOUCH_FLAG
	LT_TpInit();
#else
	CTP_Init();
#endif

#if   MODULE_9A            																	//执行9A 00开机指令
	cmd_flag=1;
	buff_9A[0] = 0x9a;
	buff_9A[1] = 0x00;
	buff_9A[2] = 0x00;
	if(LT_ManageCmd_9A(buff_9A)==OK)
	{
		LT_DataToPc(buff_9A,3);
		cmd_flag=0;
	}

	cmd_flag=1;
	buff_80[0] = 0x80;
	buff_80[1] = 0x2C;
	LT_ManageCmd_80(buff_80);
	cmd_flag=0;
//
//	cmd_flag=1;
//
//	buff_90[0] = 0x90;
//	buff_90[1] = 0x01;
//
//	gUsartRx.Count = buff_90+7;
//	LT_ManageCmd_90(buff_90);
//	cmd_flag=0;
#endif

//	Delay_ms(1);
	LCD_BL_Init(400);																		//Backlight 0~900

	busyflag = 0;
	gUsartRx.Count=0;

	if(init_ok_flag)
	{
		LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
		LT268_TFT_ShowAscll(10,140,24,1,Red,Red,(UINT8 *)"User Area Data Error, Please Update User Area Data");
	}

	while(1)
	{
		if(RS485_Handle.E_Cnt >= 500 )
		{
			N_BatteryData_Filling(0xa0);
	 		RS485_Handle.E_Cnt = 0;
		}

		Main_From_UartRxBuff();
		if(gUsartRx.Flag)
		{
			gUsartRx.Flag=0;
			busyflag = 1;
//			for(i=0;i<10;i++)
//			{
//				UART0->SCIDRL = gUsartRx.Buf[i];
//				while (UART0->U8SCISR1.TC == 0){};
//			}
//			for(i=0;i<27;i++)
//			{
//				RS485_Handle.ucCmdDataN[i]=gUsartRx.Buf[i];
//				UART0->SCIDRL = RS485_Handle.ucCmdDataN[i];
//				while (UART0->U8SCISR1.TC == 0){};
//				UART0->SCIDRL = Allobj_RS485_Handle.battery_soc/10;
//				while (UART0->U8SCISR1.TC == 0){};
//
//				UART0->SCIDRL = Allobj_RS485_Handle.battery_temp/10;
//				while (UART0->U8SCISR1.TC == 0){};
//
//				UART0->SCIDRL = Allobj_RS485_Handle.battery_vol/10;
//				while (UART0->U8SCISR1.TC == 0){};
//
//				UART0->SCIDRL = Allobj_RS485_Handle.battery_current/10;
//				while (UART0->U8SCISR1.TC == 0){};
//			}
//			LT_ReceiveCmd(gUsartRx.Buf);
//			Receive_E_Handle(&RS485_Handle);
			show(&RS485_Handle);
//			show_number(Allobj_RS485_Handle);


			busyflag = 0;
			RS485_Handle.cmdFlatN=0;
			gUsartRx.Count = 0;									//清零才能接收下次数据
			cmd_9A_flag=0;
			LT_ClearRxBuf();

		}
		if(RS485_Handle.TempCount>=45)
		{
			show_temp(Allobj_RS485_Handle);
			RS485_Handle.TempCount=0;
		}

		#if   MODULE_81
				if(gTurnFlag)					    TurnForm();
		#endif

		#if   MODULE_88
				if(gGifFlag)					    TurnGif();
		#endif

		#if   MODULE_D8
				if(rool_one_flag)					TurnRoll_One();
		#endif

		#if   MODULE_D9
				if(RollFlag)						TurnPicture();
		#endif

		#if   MODULE_C9
				if(Slide_Flag)			 			 Slide();
		#endif

		#if   MODULE_A0_A1
				if(ControlFlag)						 button();
		#endif

		#if   MODULE_A2_A3
				if(ControlFlag2)					 button2();
		#endif
			}
}



