#ifndef __LEVETOP_H
#define __LEVETOP_H

#include "LT268A.h"
#include "bsp.h"
#include "data.h"
#include "uart.h"

//处理函数中返回相关参数的定义
//#define OK                     0						// 正确执行
//#define CMD_ERROR              1    					// 无此命令
//#define CRC_ERROR              2    					// CRC核对错误
//#define CMD_INFO_ERROR         3    					// 无此命令的具体信息
//#define CMD_OPER_ERROR         4    					// 无此操作数

#define OK                     0			// 正确执行
#define CMD_OPER_ERROR         1    		// 指令参数错误
#define CMD_INFO_ERROR         2    		// 不存在该指令
#define CMD_CONFIG_ERROR       3    		// 指令FLASH配置溢出
#define CRC_ERROR              4			// CRC错误
#define CMD_ERROR              5   			// Flash数据异常
#define Password_Num_ERROR     6    		// A4h键盘显示数字图片与相应的按键数量不符
#define CMD_RETURN_NULL        10    		// 返回值为空

#define PIC_INFO_SIZE	 				 12
#define CMD_LEN 							 100

//每张图片信息的结构体
typedef struct
{
	UINT16 w;       																															// 宽度
	UINT16 h;       																															// 高度
	UINT32 addr;    																															// 在FLASH中存储的起始位置
	UINT32 size;		 																															//picture size
}Picture_Info;
extern Picture_Info gPictureInfo;
extern UINT8 gCmdInfo[CMD_LEN];
extern UINT8 gPicInfoBuf[PIC_INFO_SIZE];

//flash的规划地址
extern const UINT32 CMD_TABLE_ADDR;
extern const UINT32 PIC_TABLE_ADDR;
extern const UINT32 FONT_TABLE_ADDR;
extern const UINT32 CMD_INFO_ADDR;
extern const UINT32 VERSION_TABLE_ADDR;

extern const UINT32 BAUDRATE_ADDR;
extern const UINT32 XY_SIZE_ADDR;
extern const UINT32 LCD_PARAM_ADDR;

extern unsigned short int LCD_XSIZE_TFT;
extern unsigned short int LCD_YSIZE_TFT;
extern unsigned int gBaudrate;
extern unsigned short int LCD_VBPD;
extern unsigned short int LCD_VFPD;
extern unsigned short int LCD_VSPW;
extern unsigned short int LCD_HBPD;
extern unsigned short int LCD_HFPD;
extern unsigned short int LCD_HSPW;

void LT_ReadParam(void);

UINT8 LT_RedCmdInfo(UINT8 *rxBuf,UINT16 *addr,UINT8 *oper);															//获取命令信息
UINT8 LT_CompoundPicInfo(UINT32 addr);																						//获取图片信息并在全屏时把动作的窗口关闭

UINT8 Get_Cursor_Init_info(UINT8 *i,UINT32 *addr,UINT8 *Image);													//图形光标初始化

UINT8 Get_80_info1(UINT8 *rxBuf,UINT8 *buf);
UINT8 Get_80_info2(UINT8 *i,UINT8 *remove_bcolor_flag,UINT16 *x,UINT16 *y);
UINT8 Get_81_info1(UINT8 *rxBuf,UINT8 *sum,UINT8 *t,UINT8 *flag,UINT16 *x,UINT16 *y,UINT16 *pic,UINT8 *oper);
UINT8 Get_81_info2(UINT16 *pic);
UINT8 Get_88_info1(UINT8 *rxBuf,UINT16 *s,UINT8 *t,UINT16 *f,UINT16 *x,UINT16 *y,UINT8 *pic,UINT8 *oper,UINT8 *loop,UINT8 *flag);
UINT8 Get_88_info2(UINT16 *pic);
//UINT8 Get_8A_info1(UINT8 *rxBuf,UINT8 *buf);
//UINT8 Get_8A_info2(UINT8 *i,UINT8 *remove_bcolor_flag,UINT16 *x,UINT16 *y);
UINT8 Get_8F_info1(UINT16 *pic);
UINT8 Get_90_info1(UINT8 *rxBuf,UINT8 *oper,UINT8 *dir,UINT8 *color_flag,UINT8 *Color_F,UINT8 *Color_B,UINT16 *x,UINT16 *y);
UINT8 Get_90_info2(UINT16 *dot_w,UINT16 *dot_h);
UINT8 Get_90_info3(UINT16 *pic_w,UINT16 *dot_w,UINT16 *comma_w);
UINT8 Get_91_info1(UINT8 *rxBuf,UINT8 *oper,UINT8 *dir,UINT8 *color_flag,UINT16 *x,UINT16 *y);
UINT8 Get_91_info2(UINT16 *dot_w,UINT16 *dot_h);
UINT8 Get_91_info3(UINT16 *pic_w,UINT16 *dot_w);
UINT8 Get_98_info(UINT8 *rxBuf,UINT16 *x,UINT16 *y,UINT8 *size);
UINT8 Get_9A_info(UINT8 *rxBuf,UINT8 *buf1,UINT8 *buf2,UINT8 *length);
UINT8 Get_A0_info(UINT8 *rxBuf,UINT8 *oper,UINT8 * flag,UINT8 *buf1,UINT8 *buf2,UINT16 *x,UINT16 *y);
UINT8 Get_A2_info(UINT8 *rxBuf,UINT8 *oper,UINT8 *buf1,UINT8 *buf2,UINT16 *x,UINT16 *y,UINT16 *w,UINT16 *h);
UINT8 Get_B0_info1(UINT8 *rxBuf,UINT16 *x,UINT16 *y,UINT8 *dir,UINT8 *width,UINT32 *color,UINT8 *mark,UINT8 *buf,UINT16 *h,UINT32 *color1);
UINT8 Get_B8_info(UINT8 *rxBuf,UINT32 *flashAddr,UINT32 *len);
UINT8 Get_C0_C3_info(UINT8 *rxBuf,UINT8 *oper,UINT8 *pos,UINT8 *size,UINT32 *len,UINT32 *flashAddr,UINT16 *x,UINT16 *y,UINT16 *w,UINT32 *color,UINT32 *b_color,UINT8 *select_font,UINT8 *size_h,UINT8 *size_v,UINT8 *transparent,UINT8 *alignment);
UINT8 Get_C9_info(UINT8 *rxBuf,UINT8 *buf);
UINT8 Get_D8_info1(UINT8 *rxBuf,UINT8 *oper,UINT8 *mode,UINT8 *t,UINT16 *p_c,UINT16 *x,UINT16 *y);
UINT8 Get_D8_info2(UINT16 *p_c);
UINT8 Get_D9_info1(UINT8 *rxBuf,UINT8 *oper,UINT8 * mode,UINT8 *t,UINT8 *sum,UINT16 *pic,UINT16 *x,UINT16 *y);
UINT16 Get_D9_info2(UINT16 *pic);
UINT8 Get_DC_info(UINT8 *rxBuf,UINT16 *x,UINT16 *y,UINT16 *w,UINT16 *r,UINT32 *color,UINT8 *t);
UINT8 Get_DF_info(UINT8 *rxBuf,UINT8 *flag,UINT8 *width,UINT32 *color);
UINT8 Get_E0_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT32 *color,UINT8 *width);
UINT8 Get_E1_E3_info(UINT8 *rxBuf,UINT16 *x,UINT16 *y,UINT16 *r,UINT32 *color,UINT32 *color1,UINT8 *width);
UINT8 Get_E4_E6_info(UINT8 *rxBuf,UINT16 *x,UINT16 *y,UINT16 *x_r,UINT16 *y_r,UINT32 *color,UINT32 *color1,UINT8 *width);
UINT8 Get_E7_E9_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT32 *color,UINT32 *color1,UINT8 *width);
UINT8 Get_EA_EC_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT16 *x_r,UINT16 *y_r,UINT32 *color,UINT32 *color1,UINT8 *width);
UINT8 Get_ED_EF_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT16 *x3,UINT16 *y3,UINT32 *color,UINT32 *color1);
UINT8 Get_F0_F1_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT16 *x3,UINT16 *y3,UINT16 *x4,UINT16 *y4,UINT32 *color);
UINT8 Get_F2_F3_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT16 *x3,UINT16 *y3,UINT16 *x4,UINT16 *y4,UINT16 *x5,UINT16 *y5,UINT32 *color);
UINT8 Get_F4_info(UINT8 *rxBuf,UINT16 *x,UINT16 *y,UINT16 *x_r,UINT16 *y_r,UINT16 *h,UINT32 *color,UINT32 *color1,UINT8 *width);
UINT8 Get_F5_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *x2,UINT16 *y2,UINT16 *w,UINT16 *h,UINT32 *color,UINT32 *color1,UINT8 *width);
UINT8 Get_F6_info(UINT8 *rxBuf,UINT16 *x1,UINT16 *y1,UINT16 *w,UINT16 *h,UINT16 *cn,UINT16 *rn,UINT16 *w_1,UINT16 *w_2,UINT32 *c1,UINT32 *c2,UINT32 *c3,UINT8 *mode);

void LT268_TFT_ShowPicture(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT32 Addr);
void LT268_TFT_ShowPicture_Png(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT32 Addr);
void LT268_TFT_ShowPicture_zip(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT32 Addr);

void LT268_TFT_FullScreen_Cut(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT32 Addr,UINT16 Color);

void LT268_TFT_D8_Up(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 High_Pixel,UINT32 Addr);
void LT268_TFT_D8_Down(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 High_Pixel,UINT32 Addr);
void LT268_TFT_D8_Left(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 Width_Pixel,UINT32 Addr);
void LT268_TFT_D8_Right(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 Width_Pixel,UINT32 Addr);

void LT268_TFT_D9_Up(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 High_Pixel,UINT32 Addr,UINT32 Addr_next);
void LT268_TFT_D9_Down(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 High_Pixel,UINT32 Addr,UINT32 Addr_next);
void LT268_TFT_D9_Left(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 Width_Pixel,UINT32 Addr,UINT32 Addr_next);
void LT268_TFT_D9_Right(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 Width_Pixel,UINT32 Addr,UINT32 Addr_next);

#endif


