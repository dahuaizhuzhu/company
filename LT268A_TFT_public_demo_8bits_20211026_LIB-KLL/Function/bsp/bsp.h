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
//	UINT8  openflag ;														// 1�򿪻�����������0ʱ�رս�����
//	UINT16 w;       															// ���
//	UINT16 h;       															// �߶�
//	UINT32 addr;    															// ��FLASH�д洢����ʼλ��
//	UINT8 flag1;
//	UINT16 w1;       															// ���
//	UINT16 h1;       															// �߶�
//	UINT32 addr1;    															// ��FLASH�д洢����ʼλ��
//	UINT16 x;			 															// ��������ͼ��ʾ��ʼx����
//	UINT16 y;			 															// ��������ͼ��ʾ��ʼy����
//	UINT16 length;																// �������ܳ���
//	UINT8  width;																// ���������
//	UINT8  dir;																	// ����������ͼ�ķ���o�ϣ�1�£�2��3��
//	UINT8  mark;																	// ��Ե��״��0���Σ�lԲ��
//	UINT16 x1;
//	UINT16 y1;
//	UINT16 x2;			 															// ��ͼ��ʾ��ʼx����
//	UINT16 y2;			 															// ��ͼ��ʾ��ʼy����
//	UINT8  flag;																	// ȥ����ɫ��1ȥ����ɫ��0��������
//	UINT32 color1;																// ��������ͼ��ɫ
//	UINT32 color2;																// ��������ɫ
//	UINT16 lastx;			 															// �ϴλ�����x����
//	UINT16 lasty;			 															// �ϴλ�����y����
//}Slider_Info;
//extern Slider_Info gSliderInfo[];						//�ýṹ������������ڵĸ���
//extern UINT8 Sliderflag;
//extern UINT8 SliderCount;

#if MODULE_81
typedef struct
{
	UINT16 x;			 													//ͼƬ��ʾ��ʼx����
	UINT16 y;			 													//ͼƬ��ʾ��ʼy����
	UINT16 w;																//���ڿ��
	UINT16 h;																//���ڸ߶�
	UINT32 addr;    														// ��FLASH�д洢����ʼλ��
	UINT16 t_c;     														// ʱ�����ͳ��
	UINT16 t;       														// ��ʱʱ��
	UINT8  operation;
	UINT8  sum;     														// ���ж���ͼƬ
	UINT8  p_c;     														// ͼƬ����
	UINT16  p[21];   														// ͼƬ�ı��
	UINT8  flag;															// �����洢�Ƿ�ȥ������־
}Turn_Info;
extern Turn_Info gTurnInfo[];											//�ýṹ������������ڵĸ���
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
	UINT32 addr;    														// ��FLASH�д洢����ʼλ��
	UINT16 t_c;     														// ʱ�����ͳ��
	UINT16 t;       														// ��ʱʱ��
	UINT8  operation;
	UINT16  s;       														// ��ʼͼƬ���
	UINT16  f;       														// ����ͼƬ���
	UINT16  p_c;     														// ͼƬ����
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
	UINT16 w;       														// ���
	UINT16 h;       														// �߶�
	UINT32 addr;    														// ��FLASH�д洢����ʼλ��
	UINT8 flag;
	UINT8  buf[8][2];       												//�洢ָ��
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
	UINT16 w;       														// ���
	UINT16 h;       														// �߶�
	UINT32 addr;    														// ��FLASH�д洢����ʼλ��
	UINT8  buf[8][2];       												// �洢ָ��
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
	UINT16 x;																	//ͼƬ����x����
	UINT16 y;																	//ͼƬ����y����
	UINT16 t_c;     															// ʱ�����ͳ��
	UINT16 t;       															// ��ʱʱ��
	UINT8  mode;																//ͼƬ����ģʽ�����ϡ����¡���������
	UINT8 operation;															//���ڷ��͵ĵ�2���ֽ���
	UINT16  p_f;     															// ͼƬ���������ص�
	UINT16 p_c;																	//�ڼ���ͼ
	UINT8 start_end;															//0��ʼ����ͼƬ��ͼƬ�ѹ�����
	UINT16 w;																	//ͼƬ���
	UINT16 h;																	//ͼƬ�߶�
	UINT32 addr;																//ͼƬ�ĵ�ַ
}Roll_One;
extern UINT8 gOpenD8;
extern UINT8 rool_one_flag;
extern Roll_One roll_one[];
extern UINT8 roll_one_count;
#endif

#if MODULE_D9
typedef struct
{
	UINT16 x;																	//ͼƬ����x����
	UINT16 y;																	//ͼƬ����y����
	UINT16 t_c;     															// ʱ�����ͳ��
	UINT16 t;       															// ��ʱʱ��
	UINT8  mode;																//ͼƬ����ģʽ�����ϡ����¡���������
	UINT8 sum;																	//ͼƬ����
	UINT8 operation;															//���ڷ��͵ĵ�2���ֽ���
	UINT16  p_f;     															// ͼƬ���������ص�
	UINT8 p_c;																	//�ڼ���ͼ
	UINT16  p[10];   															// ͼƬ�ı��
	UINT16 w;																	//ͼƬ���
	UINT16 h;																	//ͼƬ�߶�
	UINT16 pos;																//ͼƬ����ڻ����λ��
	UINT32 addr;																//ͼƬ�ĵ�ַ
	UINT32 addr_last;															//��һ��ͼƬ�ĵ�ַ
	UINT32 addr_next;															//��һ��ͼƬ�ĵ�ַ
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
	UINT8 mode;    																			//0:����ģʽ  1:ѭ��ģʽ
	UINT8 num;
	UINT8 sum;
	UINT8 pic[10];																			//�洢���ڻ�����ͼƬ���
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
void LT_ReadFlash(UINT8* pBuffer,UINT32 ReadAddr,UINT16 NumByteToRead);				//�����иú�������װ�Ŀ⺯���õ�
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



