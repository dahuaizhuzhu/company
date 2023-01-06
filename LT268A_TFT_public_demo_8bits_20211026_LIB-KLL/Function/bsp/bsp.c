#include <string.h>
#include "bsp.h"
#include "function.h"
#include "pwm.h"
#include "QR_Encode.h"
#include "data.h"
#include "delay.h"
#include "pit.h"
#include "SinCosTable.h"
#include "function.h"
#include "w25qxx.h"
#include "uart.h"
#include "rtc.h"
#include "tp.h"

UINT8 cmd_flag=0;                              			     //cmd into

#if MODULE_81
#define TURN_SIZE 4												//81
UINT8 gTurnCount = 0;
Turn_Info gTurnInfo[TURN_SIZE];
UINT8 gTurnFlag = 0;
UINT8 gOpen81 = 0;
#endif

#if MODULE_88
#define GIF_SIZE 4												//88
UINT8 gGifCount = 0;
Gif_Info gGifInfo[GIF_SIZE];
UINT8 gGifFlag = 0;
UINT8 gOpen88 = 0;
#endif

#if MODULE_90
#define NUM_SIZE_90 10											//90
UINT16 gNumWidth[NUM_SIZE_90] = {0};
#endif

#if MODULE_91
#define NUM_SIZE_91 10											//91
UINT16 gNumWidth1[NUM_SIZE_91] = {0};
#endif

#if MODULE_B0
UINT16 ProgressLenght[8]={0};
#endif

#if MODULE_A0_A1
#define CONTROL_SIZE 20											//A0_A1
Control_Info controlInfo[CONTROL_SIZE];
UINT8 control_buf[8][2];
UINT8 ControlFlag = 0;
UINT8 ControlCount = 0;
UINT8 button_count;
UINT8 button_flag = 0;
#endif

#if MODULE_A2_A3
#define CONTROL_SIZE2 10										//A2_A3
Control_Info2 controlInfo2[CONTROL_SIZE2] = {0};
UINT8 control_buf2[8][2] = {0};
UINT8 ControlCount2 = 0;
UINT8 button_count2;
UINT8 ControlFlag2 = 0;
UINT8 button_flag2 = 0;
#endif

#if MODULE_C9
UINT8 Slide_oper=0;														 //C9
UINT8 Slide_Flag=0;
UINT8 Slide_count=0;
UINT8 Slide_mode=4;
UINT8 Slide_press=0;
UINT8 Slide_cmd[4][2];
#endif

#if MODULE_CA_CF												//CA-CF
UINT8 UartRegIndex=0;
UINT8 UartReg[256]={0};
UINT8 UartBin=0;
#endif

#define C0_D7      4
#define C0_D7_SIZE 30
//volatile UINT16 gRecordWidth[C0_D7][C0_D7_SIZE];
volatile UINT16 gRecordHigh[C0_D7][C0_D7_SIZE];
UINT8 C0_gNumRow=0;


const UINT16 gDutyBuf[16] = {0,20,30,50,80,120,160,200,250,280,300,450,500,600,700,799};			//将背光分成16等级,BA

#if MODULE_D8
#define ROLL_ONE_SIZE 4												//D8
Roll_One roll_one[ROLL_ONE_SIZE];
UINT8 gOpenD8 = 0;
UINT8 d8_sum = 0;
UINT8 rool_one_flag = 0;
UINT8 roll_one_count = 0;
#endif

#if MODULE_D9
#define ROLL_MORE_SIZE 4											//D9
Roll_Info RollInfo[ROLL_MORE_SIZE];
UINT8 RollFlag = 0;
UINT8 gOpenD9 = 0;
UINT8 Rollcount = 0;
#endif

UINT32 FullScreen_Pic_Addr=0;
UINT16 FullScreen_Square_Color=White;

UINT8 FF_Update_Flag=0;												//FF

UINT8 New_Function(UINT8 cmd,UINT8 *RxBuf)
{
	UINT8 command;
	switch(cmd)
	{
	case 0:
#if   MODULE_80
				 command=LT_ManageCmd_80(RxBuf); 		break;									//---0x80
#endif
#if  !(MODULE_80)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 1:
#if   MODULE_81
				 command=LT_ManageCmd_81(RxBuf);  		break;	    							//---0x81
#endif
#if  !(MODULE_81)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 2:
#if   MODULE_82
				 command=LT_ManageCmd_82(RxBuf);		break;	 								//---0x82
#endif
#if  !(MODULE_82)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 3:command=LT_Idle(RxBuf);          			break;    								//---0x83

	case 4:
#if   MODULE_84
				 command=LT_ManageCmd_84(RxBuf);		break;	 								//---0x84
#endif
#if  !(MODULE_84)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 5:
#if   MODULE_85
				 command=LT_ManageCmd_85(RxBuf);    	break;      							//---0x85
#endif
#if  !(MODULE_85)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 6:
#if   MODULE_86_87
				 command=LT_ManageCmd_86(RxBuf);    	break;     								//---0x86
#endif
#if   !(MODULE_86_87)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 7:
#if   MODULE_86_87
				 command=LT_ManageCmd_87(RxBuf);   		break;    								//---0x87
#endif
#if   !(MODULE_86_87)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 8:
#if   MODULE_88
				 command=LT_ManageCmd_88(RxBuf);   		break;    								//---0x88
#endif
#if  !(MODULE_88)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 9:
#if   MODULE_89
				 command=LT_ManageCmd_89(RxBuf);   		break;    								//---0x89
#endif
#if  !(MODULE_89)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 10:
#if   MODULE_8A
				 command=LT_ManageCmd_8A(RxBuf); 		break;									//---0x8a
#endif
#if  !(MODULE_8A)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 11:
#if   MODULE_8B
				 command=LT_ManageCmd_8B(RxBuf); 		break;									//---0x8b
#endif
#if  !(MODULE_8B)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 12:
#if   MODULE_8C_8D
				 command=LT_ManageCmd_8C(RxBuf); 		break;	 								//---0x8c
#endif
#if   !(MODULE_8C_8D)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 13:
#if   MODULE_8C_8D
				 command=LT_ManageCmd_8D(RxBuf); 		break;									//---0x8d
#endif
#if   !(MODULE_8C_8D)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 14:command=LT_Idle(RxBuf);    	   				break;    								//---0x8E
	case 15:                                                     								//---0x8F
#if   MODULE_8F
				 command=LT_ManageCmd_8F(RxBuf); 		break;
#endif
#if  !(MODULE_8F)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 16:
#if   MODULE_90
				 command=LT_ManageCmd_90(RxBuf);    	break;      							//---0x90
#endif
#if  !(MODULE_90)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 17:
#if   MODULE_91
				 command=LT_ManageCmd_91(RxBuf);    	break;      							//---0x91
#endif
#if  !(MODULE_91)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 18:command=LT_Idle(RxBuf); 		 			break;									//---0x92
	case 19:command=LT_Idle(RxBuf); 		 			break;									//---0x93
	case 20:
#if   MODULE_94_95
				 command=LT_ManageCmd_94(RxBuf);    	break;      							//---0x94
#endif
#if  !(MODULE_94_95)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
//
	case 21:
#if   MODULE_94_95
				 command=LT_ManageCmd_95(RxBuf);    	break;      							//---0x95
#endif
#if  !(MODULE_94_95)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 22:command=LT_Idle(RxBuf); 		 			break;									//---0x96
	case 23:command=LT_Idle(RxBuf); 		 			break;									//---0x97

	case 24:
#if   MODULE_98
				 command=LT_ManageCmd_98(RxBuf);  		break;									//---0x98
#endif
#if  !(MODULE_98)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 25:command=LT_Idle(RxBuf); 		 			break;									//---0x99
	case 26:
#if   MODULE_9A
				 command=LT_ManageCmd_9A(RxBuf);  		break;									//---0x9A
#endif
#if  !(MODULE_9A)
				 command=LT_Idle(RxBuf); 		 		break;
#endif

	case 27:
#if   MODULE_9B_9C
				command=LT_ManageCmd_9B(RxBuf); 		break;									//---0x9B
#endif
#if  !(MODULE_9B_9C)
				 command=LT_Idle(RxBuf); 		 		break;
#endif

	case 28:
#if   MODULE_9B_9C
				command=LT_ManageCmd_9C(RxBuf); 		break;									//---0x9C
#endif
#if  !(MODULE_9B_9C)
				 command=LT_Idle(RxBuf); 		 		break;
#endif

	case 29:command=LT_Idle(RxBuf); 		 			break;									//---0x9D
	case 30:
#if   MODULE_9E
				command=LT_ManageCmd_9E(RxBuf); 		break;								    //---0x9E
#endif
#if  !(MODULE_9E)
				 command=LT_Idle(RxBuf); 		 		break;
#endif

	case 31:command=LT_Idle(RxBuf); 		 			break;									//---0x9F
	case 32:
#if   MODULE_A0_A1
				 command=LT_ManageCmd_A0(RxBuf);   		break; 									//---0xA0_A1
#endif
#if  !(MODULE_A0_A1)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 33:
#if   MODULE_A0_A1
				 command=LT_ManageCmd_A1(RxBuf);   		break;
#endif
#if  !(MODULE_A0_A1)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 34:
#if   MODULE_A2_A3
				 command=LT_ManageCmd_A2(RxBuf);   		break;        							  //---0xA2_A3
#endif
#if  !(MODULE_A2_A3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 35:
#if   MODULE_A2_A3
				 command=LT_ManageCmd_A3(RxBuf);   		break;
#endif
#if  !(MODULE_A2_A3)
				 command=LT_Idle(RxBuf);    	   		break;								    //---0xA2
#endif
	case 36:command=LT_Idle(RxBuf); 		 			break;									//---0xA4
	case 37:command=LT_Idle(RxBuf); 		 			break;									//---0xA5
	case 38:command=LT_Idle(RxBuf); 		 			break;									//---0xA6
	case 39:command=LT_Idle(RxBuf); 		 			break;									//---0xA7
	case 40:command=LT_Idle(RxBuf); 		 			break;									//---0xA8
	case 41:command=LT_Idle(RxBuf); 		 			break;									//---0xA9
	case 42:command=LT_Idle(RxBuf); 		 			break;									//---0xAA
	case 43:command=LT_Idle(RxBuf); 		 			break;									//---0xAB
	case 44:command=LT_Idle(RxBuf); 		 			break;									//---0xAC
	case 45:command=LT_Idle(RxBuf); 		 			break;									//---0xAD
	case 46:command=LT_Idle(RxBuf); 		 			break;									//---0xAE
	case 47:command=LT_Idle(RxBuf); 		 			break;									//---0xAF
	case 48:
#if   MODULE_B0
				 command=LT_ManageCmd_B0(RxBuf);  		break;									//---0xB0
#endif
#if  !(MODULE_B0)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 49:
#if   MODULE_B1
				 command=LT_ManageCmd_B1(RxBuf);  		break;									//---0xB1
#endif
#if  !(MODULE_B1)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 50:command=LT_Idle(RxBuf); 		 			break;									//---0xB2
	case 51:command=LT_Idle(RxBuf); 		 			break;									//---0xB3

	case 52:
#if   MODULE_B4
				 command=LT_ManageCmd_B4(RxBuf);  		break;									//---0xB4
#endif
#if  !(MODULE_B4)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 53:command=LT_Idle(RxBuf); 		 			break;									//---0xB5
	case 54:command=LT_Idle(RxBuf); 		 			break;									//---0xB6
	case 55:command=LT_Idle(RxBuf); 		 			break;									//---0xB7

	case 56:
#if   MODULE_B8_B9
				 command=LT_ManageCmd_B8(RxBuf);		break; 									//---0xB8
#endif
#if   !(MODULE_B8_B9)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 57:
#if   MODULE_B8_B9
				 command=LT_ManageCmd_B9(RxBuf);		break; 									//---0xB9
#endif
#if   !(MODULE_B8_B9)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 58:
#if   MODULE_BA
				 command=LT_ManageCmd_BA(RxBuf);		break; 									//---0xBA
#endif
#if  !(MODULE_BA)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 59:command=LT_Idle(RxBuf); 		 			break;									//---0xBB

	case 60:
#if   MODULE_BC
				 command=LT_ManageCmd_BC(RxBuf);		break; 									//---0xBC
#endif
#if  !(MODULE_BC)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 61:
#if   MODULE_BD
				 command=LT_ManageCmd_BD(RxBuf);		break; 									//---0xBD
#endif
#if  !(MODULE_BD)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 62:
#if   MODULE_BE
				 command=LT_ManageCmd_BE(RxBuf);		break; 									//---0xBE
#endif
#if  !(MODULE_BE)
				 command=LT_Idle(RxBuf); 		 		break;
#endif

	case 63:
#if   MODULE_BF
				 command=LT_ManageCmd_BF(RxBuf);		break; 									//---0xBF
#endif
#if  !(MODULE_BF)
				 command=LT_Idle(RxBuf); 		 		break;
#endif

	case 64:
#if   MODULE_C0_C3
				 command=LT_ManageCmd_C0_C3(RxBuf);		break; 									//---0xC0
#endif
#if   !(MODULE_C0_C3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 65:
#if   MODULE_C0_C3
				 command=LT_ManageCmd_C0_C3(RxBuf);		break; 									//---0xC1
#endif
#if   !(MODULE_C0_C3)
				 command=LT_Idle(RxBuf);    	  		break;
#endif

	case 66:
#if   MODULE_C0_C3
				 command=LT_ManageCmd_C0_C3(RxBuf);		break; 									//---0xC2
#endif
#if   !(MODULE_C0_C3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 67:
#if   MODULE_C0_C3
				 command=LT_ManageCmd_C0_C3(RxBuf);		break; 									//---0xC3
#endif
#if   !(MODULE_C0_C3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 68:command=LT_Idle(RxBuf); 		 			break;									//---0xc4
	case 69:command=LT_Idle(RxBuf); 		 			break;									//---0xc5
	case 70:command=LT_Idle(RxBuf); 		 			break;									//---0xc6
	case 71:command=LT_Idle(RxBuf); 		 			break;									//---0xc7
	case 72:command=LT_Idle(RxBuf); 		 			break;									//---0xc8
	case 73:
#if   MODULE_C9
				 command=LT_ManageCmd_C9(RxBuf);		break; 									//---0xc9
#else
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 74:																					//---0xca
#if   MODULE_CA_CF
				 command=LT_ManageCmd_CA(RxBuf);		break; 									//---0xca
#endif
#if  !(MODULE_CA_CF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 75:
	#if   MODULE_CA_CF
				 command=LT_ManageCmd_CB(RxBuf);		break; 									//---0xcb
#endif
#if  !(MODULE_CA_CF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 76:
	#if   MODULE_CA_CF
				 command=LT_ManageCmd_CC(RxBuf);		break; 									//---0xcd
#endif
#if  !(MODULE_CA_CF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 77:
	#if   MODULE_CA_CF
				 command=LT_ManageCmd_CD(RxBuf);		break; 									//---0xcd
#endif
#if  !(MODULE_CA_CF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 78:
	#if   MODULE_CA_CF
				 command=LT_ManageCmd_CE(RxBuf);		break; 									//---0xce
#endif
#if  !(MODULE_CA_CF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 79:
	#if   MODULE_CA_CF
				 command=LT_ManageCmd_CF(RxBuf);		break; 									//---0xcf
#endif
#if  !(MODULE_CA_CF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 80:
#if   MODULE_D0_D3
				 command=LT_ManageCmd_D0_D3(RxBuf);		break; 									//---0xD0
#endif
#if   !(MODULE_D0_D3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 81:
#if   MODULE_D0_D3
				 command=LT_ManageCmd_D0_D3(RxBuf);		break; 									//---0xD1
#endif
#if   !(MODULE_D0_D3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 82:
#if   MODULE_D0_D3
				 command=LT_ManageCmd_D0_D3(RxBuf);		break; 									//---0xD2
#endif
#if   !(MODULE_D0_D3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 83:
#if   MODULE_D0_D3
				 command=LT_ManageCmd_D0_D3(RxBuf);		break; 									//---0xd3
#endif
#if   !(MODULE_D0_D3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 84:command=LT_Idle(RxBuf); 		 			break;									//---0xd4
	case 85:command=LT_Idle(RxBuf); 		 			break;									//---0xd5
	case 86:command=LT_Idle(RxBuf); 		 			break;									//---0xd6
	case 87:command=LT_Idle(RxBuf); 		 			break;									//---0xD7
	case 88:
#if  MODULE_D8
				 command=LT_ManageCmd_D8(RxBuf);		break; 									//---0xD8
#endif
#if  !(MODULE_D8)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 89:
#if   MODULE_D9
				 command=LT_ManageCmd_D9(RxBuf);		break; 									//---0xD9
#endif
#if  !(MODULE_D9)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 90:command=LT_Idle(RxBuf); 		 			break;									//---0xDA
	case 91:
#if   MODULE_DB
				 command=LT_ManageCmd_DB(RxBuf);		break; 									//---0xDB
#endif
#if  !(MODULE_DB)
				 command=LT_Idle(RxBuf);    	   		break;
#endif
	case 92:
#if   MODULE_DC
				 command=LT_ManageCmd_DC(RxBuf);		break; 									//---0xdc
#endif
#if  !(MODULE_DC)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 93:command=LT_Idle(RxBuf); 		 			break;									//---0xDD
	case 94:command=LT_Idle(RxBuf); 		 			break;									//---0xDE
	case 95:
	#if   MODULE_DF
				 command=LT_ManageCmd_DF(RxBuf);		break; 									//---0xDF
	#endif
	#if  !(MODULE_DF)
				 command=LT_Idle(RxBuf);    	   		break;
	#endif

	case 96:
#if   MODULE_E0
				 command=LT_ManageCmd_E0(RxBuf);		break; 									//---0xe0
#endif
#if  !(MODULE_E0)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 97:
#if   MODULE_E1_E3
				 command=LT_ManageCmd_E1_E3(RxBuf);		break; 									//---0xe1
#endif
#if   !(MODULE_E1_E3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 98:
#if   MODULE_E1_E3
				 command=LT_ManageCmd_E1_E3(RxBuf);		break; 									//---0xe2
#endif
#if   !(MODULE_E1_E3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 99:
#if   MODULE_E1_E3
				 command=LT_ManageCmd_E1_E3(RxBuf);		break; 									//---0xe3
#endif
#if   !(MODULE_E1_E3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 100:
#if   MODULE_E4_E6
				 command=LT_ManageCmd_E4_E6(RxBuf);		break; 									//---0xe4
#endif
#if   !(MODULE_E4_E6)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 101:
#if   MODULE_E4_E6
				 command=LT_ManageCmd_E4_E6(RxBuf);		break; 									//---0xe5
#endif
#if   !(MODULE_E4_E6)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 102:
#if   MODULE_E4_E6
				 command=LT_ManageCmd_E4_E6(RxBuf);		break; 									//---0xe6
#endif
#if   !(MODULE_E4_E6)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 103:
#if   MODULE_E7_E9
				 command=LT_ManageCmd_E7_E9(RxBuf);		break; 									//---0xe7
#endif
#if   !(MODULE_E7_E9)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 104:
#if   MODULE_E7_E9
				 command=LT_ManageCmd_E7_E9(RxBuf);		break; 									//---0xe8
#endif
#if   !(MODULE_E7_E9)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 105:
#if   MODULE_E7_E9
				 command=LT_ManageCmd_E7_E9(RxBuf);		break; 									//---0xe9
#endif
#if   !(MODULE_E7_E9)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 106:
#if   MODULE_EA_EC
				 command=LT_ManageCmd_EA_EC(RxBuf);		break; 									//---0xea
#endif
#if   !(MODULE_EA_EC)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 107:
#if   MODULE_EA_EC
				 command=LT_ManageCmd_EA_EC(RxBuf);		break; 									//---0xeb
#endif
#if   !(MODULE_EA_EC)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 108:
#if   MODULE_EA_EC
				 command=LT_ManageCmd_EA_EC(RxBuf);		break; 									//---0xec
#endif
#if   !(MODULE_EA_EC)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 109:
#if   MODULE_ED_EF
				 command=LT_ManageCmd_ED_EF(RxBuf);		break; 									//---0xed
#endif
#if   !(MODULE_ED_EF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 110:
#if   MODULE_ED_EF
				 command=LT_ManageCmd_ED_EF(RxBuf);		break; 									//---0xee
#endif
#if   !(MODULE_ED_EF)
				 command=LT_Idle(RxBuf);    	  		break;
#endif

	case 111:
#if   MODULE_ED_EF
				 command=LT_ManageCmd_ED_EF(RxBuf);		break; 									//---0xef
#endif
#if   !(MODULE_ED_EF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 112:
#if   MODULE_F0_F1
				 command=LT_ManageCmd_F0_F1(RxBuf);		break; 									//---0xf0
#endif
#if   !(MODULE_F0_F1)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 113:
#if   MODULE_F0_F1
				 command=LT_ManageCmd_F0_F1(RxBuf);		break; 									//---0xf1
#endif
#if   !(MODULE_F0_F1)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 114:
#if   MODULE_F2_F3
				 command=LT_ManageCmd_F2_F3(RxBuf);		break;						 			//---0xf2
#endif
#if   !(MODULE_F2_F3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 115:
#if   MODULE_F2_F3
				 command=LT_ManageCmd_F2_F3(RxBuf);		break; 									//---0xf3
#endif
#if   !(MODULE_F2_F3)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 116:
#if   MODULE_F4
				 command=LT_ManageCmd_F4(RxBuf);		break; 									//---0xf4
#endif
#if   !(MODULE_F4)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 117:
#if   MODULE_F5
				 command=LT_ManageCmd_F5(RxBuf);		break; 									//---0xf5
#endif
#if   !(MODULE_F5)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 118:
#if   MODULE_F6
				 command=LT_ManageCmd_F6(RxBuf);   		break;    								//---0xf6
#endif
#if   !(MODULE_F6)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	case 119:command=LT_Idle(RxBuf); 		 			break;									//---0xf7
	case 120:command=LT_Idle(RxBuf); 		 			break;									//---0xf8
	case 121:command=LT_Idle(RxBuf); 		 			break;									//---0xf9
	case 122:command=LT_Idle(RxBuf); 		 			break;									//---0xfa
	case 123:command=LT_Idle(RxBuf); 		 			break;									//---0xfb
	case 124:command=LT_Idle(RxBuf); 		 			break;									//---0xfc
	case 125:command=LT_Idle(RxBuf); 		 			break;									//---0xfd
	case 126:command=LT_Idle(RxBuf); 		 			break;									//---0xfe

	case 127:
#if   MODULE_FF
				 command=LT_ManageCmd_FF(RxBuf);    	break;  								//---0xFF
#endif
#if   !(MODULE_FF)
				 command=LT_Idle(RxBuf);    	   		break;
#endif

	}
	return command;
}
/***************将24位色深转为16位*********************/
UINT16 LT_Color24_To_16(UINT32 color)
{
	UINT16 r,g,b;
	r = ((color>>16)&0xff)/8;
	g = ((color>>8)&0xff)/4;
	b = ((color>>0)&0xff)/8;

	return ((r<<11)+(g<<5)+b);
}

/***************将8位色深转为16位*********************/
UINT16 LT_Color8_To_16(UINT8 color)
{
	UINT16 r,g,b;
	r = (color>>5)&0x07;
	g = (color>>2)&0x07;
	b = (color>>0)&0x03;

if(r==0)  r=0;
else if (r==7)  r=31;
else r=5*r;

	if(g==0)  g=0;
else if (g==7)  g=63;
else g=10*g+1;

	if(b==0)  b=0;
else if (b==3)  b=31;
else b=15*b;
//	r = ((color>>5)&0x07)*4;
//	g = ((color>>2)&0x07)*8;
//	b = ((color>>0)&0x03)*8;
	return ((r<<11)+(g<<5)+b);
}

/*
* 函数名：Rx_CRC_CCITT
* 功能  ：CRC校验
* 输入  ：buf：数据缓存首地址
          len：数据长度
* 输出  ：无
* 作者  ：LEVETOP
*/
UINT16 Rx_CRC_CCITT(UINT8 *puchMsg, UINT16 usDataLen)
{
	UINT16 wCRCin = 0x0000;
	UINT16 wCPoly = 0x1021;
	UINT8 wChar = 0;
	int i;
	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for (i = 0; i < 8; i++)
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}
	return (wCRCin&0xffff);
}

/*
* 函数名：LT_ReadFlash
* 功能  ：从外挂的FLASH中读取数据
* 输入  ：pBuffer:数据存储区
*         ReadAddr:开始读入的地址(24bit)
*         要读入的字节数(最大65535)
* 输出  ：无
* 作者  ：LEVETOP
*/
void LT_ReadFlash(UINT8* pBuffer,UINT32 ReadAddr,UINT16 NumByteToRead)
{
#if(Flash_Type!=2)
	LT268_W25QXX_Read(pBuffer,ReadAddr,NumByteToRead);
#endif
}


/*
* 函数名：LT_CalculateCmdAddr
* 功能  ：读取该命令的信息，并将其拆分成该命令结构体所对应的各个信息
* 输入  ：cmd：指令
          operand：操作数
* 输出  ：无
* 作者  ：LEVETOP
*/

UINT8 LT_AnalyzeCmdInfo(UINT8 *rxBuf)
{
	UINT8 res = 0;
	UINT8 cmd = rxBuf[0];
	UINT8 nn = rxBuf[1];
	UINT8 buff[3];
	buff[0] = cmd;
	buff[1] = nn;
	if(gUsartRx.Buf[0] != 0xFF && init_ok_flag == 1)
	{
		buff[2] = CMD_INFO_ERROR;
		LT_DataToPc(buff,3);								//该指令不属于80至FF，即没有此指令
		return CMD_RETURN_NULL;
	}

	if((cmd >= 0x80)&&(cmd <= 0xff))
	{
		//LT268_TFT_SetWindows(0,0,LCD_XSIZE_TFT,LCD_YSIZE_TFT);

		cmd -= 0x80;
		res = New_Function(cmd,rxBuf);

		if(res == OK)
		{
			buff[2] = OK;
			LT_DataToPc(buff,3);						     //成功执行该指令
		}
		if(res == CMD_OPER_ERROR)
		{
			buff[1] = 0x00;
			buff[2] = CMD_OPER_ERROR;               	     //指令参数错误
			LT_DataToPc(buff,3);
		}
		return res;
	}

	#if		USER_DEFINE_COMAND
		else if(cmd >= 0x60 && cmd <= 0x7F)
		{
			cmd -= 0x60;
			res = User_Function(cmd,rxBuf);
	//			if(res == OK)
	//			{
	//				buff[2] = OK;
	//				LT_DataToPc(buff,3);
	//			}
		}
	#endif

	else
	{
		buff[1] =0x00;
		buff[2] = CMD_INFO_ERROR;
		LT_DataToPc(buff,3);								//该指令不属于80至FF，即不存在该指令
		return CMD_RETURN_NULL;
	}

	return res;
}
/*
	功能：接收来自串口的命令
	输入：buf: 来自串口接收到数据的缓存
	输出：无
	作者：LEVETOP
*/
void LT_ReceiveCmd(UINT8 *buf)
{
//	Delay_ms(5);
	if(buf[gUsartRx.Count-2] == 0x0D && buf[gUsartRx.Count-1] == 0x0A)
	{
		gUsartRx.Count-=2;
	}
	#if   CRC_FLAG											//CRC_FLAG为1时要进行CRC校验
		UINT8 rebuf[16];
		UINT16 rxCrc,mcuCrc;
		gUsartRx.Flag = 0;
		busyflag = 1;

		rxCrc = gUsartRx.Buf[gUsartRx.Count-6];
		rxCrc = (rxCrc<<8)+gUsartRx.Buf[gUsartRx.Count-5];
		mcuCrc = Rx_CRC_CCITT(&buf[1],gUsartRx.Count-7);
		if(rxCrc==mcuCrc)
		{
			LT_AnalyzeCmdInfo(&buf[1]);
		}
		else
		{
			rebuf[0] = buf[1];
			rebuf[1] = buf[2];
			rebuf[2] = CRC_ERROR;							//CRC error
			LT_DataToPc(rebuf,3);
		}
	#endif

	#if			!(CRC_FLAG)
		gUsartRx.Flag = 0;
		busyflag = 1;
		LT_AnalyzeCmdInfo(&buf[1]);
	#endif

		busyflag = 0;
		gUsartRx.Count = 0;									//清零才能接收下次数据
		cmd_9A_flag=0;
		LT_ClearRxBuf();
}

void close_old_window(void)
{
	if(gPictureInfo.w == LCD_XSIZE_TFT && gPictureInfo.h == LCD_YSIZE_TFT)
	{
#if   MODULE_81
		gOpen81 = 0;
		gTurnFlag = 0;
#endif

#if   MODULE_88
		gOpen88 = 0;
		gGifFlag = 0;
#endif

#if   MODULE_A0_A1
		ControlFlag = 0;
		ControlCount = 0;
#endif

#if   MODULE_A2_A3
		ControlFlag2 = 0;
		ControlCount2 = 0;
#endif

#if   MODULE_C9
		Slide_Flag=0;
#endif

#if   MODULE_D8
		gOpenD8 = 0;
		rool_one_flag = 0;
#endif

#if   MODULE_D9
		gOpenD9 = 0;
		RollFlag = 0;
#endif

		FullScreen_Pic_Addr=gPictureInfo.addr;					//记录当前全屏图片的地址

	}
}

//--------------------------------------------------0x80指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_80
* 功能  ：处理命令CMD_80
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_80
UINT8 LT_ManageCmd_80(UINT8 *rxBuf)
{
	UINT8 buf = 0;
	UINT8 i = 0,res = 0;
	UINT8 remove_bcolor_flag;
	UINT16 x,y;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_80_info1(rxBuf,&buf);																//获取命令信息
		if(res!=OK)	return res;

		for(i = 0 ; i < (buf-1)/7 ; i ++)
		{
//			PWM0->U32PPCR.PDR1=0;			   		//写  0 or 1

			Get_80_info2(&i,&remove_bcolor_flag,&x,&y);												//对命令信息进行处理得到x、y坐标，是否去背景色，第几张图片及图片大小等信息

			if(remove_bcolor_flag == 0)  	   LT268_TFT_ShowPicture(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else if(remove_bcolor_flag == 1)   LT268_TFT_ShowPicture_Png(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else if(remove_bcolor_flag == 4)   LT268_TFT_ShowPicture_zip(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else return CMD_OPER_ERROR;

//			PWM0->U32PPCR.PDR1=1;			   		//写  0 or 1

			close_old_window();
		}
		return OK;
	}
	else
		return CMD_OPER_ERROR;
}
#endif
//--------------------------------------------------0x8A指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_8A
* 功能  ：处理命令CMD_8A
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_8A
UINT8 LT_ManageCmd_8A(UINT8 *rxBuf)
{
	UINT8 buf = 0;
	UINT8 i = 0,res = 0;
	UINT8 remove_bcolor_flag;
	UINT16 x,y;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_80_info1(rxBuf,&buf);																//获取命令信息
		if(res!=OK)	return res;
		for(i = 0 ; i < (buf-1)/7 ; i ++)
		{
			Get_80_info2(&i,&remove_bcolor_flag,&x,&y);
			//对命令信息进行处理得到x、y坐标，是否去背景色，第几张图片及图片大小等信息
			if(remove_bcolor_flag == 0)  	   LT268_TFT_ShowPicture(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else if(remove_bcolor_flag == 1)   LT268_TFT_ShowPicture_Png(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else if(remove_bcolor_flag == 4)   LT268_TFT_ShowPicture_zip(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else return CMD_OPER_ERROR;

			close_old_window();
		}
		return OK;
	}
	else
		return CMD_OPER_ERROR;
}
#endif
//------------------------------------------------------0x8F---------------------------------------------------------
#if   MODULE_8F
/*
* 函数名：LT_ManageCmd_8F
* 功能  ：灵活显示图片
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ManageCmd_8F(UINT8 *rxBuf)
{
	UINT8 remove_bcolor_flag;
	UINT16 x,y,pic_num;

	if((gUsartRx.Count==16)||(cmd_flag== 1))
	{
		x = rxBuf[2];
		x = (x << 8) + rxBuf[3];
		y = rxBuf[4];
		y = (y << 8) + rxBuf[5];
		remove_bcolor_flag = rxBuf[6];
		pic_num = rxBuf[7];
		pic_num = (pic_num << 8) + rxBuf[8];

		Get_8F_info1(&pic_num);

		if(remove_bcolor_flag == 0)  	   LT268_TFT_ShowPicture(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else if(remove_bcolor_flag == 1)   LT268_TFT_ShowPicture_Png(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else if(remove_bcolor_flag == 4)   LT268_TFT_ShowPicture_zip(x,y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else return CMD_OPER_ERROR;

		close_old_window();


		return OK;
	}
	else
		return CMD_OPER_ERROR;
}
#endif
//--------------------------------------------------0x81指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_81
* 功能  ：处理命令CMD_81
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_81
UINT8 LT_ManageCmd_81(UINT8 *rxBuf)
{
	UINT8 i = 0,j = 0,res = 0;
	UINT8 sum,t,oper,flag;
	UINT16 x,y;
	UINT16 pic[21] = {0};

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(rxBuf[1] & 0x80)																								//当rxBuf[1]最高位为1时停止动态显示
		{
			gOpen81 = 0;
			gTurnFlag = 0;
			return OK;
		}
		if(gOpen81 == 0)				gTurnCount = 0;
		res = Get_81_info1(rxBuf,&sum,&t,&flag,&x,&y,pic,&oper);														//获取81指令命令信息并存到结构体gTurnInfo中，同时得到图片的信息
		if(res!=OK)	return res;
		for(i = 0 ; i < gTurnCount ; i++)
		{
//			if(gTurnInfo[i].operation == oper)
//			{
//				return CMD_OPER_ERROR;
//			}
			if((x == gTurnInfo[i].x)&&(y == gTurnInfo[i].y))
			{
				gTurnCount--;																							//当该窗口已存在时，将现获取的命令信息取代之前的命令信息
				break;
			}
		}
		gTurnInfo[i].operation = oper;																					//之前还没有该窗口时，开辟一个新窗口
		gTurnInfo[i].sum = sum;
		gTurnInfo[i].t = t;
		gTurnInfo[i].x = x;
		gTurnInfo[i].y = y;
		gTurnInfo[i].w = gPictureInfo.w;
		gTurnInfo[i].h = gPictureInfo.h;
		gTurnInfo[i].flag = flag;

		for(j = 0 ; j < gTurnInfo[i].sum ; j++)
		{
			gTurnInfo[i].p[j] = pic[j];
		}

		if(gTurnInfo[i].flag == 0)       LT268_TFT_ShowPicture(gTurnInfo[i].x,gTurnInfo[i].y,gTurnInfo[i].w,gTurnInfo[i].h,gPictureInfo.addr);
		else if(gTurnInfo[i].flag == 1)  LT268_TFT_ShowPicture_Png(gTurnInfo[i].x,gTurnInfo[i].y,gTurnInfo[i].w,gTurnInfo[i].h,gPictureInfo.addr);
		else if(gTurnInfo[i].flag == 4)  LT268_TFT_ShowPicture_zip(gTurnInfo[i].x,gTurnInfo[i].y,gTurnInfo[i].w,gTurnInfo[i].h,gPictureInfo.addr);
		else return CMD_OPER_ERROR;

		gOpen81 = 1;																												//用于定时
		gTurnCount++;																												//开辟的窗口数，gTurnCount<=TURN_SIZE，否则会出错

		return OK;
	}
	else
		return CMD_OPER_ERROR;
}

/*
* 函数名：LT_ShowTurnPicture
* 功能  ：处理固定图片的显示和重复命令
* 输入  ：num:显示轮流图片的命令
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ShowTurnPicture(UINT8 num)
{
	gTurnInfo[num].p_c++;

	// 判断执行到的图片是否已经超过需要播放图片的总数
	if(gTurnInfo[num].p_c >= gTurnInfo[num].sum)		gTurnInfo[num].p_c = 0;

	Get_81_info2(&(gTurnInfo[num].p[gTurnInfo[num].p_c]));															//获取图片信息																										//2019

	if(gTurnInfo[num].flag == 0)    	LT268_TFT_ShowPicture(gTurnInfo[num].x,gTurnInfo[num].y,gTurnInfo[num].w,gTurnInfo[num].h,gPictureInfo.addr);
	else if(gTurnInfo[num].flag == 1)   LT268_TFT_ShowPicture_Png(gTurnInfo[num].x,gTurnInfo[num].y,gTurnInfo[num].w,gTurnInfo[num].h,gPictureInfo.addr);
	else if(gTurnInfo[num].flag == 4)   LT268_TFT_ShowPicture_zip(gTurnInfo[num].x,gTurnInfo[num].y,gTurnInfo[num].w,gTurnInfo[num].h,gPictureInfo.addr);
	else return CMD_OPER_ERROR;

	return OK;
}

void TurnForm(void)
{
	UINT8 i = 0;
	gTurnFlag = 0;
	for(i = 0 ; i < gTurnCount ; i++)	gTurnInfo[i].t_c++;
	for(i = 0 ; i < gTurnCount ; i++)
	{
		if(gTurnInfo[i].t_c >= gTurnInfo[i].t)
		{
			LT_ShowTurnPicture(i);																													//当某个窗口定时时间到时，开始切换到另张图片
			gTurnInfo[i].t_c = 0;																														//清零
		}
	}
}

#endif

//--------------------------------------------------0x84指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_84
* 功能  ：处理命令CMD_84
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_84
UINT8 LT_ManageCmd_84(UINT8 *rxBuf)
{
	UINT8 i = 0,j;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		for(i = 0 ; i < gTurnCount ; i++)
		{
			if(gTurnInfo[i].operation == rxBuf[1])
			{
				break;
			}
		}
		if(i == gTurnCount)
			return OK;

		LT268_TFT_FullScreen_Cut(gTurnInfo[i].x,gTurnInfo[i].y,gTurnInfo[i].w,gTurnInfo[i].h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		gTurnInfo[i].addr = gTurnInfo[gTurnCount - 1].addr;
		gTurnInfo[i].operation = gTurnInfo[gTurnCount - 1].operation;
		gTurnInfo[i].x = gTurnInfo[gTurnCount - 1].x;
		gTurnInfo[i].y = gTurnInfo[gTurnCount - 1].y;
		gTurnInfo[i].w = gTurnInfo[gTurnCount - 1].w;
		gTurnInfo[i].h = gTurnInfo[gTurnCount - 1].h;
		gTurnInfo[i].t = gTurnInfo[gTurnCount - 1].t;
		gTurnInfo[i].t_c = gTurnInfo[gTurnCount - 1].t_c;
		gTurnInfo[i].sum = gTurnInfo[gTurnCount - 1].sum;
		gTurnInfo[i].p_c = gTurnInfo[gTurnCount - 1].p_c;
		gTurnInfo[i].flag = gTurnInfo[gTurnCount - 1].flag;

		for(j = 0 ; j < gTurnInfo[i].sum ; j++)
		{
			gTurnInfo[i].p[j] = gTurnInfo[gTurnCount - 1].p[j];
		}

		gTurnInfo[gTurnCount - 1].x = 0;
		gTurnInfo[gTurnCount - 1].y = 0;
		gTurnInfo[gTurnCount - 1].w = 0;
		gTurnInfo[gTurnCount - 1].h = 0;
		gTurnCount--;
		if(gTurnCount==0)
		{
			gOpen81=0;
			gTurnFlag=0;
		}
		return OK;
	}
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0x85---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_85
* 功能  ：该指令没有用到
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_85
UINT8 LT_ManageCmd_85(UINT8 *rxBuf)
{
	UINT8 buf = 0;
	UINT8 i = 0,res = 0;
	UINT8 remove_bcolor_flag;
	UINT16 x,y;
	rxBuf[0]=0x80;
	res = Get_80_info1(rxBuf,&buf);																								//获取命令信息
	if(res!=OK)	return res;

	for(i = 0 ; i < (buf-1)/7 ; i ++)
	{
		Get_80_info2(&i,&remove_bcolor_flag,&x,&y);

		LT268_TFT_FullScreen_Cut(x,y,gPictureInfo.w,gPictureInfo.h,FullScreen_Pic_Addr,color65k_white);

		close_old_window();
	}
		return OK;
}
#endif

//--------------------------------------------------0x88指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_88
* 功能  ：处理命令CMD_88
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_88
UINT8 LT_ManageCmd_88(UINT8 *rxBuf)
{
	UINT8 i = 0,res = 0;
	UINT8 t,oper,pic[10] = {0};
	UINT16 x, y, s, f;
	UINT8 loop=0,flag=0;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(rxBuf[1] & 0x80)
		{
			gOpen88 = 0;
			gGifFlag = 0;
			return OK;
		}
		if(gOpen88 == 0)				gGifCount = 0;

		res = Get_88_info1(rxBuf,&s,&t,&f,&x,&y,pic,&oper,&loop,&flag);																	//获取88指令命令信息并存到结构体gGifInfo中，同时得到图片的信息
		if(res!=OK)	return res;

		for(i = 0 ; i < gGifCount ; i++)
		{
	//		if(gGifInfo[i].operation == oper)
	//		{
	//			return CMD_OPER_ERROR;
	//		}
			if((x == gGifInfo[i].x)&&(y == gGifInfo[i].y))
			{
				gGifCount--;																																		//当该窗口已存在时，将现获取的命令信息取代之前的命令信息
				break;
			}
		}

		gGifInfo[i].operation = oper;																												//之前还没有该窗口时，开辟一个新窗口
		gGifInfo[i].s = s;
		gGifInfo[i].f = f;
		gGifInfo[i].p_c = s;
		gGifInfo[i].t = t;
		gGifInfo[i].x = x;
		gGifInfo[i].y = y;
		gGifInfo[i].loop=loop;
		gGifInfo[i].flag=flag;
		gGifInfo[i].w = gPictureInfo.w;
		gGifInfo[i].h = gPictureInfo.h;


		if(gGifInfo[i].flag==0)LT268_TFT_ShowPicture(gGifInfo[i].x,gGifInfo[i].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else if(gGifInfo[i].flag==1)LT268_TFT_ShowPicture_Png(gGifInfo[i].x,gGifInfo[i].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else if(gGifInfo[i].flag==4)LT268_TFT_ShowPicture_zip(gGifInfo[i].x,gGifInfo[i].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else return CMD_OPER_ERROR;

		gOpen88 = 1;
		gGifCount++;																																				//开启的窗口数要<=GIF_SIZE,否则会出错

		return OK;
	}
	else
		return CMD_OPER_ERROR;
}

/*
* 函数名：LT_ShowGifPicture
* 功能  ：处理固定图片的显示和重复命令
* 输入  ：num:显示轮流图片的命令
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ShowGifPicture(UINT8 num)
{
	if(gGifInfo[num].loop==1)
	{
		gGifInfo[num].p_c++;
		// 判断执行到的图片是否已经超过需要播放图片的总数
		if(gGifInfo[num].p_c > gGifInfo[num].f)		gGifInfo[num].p_c = gGifInfo[num].s;

		Get_88_info2(&(gGifInfo[num].p_c));																									//获取图片信息

		if(gGifInfo[num].flag==0)		LT268_TFT_ShowPicture(gGifInfo[num].x,gGifInfo[num].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else if(gGifInfo[num].flag==1)LT268_TFT_ShowPicture_Png(gGifInfo[num].x,gGifInfo[num].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else if(gGifInfo[num].flag==4)LT268_TFT_ShowPicture_zip(gGifInfo[num].x,gGifInfo[num].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
		else return CMD_OPER_ERROR;
	}
	else if(gGifInfo[num].loop==0)
	{
		if(gGifInfo[num].p_c <gGifInfo[num].f)
		{
			gGifInfo[num].p_c++;

			Get_88_info2(&(gGifInfo[num].p_c));

			if(gGifInfo[num].flag==0)		LT268_TFT_ShowPicture(gGifInfo[num].x,gGifInfo[num].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else if(gGifInfo[num].flag==1)LT268_TFT_ShowPicture_Png(gGifInfo[num].x,gGifInfo[num].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else if(gGifInfo[num].flag==4)LT268_TFT_ShowPicture_zip(gGifInfo[num].x,gGifInfo[num].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
			else return CMD_OPER_ERROR;
		}
	}
	return OK;
}
void TurnGif(void)
{
	UINT8 i = 0;
	gGifFlag = 0;
	for(i = 0 ; i < gGifCount ; i++)	gGifInfo[i].t_c++;
	for(i = 0 ; i < gGifCount ; i++)
	{
		if(gGifInfo[i].t_c >= gGifInfo[i].t)
		{
			LT_ShowGifPicture(i);																														//当某个窗口定时时间到时，切换图片
			gGifInfo[i].t_c = 0;
		}
	}
}
#endif

//--------------------------------------------------0x89指令---------------------------------------------------------
#if   MODULE_89
UINT8 LT_ManageCmd_89(UINT8 *rxBuf)
{

	UINT8 i = 0;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		for(i = 0 ; i < gGifCount ; i++)
		{
			if(gGifInfo[i].operation == rxBuf[1])
			{
				break;
			}
		}
		if(i == gGifCount)
			return OK;

	//	LT768_BTE_Memory_Copy(MAIN_BUFF,LCD_XSIZE_TFT,gGifInfo[i].x,gGifInfo[i].y,
	//											MAIN_BUFF,LCD_XSIZE_TFT,gGifInfo[i].x,gGifInfo[i].y,
	//											Display_Layer,LCD_XSIZE_TFT,gGifInfo[i].x,gGifInfo[i].y,
	//											0x0c,gGifInfo[i].w,gGifInfo[i].h
	//										 );
		LT268_TFT_FullScreen_Cut(gGifInfo[i].x,gGifInfo[i].y,gGifInfo[i].w,gGifInfo[i].h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		gGifInfo[i].addr = gGifInfo[gGifCount - 1].addr;
		gGifInfo[i].operation = gGifInfo[gGifCount - 1].operation;
		gGifInfo[i].x = gGifInfo[gGifCount - 1].x;
		gGifInfo[i].y = gGifInfo[gGifCount - 1].y;
		gGifInfo[i].w = gGifInfo[gGifCount - 1].w;
		gGifInfo[i].h = gGifInfo[gGifCount - 1].h;
		gGifInfo[i].loop = gGifInfo[gGifCount - 1].loop;
		gGifInfo[i].t = gGifInfo[gGifCount - 1].t;
		gGifInfo[i].s = gGifInfo[gGifCount - 1].s;
		gGifInfo[i].f = gGifInfo[gGifCount - 1].f;

		gGifInfo[i].p_c = gGifInfo[gGifCount - 1].p_c;
		gGifInfo[i].t_c = gGifInfo[gGifCount - 1].t_c;

		gGifInfo[gGifCount - 1].x = 0;
		gGifInfo[gGifCount - 1].y = 0;
		gGifInfo[gGifCount - 1].w = 0;
		gGifInfo[gGifCount - 1].h = 0;
		gGifCount--;
		if(gGifCount==0)
		{
			gOpen88=0;
			gGifFlag=0;
		}

		return OK;
	}
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0x8B--------------------------------------------------------
/*
* 函数名：LT_ManageCmd_8B
* 功能  ：对电阻屏进行校正，电容屏不作任何处理
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_8B
UINT8 LT_ManageCmd_8B(UINT8 *rxBuf)
{
	UINT8 buff[3];
//	if((gUsartRx.Count==8)||(cmd_flag== 1))
//	{
		#if  R_TOUCH_FLAG
				LT_TpAdjust();
		#if  MODULE_81
				gOpen81 = 0;
				gTurnFlag = 0;
		#endif

		#if  MODULE_88
				gOpen88 = 0;
				gGifFlag = 0;
		#endif

		#if  MODULE_A0_A1
				ControlFlag = 0;
				ControlCount = 0;
		#endif

		#if   MODULE_A2_A3
				ControlFlag2 = 0;
				ControlCount2 = 0;
		#endif

		#if  MODULE_B8_B9
				close_wav();
		#endif

		#if  MODULE_D8
				gOpenD8 = 0;
				rool_one_flag = 0;
		#endif

		#if  MODULE_D9
				gOpenD9 = 0;
				RollFlag = 0;
		#endif
			buff[0]= 0x8B;
			buff[1]= 0x00;
			buff[2]= 0x00;
			LT_DataToPc(buff,3);

		#if   MODULE_9A
			UINT8 buff_9A[3];
			cmd_flag=1;
			buff_9A[0] = 0x9A;
			buff_9A[1] = 0x00;
			buff_9A[2] = 0x00;
			if(LT_ManageCmd_9A(buff_9A)==OK)
			{
				LT_DataToPc(buff_9A,3);
				cmd_flag=0;
			}
		#endif

		#endif

		#if !R_TOUCH_FLAG
			buff[0]=0x8B;
			buff[1]=0x00;
			buff[2]=CMD_INFO_ERROR;
			LT_DataToPc(buff,3);
		#endif

//		return OK;
//	}
//	else  return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0x90---------------------------------------------------------
#if   MODULE_90
/*
* 函数名：LT_ManageCmd_90
* 功能  ：处理数字图片
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT16 LT_NumWidth_90(UINT8 *rxBuf,UINT16 x)
{
	UINT8 i = 0;
	UINT8 record = 0;
	UINT16 pic_w = 0;
	UINT16 dot_w = 0;
	UINT16 comma_w = 0;
	UINT16 width = 0;   // x

	UINT8 len = gUsartRx.Count - 7;																						//得到指令的长度

	Get_90_info3(&pic_w,&dot_w,&comma_w);

	for(i = 2 ; i < len ; i++)
	{
		if(rxBuf[i] == '.')
		{
			record = i;		   //在有小数点位置跳出并记住小数点所在位置
			break;
		}
	}

	//有小数
	if(record != 0)
	{
		for(i = 0 ; i < len-record-1 ; i++)					//len-record-1为小数点后面数字的个数
		{
			width += pic_w;
			if(width>LCD_XSIZE_TFT)	return width;		  //小数点后面数字宽度
		}

		width += dot_w;									//小数点后面数字宽度 + 小数点宽度
		if(width>LCD_XSIZE_TFT)	return width;

		for(i = 0 ; i < record-2 ; i++)
		{
			width += pic_w;							     	//小数点前面数字宽度 + 小数点后面宽度 + 小数点宽度
			if(width>LCD_XSIZE_TFT)	return width;
#if Comma
			if(i%3==2)
			{
				if((i + 1) < record-2)
				width += comma_w;														//小数点前面三个数字后如何还有数则加一个分隔号宽度
				if(width>LCD_XSIZE_TFT)	return width;
			}
#endif
		}
	}
	else																				//无小数
	{
		for(i = 0 ; i < len-2 ; i++)
		{
			width += pic_w;
			if(width>LCD_XSIZE_TFT)	return width;										//指令发送数字图片宽度和
#if Comma
			if(i%3==2)
			{
				if((i + 1) < len-2)
				width += comma_w;														//每隔三个数字后如果还有数字则加上一个分隔号宽度
				if(width>LCD_XSIZE_TFT)	return width;
			}
#endif
		}
	}
	//if((width%4)!=0)	width += (4 - width%4);											//把总数字图片宽度弄成4的倍数
	return width;
}

UINT8 LT_ManageCmd_90(UINT8 *rxBuf)
{
	UINT8 oper = 0;
	UINT16 x,y;
	UINT16 width = 0;
//	UINT16 bw_width = 0;
	UINT16 num_w,num_h,dot_w,dot_h,comma_w,comma_h;
	UINT32 num_addr;

//	UINT16 w = 0;
	UINT8 dir,color_flag,Color_F,Color_B;
	UINT8 res = 0;

	if((gUsartRx.Count>=9)||(cmd_flag== 1))
	{
		res = Get_90_info1(rxBuf,&oper,&dir,&color_flag,&Color_F,&Color_B,&x,&y);
		if(res!=OK)	return res;

		width = LT_NumWidth_90(rxBuf,x);																										//得到要显示数字图片的总宽度（包含逗号与分隔号），且为4的倍数
		if(dir==0) {if((width+x)>LCD_XSIZE_TFT)		width=LCD_XSIZE_TFT-x; }
		else	   {if(width>x)		width=x;    }

		num_w = gPictureInfo.w;
		num_h = gPictureInfo.h;
		num_addr=gPictureInfo.addr;

		Get_90_info2(&dot_w,&dot_h);																												//获取相关的符合图片信息
		comma_w = gPictureInfo.w;
		comma_h = gPictureInfo.h;

		Display_Number_picturn(rxBuf,dir,x,y,width,&gNumWidth[oper],num_w,num_h,dot_w,dot_h,comma_w,comma_h,color_flag,Color_F,Color_B,num_addr);
		return OK;
	}
	return CMD_OPER_ERROR;
}

void Display_Number_picturn(UINT8 *rxBuf,UINT8 dir,UINT16 x,UINT16 y,UINT16 width,UINT16 *gNumWidth,UINT16 num_w,UINT16 num_h,UINT16 dot_w,UINT16 dot_h,UINT16 comma_w,UINT16 comma_h,UINT8 color_flag,UINT8 Color_F,UINT8 Color_B,UINT32 num_addr)
{
	UINT8 i = 0 ,j = 0;
	UINT8 flag = 0;
	INT16 temp =0;
	UINT16 num_w2,dot_w2=0,comma_w2;

	if(dir==0) 																																					//向右
	{
		if(color_flag==1)LT268_TFT_FullScreen_Cut(x,y,*gNumWidth,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		else if(width<*gNumWidth) LT268_TFT_FullScreen_Cut(x+width,y,*gNumWidth-width,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		temp = 0;
	}
	else               																																	//向左
	{
		if(width-*gNumWidth<0)
		{
			if(color_flag==1)LT268_TFT_FullScreen_Cut(x-*gNumWidth,y,*gNumWidth,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
			else LT268_TFT_FullScreen_Cut(x-*gNumWidth,y,*gNumWidth-width,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		}
		else
		{
			if(color_flag==1)LT268_TFT_FullScreen_Cut(x-*gNumWidth,y,*gNumWidth,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		}
		temp = width;
	}

	*gNumWidth = width;
	//LTPrintf("width==%d\r\n",width);
	flag = 0;
	for(i = 2 ; i < gUsartRx.Count - 7 ; i++)
	{
		if(rxBuf[i]=='.')
		{
			flag = 1;																																				//判断要显示的图片是否含有'.'图片
			break;
		}
	}

	if(num_w%8!=0)	num_w2 = (num_w/8+1)*8;
	else	num_w2 = num_w;

	if(comma_w%8!=0)	comma_w2 = (comma_w/8+1)*8;
	else	comma_w2 = comma_w;

	if(dot_w%8!=0)	dot_w2 = (dot_w/8+1)*8;
	else	dot_w2 = dot_w;
	//LTPrintf("dot_w==%d,,dot_w2==%d\r\n",dot_w,dot_w2);
	if(dir==0)
	{
		//-------------------------------------------------- 显示整数部分 -----------------------------------------------
		//LTPrintf("显示整数部分\r\n");
		for(j = 2; j < i ; j++)
		{
#if Comma
			if(count==3)
			{
				count = 0;
				if(temp>width)	break;

				LT268_TFT_ShowNum(x+temp,y,comma_w,comma_h,color_flag,num_addr+(num_w2*num_h*10+dot_w2*dot_h)/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));	//显示某个要显示的数字图片

				temp += comma_w;
																														//超过显示区域后的数字不显示
			}
			count++;
#endif
			if(temp>width)	break;
			if(x+temp+num_w>LCD_XSIZE_TFT)	break;

			LT268_TFT_ShowNum(x+temp,y,num_w,num_h,color_flag,num_addr+num_w2*num_h*(rxBuf[j]-'0')/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));

			temp += num_w;
//  		LTPrintf("temp==%d\r\n",temp);																										//超过显示区域后的数字不显示
		}

		//-------------------------------------------------- 显示小数部分 -----------------------------------------------
		if(flag==1)
		{
			if(temp<=width)  																																			//超过显示区域后的数字不显示
			{
				LT268_TFT_ShowNum(x+temp,y,dot_w,dot_h,color_flag,num_addr+num_w2*num_h*10/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));

			}
			temp += dot_w;

			//LTPrintf("显示小数部分\r\n");
			for(j = i+1 ; j < gUsartRx.Count-7; j++)
			{
				if(temp>width)	break;   																														//超过显示区域后的数字不显示
				if(x+temp+num_w>LCD_XSIZE_TFT)	break;

				LT268_TFT_ShowNum(x+temp,y,num_w,num_h,color_flag,num_addr+num_w2*num_h*(rxBuf[j]-'0')/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));

				temp += num_w;
			}
		}

	}

	else if(dir==1)
	{
		//-------------------------------------------------- 显示小数部分 -----------------------------------------------
		if(flag==1)
		{
			//LTPrintf("显示小数部分\r\n");
			for(j = gUsartRx.Count - 8 ; j > i ; j--)
			{
				temp -= num_w;
				if(temp<0)	break;   																														//超过显示区域后的数字不显示
				LT268_TFT_ShowNum(x-width+temp,y,num_w,num_h,color_flag,num_addr+num_w2*num_h*(rxBuf[j]-'0')/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));
			}
			temp -= dot_w;
			if(temp>=0)  																																			//超过显示区域后的数字不显示
			{
				LT268_TFT_ShowNum(x-width+temp,y,dot_w,dot_h,color_flag,num_addr+num_w2*num_h*10/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));
			}
		}

		//-------------------------------------------------- 显示整数部分 -----------------------------------------------
		//LTPrintf("显示整数部分\r\n");
		for(j = i-1; j >= 2 ; j--)
		{
#if Comma
			if(count==3)
			{
				count = 0;
				temp -= comma_w;

				if(temp<0)	break;  																													//超过显示区域后的数字不显示
				if(x-width+temp<0)	break;

				LT268_TFT_ShowNum(x-width+temp,y,comma_w,comma_h,color_flag,num_addr+(num_w2*num_h*10+dot_w2*dot_h)/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));																		//显示某个要显示的数字图片
			}
			count++;
#endif

			temp -= num_w;
			if(temp<0)	break;    																													//超过显示区域后的数字不显示
			if(x-width+temp<0)	break;

			LT268_TFT_ShowNum(x-width+temp,y,num_w,num_h,color_flag,num_addr+num_w2*num_h*(rxBuf[j]-'0')/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));
		}
	}
}
#endif

//------------------------------------------------------0x91---------------------------------------------------------
#if   MODULE_91
/*
* 函数名：LT_ManageCmd_91
* 功能  ：处理数字图片
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT16 LT_NumWidth_91(UINT8 *rxBuf,UINT16 x)
{
	UINT8 i = 0;
	UINT8 record = 0;
	UINT16 pic_w = 0;
	UINT16 dot_w = 0;
	UINT16 width = 0;   // x

	UINT8 len = gUsartRx.Count - 7;																						//得到指令的长度

	Get_91_info3(&pic_w,&dot_w);

	for(i = 2 ; i < len ; i++)
	{
		if(rxBuf[i] == '.')
		{
			record = i;																													//在有小数点位置跳出并记住小数点所在位置
			break;
		}
	}

	//有小数
	if(record != 0)
	{
		for(i = 0 ; i < len-record-1 ; i++)																		//len-record-1为小数点后面数字的个数
		{
			width += pic_w;
			if(width>LCD_XSIZE_TFT)	return width-pic_w;													//小数点后面数字宽度
		}

		width += dot_w;																												//小数点后面数字宽度 + 小数点宽度
		if(width>LCD_XSIZE_TFT)	return width-dot_w;

		for(i = 0 ; i < record-2 ; i++)
		{
			width += pic_w;																											//小数点前面数字宽度 + 小数点后面宽度 + 小数点宽度
			if(width>LCD_XSIZE_TFT)	return width-pic_w;
#if Comma
			if(i%3==2)
			{
				if((i + 1) < record-2)
				width += dot_w;																										//小数点前面三个数字后如何还有数则加一个分隔号宽度
				if(width>LCD_XSIZE_TFT)	return width-dot_w;
			}
#endif
		}
	}
	else																																		//无小数
	{
		for(i = 0 ; i < len-2 ; i++)
		{
			width += pic_w;
			if(width>LCD_XSIZE_TFT)	return width-pic_w;													//指令发送数字图片宽度和
#if Comma
			if(i%3==2)
			{
				if((i + 1) < len-2)
				width += dot_w;																										//每隔三个数字后如果还有数字则加上一个分隔号宽度
				if(width>LCD_XSIZE_TFT)	return width-dot_w;
			}
#endif
		}
	}
//	if((width%4)!=0)	width += (4 - width%4);																//把总数字图片宽度弄成4的倍数
	return width;
}

void Display_Number_picturn_16bpp(UINT8 *rxBuf,UINT8 dir,UINT16 x,UINT16 y,UINT16 width,UINT16 *gNumWidth1,UINT16 num_w,UINT16 num_h,UINT16 dot_w,UINT16 dot_h,UINT16 comma_w,UINT16 comma_h,UINT8 color_flag,UINT32 num_addr)
{
	UINT8 i = 0;
	UINT8 j = 0;
	UINT8 count = 0;
	UINT8 flag = 0;
	INT16 temp =0;

	if(dir==0) 																																					//向左
	{
//		LTPrintf("width==%d,,*gNumWidth1=%d\r\n",width,*gNumWidth1);
		if(color_flag==1)	LT268_TFT_FullScreen_Cut(x,y,*gNumWidth1,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		else if(width<*gNumWidth1) LT268_TFT_FullScreen_Cut(x+width,y,*gNumWidth1-width,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		temp = 0;
	}
	else               																																	//向右
	{
		if(x-*gNumWidth1<0)
		{
			if(color_flag==1)LT268_TFT_FullScreen_Cut(0,y,*gNumWidth1,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		}
		else
		{
			if(color_flag==1)LT268_TFT_FullScreen_Cut(x-*gNumWidth1,y,*gNumWidth1,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
			else if(width<*gNumWidth1) LT268_TFT_FullScreen_Cut(x-*gNumWidth1,y,*gNumWidth1-width,num_h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		}
		temp = width;
	}

	*gNumWidth1 = width;
	flag = 0;
	for(i = 2 ; i < gUsartRx.Count - 7 ; i++)
	{
		if(rxBuf[i]=='.')
		{
			flag = 1;																																				//判断要显示的图片是否含有'.'图片
			break;
		}
	}

	if(dir==0)
	{
		//-------------------------------------------------- 显示整数部分 -----------------------------------------------
		//LTPrintf("显示整数部分\r\n");
		for(j = 2; j < i ; j++)
		{
#if Comma
			if(count==3)
			{
				count = 0;
				if(temp>width)	break;

				if(color_flag==0)			LT268_TFT_ShowPicture(x+temp,y,comma_w,comma_h,num_addr+(num_w*num_h*10+dot_w*dot_h)*2);
				else if(color_flag==1)	    LT268_TFT_ShowPicture_Png(x+temp,y,comma_w,comma_h,num_addr+(num_w*num_h*10+dot_w*dot_h)*2);
				else if(color_flag==4)	    LT268_TFT_ShowPicture_zip(x+temp,y,comma_w,comma_h,num_addr+(num_w*num_h*10+dot_w*dot_h)*2);

				temp += comma_w;
																														//超过显示区域后的数字不显示
			}
			count++;
#endif

			if(temp>width)	break;
			if(x+temp+num_w>LCD_XSIZE_TFT)	break;

			if(color_flag==0)			LT268_TFT_ShowPicture(x+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
			else if(color_flag==1)		LT268_TFT_ShowPicture_Png(x+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
			else if(color_flag==4)		LT268_TFT_ShowPicture_zip(x+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);

//			LT268_TFT_ShowNum(x+temp,y,num_w,num_h,color_flag,num_addr+num_w*num_h*(rxBuf[j]-'0')/8,LT_Color8_To_16(Color_F),LT_Color8_To_16(Color_B));
			temp += num_w;
																														//超过显示区域后的数字不显示
		}

		//-------------------------------------------------- 显示小数部分 -----------------------------------------------
		if(flag==1)
		{
			if(temp<=width)  																																			//超过显示区域后的数字不显示
			{
				if(color_flag==0)		LT268_TFT_ShowPicture(x+temp,y,dot_w,dot_h,num_addr+num_w*num_h*10*2);
				else if(color_flag==1)	LT268_TFT_ShowPicture_Png(x+temp,y,dot_w,dot_h,num_addr+num_w*num_h*10*2);
				else if(color_flag==4)	LT268_TFT_ShowPicture_zip(x+temp,y,dot_w,dot_h,num_addr+num_w*num_h*10*2);
			}
			temp += dot_w;

			//LTPrintf("显示小数部分\r\n");
			for(j = i+1 ; j < gUsartRx.Count-7; j++)
			{
				if(temp>width)	break;   																														//超过显示区域后的数字不显示
				if(x+temp+num_w>LCD_XSIZE_TFT)	break;

				if(color_flag==0) 		LT268_TFT_ShowPicture(x+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
				else if(color_flag==1)	LT268_TFT_ShowPicture_Png(x+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
				else if(color_flag==4)	LT268_TFT_ShowPicture_zip(x+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);

				temp += num_w;
			}
		}

	}

	else if(dir==1)
	{
		//-------------------------------------------------- 显示小数部分 -----------------------------------------------
		if(flag==1)
		{
			//LTPrintf("显示小数部分\r\n");
			for(j = gUsartRx.Count - 8 ; j > i ; j--)
			{
				temp -= num_w;
				if(temp<0)	break;   																														//超过显示区域后的数字不显示
				if(color_flag==0)      	   LT268_TFT_ShowPicture(x-width+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
				else if(color_flag==1) LT268_TFT_ShowPicture_Png(x-width+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
				else if(color_flag==4) LT268_TFT_ShowPicture_zip(x-width+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
			}

			temp -= dot_w;
			if(temp>=0)  																																			//超过显示区域后的数字不显示
			{
				if(color_flag==0)		LT268_TFT_ShowPicture(x-width+temp,y,dot_w,dot_h,num_addr+num_w*num_h*10*2);
				else if(color_flag==1)	LT268_TFT_ShowPicture_Png(x-width+temp,y,dot_w,dot_h,num_addr+num_w*num_h*10*2);
				else if(color_flag==4)	LT268_TFT_ShowPicture_zip(x-width+temp,y,dot_w,dot_h,num_addr+num_w*num_h*10*2);
			}
		}

		//-------------------------------------------------- 显示整数部分 -----------------------------------------------
		//LTPrintf("显示整数部分\r\n");
		for(j = i-1; j >= 2 ; j--)
		{
#if Comma
			if(count==3)
			{
				count = 0;
				temp -= comma_w;

				if(temp<0)	break;  																													//超过显示区域后的数字不显示
				if(x-width+temp<0)	break;

				if(color_flag==0)		LT268_TFT_ShowPicture(x-width+temp,y,comma_w,comma_h,num_addr+(num_w*num_h*10+dot_w*dot_h)*2);
				else if(color_flag==1)	LT268_TFT_ShowPicture_Png(x-width+temp,y,comma_w,comma_h,num_addr+(num_w*num_h*10+dot_w*dot_h)*2);
				else if(color_flag==4)	LT268_TFT_ShowPicture_zip(x-width+temp,y,comma_w,comma_h,num_addr+(num_w*num_h*10+dot_w*dot_h)*2);
			}
			count++;
#endif
			temp -= num_w;

			if(temp<0)	break;    																													//超过显示区域后的数字不显示
			if(x-width+temp<0)	break;

			if(color_flag==0)			LT268_TFT_ShowPicture(x-width+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
			else if(color_flag==1)		LT268_TFT_ShowPicture_Png(x-width+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
			else if(color_flag==4)		LT268_TFT_ShowPicture_zip(x-width+temp,y,num_w,num_h,num_addr+num_w*num_h*(rxBuf[j]-'0')*2);
		}
	}
}


UINT8 LT_ManageCmd_91(UINT8 *rxBuf)
{
	UINT8 oper = 0;
	UINT16 x,y;
	UINT16 width = 0;
	UINT16 num_w,num_h,dot_w,dot_h,comma_w,comma_h;
	UINT32 num_addr;
	UINT8 dir,color_flag;
	UINT8 res = 0;

	if((gUsartRx.Count>=9)||(cmd_flag== 1))
	{
		res = Get_91_info1(rxBuf,&oper,&dir,&color_flag,&x,&y);
		if(res!=OK)	return res;

		width = LT_NumWidth_91(rxBuf,x);																										//得到要显示数字图片的总宽度（包含逗号与分隔号），且为4的倍数

//		if(gNumWidth1[oper]>width)	w = gNumWidth1[oper];																			//如果前一个显示数字宽度大于现在要显示的宽度，取宽度为大的那个
//		else                      w = width;
		num_w = gPictureInfo.w;
		num_h = gPictureInfo.h;
		num_addr=gPictureInfo.addr;

		Get_91_info2(&dot_w,&dot_h);																												//获取相关的符合图片信息

		comma_w = dot_w;
		comma_h = dot_h;
		if(color_flag==2)	color_flag=1;

		Display_Number_picturn_16bpp(rxBuf,dir,x,y,width,&gNumWidth1[oper],num_w,num_h,dot_w,dot_h,comma_w,comma_h,color_flag,num_addr);
		return OK;
	}
	else
	return CMD_OPER_ERROR;
}



#endif

//------------------------------------------------------0x9A---------------------------------------------------------
/*
函数功能：处理命令CMD_9A
参数：
*/
UINT8 cmd_9A_flag=0;
#if   MODULE_9A
UINT8 LT_ManageCmd_9A(UINT8 *rxBuf)
{
	UINT8 buf1[8],buf2[8];
	UINT8 buf[8][2];
	UINT8 res = 0,j = 0;
	UINT8 length =0;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_9A_info(rxBuf,buf1,buf2,&length);
		if(res!=OK)	return res;
		length=(length-1)/2;

		for(j = 0;j < length;j++)
		{
			cmd_flag=1;
			buf[j][0] = buf1[j];
			buf[j][1] = buf2[j];
			if(buf[j][0]>=0x80)   New_Function(buf[j][0]-0x80,buf[j]);
			#if		USER_DEFINE_COMAND
					else if(buf[j][0]>=0x60 && buf[j][0]<=0x7F)	User_Function(buf[j][0]-0x60,buf[j]);
			#endif
		}
		cmd_flag=0;
		return OK;
	}
	else
	return CMD_OPER_ERROR;
}
#endif


//--------------------------------------------------0x9E指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_9E
* 功能  ：处理命令CMD_9E
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_9E
u8 LT_ManageCmd_9E(u8 *rxBuf)
{
	u8 cmd ;
	u8 i,j;
	cmd = rxBuf[1];
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(cmd ==0x81)
		{
			gOpen81 = 0;
			gTurnFlag = 0;
		}
		else if(cmd == 0x88 )
		{
			gOpen88 = 0;
			gGifFlag = 0;
		}
		else if(cmd == 0xA0)
		{
			ControlFlag = 0;
			ControlCount = 0;
		}
		else if(cmd ==0xA2)
		{
			ControlFlag2 = 0;
			ControlCount2 = 0;
		}
		else if(cmd == 0xB8)
		{
			gOpenD8 = 0;
			rool_one_flag = 0;
		}
		else if(cmd == 0xC9)
		{
			Slide_Flag=0;
		}
		else if(cmd == 0xD8)
		{
			gOpenD8 = 0;
			rool_one_flag = 0;
		}
		else if(cmd == 0xD9)
		{
			gOpenD9 = 0;
			RollFlag = 0;
		}

		else return CMD_OPER_ERROR;

		return OK;
	}
	return CMD_OPER_ERROR;
}
#endif




//--------------------------------------------------0xA0_A1指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_A0_A1
* 功能  ：处理命令CMD_A0_A1
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_A0_A1
UINT8 LT_ManageCmd_A0(UINT8 *rxBuf)
{
	UINT8 j;
	UINT16 i = 0;
	UINT8 oper = 0,flag = 0;
	UINT8 buf1[8] = {0},buf2[8] = {0};
	UINT16 x,y;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
	res = Get_A0_info(rxBuf,&oper,&flag,buf1,buf2,&x,&y);																														//获取控件的相关信息
	if(res!=OK)	return res;

	for(i = 0 ; i < ControlCount ; i++)
	{
		if(controlInfo[i].operation == oper)
		{
			ControlCount--;
			break;
		}
		if((x == controlInfo[i].x)&&(y == controlInfo[i].y))
		{
			ControlCount--;
			break;
		}
	}
	controlInfo[i].operation	= oper;
	controlInfo[i].x = x;
	controlInfo[i].y = y;
	controlInfo[i].flag = gCmdInfo[1];
	for(j = 0 ;j < 8;j++)
	{
		controlInfo[i].buf[j][0] = buf1[j];
		controlInfo[i].buf[j][1] = buf2[j];
	}
	controlInfo[i].addr = gPictureInfo.addr;
	controlInfo[i].h = gPictureInfo.h;
	controlInfo[i].w = gPictureInfo.w;																																							//将控件信息存到对应的结构体controlInfo中

	if(flag==0)	LT268_TFT_ShowPicture(controlInfo[i].x,controlInfo[i].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
	if(flag==1)	LT268_TFT_ShowPicture_Png(controlInfo[i].x,controlInfo[i].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);
	if(flag==4)	LT268_TFT_ShowPicture_zip(controlInfo[i].x,controlInfo[i].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);

	close_old_window();
	ControlCount++;
	if(ControlCount > CONTROL_SIZE)				ControlCount = 	CONTROL_SIZE;
	ControlFlag = 1;
	return OK;
	}
		return CMD_OPER_ERROR;
}

UINT8 LT_ManageCmd_A1(UINT8 *rxBuf)
{
	UINT8 i = 0,j,k;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		for(i = 0 ; i < ControlCount ; i++)
		{
			if(controlInfo[i].operation == rxBuf[1])
			{
				break;
			}
		}
		if(i == ControlCount)	return OK;

		LT268_TFT_FullScreen_Cut(controlInfo[i].x,controlInfo[i].y,controlInfo[i].w,controlInfo[i].h,FullScreen_Pic_Addr,FullScreen_Square_Color);

		controlInfo[i].addr = controlInfo[ControlCount - 1].addr;
		for(j = 0;j < 8;j++)
		{
			for(k = 0;k < 2;k++)
			{
				controlInfo[i].buf[j][k] = controlInfo[ControlCount - 1].buf[j][k];
			}
		}
		controlInfo[i].flag = controlInfo[ControlCount - 1].flag;
		controlInfo[i].operation = controlInfo[ControlCount - 1].operation;
		controlInfo[i].x = controlInfo[ControlCount - 1].x;
		controlInfo[i].y = controlInfo[ControlCount - 1].y;
		controlInfo[i].w = controlInfo[ControlCount - 1].w;
		controlInfo[i].h = controlInfo[ControlCount - 1].h;

		controlInfo[ControlCount - 1].x = 0;
		controlInfo[ControlCount - 1].y = 0;
		controlInfo[ControlCount - 1].w = 0;
		controlInfo[ControlCount - 1].h = 0;
		ControlCount--;
		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}

void button(void)
{
	UINT8 i,j;
	UINT8 buff[3];
	gTpInfo.scan();

	if(button_flag==0 && gTpInfo.sta)
	{
			button_flag = 1;
			for(i = 0;i < ControlCount;i++)
			{
				if(First_pressX >= controlInfo[i].x && First_pressX <= controlInfo[i].x + controlInfo[i].w && First_pressY >= controlInfo[i].y && First_pressY <= controlInfo[i].y + controlInfo[i].h )
				{//按下控件时
					if(controlInfo[i].flag == 1 || controlInfo[i].flag == 2)
					{
						if(controlInfo[i].flag == 1)
						{
						}
					}
					if(controlInfo[i].flag == 0)
					{																																					//对控件进行透明度处理方便比较直观看出控件是否按下
					}
					buff[0] = 0xA0;
					buff[1] = controlInfo[i].operation;
					buff[2] = 0x31;
					LT_DataToPc(buff,3);																																											//发送控件按下提示字符给上位机
					button_count = i;
					button_flag = 2;
					break;
				}

			}

	}
	if(gTpInfo.sta == 0 )
	{
		if( button_flag == 1)   button_flag=0;
		else if( button_flag == 2)
		{
			//控件按下之后再松开
			if(controlInfo[button_count].flag == 0)
			{
			}
			else if(controlInfo[button_count].flag == 1)
			{
			}
			else if(controlInfo[button_count].flag == 2)																															//还原回原先控件画面
			{
			}

			i=button_count;
			if(gTpInfo.x[0] >= controlInfo[i].x && gTpInfo.x[0] <= controlInfo[i].x + controlInfo[i].w && gTpInfo.y[0] >= controlInfo[i].y && gTpInfo.y[0] <= controlInfo[i].y + controlInfo[i].h)
			{
				buff[0] = 0xA0;
				buff[1] = controlInfo[button_count].operation;
				buff[2] = 0x30;
				LT_DataToPc(buff,3);
				for(j = 0;j < 8;j++)
				{
					control_buf[j][0] = controlInfo[button_count].buf[j][0];
					control_buf[j][1] = controlInfo[button_count].buf[j][1];
				}
				for(j = 0;j < 8;j++)
				{																																	//执行控件控制的指令
					cmd_flag = 1;
					if(control_buf[j][0]>=0x80)	New_Function(control_buf[j][0]-0x80,control_buf[j]);
					#if		USER_DEFINE_COMAND
					else if(control_buf[j][0]>=0x60 && control_buf[j][0]<=0x7F)	User_Function(control_buf[j][0]-0x60,control_buf[j]);
					#endif
					cmd_flag = 0;
				}
			}

			button_flag = 0;
		}
	}

}
#endif

//------------------------------------------------------0xA2_A3--------------------------------------------------------
/*
* 函数名：LT_ManageCmd_0xA2_A3
* 功能  ：处理命令CMD_0xA2_A3
* 输入  ：下位机接收到的数据缓存首地址
* 输出  ：无
* 作者  ：LEVETOP
*/
#if   MODULE_A2_A3
UINT8 LT_ManageCmd_A2(UINT8 *rxBuf)
{
	UINT8 j;
	UINT16 i = 0;
	UINT8 oper = 0;
	UINT8 buf1[8] = {0},buf2[8] = {0};
	UINT16 x,y,canvas_w,w,h;
	UINT8 res = 0;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_A2_info(rxBuf,&oper,buf1,buf2,&x,&y,&w,&h);		//获取控件相关信息

		if(res!=OK)	return res;

		for(i = 0 ; i < ControlCount2 ; i++)
		{
			if(controlInfo2[i].operation == oper)
			{
				ControlCount2--;
				break;
			}
			if((x == controlInfo2[i].x)&&(y == controlInfo2[i].y))
			{
				ControlCount2--;
				break;
			}
		}
		controlInfo2[i].operation	= oper;
		controlInfo2[i].x = x;
		controlInfo2[i].y = y;
		for(j = 0 ;j < 8;j++)
		{
			controlInfo2[i].buf[j][0] = buf1[j];
			controlInfo2[i].buf[j][1] = buf2[j];
		}
		controlInfo2[i].h =h;
		controlInfo2[i].w =w;									//将控件信息存到对应的结构体controlInfo2中

		ControlCount2++;
		if(ControlCount2 > CONTROL_SIZE)		ControlCount2 = CONTROL_SIZE;
		ControlFlag2 = 1;
		return OK;
	}
	return CMD_OPER_ERROR;
}

UINT8 LT_ManageCmd_A3(UINT8 *rxBuf)
{
	UINT8 i = 0,j,k;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		for(i = 0 ; i < ControlCount2 ; i++)
		{
			if(controlInfo2[i].operation == rxBuf[1])
			{
				break;
			}
		}
		if(i == ControlCount2)
			return OK;


		controlInfo2[i].addr = controlInfo2[ControlCount2 - 1].addr;
		for(j = 0;j < 8;j++)
		{
			for(k = 0;k < 2;k++)
			{
				controlInfo2[i].buf[j][k] = controlInfo2[ControlCount2 - 1].buf[j][k];
			}
		}

		controlInfo2[i].operation = controlInfo2[ControlCount2 - 1].operation;
		controlInfo2[i].x = controlInfo2[ControlCount2 - 1].x;
		controlInfo2[i].y = controlInfo2[ControlCount2 - 1].y;
		controlInfo2[i].w = controlInfo2[ControlCount2 - 1].w;
		controlInfo2[i].h = controlInfo2[ControlCount2 - 1].h;

		controlInfo2[ControlCount2 - 1].x = 0;
		controlInfo2[ControlCount2 - 1].y = 0;
		controlInfo2[ControlCount2 - 1].w = 0;
		controlInfo2[ControlCount2 - 1].h = 0;
		ControlCount2--;
		return OK;
	}
	return CMD_OPER_ERROR;
	}

void button2(void)
{
	UINT8 i,j;
	UINT8 buff[3];
		gTpInfo.scan();

		if(gTpInfo.sta)
		{

			for(i = 0;i < ControlCount2;i++)
			{

				if(gTpInfo.x[0] >= controlInfo2[i].x && gTpInfo.x[0] <= controlInfo2[i].x + controlInfo2[i].w && gTpInfo.y[0] >= controlInfo2[i].y && gTpInfo.y[0] <= controlInfo2[i].y + controlInfo2[i].h && button_flag2 == 0)
				{

					buff[0]	= 0xA2;
					buff[1] = controlInfo2[i].operation;
					buff[2] = 0x31;
					LT_DataToPc(buff,3);
					button_count2 = i;
					button_flag2 = 1;
					break;
				}

			}
		}
		if(gTpInfo.sta == 0 && button_flag2 == 1)
		{


			button_flag2 = 0;
			buff[0]	= 0xA2;
			buff[1] = controlInfo2[button_count2].operation;
			buff[2] = 0x30;
			LT_DataToPc(buff,3);
			for(j = 0;j < 8;j++)
			{
				control_buf2[j][0] = controlInfo2[button_count2].buf[j][0];
				control_buf2[j][1] = controlInfo2[button_count2].buf[j][1];

			}
			for(j = 0;j < 8;j++)
			{
				cmd_flag = 1;
				if(control_buf2[j][0]>=0x80)	New_Function(control_buf2[j][0]-0x80,control_buf2[j]);
				#if		USER_DEFINE_COMAND
				else if(control_buf2[j][0]>=0x60 && control_buf2[j][0]<=0x7F)	User_Function(control_buf2[j][0]-0x60,control_buf2[j]);
				#endif
				cmd_flag = 0;
			}
		}
}
#endif

//------------------------------------------------------0x8C--------------------------------------------------------
#if   MODULE_8C_8D
/*
* 函数名：LT_ManageCmd_8C
* 功能  ：设置RTC指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ManageCmd_8C(UINT8 *rxBuf)
{
	gRtcTime.year = rxBuf[1];
	gRtcTime.month = rxBuf[2];
	gRtcTime.day = rxBuf[3];
	gRtcTime.hour = rxBuf[4];
	gRtcTime.min = rxBuf[5];
	gRtcTime.sec = rxBuf[6];
	gRtcTime.week = rxBuf[7];

	LT_Ds1302WriteTimeAll(0);

	return OK;
}

//------------------------------------------------------0x8D---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_8D
* 功能  ：读取RTC指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ManageCmd_8D(UINT8 *rxBuf)
{
	LT_Ds1302Readtime();
	return OK;
}
#endif

//--------------------------------------------------0xB0指令---------------------------------------------------------
#if   MODULE_B0
UINT8 LT_ManageCmd_B0(UINT8 *rxBuf)
{
	UINT16 x,y,length,h;
	UINT8 width,dir;
	UINT32 color,color1;
	UINT8 res = 0,buf[2] = {0},mark;

	if((gUsartRx.Count==11)||(cmd_flag== 1))
	{
		if(gUsartRx.Count == 11)
		{
		ProgressLenght[rxBuf[1]] = rxBuf[2];
		ProgressLenght[rxBuf[1]] = (ProgressLenght[rxBuf[1]]<<8)+rxBuf[3];
		}
		res = Get_B0_info1(rxBuf,&x,&y,&dir,&width,&color,&mark,buf,&h,&color1);//Get_B0_info1(rxBuf,&x,&y,&dir,&width,&color,buf);
		if(res!=OK)	return res;
		if(mark)
		{
		cmd_flag=1;
			if(buf[0]==0x80)		LT_ManageCmd_80(buf);
			else if(buf[0]==0x8A)	LT_ManageCmd_8A(buf);
		cmd_flag=0;
	//		Canvas_Image_Start_address(Display_Layer);
	//		Canvas_image_width(LCD_XSIZE_TFT);
		}

		switch(dir)
			{
				case 0 : 																																											//向上
									if(mark == 0)				LT268_TFT_DrawSquare_Fill(x,y,x + width,y - h,LT_Color24_To_16(color1));
									LT268_TFT_DrawSquare_Fill(x,y,x + width,y - ProgressLenght[rxBuf[1]],LT_Color24_To_16(color));
								  break;
				case 1 :																																																//向下
									if(mark == 0)				LT268_TFT_DrawSquare_Fill(x,y,x + width,y + h,LT_Color24_To_16(color1));
									LT268_TFT_DrawSquare_Fill(x,y,x + width,y + ProgressLenght[rxBuf[1]],LT_Color24_To_16(color));
								  break;
				case 2 :																																																//向左
									if(mark == 0)				LT268_TFT_DrawSquare_Fill(x,y,x - h,y + width,LT_Color24_To_16(color1));
									LT268_TFT_DrawSquare_Fill(x,y,x - ProgressLenght[rxBuf[1]],y + width,LT_Color24_To_16(color));
								  break;
				case 3 : 																																																//向右
									if(mark == 0)				LT268_TFT_DrawSquare_Fill(x,y,x + h,y + width,LT_Color24_To_16(color1));
									LT268_TFT_DrawSquare_Fill(x,y,x + ProgressLenght[rxBuf[1]],y + width,LT_Color24_To_16(color));
									break;
				default : break;
			}

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xBC---------------------------------------------------------
#if   MODULE_BC
/*
* 函数名：LT_ManageCmd_BC
* 功能  ：Display on与Display off
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ManageCmd_BC(UINT8 *rxBuf)
{
	UINT8 buf[3];
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(rxBuf[1] == 0x00)
		{
		    LT_BacklightSet(0);

			LT268_Display_OFF();
			busyflag = 0;
			gUsartRx.Count=0;
			buf[0] = 0xBC;
			buf[1] = 0x00;
			buf[2] = OK;
			LT_DataToPc(buf,3);
			while(1)
			{
				Main_From_UartRxBuff();
				if(gUsartRx.Flag == 1)
				{
					gUsartRx.Flag = 0;
					Delay_ms(100);
					if((rxBuf[1] == 0x01)&&(rxBuf[0] == 0xBC))
					{
						LT268_Display_ON();
						LT_BacklightSet(gControlDuty);
						buf[0] = 0xBC;
						buf[1] = 0x01;
						buf[2] = OK;
						LT_DataToPc(buf,3);
						break;
					}
					else
					{
						gUsartRx.Flag = 0;
						gUsartRx.Count=0;
					}
				}
			}
		}
		else if(rxBuf[1] == 0x01)
		{
			LT268_Display_ON();
			LT_BacklightSet(gControlDuty);
			buf[0] = 0xBC;
			buf[1] = 0x01;
			buf[2] = OK;
			LT_DataToPc(buf,3);
		}
//		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xBA---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_BA
* 功能  ：设置背光亮度指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_BA
UINT8 LT_ManageCmd_BA(UINT8 *rxBuf)
{
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(rxBuf[1]>0x0f)	rxBuf[1] = 0x0f;
		gControlDuty = gDutyBuf[rxBuf[1]];
		LT_BacklightSet(gControlDuty);						//设置背光亮度函数

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xBD---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_BD
* 功能  ：软件复位
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_BD
UINT8 LT_ManageCmd_BD(UINT8 *rxBuf)
{
	if((gUsartRx.Count>=8)||(cmd_flag== 1))
	{
//		if(rxBuf[0]==0)
//		{
			UINT8 buf[3];
			buf[0] = rxBuf[0];;
			buf[1] = 0x00;
			buf[2] = 0x00;
			LT_DataToPc(buf,3);

			EIC->U32ICSR.SRST=1;
//		}
		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xBE---------------------------------------------------------
#if   MODULE_BE
/*
* 函数名：LT_ManageCmd_BE
* 功能  ：该指令表示是否可以进行串口发送指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
UINT8 LT_ManageCmd_BE(UINT8 *rxBuf)
{
	if((gUsartRx.Count==8)||(cmd_flag== 1))
	{
		UINT8 buf[3];
		buf[0] = rxBuf[0];;
		buf[1] = 0x00;
		buf[2] = 0x5A;
		LT_DataToPc(buf,3);
	}
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xBF---------------------------------------------------------
#if   MODULE_BF
/*
* 函数名：LT_ManageCmd_BF
* 功能  ：反馈工程时间和版本内容
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
void Get_Compile_Date(UINT16 *Year,UINT8 *Month,UINT8 *Day)
{
	UINT8 i=0;
	const char *pMonth[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	const char Date[12] = __DATE__;
	for(i=0;i<12;i++)
	{
		if(memcmp(Date, pMonth[i], 3)==0)
		{
			*Month=i+1;
			break;
		}
	}
	*Year = (UINT16)atoi(Date + 7);
	*Day = (UINT8)atoi(Date + 4);
}

UINT8 LT_ManageCmd_BF(UINT8 *rxBuf)
{
	UINT8 buf[49];
	UINT16 Year;
	UINT8 Month;
	UINT8 Day;
	if((gUsartRx.Count==8)||(cmd_flag== 1))
	{
	LT_ReadFlash(&buf[6],VERSION_TABLE_ADDR,42);
	Get_Compile_Date(&Year,&Month,&Day);
	buf[0]=0xBF;
	buf[1]=Year>>8;
	buf[2]=Year;
	buf[3]=Month;
	buf[4]=Day;
	buf[5]=0xCC;
	buf[48]=0x00;

	LT_DataToPc(buf,49);
//	return OK;
	}
	else		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xC0~0xC3---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_C0_C3
* 功能  ：显示汉字，支持16 * 16,24 * 24与36 * 36
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_C0_C3
UINT16 LT_FontWidth(UINT8 size,UINT8 h,UINT16 length,UINT8 *buf)
{
	UINT8 fontW = 0;
	UINT16 i = 0;
	INT16 count = length;
	UINT16 w = 0;
	fontW = size*h;
	while(count>0)
	{
		if(buf[i] < 0xa1)
		{
			w += fontW/2;                        //单数个非汉字后面连着汉字的话在非汉字与汉字之间加个非汉字的距离，非单数则没有该距离
			i++;
			count--;
		}
		else
		{
			w += fontW;
			i += 2;
			count-=2;
		}
	}
	return w;								//返回要显示汉字的总宽
}

UINT8 LT_ManageCmd_C0_C3(UINT8 *rxBuf)
{
	UINT16 x,y,y0,w=0;
	UINT32 color,b_color;
	UINT32 len = 0;
	UINT32 flashAddr = 0;
	UINT8  size = 0;
	UINT8 select_font,size_h,size_v,transparent,alignment;
	UINT8 oper = 0;
	UINT8 pos = 0;
	UINT8 res = 0;
	if((gUsartRx.Count>=9)||(cmd_flag== 1))
	{
		res = Get_C0_C3_info(rxBuf,&oper,&pos,&size,&len,&flashAddr,&x,&y,&w,&color,&b_color,&select_font,&size_h,&size_v,&transparent,&alignment);
		if(res!=OK)	return res;
		y0=y;
		if (x+w>LCD_XSIZE_TFT) w=LCD_XSIZE_TFT-x;  			//x轴边界

		if(gRecordHigh[pos][oper]!=0)
		{
			LT268_TFT_FullScreen_Cut(x,y,w,gRecordHigh[pos][oper],FullScreen_Pic_Addr,FullScreen_Square_Color);
			LT268_TFT_ShowString(x,y,w,size,transparent,flashAddr,LT_Color24_To_16(color),LT_Color24_To_16(b_color),gUsartRx.Count-9,&rxBuf[2]);
		}
		else
		{
			LT268_TFT_ShowString(x,y,w,size,transparent,flashAddr,LT_Color24_To_16(color),LT_Color24_To_16(b_color),gUsartRx.Count-9,&rxBuf[2]);										//第一次直接显示到显示窗口
		}

		gRecordHigh[pos][oper] = C0_gNumRow*size;     //y轴边界

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xC9---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_c9
* 功能  ：滑动操作
* 作者  ：LEVETOP
*/
#if   MODULE_C9
UINT8 LT_ManageCmd_C9(UINT8 *rxBuf)
{
	UINT8 i;
	UINT8 res=0;
	UINT8 buf[16];

	if((gUsartRx.Count=9)||(cmd_flag== 1))
	{
		if(Slide_count > 0)
		{
			Slide_count = 0;
		}

	    res=Get_C9_info(rxBuf,buf);
		if(res!=OK)	return res;

		Slide_oper=rxBuf[1];
		for(i=0;i<4;i++)
		{
			Slide_cmd[i][0]=buf[i*2];
			Slide_cmd[i][1]=buf[i*2+1];
			//LTPrintf("buff cmd     %x    %x          \r\n",buf[i*2],buf[i*2+1]);
		}

		Slide_count++;
		Slide_Flag=1;

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}

void Slide(void)
{
	UINT8 cmd[2],buff[4];
	INT16 Slide_xw,Slide_yw;

	gTpInfo.scan();

	if(Slide_press==0 && gTpInfo.sta)
	{
			Slide_press=1;

	}

	if(gTpInfo.sta == 0 && Slide_press)
	{
		  Slide_press=0;
		  Slide_xw=abs(gTpInfo.x[0] - First_pressX);
		  Slide_yw=abs(gTpInfo.y[0] - First_pressY);

		  if(Slide_xw>=slide_lenght||Slide_yw>=slide_lenght)
		  {
		   if(Slide_xw<Slide_yw)
		   {
			if( gTpInfo.y[0] < First_pressY ) Slide_mode=0;
			else  Slide_mode=1;
		   }
		   else
		   {
			if( gTpInfo.x[0] < First_pressX ) Slide_mode=2;
			else  Slide_mode=3;
		   }
		  }

		if( Slide_mode!=4 )
		{
			Slide_Flag=0;
			button_flag=0;                           			//防止松手执行A0 A2
			button_flag2=0;

			buff[0] = 0xC9;
			buff[1] = Slide_oper;
			buff[2] = Slide_mode;
			cmd[0]=Slide_cmd[Slide_mode][0];
			cmd[1]=Slide_cmd[Slide_mode][1];
			cmd_flag=1;

			if((cmd[0] >= 0x80)&&(cmd[0] < 0xff))
			{
				New_Function(cmd[0]-0x80,cmd);
					buff[3] = OK;
					LT_DataToPc(buff,4);
			}
			else if(cmd[0] >= 0x60 && cmd[0] <= 0x7F)
			{
				User_Function(cmd[0]-0x60,cmd);
					buff[3] = OK;
					LT_DataToPc(buff,4);
			}
			else if(cmd[0] == 0xFF)
			{
				Slide_Flag=1;
					buff[3] = CMD_INFO_ERROR;
					LT_DataToPc(buff,4);
			}
			else
			{
					buff[3] = CMD_OPER_ERROR;
					LT_DataToPc(buff,4);
			}
			//LTPrintf("buff cmd     %02x    %02x          \r\n",cmd[0],cmd[1]);
			//LTPrintf(" Slide   xw=%d    yw=%d     mode=%d   Slide_Flag=%d  \r\n",Slide_xw,Slide_yw,Slide_mode,Slide_Flag);

			cmd_flag=0;
			Slide_mode=4;
		}
	}
}

#endif

//----------------------------------------寄存器操作--------------------------------//
#if   MODULE_CA_CF

UINT8 LT_ManageCmd_CA(UINT8 *rxBuf)
{
	UartRegIndex=rxBuf[1];

	cmd_flag = 1;
	UINT8 buff_9A[2];
	buff_9A[0] = 0x9A;
	buff_9A[1] = UartReg[UartRegIndex];
	LT_ManageCmd_9A(buff_9A);
	cmd_flag = 0;
	return OK;
}

UINT8 LT_ManageCmd_CB(UINT8 *rxBuf)
{
	 UartRegIndex=rxBuf[1];
	 UartBin=1;

	return UartRegIndex;
}

UINT8 LT_ManageCmd_CC(UINT8 *rxBuf)
{
	if(UartBin==1)
	{
	UartBin=0;
	UartReg[UartRegIndex]=rxBuf[1];

	return OK;
	}
	else return CMD_OPER_ERROR;
}

UINT8 LT_ManageCmd_CD(UINT8 *rxBuf)
{
	UINT8 buff[4];
	buff[0]=0xCD;
	buff[1]=rxBuf[1];
	buff[2]=UartReg[rxBuf[1]];
	buff[3]=0x00;
	LT_DataToPc(buff,4);
	//return UartReg[rxBuf[1]];
	return OK;
}

UINT8 LT_ManageCmd_CE(UINT8 *rxBuf)
{
	if(UartReg[rxBuf[1]]<255)
	{
	UartReg[rxBuf[1]]++;
	return OK;
	}
	else return CMD_OPER_ERROR;
}

UINT8 LT_ManageCmd_CF(UINT8 *rxBuf)
{
	if(UartReg[rxBuf[1]]>0)
	{
	UartReg[rxBuf[1]]--;
	return OK;
	}
	else return CMD_OPER_ERROR;
}

#endif
//------------------------------------------------------0xB8--------------------------------------------------------
/*
* 函数名：LT_ManageCmd_B8
* 功能  ：播放、暂停WAV
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_B8_B9
UINT8 LT_ManageCmd_B8(UINT8 *rxBuf)
{
	UINT32 len = 0;
	UINT32 flashAddr = 0;
	UINT8 res = 0;

	close_wav();
	res = Get_B8_info(rxBuf,&flashAddr,&len);		//获取相关命令信息
	if(res!=OK)	return res;

	gWavFlashAddr = flashAddr;
	gWavLen = len + gWavFlashAddr;
	gWavFlag = 1;
	gWavState = 1;
	gWavOpen = 1;
	gWavType = rxBuf[1] & 0x80;
	return OK;
}

//------------------------------------------------------0xB9--------------------------------------------------------
UINT8 LT_ManageCmd_B9(UINT8 *rxBuf)
{
	close_wav();
	return OK;
}
#endif

//------------------------------------------------------0xd8---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_d8
* 功能  ：一张图片滚动
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_D8
UINT8 LT_ManageCmd_D8(UINT8 *rxBuf)
{
	UINT8 mode,t,i;
	UINT16 x,y,p_c;
	UINT8 res = 0;
	UINT8 oper = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(rxBuf[1] & 0x80)
		{
			gOpenD8 = 0;
			rool_one_flag = 0;
			return OK;
		}
		if(gOpenD8 == 0)
		{
			roll_one_count = 0;																																														//确保第一次进来的数据存放在结构体数组的第一个元素中
			d8_sum = 0;
		}
		if(roll_one_count > ROLL_ONE_SIZE - 1)
		{
			roll_one_count = 0;
			d8_sum = ROLL_ONE_SIZE;																																												//当发送的D8指令多于ROLL_ONE_SIZE窗口数，又循环回来存放
		}
		roll_one[roll_one_count].p_f = 0;																																								//确保一开始滚动的图片从0开始

		res = Get_D8_info1(rxBuf,&oper,&mode,&t,&p_c,&x,&y);																																	//获取要滚动图片的相关信息存放在结构体roll_one中
		if(res!=OK)	return res;

		for(i = 0 ; i < roll_one_count ; i++)
		{
			if(roll_one[i].operation == oper)
			{
				return OK;
			}
			if((x == roll_one[i].x)&&(y == roll_one[i].y))
			{
				roll_one_count--;
				break;
			}
		}
		roll_one[i].operation = oper;
		roll_one[roll_one_count].x = x;
		roll_one[roll_one_count].y = y;
		roll_one[roll_one_count].mode = mode;
		roll_one[roll_one_count].t = t;
		roll_one[roll_one_count].p_c = p_c;
		roll_one[roll_one_count].start_end = 0;

		gOpenD8 = 1;
		roll_one_count++;
		if(d8_sum != ROLL_ONE_SIZE)       d8_sum = roll_one_count;
		return OK;
	 }
	else
	return CMD_OPER_ERROR;
}

void TurnRoll_One(void)
{
	UINT8 i;
	rool_one_flag = 0;
	for( i = 0;i < d8_sum;i++)
		roll_one[i].t_c++;
	for(i = 0;i < d8_sum;i++)
	{
		if(roll_one[i].t_c >= roll_one[i].t && roll_one[i].start_end == 0)
		{

			Get_D8_info2(&(roll_one[i].p_c));															//当某张图片滚动定时时间到时，获取图片信息

			roll_one[i].w= gPictureInfo.w;
			roll_one[i].h = gPictureInfo.h;
			roll_one[i].addr = gPictureInfo.addr;

			Roll_one(i);																				//图片切换函数
			roll_one[i].t_c = 0;
		}
	}

}

void Roll_one (UINT8 d8_count)
{

	switch(roll_one[d8_count].mode)
	{
		case 0 : 																																	//向上

			LT268_TFT_D8_Up(roll_one[d8_count].x, roll_one[d8_count].y, roll_one[d8_count].w, roll_one[d8_count].h, roll_one[d8_count].p_f, roll_one[d8_count].addr);

							roll_one[d8_count].p_f+=4;																											//移动四个像素点
							if(roll_one[d8_count].p_f > roll_one[d8_count].h && (roll_one[d8_count].p_f - 4) < roll_one[d8_count].h)
							{
								roll_one[d8_count].p_f = roll_one[d8_count].h;																		//最后一次移动的位置
							}
							if(roll_one[d8_count].p_f > roll_one[d8_count].h)
							{
								roll_one[d8_count].p_f = 0;
								roll_one[d8_count].start_end = 1;																					//图片滚动结束标志
							}
						  break;
		case 1 :																																	//向下

			LT268_TFT_D8_Down(roll_one[d8_count].x, roll_one[d8_count].y, roll_one[d8_count].w, roll_one[d8_count].h, roll_one[d8_count].p_f, roll_one[d8_count].addr);

							roll_one[d8_count].p_f+=4;
							if(roll_one[d8_count].p_f > roll_one[d8_count].h && (roll_one[d8_count].p_f - 4) < roll_one[d8_count].h)
							{
								roll_one[d8_count].p_f = roll_one[d8_count].h;
							}
							if(roll_one[d8_count].p_f > roll_one[d8_count].h)
							{
								roll_one[d8_count].p_f = 0;
								roll_one[d8_count].start_end = 1;
							}
						  break;
		case 2 :																																		//向左

			LT268_TFT_D8_Left(roll_one[d8_count].x, roll_one[d8_count].y, roll_one[d8_count].w, roll_one[d8_count].h, roll_one[d8_count].p_f, roll_one[d8_count].addr);

							roll_one[d8_count].p_f+=4;
							if(roll_one[d8_count].p_f > roll_one[d8_count].h && (roll_one[d8_count].p_f - 4) < roll_one[d8_count].h)
							{
								roll_one[d8_count].p_f = roll_one[d8_count].h;
							}
							if(roll_one[d8_count].p_f > roll_one[d8_count].w)
							{
								roll_one[d8_count].p_f = 0;
								roll_one[d8_count].start_end = 1;
							}
						  break;
		case 3 : 																																		//向右

			LT268_TFT_D8_Right(roll_one[d8_count].x, roll_one[d8_count].y, roll_one[d8_count].w, roll_one[d8_count].h, roll_one[d8_count].p_f, roll_one[d8_count].addr);

							roll_one[d8_count].p_f+=4;
							if(roll_one[d8_count].p_f > roll_one[d8_count].h && (roll_one[d8_count].p_f - 4) < roll_one[d8_count].h)
							{
								roll_one[d8_count].p_f = roll_one[d8_count].h;
							}
							if(roll_one[d8_count].p_f > roll_one[d8_count].w)
							{
								roll_one[d8_count].p_f = 0;
								roll_one[d8_count].start_end = 1;
							}
							break;
		default : break;
	}

}
#endif
//------------------------------------------------------0xd9---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_d9
* 功能  ：多张图片滚动
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_D9
UINT8 LT_ManageCmd_D9(UINT8 *rxBuf)
{
	UINT8 i = 0,j;
	UINT8 res = 0;
	UINT8 oper = 0;
	UINT8 mode,t,sum;
	UINT16 pic[50] = {0};
	UINT16 x = 0, y = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		if(rxBuf[1] & 0x80)
		{
			gOpenD9 = 0;
			RollFlag = 0;
			return OK;
		}
		if(gOpenD9 == 0)
		{
			Rollcount = 0;
		}
		res = Get_D9_info1(rxBuf,&oper,&mode,&t,&sum,pic,&x,&y);
		if(res!=OK)	return res;

		for(i = 0 ; i < Rollcount ; i++)
		{
			if(RollInfo[i].operation == oper)
			{
				return OK;
			}
			if((x == RollInfo[i].x)&&(y == RollInfo[i].y))
			{
				Rollcount--;
				break;
			}
		}

		RollInfo[i].operation = oper;
		RollInfo[i].mode = mode;
		RollInfo[i].t = t;
		RollInfo[i].sum = sum;
		RollInfo[i].x = x;
		RollInfo[i].y = y;
		RollInfo[i].p_f =0;
		RollInfo[i].p_c =0;										//确保一进来图片显示的是第一张图片，将不同的窗口数据存放在不同的结构体数组元素中
		RollInfo[i].w = gPictureInfo.w;
		RollInfo[i].h = gPictureInfo.h;
		for(j = 0;j < RollInfo[i].sum;j++)
		{
			RollInfo[i].p[j] = pic[j];
		}

		gOpenD9 = 1;
		Rollcount++;												//开启的窗口数要<=ROLL_MORE_SIZE,否则会出错
		return OK;
	}
	else
		return CMD_OPER_ERROR;
}

void TurnPicture(void)
{
	UINT8 i = 0;
	UINT16 addr = 0;
	RollFlag = 0;

	for(i = 0 ; i < Rollcount; i++)	RollInfo[i].t_c++;
	for(i = 0 ; i < Rollcount; i++)
	{
		if(RollInfo[i].p_f == 0)
		{
			addr = Get_D9_info2(&(RollInfo[i].p[RollInfo[i].p_c]));
			LT_CompoundPicInfo(addr);
			RollInfo[i].w = gPictureInfo.w;
			RollInfo[i].h = gPictureInfo.h;
			RollInfo[i].addr = gPictureInfo.addr;

			if(RollInfo[i].p_c + 1 >= RollInfo[i].sum)
			{
				addr = Get_D9_info2(&(RollInfo[i].p[0]));
				LT_CompoundPicInfo(addr);
				RollInfo[i].w = gPictureInfo.w;
				RollInfo[i].h = gPictureInfo.h;
				RollInfo[i].addr_next = gPictureInfo.addr;
			}
			else
			{
				addr = Get_D9_info2(&(RollInfo[i].p[RollInfo[i].p_c+1]));
				LT_CompoundPicInfo(addr);
				RollInfo[i].w = gPictureInfo.w;
				RollInfo[i].h = gPictureInfo.h;
				RollInfo[i].addr_next = gPictureInfo.addr;

			}
		}
		if(RollInfo[i].t_c >= RollInfo[i].t )
		{
			Roll(i);								//定时时间到之后，进入图片切换函数
			RollInfo[i].t_c = 0;
		}
	}
}


void Roll (UINT8 Rollcount)
{
	switch(RollInfo[Rollcount].mode)
	{
		case 0 :

			LT268_TFT_D9_Up(RollInfo[Rollcount].x, RollInfo[Rollcount].y, RollInfo[Rollcount].w, RollInfo[Rollcount].h, RollInfo[Rollcount].p_f, RollInfo[Rollcount].addr,RollInfo[Rollcount].addr_next);

							RollInfo[Rollcount].p_f++;																																		//图片移动1个像素点
							if(RollInfo[Rollcount].p_f >= RollInfo[Rollcount].h)
							{
								RollInfo[Rollcount].p_f = 0;																																//滚动完一张，另一张从0开始滚动
								RollInfo[Rollcount].p_c++;																																	//要滚动的图片编号
								if(RollInfo[Rollcount].p_c >= RollInfo[Rollcount].sum)
									RollInfo[Rollcount].p_c = 0;
							}
						  break;																																												//向上
		case 1 :

			LT268_TFT_D9_Down(RollInfo[Rollcount].x, RollInfo[Rollcount].y, RollInfo[Rollcount].w, RollInfo[Rollcount].h, RollInfo[Rollcount].p_f, RollInfo[Rollcount].addr,RollInfo[Rollcount].addr_next);

							RollInfo[Rollcount].p_f++;
							if(RollInfo[Rollcount].p_f >= RollInfo[Rollcount].h)
							{
								RollInfo[Rollcount].p_f = 0;
								RollInfo[Rollcount].p_c++;																																	//要滚动的图片编号
								if(RollInfo[Rollcount].p_c >= RollInfo[Rollcount].sum)
									RollInfo[Rollcount].p_c = 0;
							}
						  break;																																												//向下
		case 2 :

			LT268_TFT_D9_Left(RollInfo[Rollcount].x, RollInfo[Rollcount].y, RollInfo[Rollcount].w, RollInfo[Rollcount].h, RollInfo[Rollcount].p_f, RollInfo[Rollcount].addr,RollInfo[Rollcount].addr_next);

							RollInfo[Rollcount].p_f++;
							if(RollInfo[Rollcount].p_f >= RollInfo[Rollcount].w)
							{
								RollInfo[Rollcount].p_f = 0;
								RollInfo[Rollcount].p_c++;
								if(RollInfo[Rollcount].p_c >= RollInfo[Rollcount].sum)
									RollInfo[Rollcount].p_c = 0;
							}
						  break;																																												//向左
		case 3 :

			LT268_TFT_D9_Right(RollInfo[Rollcount].x, RollInfo[Rollcount].y, RollInfo[Rollcount].w, RollInfo[Rollcount].h, RollInfo[Rollcount].p_f, RollInfo[Rollcount].addr,RollInfo[Rollcount].addr_next);

							RollInfo[Rollcount].p_f++;
							if(RollInfo[Rollcount].p_f >= RollInfo[Rollcount].w )
							{
								RollInfo[Rollcount].p_f = 0;
								RollInfo[Rollcount].p_c++;
								if(RollInfo[Rollcount].p_c >= RollInfo[Rollcount].sum)
									RollInfo[Rollcount].p_c = 0;
							}
							break;																																												//向右
		default : break;
	}

}

#endif

//------------------------------------------------------0xDB------------------------------------------------------//
#if   MODULE_DB
UINT8 LT_ManageCmd_DB(UINT8 *rxBuf)
{

	UINT8 i ,j;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		for(i = 0 ; i < Rollcount ; i++)
		{
			if(RollInfo[i].operation == rxBuf[1])
			{
				break;
			}
		}
		if(i == Rollcount)
			return OK;

	//	LT768_BTE_Memory_Copy(MAIN_BUFF,LCD_XSIZE_TFT,RollInfo[i].x,RollInfo[i].y,
	//											MAIN_BUFF,LCD_XSIZE_TFT,RollInfo[i].x,RollInfo[i].y,
	//											Display_Layer,LCD_XSIZE_TFT,RollInfo[i].x,RollInfo[i].y,
	//											0x0c,RollInfo[i].w,RollInfo[i].h
	//										 );
		LT268_TFT_FullScreen_Cut(RollInfo[i].x,RollInfo[i].y,RollInfo[i].w,RollInfo[i].h,FullScreen_Pic_Addr,FullScreen_Square_Color);
		RollInfo[i].addr = RollInfo[Rollcount - 1].addr;
		RollInfo[i].x = RollInfo[Rollcount - 1].x;
		RollInfo[i].y = RollInfo[Rollcount - 1].y;
		RollInfo[i].w = RollInfo[Rollcount - 1].w;
		RollInfo[i].h = RollInfo[Rollcount - 1].h;
		RollInfo[i].sum = RollInfo[Rollcount - 1].sum;
		RollInfo[i].mode = RollInfo[Rollcount - 1].mode;
		RollInfo[i].operation = RollInfo[Rollcount - 1].operation;
		RollInfo[i].p_c = RollInfo[Rollcount - 1].p_c;
		RollInfo[i].p_f = RollInfo[Rollcount - 1].p_f;
		RollInfo[i].t = RollInfo[Rollcount - 1].t;
		RollInfo[i].t_c = RollInfo[Rollcount - 1].t_c;
		RollInfo[i].pos = RollInfo[Rollcount - 1].pos;
		RollInfo[i].addr_next = RollInfo[Rollcount - 1].addr_next;


		for(j = 0;j < RollInfo[i].sum;j++)
		{
			RollInfo[i].p[j] = RollInfo[Rollcount - 1].p[j];
		}

		RollInfo[Rollcount - 1].x = 0;
		RollInfo[Rollcount - 1].y = 0;
		RollInfo[Rollcount - 1].w = 0;
		RollInfo[Rollcount - 1].h = 0;
		Rollcount--;
		if(Rollcount==0)
		{
			gOpenD9=0;
			RollFlag=0;
		}
		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xDC------------------------------------------------------//
#if   MODULE_DC
UINT8 LT_ManageCmd_DC(UINT8 *rxBuf)
{
	UINT16 x,y,w,r;
	UINT32 color = 0;
	UINT8 t;
	UINT16 X, Y;
	UINT16 angle,start_angle;
	float x0 ,y0 ;
	float x1,y1;
	float i;
	UINT8 res = 0;

	if((gUsartRx.Count==13)||(cmd_flag== 1))
	{
		res = Get_DC_info(rxBuf,&x,&y,&w,&r,&color,&t);
		if(res!=OK)	return res;

		angle = rxBuf[4];
		angle = (angle << 8) + rxBuf[5];															//要画的圆环的角度

		start_angle = rxBuf[2];
		start_angle = (start_angle << 8) + rxBuf[3];												//要画的圆环的起始角度

		for(i = start_angle ;i <= start_angle + angle;i++)
		{
			x0 = x + r * fast_sin(i);
			y0 = y - r * fast_cos(i);																//得到圆环内x、y坐标
			x1 = x + (r + w) * fast_sin(i);
			y1 = y - (r + w) * fast_cos(i);															//得到圆环外x、y坐标
			X = (x0 + x1) / 2 + 0.5f;
			Y = (y0 + y1) / 2 + 0.5f;																//得到圆环中心点

			LT268_TFT_DrawCircle_Fill(X,Y,w / 2,LT_Color24_To_16(color));							//画圆环
			Delay_us(t);
		}

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//--------------------------------------------------0xDF指令---------------------------------------------------------
#if   MODULE_DF
UINT8 LT_ManageCmd_DF(UINT8 *rxBuf)
{
	UINT8 res = 0;
	UINT8 flag = 0,r = 0;
	UINT16 x = 0,y = 0;
	UINT32 color = 0;

	if((gUsartRx.Count==13)||(cmd_flag== 1))
	{
		x = rxBuf[2];
		x = (x<<8)+rxBuf[3];
		y = rxBuf[4];
		y = (y<<8)+rxBuf[5];

		res = Get_DF_info(rxBuf,&flag,&r,&color);
		if(res!=OK)	return res;

		if(flag)	LT268_TFT_DrawSquare_Fill(x,y,x + r,y + r,LT_Color24_To_16(color));
		else		LT268_TFT_DrawCircle_Fill(x,y,r,LT_Color24_To_16(color));

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xE0指令---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_E0
* 功能  ：处理画线指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_E0
UINT8 LT_ManageCmd_E0(UINT8 *rxBuf)
{
	UINT16 x1,x2,y1,y2;
	UINT32 color;
	UINT8 res = 0;
	UINT8 width = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_E0_info(rxBuf,&x1,&y1,&x2,&y2,&color,&width);															//获取命令信息
		if(res!=OK)	return res;

		LT268_TFT_DrawLine_Width(x1,y1,x2,y2,LT_Color24_To_16(color),width);										//画带宽线

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//--------------------------------------------------0xE1~0xE3---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_E1_E3
* 功能  ：处理圆指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_E1_E3
UINT8 LT_ManageCmd_E1_E3(UINT8 *rxBuf)
{
	UINT8 width = 0;
	UINT16 x,y,r;
	UINT32 color,color1;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_E1_E3_info(rxBuf,&x,&y,&r,&color,&color1,&width);																//获取命令信息
		if(res!=OK)	return res;

		if(rxBuf[0] == 0xE1)			LT268_TFT_DrawCircle(x,y,r,LT_Color24_To_16(color));							//空心圆
		else if(rxBuf[0] == 0xE2)		LT268_TFT_DrawCircle_Fill(x,y,r,LT_Color24_To_16(color));					//实心圆
		else if(rxBuf[0] == 0xE3)		LT268_TFT_DrawCircle_Width(x,y,r,LT_Color24_To_16(color),LT_Color24_To_16(color1),width);		//带宽圆

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif
//--------------------------------------------------0xE4~0xE6---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_E4_E6
* 功能  ：处理画椭圆指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_E4_E6
UINT8 LT_ManageCmd_E4_E6(UINT8 *rxBuf)
{
	UINT8 width;
	UINT16 x,y,x_r,y_r;
	UINT32 color,color1;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_E4_E6_info(rxBuf,&x,&y,&x_r,&y_r,&color,&color1,&width);															//获取命令信息
		if(res!=OK)	return res;

		if(rxBuf[0] == 0xE4)		LT268_TFT_DrawEllipse(x,y,x_r,y_r,LT_Color24_To_16(color));							//空心椭圆
		else if(rxBuf[0] == 0xE5)	LT268_TFT_DrawEllipse_Fill(x,y,x_r,y_r,LT_Color24_To_16(color));					//实心椭圆
		else if(rxBuf[0] == 0xE6)	LT268_TFT_DrawEllipse_Width(x,y,x_r,y_r,LT_Color24_To_16(color),LT_Color24_To_16(color1),width);	//带宽椭圆

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif
//--------------------------------------------------0xE7~0xE9---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_E7_E9
* 功能  ：处理画矩形指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if  MODULE_E7_E9
UINT8 LT_ManageCmd_E7_E9(UINT8 *rxBuf)
{
	UINT8 width;
	UINT16 x1,y1,x2,y2;
	UINT32 color,color1;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_E7_E9_info(rxBuf,&x1,&y1,&x2,&y2,&color,&color1,&width);																				//获取命令信息
		if(res!=OK)	return res;

		if(x1 == 0 && y1 == 0 && x2 >= (LCD_XSIZE_TFT - 1) && y2 >= (LCD_YSIZE_TFT - 1) && rxBuf[0] == 0xE8)			//画矩形接近全屏或者全屏时关闭动作画面
		{
			#if  MODULE_81
					gOpen81 = 0;
					gTurnFlag = 0;
			#endif

			#if  MODULE_88
					gOpen88 = 0;
					gGifFlag = 0;
			#endif

			#if  MODULE_A0_A1
					ControlFlag = 0;
					ControlCount = 0;
			#endif

			#if  MODULE_A2_A3
					ControlFlag2 = 0;
					ControlCount2 = 0;
			#endif

			#if   MODULE_C9
					Slide_Flag=0;
			#endif

			#if  MODULE_D8
					gOpenD8 = 0;
					rool_one_flag = 0;
			#endif

			#if  MODULE_D9
					gOpenD9 = 0;
					RollFlag = 0;
			#endif

			LT268_TFT_DrawSquare_Fill(x1,y1,x2,y2,LT_Color24_To_16(color));
			FullScreen_Pic_Addr=0;
			FullScreen_Square_Color=LT_Color24_To_16(color);
			}

			if(rxBuf[0] == 0xE7)		LT268_TFT_DrawSquare(x1,y1,x2,y2,LT_Color24_To_16(color));							//画空心矩形
			else if(rxBuf[0] == 0xE8)	LT268_TFT_DrawSquare_Fill(x1,y1,x2,y2,LT_Color24_To_16(color));					//画实心矩形
			else if(rxBuf[0] == 0xE9)	LT268_TFT_DrawSquare_Width(x1,y1,x2,y2,LT_Color24_To_16(color),LT_Color24_To_16(color1),width);		//画带线框矩形

			return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif
//------------------------------------------------------0xEA~0xEC---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_EA_EC
* 功能  ：处理画圆角矩形指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_EA_EC
UINT8 LT_ManageCmd_EA_EC(UINT8 *rxBuf)
{
	UINT8 width;
	UINT16 x1,y1,x2,y2,x_r,y_r;
	UINT32 color,color1;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_EA_EC_info(rxBuf,&x1,&y1,&x2,&y2,&x_r,&y_r,&color,&color1,&width);																//获取命令信息
		if(res!=OK)	return res;

		if(rxBuf[0] == 0xEA)		LT268_TFT_DrawCircleSquare(x1,y1,x2,y2,x_r,LT_Color24_To_16(color));					//画空心圆角矩形
		else if(rxBuf[0] == 0xEB)	LT268_TFT_DrawCircleSquare_Fill(x1,y1,x2,y2,x_r,LT_Color24_To_16(color));				//画实心圆角矩形
		else if(rxBuf[0] == 0xEC)	LT268_TFT_DrawCircleSquare_Width(x1,y1,x2,y2,x_r,LT_Color24_To_16(color),LT_Color24_To_16(color1),width);	//画带线框圆角矩形

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif
//----------------------------------------------------0xED~0xEF------------------------------------------------------
/*
* 函数名：LT_ManageCmd_ED_EF
* 功能  ：处理三角形指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_ED_EF
UINT8 LT_ManageCmd_ED_EF(UINT8 *rxBuf)
{
	UINT16 x1,y1,x2,y2,x3,y3;
	UINT32 color,color1;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_ED_EF_info(rxBuf,&x1,&y1,&x2,&y2,&x3,&y3,&color,&color1);											//获取命令信息
		if(res!=OK)	return res;

		if(rxBuf[0] == 0xED)		LT268_TFT_DrawTriangle(x1,y1,x2,y2,x3,y3,LT_Color24_To_16(color));
		else if(rxBuf[0] == 0xEE)	LT268_TFT_DrawTriangle_Fill(x1,y1,x2,y2,x3,y3,LT_Color24_To_16(color));
		else if(rxBuf[0] == 0xEF)	LT268_TFT_DrawTriangle_Frame(x1,y1,x2,y2,x3,y3,LT_Color24_To_16(color),LT_Color24_To_16(color1));

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xF4---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_F4
* 功能  ：处理圆柱指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_F4
UINT8 LT_ManageCmd_F4(UINT8 *rxBuf)
{
	UINT8 width;
	UINT16 x,y,x_r,y_r,h;
	UINT32 color,color1;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_F4_info(rxBuf,&x,&y,&x_r,&y_r,&h,&color,&color1,&width);																					//获取命令信息
		if(res!=OK)	return res;

		LT268_TFT_DrawCylinder(x,y,x_r,y_r,h,LT_Color24_To_16(color),LT_Color24_To_16(color1),width);

		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//------------------------------------------------------0xF6---------------------------------------------------------
/*
* 函数名：LT_ManageCmd_F6
* 功能  ：处理表格指令
* 输入  ：无
* 输出  ：0：成功   其他：失败
* 作者  ：LEVETOP
*/
#if   MODULE_F6
UINT8 LT_ManageCmd_F6(UINT8 *rxBuf)
{
	UINT16 x1,y1,w,h,cn,rn,w_1,w_2;
	UINT32 c1,c2,c3;
	UINT8 mode;
	UINT8 res = 0;

	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		res = Get_F6_info(rxBuf,&x1,&y1,&w,&h,&cn,&rn,&w_1,&w_2,&c1,&c2,&c3,&mode);																	//获取命令信息
		if(res!=OK)	return res;

		LT268_TFT_MakeTable(x1,y1,w,h,cn,rn,LT_Color24_To_16(c1),LT_Color24_To_16(c2),LT_Color24_To_16(c3),w_1,w_2,mode);
		return OK;
	 }
	else
		return CMD_OPER_ERROR;
}
#endif

//-------------------------------------------------------0xff-------------------------------------------------------
#if   MODULE_FF
void LT_CmdUpdata(void)
{
	UINT8 flag = 0;
	UINT8 count = 0;
	UINT8 temp[6] = {0};
	UINT8 state = 0;
	UINT16 outTime = 0;
	UINT16 rxCrc = 0;
	UINT16 mcuCrc = 0;
	UINT16 size = 0;
	UINT16 rx_size = 0;

	#if	  W25Q128																	//2019
		UINT16 addr = 0;
	#endif

	rx_size = 1024+2;
	size = rx_size - 2;

	#if   MODULE_81
		gOpen81 = 0;
		gTurnFlag = 0;
	#endif

	#if   MODULE_88
		gOpen88 = 0;
		gGifFlag = 0;
	#endif

	#if   MODULE_A0_A1
		ControlFlag = 0;
		ControlCount = 0;
	#endif

	#if   MODULE_A2_A3
		ControlFlag2 = 0;
		ControlCount2 = 0;
	#endif

	#if   MODULE_C9
			Slide_Flag=0;
	#endif

	#if   MODULE_D8
		gOpenD8 = 0;
		rool_one_flag = 0;
	#endif

	#if   MODULE_D9
		gOpenD9 = 0;
		RollFlag = 0;
	#endif

	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
	LT268_TFT_ShowAscll(10,140,24,1,Red,Red,(UINT8 *)"Userinfo.ini Update, Please Wait .....");
	//擦除FLASH里的前12K数据
	#if			W25Q128																	//2019
	//擦除FLASH里的前12K数据
	//	LT268_W25QXX_SectorErase4KB(0);
	//	LT268_W25QXX_SectorErase4KB(1);
	//	LT268_W25QXX_SectorErase4KB(2);
		LT268_W25QXX_BlockErase64KB(0);
		LT268_W25QXX_BlockErase64KB(1);
	#endif

	FF_Update_Flag=1;
	PIT1_Init();

	temp[0] = 'O';
	temp[1] = 'K';
	temp[2] = size>>8;
	temp[3] = size&0xff;
	mcuCrc = Rx_CRC_CCITT(temp,4);
	temp[4] = mcuCrc>>8;
	temp[5] = mcuCrc&0xff;

	LT_DataToPc_NoFrame(temp,6);

	gUsartRx.Flag = 0;
	gUsartRx.Count = 0;
	busyflag = 0;

	while(1)
	{
		if(gUsartRx.Flag)
		{
			if(gUsartRx.Count!=rx_size)
			{
				LT_DataToPc_NoFrame((UINT8*)"NG",2);
				flag = 0;
				break;
			}
			rxCrc = gUsartRx.Buf[rx_size-2];
			rxCrc = (rxCrc<<8)+gUsartRx.Buf[rx_size-1];
			mcuCrc = Rx_CRC_CCITT(gUsartRx.Buf,rx_size-2);
			if(rxCrc==mcuCrc)
			{
				#if	  W25Q128
					LT268_W25QXX_Write_NoCheck(gUsartRx.Buf,addr,rx_size-2);
					addr += (rx_size-2);
				#endif

				LT_DataToPc_NoFrame((UINT8*)"OK",2);
			}
			else
			{
				LT_DataToPc_NoFrame((UINT8*)"NG",2);
				flag = 0;
				break;
			}
			count++;
			outTime = 0;
			state = 1;
			flag = 1;
			gUsartRx.Flag = 0;
			gUsartRx.Count = 0;
			busyflag = 0;
		}

		outTime++;
		if(state)
		{
			Delay_us(100);
			if(outTime>=10000)	//给两包数据留一定的时间间隔
			{
				flag = 1;
				break;
			}
		}
		else
		{
			Delay_us(100);
			if(outTime>=10000)
			{
				outTime = 0;
				break;
			}
		}
	}
	FF_Update_Flag=0;
	LT_UsartTimeDisable();

	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);

	if(flag && (count == 12 || count == 128))
	{
		LT268_TFT_ShowAscll(10,140,24,1,Red,Red,(UINT8 *)"Userinfo.ini Update Complete! ");
		init_ok_flag = 0;
	}
	else
	{
		LT268_TFT_ShowAscll(10,140,24,1,Red,Red,(UINT8 *)"Userinfo.ini Updata Failure");
		init_ok_flag = 1;
	}
	gUsartRx.Flag = 0;
}
//串口更新前12K数据命令
//PC--->MCU：0xff+"LEVETOP"+CRC
//MCU--->PC："OK"+SIZE(2byte、高字节在前)+CRC
UINT8 LT_ManageCmd_FF(UINT8 *rxBuf)
{
	UINT16 crc = 0;
	crc = rxBuf[gUsartRx.Count - 7];
	crc = (crc << 8) + rxBuf[gUsartRx.Count - 6];
	if(Rx_CRC_CCITT(rxBuf,gUsartRx.Count - 7)!=crc)	return CRC_ERROR;
	if((rxBuf[1]=='L')&&(rxBuf[2]=='E')&&(rxBuf[3]=='V')&&(rxBuf[4]=='E')&&(rxBuf[5]=='T')&&(rxBuf[6]=='O')&&(rxBuf[7]=='P'))	//接收到这些数据，即进入更新函数
	{
		LT_CmdUpdata();
		return OK;
	}

	return CMD_ERROR;
}
#endif
//----------------------------------------------------无此功能函数---------------------------------------------------
UINT8 LT_Idle(UINT8 *rxBuf)
{
	UINT8 buff[3];
	buff[0] = rxBuf[0];
	buff[1] = rxBuf[1];
	buff[2] = CMD_INFO_ERROR;	                                // 不存在该指令
	LT_DataToPc(buff,3);
	return CMD_RETURN_NULL;
}

void Main_From_UartRxBuff(void)
{
	UINT16 i=0;
	if(Respond_Num < Rx_Num)
	{
		for(i = 0;i < (Rx_Num - Respond_Num);i++)
		{
			if(!Respond_AA_OK && Rx_Buffer_long[(i + Respond_Count) % RX_SIZE] == 0x90)
			{
				Respond_AA_OK = 1;
				gUsartRx.Count = 0;
				RS485_Handle.cmdFlatN=1;
			}
			if(Respond_AA_OK)
			{
				gUsartRx.Buf[gUsartRx.Count++] = Rx_Buffer_long[(i + Respond_Count) % RX_SIZE];
				RS485_Handle.ucCmdDataN[gUsartRx.Count-1]=gUsartRx.Buf[gUsartRx.Count-1];
				if(gUsartRx.Count > 25 && gUsartRx.Buf[gUsartRx.Count-1]!=0 && gUsartRx.Buf[gUsartRx.Count-2]!=0)
				{
					gUsartRx.Flag = 1;
					Respond_AA_OK = 0;
					break;
				}
			}
			if(Respond_AA_OK && gUsartRx.Count >= 255)
			{
				Respond_AA_OK = 0;
				break;
			}
		}
		Respond_Count = (i + Respond_Count) % RX_SIZE;
		Respond_Num += i;
	}
	else if((Respond_Num >= Rx_Num) && Rx_Num != 0)
	{
		Respond_Num = 0;
		Rx_Num = 0;
		Respond_Count = 0;
		Rx_Count_long = 0;
	}
}
