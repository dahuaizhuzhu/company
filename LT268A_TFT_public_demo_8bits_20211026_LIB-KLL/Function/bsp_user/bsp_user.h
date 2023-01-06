/*
 * bsp_user.h
 *
 *  Created on: 2020年3月30日
 *      Author: cjc59
 */

#ifndef BSP_USER_H_
#define BSP_USER_H_

#include "type.h"
#include "bsp.h"

#define USER_DEFINE_COMAND 1

#define		MODULE_60				1					//1选择60指令，0不选60指令
#define		MODULE_61				1				  	//1选择61指令，0不选61指令
#define		MODULE_62				0					//1选择62指令，0不选62指令
#define		MODULE_63				0					//1选择63指令，0不选63指令
#define		MODULE_64				0					//1选择64指令，0不选64指令
#define		MODULE_65				0					//1选择65指令，0不选65指令
#define		MODULE_66				0					//1选择66指令，0不选66指令
#define 	MODULE_67				0					//1选择67指令，0不选67指令
#define 	MODULE_68				0					//1选择68指令，0不选68指令
#define		MODULE_69				0					//1选择69指令，0不选69指令
#define		MODULE_6A				0					//1选择6A指令，0不选6A指令
#define		MODULE_6B				0					//1选择6B指令，0不选6B指令
#define		MODULE_6C				0                   //1选择6C指令，0不选6C指令
#define		MODULE_6D				0					//1选择6D指令，0不选6D指令
#define		MODULE_6E				0					//1选择6E指令，0不选6E指令
#define		MODULE_6F		    	0					//1选择6F指令，0不选6F指令
#define		MODULE_70				0					//1选择70指令，0不选70指令
#define		MODULE_71				0					//1选择71指令，0不选71指令
#define		MODULE_72		    	0					//1选择72指令，0不选72指令
#define		MODULE_73				0					//1选择73指令，0不选73指令
#define		MODULE_74				0					//1选择74指令，0不选74指令
#define		MODULE_75				0					//1选择75指令，0不选75指令
#define		MODULE_76				0					//1选择76指令，0不选76指令
#define 	MODULE_77				0					//1选择77指令，0不选77指令
#define 	MODULE_78				0					//1选择78指令，0不选78指令
#define		MODULE_79				0					//1选择79指令，0不选79指令
#define		MODULE_7A				0					//1选择7A指令，0不选7A指令
#define		MODULE_7B				0					//1选择7B指令，0不选7B指令
#define		MODULE_7C				0                   //1选择7C指令，0不选7C指令
#define		MODULE_7D				0					//1选择7D指令，0不选7D指令
#define		MODULE_7E				0					//1选择7E指令，0不选7E指令
#define		MODULE_7F		    	0					//1选择7F指令，0不选7F指令

#define LAY_MyBUFF0 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*5
#define LAY_MyBUFF1 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*6
#define LAY_MyBUFF2 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*7

UINT8 User_Function(UINT8 cmd,UINT8 *RxBuf);

#if   MODULE_60
UINT8 LT_ManageCmd_60(UINT8 *rxBuf);
#endif

#if   MODULE_61
UINT8 LT_ManageCmd_61(UINT8 *rxBuf);
#endif

#if   MODULE_62
UINT8 LT_ManageCmd_62(UINT8 *rxBuf);
#endif

#if   MODULE_63
UINT8 LT_ManageCmd_63(UINT8 *rxBuf);
#endif

#if   MODULE_64
UINT8 LT_ManageCmd_64(UINT8 *rxBuf);
#endif

#if   MODULE_65
UINT8 LT_ManageCmd_65(UINT8 *rxBuf);
#endif

#if   MODULE_66
UINT8 LT_ManageCmd_66(UINT8 *rxBuf);
#endif

#if   MODULE_67
UINT8 LT_ManageCmd_67(UINT8 *rxBuf);
#endif

#if   MODULE_68
UINT8 LT_ManageCmd_68(UINT8 *rxBuf);
#endif

#if   MODULE_69
UINT8 LT_ManageCmd_69(UINT8 *rxBuf);
#endif

#if   MODULE_6A
UINT8 LT_ManageCmd_6A(UINT8 *rxBuf);
#endif

#if   MODULE_6B
UINT8 LT_ManageCmd_6B(UINT8 *rxBuf);
#endif

#if   MODULE_6C
UINT8 LT_ManageCmd_6C(UINT8 *rxBuf);
#endif

#if   MODULE_6D
UINT8 LT_ManageCmd_6D(UINT8 *rxBuf);
#endif

#if   MODULE_6E
UINT8 LT_ManageCmd_6E(UINT8 *rxBuf);
#endif

#if   MODULE_6F
UINT8 LT_ManageCmd_6F(UINT8 *rxBuf);
#endif

#if   MODULE_70
UINT8 LT_ManageCmd_70(UINT8 *rxBuf);
#endif

#if   MODULE_71
UINT8 LT_ManageCmd_71(UINT8 *rxBuf);
#endif

#if   MODULE_72
UINT8 LT_ManageCmd_72(UINT8 *rxBuf);
#endif

#if   MODULE_73
UINT8 LT_ManageCmd_73(UINT8 *rxBuf);
#endif

#if   MODULE_74
UINT8 LT_ManageCmd_74(UINT8 *rxBuf);
#endif

#if   MODULE_75
UINT8 LT_ManageCmd_75(UINT8 *rxBuf);
#endif

#if   MODULE_76
UINT8 LT_ManageCmd_76(UINT8 *rxBuf);
#endif

#if   MODULE_77
UINT8 LT_ManageCmd_77(UINT8 *rxBuf);
#endif

#if   MODULE_78
UINT8 LT_ManageCmd_78(UINT8 *rxBuf);
#endif

#if   MODULE_79
UINT8 LT_ManageCmd_79(UINT8 *rxBuf);
#endif

#if   MODULE_7A
UINT8 LT_ManageCmd_7A(UINT8 *rxBuf);
#endif

#if   MODULE_7B
UINT8 LT_ManageCmd_7B(UINT8 *rxBuf);
#endif

#if   MODULE_7C
UINT8 LT_ManageCmd_7C(UINT8 *rxBuf);
#endif

#if   MODULE_7D
UINT8 LT_ManageCmd_7D(UINT8 *rxBuf);
#endif

#if   MODULE_7E
UINT8 LT_ManageCmd_7E(UINT8 *rxBuf);
#endif

#if   MODULE_7F
UINT8 LT_ManageCmd_7F(UINT8 *rxBuf);
#endif

#endif
/* BSP_USER_H_ */
