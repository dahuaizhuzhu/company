/*
 * bsp_user.h
 *
 *  Created on: 2020��3��30��
 *      Author: cjc59
 */

#ifndef BSP_USER_H_
#define BSP_USER_H_

#include "type.h"
#include "bsp.h"

#define USER_DEFINE_COMAND 1

#define		MODULE_60				1					//1ѡ��60ָ�0��ѡ60ָ��
#define		MODULE_61				1				  	//1ѡ��61ָ�0��ѡ61ָ��
#define		MODULE_62				0					//1ѡ��62ָ�0��ѡ62ָ��
#define		MODULE_63				0					//1ѡ��63ָ�0��ѡ63ָ��
#define		MODULE_64				0					//1ѡ��64ָ�0��ѡ64ָ��
#define		MODULE_65				0					//1ѡ��65ָ�0��ѡ65ָ��
#define		MODULE_66				0					//1ѡ��66ָ�0��ѡ66ָ��
#define 	MODULE_67				0					//1ѡ��67ָ�0��ѡ67ָ��
#define 	MODULE_68				0					//1ѡ��68ָ�0��ѡ68ָ��
#define		MODULE_69				0					//1ѡ��69ָ�0��ѡ69ָ��
#define		MODULE_6A				0					//1ѡ��6Aָ�0��ѡ6Aָ��
#define		MODULE_6B				0					//1ѡ��6Bָ�0��ѡ6Bָ��
#define		MODULE_6C				0                   //1ѡ��6Cָ�0��ѡ6Cָ��
#define		MODULE_6D				0					//1ѡ��6Dָ�0��ѡ6Dָ��
#define		MODULE_6E				0					//1ѡ��6Eָ�0��ѡ6Eָ��
#define		MODULE_6F		    	0					//1ѡ��6Fָ�0��ѡ6Fָ��
#define		MODULE_70				0					//1ѡ��70ָ�0��ѡ70ָ��
#define		MODULE_71				0					//1ѡ��71ָ�0��ѡ71ָ��
#define		MODULE_72		    	0					//1ѡ��72ָ�0��ѡ72ָ��
#define		MODULE_73				0					//1ѡ��73ָ�0��ѡ73ָ��
#define		MODULE_74				0					//1ѡ��74ָ�0��ѡ74ָ��
#define		MODULE_75				0					//1ѡ��75ָ�0��ѡ75ָ��
#define		MODULE_76				0					//1ѡ��76ָ�0��ѡ76ָ��
#define 	MODULE_77				0					//1ѡ��77ָ�0��ѡ77ָ��
#define 	MODULE_78				0					//1ѡ��78ָ�0��ѡ78ָ��
#define		MODULE_79				0					//1ѡ��79ָ�0��ѡ79ָ��
#define		MODULE_7A				0					//1ѡ��7Aָ�0��ѡ7Aָ��
#define		MODULE_7B				0					//1ѡ��7Bָ�0��ѡ7Bָ��
#define		MODULE_7C				0                   //1ѡ��7Cָ�0��ѡ7Cָ��
#define		MODULE_7D				0					//1ѡ��7Dָ�0��ѡ7Dָ��
#define		MODULE_7E				0					//1ѡ��7Eָ�0��ѡ7Eָ��
#define		MODULE_7F		    	0					//1ѡ��7Fָ�0��ѡ7Fָ��

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
