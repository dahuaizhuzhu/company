#ifndef _bsp_h
#define _bsp_h

#include "math.h"
#include "levetop.h"
#include "module_select.h"
#include "bsp_user.h"

extern UINT8 cmd_flag;
extern UINT8 init_ok_flag;                                   //User Area Data Error, Please Update User Area Data


//#define SDRAM_SIZE	(1024*1024*24)
//
//#define LAY_BUFF1 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*2
//#define LAY_BUFF2 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*3
//#define LAY_BUFF3 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*4
//#define LAY_BUFF4 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*5
//#define LAY_BUFF5 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*6
//#define LAY_BUFF6 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*7
//#define ROLL_BUFF1 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*11
//#define ROLL_BUFF2 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*15
//#define SLID_BUFF 	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*19
//#define MAIN_BUFF   LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*1
//
//#define FONT_BUFF   LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*8
//
//#define QR_BUFF   	LCD_XSIZE_TFT*LCD_YSIZE_TFT*2*9
//#define SLIDER_SIZE 	4
//#define AVAILABLEIN  	40

//typedef struct
//{
//	UINT8  openflag ;														// 1打开滑动进度条，0时关闭进度条
//	UINT16 w;       															// 宽度
//	UINT16 h;       															// 高度
//	UINT32 addr;    															// 在FLASH中存储的起始位置
//	UINT8 flag1;
//	UINT16 w1;       															// 宽度
//	UINT16 h1;       															// 高度
//	UINT32 addr1;    															// 在FLASH中存储的起始位置
//	UINT16 x;			 															// 进度条底图显示起始x坐标
//	UINT16 y;			 															// 进度条底图显示起始y坐标
//	UINT16 length;																// 进度条总长度
//	UINT8  width;																// 进度条宽度
//	UINT8  dir;																	// 画进度条底图的方向，o上，1下，2左，3右
//	UINT8  mark;																	// 边缘形状，0矩形，l圆环
//	UINT16 x1;
//	UINT16 y1;
//	UINT16 x2;			 															// 底图显示起始x坐标
//	UINT16 y2;			 															// 底图显示起始y坐标
//	UINT8  flag;																	// 去背景色，1去背景色，0不做处理
//	UINT32 color1;																// 进度条底图颜色
//	UINT32 color2;																// 进度条颜色
//	UINT16 lastx;			 															// 上次滑动的x坐标
//	UINT16 lasty;			 															// 上次滑动的y坐标
//}Slider_Info;
//extern Slider_Info gSliderInfo[];						//该结构体数组决定窗口的个数
//extern UINT8 Sliderflag;
//extern UINT8 SliderCount;

#if MODULE_81
typedef struct
{
	UINT16 x;			 													//图片显示起始x坐标
	UINT16 y;			 													//图片显示起始y坐标
	UINT16 w;																//窗口宽度
	UINT16 h;																//窗口高度
	UINT32 addr;    														// 在FLASH中存储的起始位置
	UINT16 t_c;     														// 时间计数统计
	UINT16 t;       														// 延时时间
	UINT8  operation;
	UINT8  sum;     														// 总有多少图片
	UINT8  p_c;     														// 图片计数
	UINT16  p[21];   														// 图片的编号
	UINT8  flag;															// 用来存储是否去背景标志
}Turn_Info;
extern Turn_Info gTurnInfo[];											//该结构体数组决定窗口的个数
extern UINT8 gTurnFlag;
extern UINT8 gOpen81;
extern UINT8 gTurnCount;
#endif

#if MODULE_88
typedef struct
{
	UINT16 x;
	UINT16 y;
	UINT16 w;
	UINT16 h;
	UINT32 addr;    														// 在FLASH中存储的起始位置
	UINT16 t_c;     														// 时间计数统计
	UINT16 t;       														// 延时时间
	UINT8  operation;
	UINT16  s;       														// 开始图片编号
	UINT16  f;       														// 结束图片编号
	UINT16  p_c;     														// 图片计数
	UINT8 loop;
	UINT8 flag;
}Gif_Info;
extern Gif_Info gGifInfo[];
extern UINT8 gGifFlag;
extern UINT8 gOpen88;
extern UINT8 gGifCount;
#endif

#if MODULE_A0_A1
typedef struct
{
	UINT16 x;
	UINT16 y;
	UINT8  operation;
	UINT16 w;       														// 宽度
	UINT16 h;       														// 高度
	UINT32 addr;    														// 在FLASH中存储的起始位置
	UINT8 flag;
	UINT8  buf[8][2];       												//存储指令
}Control_Info;
extern Control_Info controlInfo[];
extern UINT8 ControlFlag;
extern UINT8 button_count;
extern UINT8 button_flag;
extern UINT8 ControlCount;
extern UINT8 control_buf[8][2];
#endif

#if MODULE_A2_A3
typedef struct
{
	UINT16 x;
	UINT16 y;
	UINT8  operation;
	UINT16 w;       														// 宽度
	UINT16 h;       														// 高度
	UINT32 addr;    														// 在FLASH中存储的起始位置
	UINT8  buf[8][2];       												// 存储指令
}Control_Info2;
extern Control_Info2 controlInfo2[];
extern UINT8 ControlFlag2;
extern UINT8 button_count2;
extern UINT8 button_flag2;
extern UINT8 ControlCount2;
extern UINT8 control_buf2[8][2];
#endif

#if MODULE_D8
typedef struct
{
	UINT16 x;																	//图片滑动x坐标
	UINT16 y;																	//图片滑动y坐标
	UINT16 t_c;     															// 时间计数统计
	UINT16 t;       															// 延时时间
	UINT8  mode;																//图片滑动模式，向上、向下、向左、向右
	UINT8 operation;															//串口发送的第2个字节数
	UINT16  p_f;     															// 图片滑动的像素点
	UINT16 p_c;																	//第几张图
	UINT8 start_end;															//0开始滚动图片，图片已滚动完
	UINT16 w;																	//图片宽度
	UINT16 h;																	//图片高度
	UINT32 addr;																//图片的地址
}Roll_One;
extern UINT8 gOpenD8;
extern UINT8 rool_one_flag;
extern Roll_One roll_one[];
extern UINT8 roll_one_count;
#endif

#if MODULE_D9
typedef struct
{
	UINT16 x;																	//图片滑动x坐标
	UINT16 y;																	//图片滑动y坐标
	UINT16 t_c;     															// 时间计数统计
	UINT16 t;       															// 延时时间
	UINT8  mode;																//图片滑动模式，向上、向下、向左、向右
	UINT8 sum;																	//图片总数
	UINT8 operation;															//串口发送的第2个字节数
	UINT16  p_f;     															// 图片滑动的像素点
	UINT8 p_c;																	//第几张图
	UINT16  p[10];   															// 图片的编号
	UINT16 w;																	//图片宽度
	UINT16 h;																	//图片高度
	UINT16 pos;																//图片存放在缓存的位置
	UINT32 addr;																//图片的地址
	UINT32 addr_last;															//上一张图片的地址
	UINT32 addr_next;															//上一张图片的地址
}Roll_Info;
extern UINT8 gOpenD9;
extern UINT8 RollFlag;
extern Roll_Info RollInfo[];
extern UINT8 Rollcount;
#endif

#if MODULE_B4
typedef struct
{
	UINT8 dir;     																			//0:x  1:y
	UINT8 first;
	UINT8 mode;    																			//0:正常模式  1:循环模式
	UINT8 num;
	UINT8 sum;
	UINT8 pic[10];																			//存储用于滑动的图片编号
	INT16 x;
	INT16 y;
	INT16 dx;
	INT16 dy;
	UINT16 lastX;
	UINT16 lastY;
	UINT16 count;
	INT16 buf[5];
	UINT8 pos;
}Gesture_Info;
extern Gesture_Info gGesXY;
extern UINT8 gFirstTouch ;
extern UINT8 gOpenGesture;
#endif

extern UINT32 FullScreen_Pic_Addr;
extern UINT16 FullScreen_Square_Color;

extern UINT8 FF_Update_Flag;

UINT16 Rx_CRC_CCITT(UINT8 *puchMsg, UINT16 usDataLen);
void LT_ReadFlash(UINT8* pBuffer,UINT32 ReadAddr,UINT16 NumByteToRead);				//必须有该函数，封装的库函数用到
void LT_ReceiveCmd(UINT8 *buf);
UINT8 LT_AnalyzeCmdInfo(UINT8 *rxBuf);
UINT8 New_Function(UINT8 cmd,UINT8 *RxBuf);
UINT16 LT_Color24_To_16(UINT32 color);

#if   MODULE_80
UINT8 LT_ManageCmd_80(UINT8 *rxBuf);
#endif

#if   MODULE_81
UINT8 LT_ManageCmd_81(UINT8 *rxBuf);
void TurnForm(void);
#endif

#if   MODULE_84
UINT8 LT_ManageCmd_84(UINT8 *rxBuf);
void GradualChange(void);
#endif

#if   MODULE_85
UINT8 LT_ManageCmd_85(UINT8 *rxBuf);
#endif

#if   MODULE_88
UINT8 LT_ManageCmd_88(UINT8 *rxBuf);
void TurnGif(void);
#endif

#if   MODULE_89
UINT8 LT_ManageCmd_89(UINT8 *rxBuf);
#endif

#if   MODULE_8A
UINT8 LT_ManageCmd_8A(UINT8 *rxBuf);
#endif

#if   MODULE_8B
UINT8 LT_ManageCmd_8B(UINT8 *rxBuf);
#endif

#if   MODULE_8C_8D
UINT8 LT_ManageCmd_8C(UINT8 *rxBuf);
UINT8 LT_ManageCmd_8D(UINT8 *rxBuf);
#endif

#if   MODULE_8F
UINT8 LT_ManageCmd_8F(UINT8 *rxBuf);
#endif


#if   MODULE_90
UINT8 LT_ManageCmd_90(UINT8 *rxBuf);

UINT16 LT_NumWidth_90(UINT8 *rxBuf,UINT16 x);
void Display_Number_picturn(UINT8 *rxBuf,UINT8 dir,UINT16 x,UINT16 y,UINT16 width,UINT16 *gNumWidth,UINT16 num_w,UINT16 num_h,UINT16 dot_w,UINT16 dot_h,UINT16 comma_w,UINT16 comma_h,UINT8 color_flag,UINT8 Color_F,UINT8 Color_B,UINT32 num_addr);
#endif

#if   MODULE_91
UINT8 LT_ManageCmd_91(UINT8 *rxBuf);

UINT16 LT_NumWidth_91(UINT8 *rxBuf,UINT16 x);
void Display_Number_picturn_16bpp(UINT8 *rxBuf,UINT8 dir,UINT16 x,UINT16 y,UINT16 width,UINT16 *gNumWidth1,UINT16 num_w,UINT16 num_h,UINT16 dot_w,UINT16 dot_h,UINT16 comma_w,UINT16 comma_h,UINT8 color_flag,UINT32 num_addr);
#endif

#if   MODULE_98
UINT8 LT_ManageCmd_98(UINT8 *rxBuf);
#endif

extern UINT8 cmd_9A_flag;
#if   MODULE_9A
UINT8 LT_ManageCmd_9A(UINT8 *rxBuf);
#endif

#if   MODULE_9E
UINT8 LT_ManageCmd_9E(UINT8 *rxBuf);
#endif

#if   MODULE_A0_A1
UINT8 LT_ManageCmd_A0(UINT8 *rxBuf);
UINT8 LT_ManageCmd_A1(UINT8 *rxBuf);
void button(void);
#endif

#if   MODULE_A2_A3
UINT8 LT_ManageCmd_A2(UINT8 *rxBuf);
UINT8 LT_ManageCmd_A3(UINT8 *rxBuf);
void button2(void);
#endif

#if   MODULE_B0
UINT8 LT_ManageCmd_B0(UINT8 *rxBuf);
#endif

#if   MODULE_B8_B9
UINT8 LT_ManageCmd_B8(UINT8 *rxBuf);
UINT8 LT_ManageCmd_B9(UINT8 *rxBuf);
extern void close_wav(void);
#endif

#if   MODULE_BA
UINT8 LT_ManageCmd_BA(UINT8 *rxBuf);
#endif

#if   MODULE_BC
UINT8 LT_ManageCmd_BC(UINT8 *rxBuf);
#endif

#if   MODULE_BD
UINT8 LT_ManageCmd_BD(UINT8 *rxBuf);
#endif

#if   MODULE_BE
UINT8 LT_ManageCmd_BE(UINT8 *rxBuf);
#endif

#if   MODULE_BF
UINT8 LT_ManageCmd_BF(UINT8 *rxBuf);
#endif

#if   MODULE_C0_C3
UINT8 LT_ManageCmd_C0_C3(UINT8 *rxBuf);
#endif
extern UINT8 C0_gNumRow;

#if   MODULE_C9
UINT8 LT_ManageCmd_C9(UINT8 *rxBuf);
void Slide(void);
extern UINT8 Slide_Flag;
#endif

#if   MODULE_CA_CF
UINT8 LT_ManageCmd_CA(UINT8 *rxBuf);
UINT8 LT_ManageCmd_CB(UINT8 *rxBuf);
UINT8 LT_ManageCmd_CC(UINT8 *rxBuf);
UINT8 LT_ManageCmd_CD(UINT8 *rxBuf);
UINT8 LT_ManageCmd_CE(UINT8 *rxBuf);
UINT8 LT_ManageCmd_CF(UINT8 *rxBuf);
#endif

#if   MODULE_D8
UINT8 LT_ManageCmd_D8(UINT8 *rxBuf);
void TurnRoll_One(void);
void Roll_one(UINT8 d8_count);
#endif

#if   MODULE_D9
UINT8 LT_ManageCmd_D9(UINT8 *rxBuf);
void TurnPicture(void);
void Roll (UINT8 Rollcount);
#endif

#if   MODULE_DB
UINT8 LT_ManageCmd_DB(UINT8 *rxBuf);
#endif

#if   MODULE_DC
UINT8 LT_ManageCmd_DC(UINT8 *rxBuf);
#endif

#if   MODULE_DF
UINT8 LT_ManageCmd_DF(UINT8 *rxBuf);
#endif

#if  MODULE_E0
UINT8 LT_ManageCmd_E0(UINT8 *rxBuf);
#endif

#if   MODULE_E1_E3
UINT8 LT_ManageCmd_E1_E3(UINT8 *rxBuf);
#endif

#if   MODULE_E4_E6
UINT8 LT_ManageCmd_E4_E6(UINT8 *rxBuf);
#endif

#if   MODULE_E7_E9
UINT8 LT_ManageCmd_E7_E9(UINT8 *rxBuf);
#endif

#if   MODULE_EA_EC
UINT8 LT_ManageCmd_EA_EC(UINT8 *rxBuf);
#endif

#if   MODULE_ED_EF
UINT8 LT_ManageCmd_ED_EF(UINT8 *rxBuf);
#endif

#if  MODULE_F4
UINT8 LT_ManageCmd_F4(UINT8 *rxBuf);
#endif

#if   MODULE_F6
UINT8 LT_ManageCmd_F6(UINT8 *rxBuf);
#endif

#if   MODULE_FF
UINT8 LT_ManageCmd_FF(UINT8 *rxBuf);
#endif
UINT8 LT_Idle(UINT8 *rxBuf);

//UINT8 Display_UserfFont(UINT8 *rxBuf);

extern void Main_From_UartRxBuff(void);

#endif



