#ifndef _module_select_h
#define _module_select_h
#include "LT268A.h"

#define 		R_TOUCH_FLAG       	1 					//1选择电阻屏，0不选电阻屏
#define			FT_TOUCH_FLAG       0       	 		//1选择FT电容屏，0不选FT电容屏
#define			GT_TOUCH_FLAG 		0       	 		//1选择GT电容屏，0不选GT电容屏

#define			LT268A_SPI    0		//SPI接口		//更改接口需要更换liblevetop.a
#define 		LT268A_Data_8 1		//8位总线接口

#define			Horizontal_screen   1       //1选择横屏，0选择竖屏


#define 		Comma				0       		   // 90/91指令： 1=带逗号，0=不带逗号
#define 		CRC_FLAG         	0        			//1选择CRC，0不选CRC
#define	        slide_lenght        50				  //设置C9手势有效滑动距离


#define 		MODULE_80									1					//1选择80指令，0不选80指令
#define 		MODULE_81									1				    //1选择81指令，0不选81指令
#define 		MODULE_82									0					//1选择82指令，0不选82指令
#define 		MODULE_84									1				    //1选择84指令，0不选84指令
#define 		MODULE_85									1					//1选择85指令，0不选85指令
#define 		MODULE_86_87								0					//1选择86/87指令，0不选86/87指令
#define 		MODULE_88									1					//1选择88指令，0不选88指令
#define 		MODULE_89									1					//1选择89指令，0不选89指令
#define 		MODULE_8A									1					//1选择8A指令，0不选8A指令
#define 		MODULE_8B									1					//1选择8B指令，0不选8B指令
#define 		MODULE_8C_8D								0					//1选择8C/8D指令，0不选8C/8D指令
#define 		MODULE_8F									1					//1选择8F指令，0不选8F指令
#define 		MODULE_90									1					//1选择90指令，0不选90指令
#define 		MODULE_91									0					//1选择91指令，0不选91指令
#define 		MODULE_98									0					//1选择98指令，0不选98指令
#define 		MODULE_9A									1					//1选择9A指令，0不选9A指令
#define 		MODULE_9E									1					//1选择9E指令，0不选9E指令
#define 		MODULE_A0_A1								1					//1选择A0指令，0不选A0指令
#define 		MODULE_A2_A3								1					//1选择A2指令，0不选A2指令
#define 		MODULE_B4									0					//1选择B4指令，0不选B4指令
#define 		MODULE_B8_B9								0					//1选择B8/B9指令，0不选B8/B9指令
#define 		MODULE_BA									1					//1选择BA指令，0不选BA指令
#define 		MODULE_BC									1					//1选择BC指令，0不选BC指令
#define 		MODULE_BD									1					//1选择BD指令，0不选BD指令
#define 		MODULE_BE									1					//1选择BE指令，0不选BE指令
#define 		MODULE_BF									1					//1选择BF指令，0不选BF指令
#define 		MODULE_C0_C3								1					//1选择Cx指令，0不选Cx指令
#define 		MODULE_C9									1					//1选择C9指令，0不选C9指令
#define 		MODULE_CA_CF								0					//1选择Cx指令，0不选Cx指令
#define 		MODULE_D7									1					//1选择D7指令，0不选D7指令
#define 		MODULE_D8									1					//1选择D8指令，0不选D8指令
#define 		MODULE_D9									1					//1选择D9指令，0不选D9指令
#define 		MODULE_DB									1					//1选择DB指令，0不选DB指令
#define 		MODULE_DC									1					//1选择DC指令，0不选DC指令
#define 		MODULE_DF									0
#define 		MODULE_E0									0					//1选择E0指令，0不选E0指令
#define 		MODULE_E1_E3								0					//1选择Ex指令，0不选Ex指令
#define 		MODULE_E4_E6								0					//1选择Ex指令，0不选Ex指令
#define 		MODULE_E7_E9								0					//1选择Ex指令，0不选Ex指令
#define 		MODULE_EA_EC								0					//1选择Ex指令，0不选Ex指令
#define 		MODULE_ED_EF								0					//1选择Ex指令，0不选Ex指令
#define 		MODULE_F0_F1								0					//1选择Fx指令，0不选Fx指令
#define 		MODULE_F2_F3								0					//1选择Fx指令，0不选Fx指令
#define 		MODULE_F4									0					//1选择F4指令，0不选F4指令
#define 		MODULE_F5									0					//1选择F5指令，0不选F5指令
#define 		MODULE_F6									0					//1选择F6指令，0不选F6指令
#define 		MODULE_FF									0
#define 		MODULE_B0									0					//1选择B0指令，0不选B0指令
#define 		MODULE_B1									0					//1选择B1指令，0不选B1指令
#define 		MODULE_94_95								0
#define 		MODULE_9B_9C								0
#endif
