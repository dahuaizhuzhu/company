#ifndef _module_select_h
#define _module_select_h
#include "LT268A.h"

#define 		R_TOUCH_FLAG       	1 					//1ѡ���������0��ѡ������
#define			FT_TOUCH_FLAG       0       	 		//1ѡ��FT��������0��ѡFT������
#define			GT_TOUCH_FLAG 		0       	 		//1ѡ��GT��������0��ѡGT������

#define			LT268A_SPI    0		//SPI�ӿ�		//���Ľӿ���Ҫ����liblevetop.a
#define 		LT268A_Data_8 1		//8λ���߽ӿ�

#define			Horizontal_screen   1       //1ѡ�������0ѡ������


#define 		Comma				0       		   // 90/91ָ� 1=�����ţ�0=��������
#define 		CRC_FLAG         	0        			//1ѡ��CRC��0��ѡCRC
#define	        slide_lenght        50				  //����C9������Ч��������


#define 		MODULE_80									1					//1ѡ��80ָ�0��ѡ80ָ��
#define 		MODULE_81									1				    //1ѡ��81ָ�0��ѡ81ָ��
#define 		MODULE_82									0					//1ѡ��82ָ�0��ѡ82ָ��
#define 		MODULE_84									1				    //1ѡ��84ָ�0��ѡ84ָ��
#define 		MODULE_85									1					//1ѡ��85ָ�0��ѡ85ָ��
#define 		MODULE_86_87								0					//1ѡ��86/87ָ�0��ѡ86/87ָ��
#define 		MODULE_88									1					//1ѡ��88ָ�0��ѡ88ָ��
#define 		MODULE_89									1					//1ѡ��89ָ�0��ѡ89ָ��
#define 		MODULE_8A									1					//1ѡ��8Aָ�0��ѡ8Aָ��
#define 		MODULE_8B									1					//1ѡ��8Bָ�0��ѡ8Bָ��
#define 		MODULE_8C_8D								0					//1ѡ��8C/8Dָ�0��ѡ8C/8Dָ��
#define 		MODULE_8F									1					//1ѡ��8Fָ�0��ѡ8Fָ��
#define 		MODULE_90									1					//1ѡ��90ָ�0��ѡ90ָ��
#define 		MODULE_91									0					//1ѡ��91ָ�0��ѡ91ָ��
#define 		MODULE_98									0					//1ѡ��98ָ�0��ѡ98ָ��
#define 		MODULE_9A									1					//1ѡ��9Aָ�0��ѡ9Aָ��
#define 		MODULE_9E									1					//1ѡ��9Eָ�0��ѡ9Eָ��
#define 		MODULE_A0_A1								1					//1ѡ��A0ָ�0��ѡA0ָ��
#define 		MODULE_A2_A3								1					//1ѡ��A2ָ�0��ѡA2ָ��
#define 		MODULE_B4									0					//1ѡ��B4ָ�0��ѡB4ָ��
#define 		MODULE_B8_B9								0					//1ѡ��B8/B9ָ�0��ѡB8/B9ָ��
#define 		MODULE_BA									1					//1ѡ��BAָ�0��ѡBAָ��
#define 		MODULE_BC									1					//1ѡ��BCָ�0��ѡBCָ��
#define 		MODULE_BD									1					//1ѡ��BDָ�0��ѡBDָ��
#define 		MODULE_BE									1					//1ѡ��BEָ�0��ѡBEָ��
#define 		MODULE_BF									1					//1ѡ��BFָ�0��ѡBFָ��
#define 		MODULE_C0_C3								1					//1ѡ��Cxָ�0��ѡCxָ��
#define 		MODULE_C9									1					//1ѡ��C9ָ�0��ѡC9ָ��
#define 		MODULE_CA_CF								0					//1ѡ��Cxָ�0��ѡCxָ��
#define 		MODULE_D7									1					//1ѡ��D7ָ�0��ѡD7ָ��
#define 		MODULE_D8									1					//1ѡ��D8ָ�0��ѡD8ָ��
#define 		MODULE_D9									1					//1ѡ��D9ָ�0��ѡD9ָ��
#define 		MODULE_DB									1					//1ѡ��DBָ�0��ѡDBָ��
#define 		MODULE_DC									1					//1ѡ��DCָ�0��ѡDCָ��
#define 		MODULE_DF									0
#define 		MODULE_E0									0					//1ѡ��E0ָ�0��ѡE0ָ��
#define 		MODULE_E1_E3								0					//1ѡ��Exָ�0��ѡExָ��
#define 		MODULE_E4_E6								0					//1ѡ��Exָ�0��ѡExָ��
#define 		MODULE_E7_E9								0					//1ѡ��Exָ�0��ѡExָ��
#define 		MODULE_EA_EC								0					//1ѡ��Exָ�0��ѡExָ��
#define 		MODULE_ED_EF								0					//1ѡ��Exָ�0��ѡExָ��
#define 		MODULE_F0_F1								0					//1ѡ��Fxָ�0��ѡFxָ��
#define 		MODULE_F2_F3								0					//1ѡ��Fxָ�0��ѡFxָ��
#define 		MODULE_F4									0					//1ѡ��F4ָ�0��ѡF4ָ��
#define 		MODULE_F5									0					//1ѡ��F5ָ�0��ѡF5ָ��
#define 		MODULE_F6									0					//1ѡ��F6ָ�0��ѡF6ָ��
#define 		MODULE_FF									0
#define 		MODULE_B0									0					//1ѡ��B0ָ�0��ѡB0ָ��
#define 		MODULE_B1									0					//1ѡ��B1ָ�0��ѡB1ָ��
#define 		MODULE_94_95								0
#define 		MODULE_9B_9C								0
#endif
