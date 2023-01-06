/*
 * function.h
 *
 *  Created on: 2019Äê5ÔÂ14ÈÕ
 *      Author: cjc59
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

#include "LT268A.h"
#include "TFTLCD.h"
#include "w25qxx.h"
#include "bsp.h"

#define color256_black   0x00
#define color256_white   0xff
#define color256_red     0xe0
#define color256_green   0x1c
#define color256_blue    0x03
#define color256_yellow  color256_red|color256_green
#define color256_cyan    color256_green|color256_blue
#define color256_purple  color256_red|color256_blue

#define color65k_black   0x0000
#define color65k_white   0xffff
#define color65k_red     0xf800
#define color65k_green   0x07e0
#define color65k_blue    0x001f
#define color65k_yellow  color65k_red|color65k_green
#define color65k_cyan    color65k_green|color65k_blue
#define color65k_purple  color65k_red|color65k_blue

#define color65k_grayscale1    2113
#define color65k_grayscale2    2113*2
#define color65k_grayscale3    2113*3
#define color65k_grayscale4    2113*4
#define color65k_grayscale5    2113*5
#define color65k_grayscale6    2113*6
#define color65k_grayscale7    2113*7
#define color65k_grayscale8    2113*8
#define color65k_grayscale9    2113*9
#define color65k_grayscale10   2113*10
#define color65k_grayscale11   2113*11
#define color65k_grayscale12   2113*12
#define color65k_grayscale13   2113*13
#define color65k_grayscale14   2113*14
#define color65k_grayscale15   2113*15
#define color65k_grayscale16   2113*16
#define color65k_grayscale17   2113*17
#define color65k_grayscale18   2113*18
#define color65k_grayscale19   2113*19
#define color65k_grayscale20   2113*20
#define color65k_grayscale21   2113*21
#define color65k_grayscale22   2113*22
#define color65k_grayscale23   2113*23
#define color65k_grayscale24   2113*24
#define color65k_grayscale25   2113*25
#define color65k_grayscale26   2113*26
#define color65k_grayscale27   2113*27
#define color65k_grayscale28   2113*28
#define color65k_grayscale29   2113*29
#define color65k_grayscale30   2113*30


#define color16M_black   0x00000000
#define color16M_white   0x00ffffff
#define color16M_red     0x00ff0000
#define color16M_green   0x0000ff00
#define color16M_blue    0x000000ff
#define color16M_yellow  color16M_red|color16M_green
#define color16M_cyan    color16M_green|color16M_blue
#define color16M_purple  color16M_red|color16M_blue


/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Grey           0xF7DE
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


void SPI_Init(void);
void SPI_TransferByte(UINT16 spi0_Tx_data,UINT16 spi1_Tx_data,UINT16 *Rx_data);

void LT268_TFT_DrawPoint(UINT16 x,UINT16 y,UINT16 color);

void LT268_TFT_FillColor(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 color);

void LT268_TFT_DrawLine(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color);

void LT268_TFT_DrawLine_Width(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color,UINT16 Width);

void LT268_TFT_DrawSquare(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color);

void LT268_TFT_DrawSquare_Fill(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color);

void LT268_TFT_DrawSquare_Width(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width);

void LT268_TFT_DrawCircle(UINT16 xc, UINT16 yc, UINT16 r, UINT16 color);

void LT268_TFT_DrawCircle_Fill(UINT16 xc,UINT16 yc,UINT16 r,UINT16 color);

void LT268_TFT_DrawCircle_Width(UINT16 xc, UINT16 yc, UINT16 r,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width);

void LT268_TFT_DrawCircleSquare(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT8 r,UINT16 color);

void LT268_TFT_DrawCircleSquare_Fill(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT8 r,UINT16 color);

void LT268_TFT_DrawCircleSquare_Width(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT8 r,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width);

void LT268_TFT_DrawEllipse(UINT16 x0, UINT16 y0, UINT16 rx, UINT16 ry,UINT16 color);

void LT268_TFT_DrawEllipse_Fill(UINT16 x0,UINT16 y0,UINT16 rx,UINT16 ry,UINT16 color);

void LT268_TFT_DrawEllipse_Width(UINT16 x0, UINT16 y0, UINT16 rx,UINT16 ry,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width);

void LT268_TFT_DrawTriangle(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 x3,UINT16 y3,UINT16 color);

void LT268_TFT_DrawTriangle_Fill(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 x3,UINT16 y3,UINT16 color);

void LT268_TFT_DrawTriangle_Frame(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 x3,UINT16 y3,UINT16 WidthColor,UINT16 BackgroundColor);

UINT8 LT268_TFT_DrawCylinder(UINT16 XCenter,UINT16 YCenter,UINT16 X_R,UINT16 Y_R,UINT16 H,UINT32 CylinderColor,UINT32 ForegroundColor,UINT8 Width);

void LT268_TFT_MakeTable(UINT16 X1,UINT16 Y1,UINT16 W,UINT16 H,UINT16 Line,UINT16 Row,UINT32  TableColor,UINT32  ItemColor,UINT32  ForegroundColor,UINT16 width1,UINT16 width2,UINT8  mode);

void LT268_TFT_ShowNum(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT8 color_flag,UINT32 Addr,UINT16 F_Color,UINT16 B_Color);

void LT268_TFT_ShowChar(UINT16 x,UINT16 y,UINT8 size,UINT8 mode,UINT16 FontColor,UINT16 BackGroundColor,UINT8 num);

void LT268_TFT_ShowFont(UINT16 x,UINT16 y,UINT8 size,UINT8 mode,UINT32 FlashAddr,UINT16 FontColor,UINT16 BackGroundColor,UINT8 *font);

void LT268_TFT_ShowAscll(UINT16 x,UINT16 y,UINT8 size,UINT8 mode,UINT16 FontColor,UINT16 BackGroundColor,UINT8 *str);

void LT268_TFT_ShowString(UINT16 x,UINT16 y,UINT16 w,UINT8 size,UINT8 mode,UINT32 FlashAddr,UINT16 FontColor,UINT16 BackGroundColor,UINT16 String_Length,UINT8*str);

void LT268_Display_ON(void);

void LT268_Display_OFF(void);


#endif /* FUNCTION_H_ */
