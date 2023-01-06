/*
 * function.c
 *
 *  Created on: 2019年5月14日
 *      Author: cjc59
 */
#include "function.h"
#include "iostring.h"
#include <math.h>
#include "SinCosTable.h"
#include "font.h"
#include "levetop.h"
#include "dma.h"


void SPI_Init(void)
{
#if LT268A_SPI
	SPI->U32SPIGPIOCSR.SCMGPIOEN = 0x00;	//All for main funtion
	SPI->U32SPIGPIOCSR.SCMGPIODDR = 0x7F;

	SPI->SPIBR0 = 0x0001;	//18Mhz  //当CS_VARCLK_EN=0，fixed clock=72MHz/2(SPIBR0[15:0] + 1)

	SPI->U32SPCR.CS_CLKP = 0;			//Active-high clock, msck idle low
	SPI->U32SPCR.DW = 0;				// 0 -- 8bits, 1 -- 16bits, 2 -- 24bits, 3 -- 32bits
	SPI->U32SPCR.CS_VARCLK_EN = 0;		//1 = SPI variable clock mode enabled
																	//0 = SPI fixed clock mode enabled
								//00 : SPI0F is set after every completed transfer
								//01 : SPI0F is set after every two completed transfers
								//10 : SPI0F is set after every three completed transfers
								//11 : SPI0F is set after every four completed transfers
	SPI->U32SPCR.ICNT0 = 0;
	SPI->U32SPCR.ICNT1 = 0;
	//双通道发送时，STC=0由channel0控制发送，STC=1由channel1控制发送
	SPI->U32SPCR.STC = 0;	//0 = SPI channel-0 write fifo not empty will start data transfer
								//1 = SPI channel-1 write fifo not empty will start data transfer
	SPI->U32SPCR.SPBROE = 0;
	SPI->U32SPCR.SPLSBFE = 0;		//1 = SPI channel-0 LSB enabled
															//0 = SPI channel-0 MSB enabled
//	SPI->U32SPCR.SPISS0 = 0;		//SS0 = 1
//	SPI->U32SPCR.SPISS1 = 0;		//SS0 = 1

//	SPI->U32SPCR.WFEMPTY0IE = 0;	//0 = SPI channel-0 write fifo empty interrupt Disabled
//
//	SPI->U32SPCR.WCOL0IE = 0;	//0 = SPI channel-0 write fifo overrun interrupt Disabled
//
//	SPI->U32SPCR.RCOL0IE = 0;		//0 = SPI channel-0 read fifo overrun interrupt Disabled
//
//	SPI->U32SPCR.SP0IE = 0;	//0 = SPI channel-0 interrupt disabled

//	SPI->U32SPIDMACR.RXDMAEN0 = 0;
//	SPI->U32SPIDMACR.TXDMAEN0 = 0;

	SPI->U32SPCR.SP0E = 1;	//1 = SPI channel-0 enabled
	SPI->U32SPCR.SP1E = 1;	//1 = SPI channel-0 enabled

	SPI->U32SPCR.GTCS = 0;

	SPI->U32SPCR.GT = 0;

	SPI->SPSR = 0xffffffff;

	SPI->U32SPCR.SPISS0 = 1;
	SPI->U32SPCR.SPISS1 = 1;
#endif

#if LT268A_Data_8
	SPI->U32SPIGPIOCSR.SCMGPIOEN = 0x00;	//All for main funtion
	SPI->U32SPIGPIOCSR.SCMGPIODDR = 0x7F;

	SPI->SPIBR0 = 0x0001;	//18Mhz  //当CS_VARCLK_EN=0，fixed clock=72MHz/2(SPIBR0[15:0] + 1)

	SPI->U32SPCR.CS_CLKP = 0;			//Active-high clock, msck idle low
	SPI->U32SPCR.DW = 0;				// 0 -- 8bits, 1 -- 16bits, 2 -- 24bits, 3 -- 32bits
	SPI->U32SPCR.CS_VARCLK_EN = 0;		//0 = SPI fixed clock mode enabled

	SPI->U32SPCR.ICNT1 = 0;				//0: SPI0F is set after every completed transfer

	SPI->U32SPCR.STC = 1;				//双通道发送时,STC=1由channel1控制发送

	SPI->U32SPCR.SPBROE = 0;
	SPI->U32SPCR.SPLSBFE = 0;		//1 = SPI channel-0 LSB enabled
															//0 = SPI channel-0 MSB enabled
//	SPI->U32SPCR.SPISS0 = 0;		//SS0 = 1
//	SPI->U32SPCR.SPISS1 = 0;		//SS0 = 1

	SPI->U32SPCR.WFEMPTY1IE = 0;	//0 = SPI channel-0 write fifo empty interrupt Disabled

	SPI->U32SPCR.WCOL1IE = 0;	//0 = SPI channel-0 write fifo overrun interrupt Disabled

	SPI->U32SPCR.RCOL1IE = 0;		//0 = SPI channel-0 read fifo overrun interrupt Disabled

	SPI->U32SPCR.SP1IE = 0;	//0 = SPI channel-0 interrupt disabled

	SPI->U32SPIDMACR.RXDMAEN0 = 1;
	SPI->U32SPIDMACR.TXDMAEN0 = 1;

	SPI->U32SPIDMACR.RXDMAEN1 = 1;
	SPI->U32SPIDMACR.TXDMAEN1 = 1;

	SPI->U32SPCR.SP1E = 1;	//1 = SPI channel-0 enabled

	SPI->U32SPCR.SPISS1 = 1;

	LDMA->U32LDMACR3.START3 = 0;   // 关闭LDMA
	LDMA->U32LDMACR3.LBFE3 = 0;    // 右字节开始传输
	LDMA->U32LDMACR3.PTS3 = 1;     // 以字节传输
	LDMA->U32LDMACR3.PS3 = 0;      // SPI写
	LDMA->U32LDMACR3.TD3 = 1;      // 外设到内存
	LDMA->U32LDMACR3.MINC3 = 1;    // 内存递增
	LDMA->U32LDMACR3.CIRC3 = 0;    // 禁止循环模式
//	LDMA->U32LDMACR3.TCIE3 = 1;		// 打开SPI DMA读中断

	LDMA->U32LDMACR4.START4 = 0;   // 关闭LDMA
	LDMA->U32LDMACR4.LBFE4 = 0;    // 右字节开始传输
	LDMA->U32LDMACR4.PTS4 = 1;     // 以字节传输
	LDMA->U32LDMACR4.PS4 = 0;      // SPI读
	LDMA->U32LDMACR4.TD4 = 0;      // 内存到外设
	LDMA->U32LDMACR4.MINC4 = 1;    // 内存递增
	LDMA->U32LDMACR4.CIRC4 = 0;    // 禁止循环模式
//	LDMA->U32LDMACR4.TCIE4 = 1;    // 打开SPI DMA读中断
#endif


	if(LT268_W25QXX_ReadID()==0xef18)      { Flash_Type=1; LT268_W25QXX_4Byte_addr(); } //Nor Flash ( 256bit )
	//else if(W25N01GV_ReadID()==0xefaa21)   Flash_Type=2;                             //Nand Flash
	else	Flash_Type=0;

}

void SPI_TransferByte(UINT16 spi0_Tx_data,UINT16 spi1_Tx_data,UINT16 *Rx_data)
{
	UINT16 temp=0;

	Rx_data[0]=0;
	Rx_data[1]=0;

	SPI->SPSR = 0xffffffff;
	SPI->SPB1R = spi1_Tx_data;
	SPI->SPB0R = spi0_Tx_data;

	while((SPI->U32SPSR.SPI0F)==0);

	Rx_data[0]=SPI->SPB0R;

	temp=SPI->SPB1R;

	Rx_data[1]=(temp<<8)|(temp>>8);
}


//----------------------------------------------------------------------绘图-------------------------------------------------------------------

/*绘点*/
//x,y:坐标
//color:颜色
void LT268_TFT_DrawPoint(UINT16 x,UINT16 y,UINT16 color)
{
	LT268_TFT_SetWindows(x,y,1,1);
	TFT_DataWrite(color>>8);
	TFT_DataWrite(color);
}

/*颜色区域快速填充*/
//x,y:坐标
//Width:宽度
//High:高度
//color:颜色
void LT268_TFT_FillColor(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT16 color)
{
	UINT32 i=0;
#if	LT268A_SPI
	LT268_TFT_SetWindows(x,y,Width,High);

	CS_RESET;
	WriteData_A0;

	for(i=0;i<Width*High;i++)
	{
		SPI0_ReadWriteByte(color>>8);
		SPI0_ReadWriteByte(color);
	}
	CS_SET;
#endif

#if	LT268A_Data_8
	LT268_TFT_SetWindows(x,y,Width,High);

	Data_8_RD_SET;
	WriteData_A0;
	Data_8_CS_RESET;
	for(i=0;i<Width*High;i++)
	{
		EPORT1->EPDR =(color>>8);
		Data_8_WR_RESET;
		Data_8_WR_SET;

		EPORT1->EPDR =(color&0xff);
		Data_8_WR_RESET;
		Data_8_WR_SET;
	}
	Data_8_CS_SET;
#endif
}

/*画线*/
//x1,y1:坐标1
//x2,y2:坐标2
//color:颜色
void LT268_TFT_DrawLine(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color)
{
	UINT16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //计算坐标增量
	delta_y=y2-y1;
	uRow=x1;
	uCol=y1;
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else {incx=-1;delta_x=-delta_x;}

	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//水平线
	else{incy=-1;delta_y=-delta_y;}

	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//画线输出
	{
		LT268_TFT_DrawPoint(uRow,uCol,color);//画点
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}

/*带有宽度的画线*/
//x1,y1:坐标1
//x2,y2:坐标2
//color:颜色
//Width:宽度
void LT268_TFT_DrawLine_Width(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color,UINT16 Width)
{
	unsigned short  i = 0;
	while(Width--)
	{
		LT268_TFT_DrawLine(x1,y1+i,x2,y2+i,color);
		i++;
	}
}

/*画水平线*/
//x0,y0:坐标
//len:线长度
//color:颜色
void LT268_TFT_Draw_hline(UINT16 x0,UINT16 y0,UINT16 len,UINT16 color)
{
	if((len==0)||(x0>LCD_XSIZE_TFT-1)||(y0>LCD_YSIZE_TFT-1))return;
	LT268_TFT_FillColor(x0,y0,len,1,color);
}

/*画垂直线*/
//x0,y0:坐标
//len:线长度
//color:颜色
void LT268_TFT_Draw_vline(UINT16 x0,UINT16 y0,UINT16 len,UINT16 color)
{
	if((len==0)||(x0>LCD_XSIZE_TFT-1)||(y0>LCD_YSIZE_TFT-1))return;
	LT268_TFT_FillColor(x0,y0,1,len,color);
}

/*无填充画矩形*/
//x1,y1:坐标
//x2,y2:坐标
//color:颜色
void LT268_TFT_DrawSquare(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color)
{
	LT268_TFT_DrawLine(x1,y1,x2,y1,color);
	LT268_TFT_DrawLine(x1,y1,x1,y2,color);
	LT268_TFT_DrawLine(x1,y2,x2,y2,color);
	LT268_TFT_DrawLine(x2,y1,x2,y2,color);
}

/*填充画矩形*/
//x1,y1:坐标1
//x2,y2:坐标2
//color:颜色
void LT268_TFT_DrawSquare_Fill(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 color)
{
	UINT16 temp=0;
	if(y1>y2)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(x1>x2)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	LT268_TFT_FillColor(x1,y1,x2-x1+1,y2-y1+1,color);
}

/*有线框的填充画矩形*/
//x1,y1:坐标1
//x2,y2:坐标2
//WidthColor:线框颜色
//BackgroundColor:填充颜色
//Width:线宽
void LT268_TFT_DrawSquare_Width(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width)
{
	UINT16 temp=0;
	if(y1>y2)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(x1>x2)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	LT268_TFT_DrawSquare_Fill(x1-Width,y1-Width,x2+Width,y2+Width,WidthColor);
	LT268_TFT_DrawSquare_Fill(x1,y1,x2,y2,BackgroundColor);
}


void _draw_circle_8(int xc, int yc, int x, int y, UINT16 color)
{
	LT268_TFT_DrawPoint(xc + x, yc + y, color);
	LT268_TFT_DrawPoint(xc - x, yc + y, color);
	LT268_TFT_DrawPoint(xc + x, yc - y, color);
	LT268_TFT_DrawPoint(xc - x, yc - y, color);
	LT268_TFT_DrawPoint(xc + y, yc + x, color);
	LT268_TFT_DrawPoint(xc - y, yc + x, color);
	LT268_TFT_DrawPoint(xc + y, yc - x, color);
	LT268_TFT_DrawPoint(xc - y, yc - x, color);
}

/*无填充画圆*/
//xc,yc:坐标
//r:圆半径
//color:颜色
void LT268_TFT_DrawCircle(UINT16 xc, UINT16 yc, UINT16 r, UINT16 color)
{
	int x = 0, y = r, d;
	d = 3 - 2 * r;

	while (x <= y) {
		_draw_circle_8(xc, yc, x, y, color);
		if (d < 0) {
			d = d + 4 * x + 6;
		} else {
			d = d + 4 * (x - y) + 10;
			y--;
		}
		x++;
	}
}


/*填充画圆*/
//xc,yc:坐标
//r:圆半径
//color:颜色
void LT268_TFT_DrawCircle_Fill(UINT16 xc,UINT16 yc,UINT16 r,UINT16 color)
{
	UINT32 i;
	UINT32 imax = ((UINT32)r*707)/1000+1;
	UINT32 sqmax = (UINT32)r*(UINT32)r+(UINT32)r/2;
	UINT32 x=r;
	LT268_TFT_Draw_hline(xc-r,yc,2*r,color);
	for (i=1;i<=imax;i++)
	{
		if ((i*i+x*x)>sqmax)
		{
			// draw lines from outside
			if (x>imax)
			{
				LT268_TFT_Draw_hline (xc-i+1,yc+x,2*(i-1),color);
				LT268_TFT_Draw_hline (xc-i+1,yc-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)
		LT268_TFT_Draw_hline(xc-x,yc+i,2*x,color);
		LT268_TFT_Draw_hline(xc-x,yc-i,2*x,color);
	}
}

/*带线框的填充画圆*/
//xc,yc:坐标
//r:圆半径
//WidthColor:线框颜色
//BackgroundColor:填充颜色
//Width:线宽
void LT268_TFT_DrawCircle_Width(UINT16 xc, UINT16 yc, UINT16 r,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width)
{
	LT268_TFT_DrawCircle_Fill(xc,yc,r+Width,WidthColor);
	LT268_TFT_DrawCircle_Fill(xc,yc,r,BackgroundColor);
}


//在区域内画点
//(sx,sy),(ex,ey):设定的显示范围
//(x,y):点坐标
//color:颜色
void LT268_TFT_Draw_expoint(UINT16 sx,UINT16 sy,UINT16 ex,UINT16 ey,UINT16 x,UINT16 y,UINT16 color)
{
	if(x<=ex&&x>=sx&&y<=ey&&y>=sy)
	{
		LT268_TFT_DrawPoint(x,y,color);
	}
}
//画8点(Bresenham算法)
//(sx,sy),(ex,ey):设定的显示范围
//(rx,ry,a,b):参数
//color:颜色
void gui_draw_circle8(UINT16 sx,UINT16 sy,UINT16 ex,UINT16 ey,UINT16 rx,UINT16 ry,int a,int b,UINT16 color)
{
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx+a,ry-b,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx+b,ry-a,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx+b,ry+a,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx+a,ry+b,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx-a,ry+b,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx-b,ry+a,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx-b,ry-a,color);
	LT268_TFT_Draw_expoint(sx,sy,ex,ey,rx-a,ry-b,color);
}
//在指定位置画一个指定大小的圆
//rx,ry):圆心
//(sx,sy),(ex,ey):设定的显示范围
//r    :半径
//color:颜色
//mode :0,不填充;1,填充
void gui_draw_arc(UINT16 sx,UINT16 sy,UINT16 ex,UINT16 ey,UINT16 rx,UINT16 ry,UINT16 r,UINT16 color,UINT8 mode)
{
	int a,b,c;
	int di;
	a=0;b=r;
	di=3-(r<<1);	//判断下个点位置的标志
	while(a<=b)
	{
		if(mode)for(c=a;c<=b;c++)gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,c,color);//画实心圆
 		else gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,b,color);					   //画空心圆
		a++;
		//使用Bresenham算法画圆
		if(di<0)di +=4*a+6;
		else
		{
			di+=10+4*(a-b);
			b--;
		}
	}
}

/*无填充画圆角矩形*/
//x1,y1:坐标1
//x2,y2:坐标2
//r:圆角半径
//color:颜色
void LT268_TFT_DrawCircleSquare(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT8 r,UINT16 color)
{
	UINT16 temp;
	UINT16 btnxh=0;
	UINT16 width,height;

	if(y1>y2)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(x1>x2)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}

	width=x2-x1+1;
	height=y2-y1+1;

	if(height%2)btnxh=height+1;//基偶数处理
	else btnxh=height;

	LT268_TFT_Draw_hline(x1+r,y1,width-2*r,color);					//上
	LT268_TFT_Draw_hline(x1+r,y1+btnxh-1,width-2*r,color);			//下
	LT268_TFT_Draw_vline(x1,y1+r,btnxh/2-r,color);					//左上
	LT268_TFT_Draw_vline(x1,y1+btnxh/2,btnxh/2-r,color);			//左下
	LT268_TFT_Draw_vline(x2,y1+r,btnxh/2-r,color);			//右上
	LT268_TFT_Draw_vline(x2,y1+btnxh/2,btnxh/2-r,color);	//右下

	gui_draw_arc(x1,y1,x1+r,y1+r,x1+r,y1+r,r,color,0);//左上
	gui_draw_arc(x1,y1+btnxh-r,x1+r,y1+btnxh-1,x1+r,y1+btnxh-r-1,r,color,0);//左下
	gui_draw_arc(x1+width-r,y1,x1+width,y1+r,x1+width-r-1,y1+r,r,color,0);	 //右上
	gui_draw_arc(x1+width-r,y1+btnxh-r,x1+width,y1+btnxh-1,x1+width-r-1,y1+btnxh-r-1,r,color,0);//右下
}

/*填充画圆角矩形*/
//x1,y1:坐标1
//x2,y2:坐标2
//r:圆角半径
//color:颜色
void LT268_TFT_DrawCircleSquare_Fill(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT8 r,UINT16 color)
{
	UINT16 temp;
	UINT16 btnxh=0;
	UINT16 width,height;

	if(y1>y2)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(x1>x2)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}

	width=x2-x1+1;
	height=y2-y1+1;

	if(height%2)btnxh=height+1;//基偶数处理
	else btnxh=height;

	LT268_TFT_FillColor(x1+r,y1,width-2*r,btnxh/2,color);			//中上
	LT268_TFT_FillColor(x1+r,y1+btnxh/2,width-2*r,btnxh/2,color);	//中下
	LT268_TFT_FillColor(x1,y1+r,r,btnxh/2-r,color);					//左上
	LT268_TFT_FillColor(x1,y1+btnxh/2,r,btnxh/2-r,color);			//左下
	LT268_TFT_FillColor(x1+width-r,y1+r,r,btnxh/2-r,color);			//右上
	LT268_TFT_FillColor(x1+width-r,y1+btnxh/2,r,btnxh/2-r,color);	//右下

	gui_draw_arc(x1,y1,x1+r,y1+r,x1+r,y1+r,r,color,1);//左上
	gui_draw_arc(x1,y1+btnxh-r,x1+r,y1+btnxh-1,x1+r,y1+btnxh-r-1,r,color,1);//左下
	gui_draw_arc(x1+width-r,y1,x1+width,y1+r,x1+width-r-1,y1+r,r,color,1);	 //右上
	gui_draw_arc(x1+width-r,y1+btnxh-r,x1+width,y1+btnxh-1,x1+width-r-1,y1+btnxh-r-1,r,color,1);//右下
}

/*带线框的填充画圆角矩形*/
//x1,y1:坐标1
//x2,y2:坐标2
//r:圆角半径
//WidthColor:线框颜色
//BackgroundColor:填充颜色
//Width:线宽
void LT268_TFT_DrawCircleSquare_Width(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT8 r,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width)
{
	UINT16 temp;
	if(y1>y2)
	{
		temp=y1;
		y1=y2;
		y2=temp;
	}
	if(x1>x2)
	{
		temp=x1;
		x1=x2;
		x2=temp;
	}
	LT268_TFT_DrawCircleSquare_Fill(x1-Width,y1-Width,x2+Width,y2+Width,r,WidthColor);
	LT268_TFT_DrawCircleSquare_Fill(x1,y1,x2,y2,r,BackgroundColor);
}

/*无填充画椭圆*/
//x0,y0:坐标
//rx:x方向半径
//ry:y方向半径
//color:椭圆的颜色
void LT268_TFT_DrawEllipse(UINT16 x0, UINT16 y0, UINT16 rx, UINT16 ry,UINT16 color)
{
	UINT32 OutConst, Sum, SumY;
	UINT16 x,y;
	UINT16 xOld;
	UINT32 _rx = rx;
	UINT32 _ry = ry;
	if(rx>x0||ry>y0)return;//非法.
	OutConst = _rx*_rx*_ry*_ry+(_rx*_rx*_ry>>1);  // Constant as explaint above
	// To compensate for rounding
	xOld = x = rx;
	for (y=0; y<=ry; y++)
	{
		if (y==ry)x=0;
		else
		{
			SumY =((UINT32)(rx*rx))*((UINT32)(y*y)); // Does not change in loop
			while(Sum = SumY + ((UINT32)(ry*ry))*((UINT32)(x*x)),(x>0) && (Sum>OutConst)) x--;
		}
		// Since we draw lines, we can not draw on the first iteration
		if (y)
		{
			LT268_TFT_DrawLine(x0-xOld,y0-y+1,x0-x,y0-y,color);
			LT268_TFT_DrawLine(x0-xOld,y0+y-1,x0-x,y0+y,color);
			LT268_TFT_DrawLine(x0+xOld,y0-y+1,x0+x,y0-y,color);
			LT268_TFT_DrawLine(x0+xOld,y0+y-1,x0+x,y0+y,color);
		}
		xOld = x;
	}
}

/*填充画椭圆*/
//x0,y0:坐标
//rx:x方向半径
//ry:y方向半径
//color:椭圆的颜色
void LT268_TFT_DrawEllipse_Fill(UINT16 x0,UINT16 y0,UINT16 rx,UINT16 ry,UINT16 color)
{
	UINT32 OutConst, Sum, SumY;
	UINT16 x,y;
	UINT32 _rx = rx;
	UINT32 _ry = ry;
	OutConst = _rx*_rx*_ry*_ry+(_rx*_rx*_ry>>1);  // Constant as explaint above
	// To compensate for rounding
	x = rx;
	for (y=0; y<=ry; y++)
	{
		SumY =((UINT32)(rx*rx))*((UINT32)(y*y)); // Does not change in loop
		while (Sum = SumY + ((UINT32)(ry*ry))*((UINT32)(x*x)),(x>0) && (Sum>OutConst))x--;
		LT268_TFT_Draw_hline(x0-x,y0+y,2*x,color);
		if(y)LT268_TFT_Draw_hline(x0-x,y0-y,2*x,color);
	}
}

/*带线框的填充画椭圆*/
//x0,y0:坐标
//rx:x方向半径
//ry:y方向半径
//WidthColor:线框颜色
//BackgroundColor:填充颜色
//Width:线宽
void LT268_TFT_DrawEllipse_Width(UINT16 x0, UINT16 y0, UINT16 rx,UINT16 ry,UINT16 WidthColor,UINT16 BackgroundColor,UINT16 Width)
{
	LT268_TFT_DrawEllipse_Fill(x0,y0,rx+Width,ry+Width,WidthColor);
	LT268_TFT_DrawEllipse_Fill(x0,y0,rx,ry,BackgroundColor);
}

/*无填充画三角形*/
//x1,y1:坐标1
//x2,y2:坐标2
//x3,y3:坐标3
//color:颜色
void LT268_TFT_DrawTriangle(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 x3,UINT16 y3,UINT16 color)
{
	LT268_TFT_DrawLine(x1,y1,x2,y2,color);
	LT268_TFT_DrawLine(x1,y1,x3,y3,color);
	LT268_TFT_DrawLine(x2,y2,x3,y3,color);
}

/*填充画三角形*/
//x1,y1:坐标1
//x2,y2:坐标2
//x3,y3:坐标3
//color:颜色
void LT268_TFT_DrawTriangle_Fill(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 x3,UINT16 y3,UINT16 color)
{
	UINT16 t;
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;

	UINT16 temp;
	if(y1>y2)
	{
		temp=y2;
		y2=y1;
		y1=temp;
		temp=x2;
		x2=x1;
		x1=temp;
	}
	if(y1>y3)
	{
		temp=y3;
		y3=y1;
		y1=temp;
		temp=x3;
		x3=x1;
		x1=temp;
	}
	if(x2>x3)
	{
		temp=x3;
		x3=x2;
		x2=temp;
		temp=y3;
		y3=y2;
		y2=temp;
	}

	delta_x=x3-x2; //计算坐标增量
	delta_y=y3-y2;
	uRow=x2;
	uCol=y2;
	if(delta_x>0)incx=1; //设置单步方向
	else if(delta_x==0)incx=0;//垂直线
	else
	{
		incx=-1;delta_x=-delta_x;
	}

	if(delta_y>0)incy=1;
	else if(delta_y==0)incy=0;//水平线
	else
	{
		incy=-1;delta_y=-delta_y;
	}

	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴
	else distance=delta_y;
	for(t=0;t<=distance+1;t++ )//画线输出
	{
		LT268_TFT_DrawPoint(uRow,uCol,color);//画点
		LT268_TFT_DrawLine(x1,y1,uRow,uCol,color);
		xerr+=delta_x ;
		yerr+=delta_y ;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}


/*带线框的填充画三角形*/
//x1,y1:坐标1
//x2,y2:坐标2
//x3,y3:坐标3
//WidthColor:线框颜色
//BackgroundColor:填充颜色
void LT268_TFT_DrawTriangle_Frame(UINT16 x1,UINT16 y1,UINT16 x2,UINT16 y2,UINT16 x3,UINT16 y3,UINT16 WidthColor,UINT16 BackgroundColor)
{
	LT268_TFT_DrawTriangle_Fill(x1,y1,x2,y2,x3,y3,BackgroundColor);
	LT268_TFT_DrawTriangle(x1,y1,x2,y2,x3,y3,WidthColor);
}

/*画圆柱体*/
//XCenter,YCenter:底圆心坐标
//X_R:x方向半径
//Y_R:y方向半径
//H:高度
//CylinderColor:线框颜色
//ForegroundColor:填充颜色
//Width:线宽
UINT8 LT268_TFT_DrawCylinder(UINT16 XCenter,UINT16 YCenter,UINT16 X_R,UINT16 Y_R,UINT16 H,UINT32 CylinderColor,UINT32 ForegroundColor,UINT8 Width)
{
	UINT8 cut = 0;
	if(YCenter < H)	return 1;
	//底面椭圆
	LT268_TFT_DrawEllipse_Width(XCenter,YCenter,X_R,Y_R,CylinderColor,ForegroundColor,Width);

	//中间矩形
	LT268_TFT_DrawSquare_Fill(XCenter-X_R,YCenter-H,XCenter+X_R,YCenter,ForegroundColor);

	//顶面椭圆
	LT268_TFT_DrawEllipse_Width(XCenter,YCenter-H,X_R,Y_R,CylinderColor,ForegroundColor,Width);

	if(Width >= 1)
	{
		cut = 1;
		LT268_TFT_DrawSquare_Fill(XCenter+X_R+cut,YCenter-H,XCenter+X_R+Width,YCenter,CylinderColor);
		LT268_TFT_DrawSquare_Fill(XCenter-X_R-Width,YCenter-H,XCenter-X_R-cut,YCenter,CylinderColor);
	}
	return 0;
}

/*画表格*/
//X1,Y1:起始坐标
//W:每列宽度
//H:每行高度
//Line:行数
//Row:列数
//TableColor:线框颜色
//ItemColor:项目栏背景色
//ForegroundColor:内部窗口背景色
//width1:内框宽度
//width2:外框宽度
//mode: 0：项目栏纵向   1：项目栏横向
void LT268_TFT_MakeTable(UINT16 X1,UINT16 Y1,UINT16 W,UINT16 H,UINT16 Line,UINT16 Row,UINT32  TableColor,UINT32  ItemColor,UINT32  ForegroundColor,UINT16 width1,UINT16 width2,UINT8  mode)
{
	UINT16 i = 0;
	UINT16 x2,y2;
	x2 = X1 + W * Row;
	y2 = Y1 + H * Line;

	LT268_TFT_DrawSquare_Width(X1,Y1,x2,y2,TableColor,ForegroundColor,width2);

	if(mode == 0)	      LT268_TFT_DrawSquare_Fill(X1,Y1,X1+W,y2,ItemColor);
	else if(mode == 1)	LT268_TFT_DrawSquare_Fill(X1,Y1,x2,Y1+H,ItemColor);

	for(i = 0 ; i < Line ; i++)
	{
		LT268_TFT_DrawLine_Width(X1,Y1+i*H,x2,Y1+i*H,TableColor,width1);
	}

	for(i = 0 ; i < Row ; i++)
	{
		LT268_TFT_DrawLine_Width(X1+i*W,Y1,X1+i*W,y2,TableColor,width1);
	}
}


//----------------------------------------------------------------------图片-------------------------------------------------------------------



//----------------------------------------------------------------------数字图片-------------------------------------------------------------------
/*显示数字图片*/
//x,y:起始坐标
//Width:宽度
//High:高度
//color_flag: 0：背景透明  1：透明不背景
//Addr:数字图片的Flash地址
//F_Color:数字颜色
//B_Color:背景颜色
void LT268_TFT_ShowNum(UINT16 x,UINT16 y,UINT16 Width,UINT16 High,UINT8 color_flag,UINT32 Addr,UINT16 F_Color,UINT16 B_Color)
{
#if	LT268A_SPI
	UINT8 temp,t1,num;
	UINT8 dzk;

	UINT16 t;
	UINT16 x0=x;
	UINT16 csize;
	UINT16 surplus=Width/8+1;

	if(Width%8!=0) csize=(Width/8+1)*8*High/8;
	else csize=Width*High/8;

	for(t=0;t<csize;t++)
	{
		LT_ReadFlash(&dzk,Addr+t,1);
		temp=dzk;			//得到点阵数据

		if(Width%8!=0&&(csize+1)%surplus==0) num=Width%8;          //补足最后8的余数量数据
		else num=8;

		for(t1=0;t1<num;t1++)
		{
			if(temp&0x80)LT268_TFT_DrawPoint(x,y,F_Color);
			else if(color_flag==0)LT268_TFT_DrawPoint(x,y,B_Color);
			temp<<=1;
			x++;
			if((x-x0)==Width)
			{
				x=x0;
				y++;
				break;
			}
		}
	}
#endif

#if	LT268A_Data_8
	UINT8 temp,t1,num;
	UINT16 t;
	UINT16 x0=x;
	UINT8 flag;
	UINT16 csize;
	UINT16 surplus=Width/8+1;

	if(Width%8!=0) csize=(Width/8+1)*8*High/8;
	else csize=Width*High/8;

	SPI->U32SPCR.STC = 1;
	for(t=0;t<csize;t++)
	{
	 	Flash_SS_RESET                            			//使能器件
	    SPI1_ReadWriteByte(W25X_ReadData);         	//发送读取命令
		if(Flash_Type==1)  SPI1_ReadWriteByte((UINT8)(Addr+t>>24)); //发送32bit地址
	    SPI1_ReadWriteByte((UINT8)((Addr+t)>>16));  	//发送24bit地址
	    SPI1_ReadWriteByte((UINT8)((Addr+t)>>8));
	    SPI1_ReadWriteByte((UINT8)(Addr+t));

	    SPI_1_LDMA_Rx_Start((UINT32)&temp,1);
	    SPI_1_LDMA_Tx_Start((UINT32)&temp,1);
	    while(LDMA->U32LDMASR.TCIF3 == 0);	//while(LDMA->U32LDMASR.TCIF4 == 0);
	    LDMA->U32LDMASR.TCIF3 = 1;			//LDMA->U32LDMASR.TCIF4 = 1;

		if(Width%8!=0&&(csize+1)%surplus==0) num=Width%8;          //补足最后8的余数量数据
		else num=8;

	    for(t1=0;t1<num;t1++)
		{
			LT268_TFT_SetWindows(x,y,1,1);
		    WriteData_A0;
		    Data_8_CS_RESET;

			if(temp&0x80)
			{
	    		EPORT1->EPDR =F_Color>>8;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
	    		EPORT1->EPDR =F_Color&0xFF;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
			}
			else if(color_flag==0)
			{
	    		EPORT1->EPDR =B_Color>>8;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
	    		EPORT1->EPDR =B_Color&0xFF;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
			}
			temp<<=1;
			x++;
			if((x-x0)==Width)
			{
				x=x0;
				y++;
				break;
			}
			Data_8_CS_SET;
		}

		Flash_SS_SET
	}


/*
	UINT16 t,t1;
 	UINT16 csize=0,data_w,data_w8;
	UINT8 i,count1=Width/8,count2=Width%8;

	if(Width%8!=0) data_w   = (Width/8+1)*8;
	else  data_w = Width;
	data_w8=data_w/8;
	csize=data_w*High/8;

	LT268_TFT_SetWindows(x,y,Width,High);
	WriteData_A0;
	Data_8_CS_RESET;


 	Flash_SS_RESET                            			//使能器件
    SPI1_ReadWriteByte(W25X_ReadData);         	//发送读取命令
	if(Flash_Type==1)  SPI1_ReadWriteByte((UINT8)(Addr>>24)); //发送32bit地址
    SPI1_ReadWriteByte((UINT8)((Addr)>>16));  	//发送24bit地址
    SPI1_ReadWriteByte((UINT8)((Addr)>>8));
    SPI1_ReadWriteByte((UINT8)(Addr));

    SPI_1_LDMA_Rx_Start((UINT32)DMA_SPI_txbuf,csize);
    SPI_1_LDMA_Tx_Start((UINT32)DMA_SPI_rxbuf1,csize);
    while(LDMA->U32LDMASR.TCIF3 == 0);	//while(LDMA->U32LDMASR.TCIF4 == 0);
    LDMA->U32LDMASR.TCIF3 = 1;			//LDMA->U32LDMASR.TCIF4 = 1;


	for(t=0;t<High;t++)
	{
		for(i=0;i<count1;i++)
		{
		 for(t1=0;t1<8;t1++)
		 {
			if(DMA_SPI_txbuf[i+data_w8*t]&0x80)
			{
	    		EPORT1->EPDR =F_Color>>8;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
	    		EPORT1->EPDR =F_Color&0xFF;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
			}
			else if(color_flag==0)
			{
	    		EPORT1->EPDR =B_Color>>8;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
	    		EPORT1->EPDR =B_Color&0xFF;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
			}
			DMA_SPI_txbuf[i+data_w8*t]<<=1;
		 }
		}
		if(count2!=0)
		{
		 for(t1=0;t1<count2;t1++)
		 {
			if(DMA_SPI_txbuf[i+data_w8*t]&0x80)
			{
	    		EPORT1->EPDR =F_Color>>8;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
	    		EPORT1->EPDR =F_Color&0xFF;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
			}
			else if(color_flag==0)
			{
	    		EPORT1->EPDR =B_Color>>8;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
	    		EPORT1->EPDR =B_Color&0xFF;
	    		Data_8_WR_RESET;
	    		Data_8_WR_SET;
			}
			DMA_SPI_txbuf[i+data_w8*t]<<=1;
		 }
		}
	}
		Data_8_CS_SET;
*/

#endif
}


//----------------------------------------------------------------------字库-------------------------------------------------------------------
/*中文字库编码寻址*/
//code 字符串的开始地址,GBK码
//mat  数据存放地址 (size/8+((size%8)?1:0))*(size) bytes大小
//size:字体大小
//FlashAddr:字库地址
void LT268_TFT_Get_HzMat(unsigned char *code,unsigned char *mat,UINT8 csize,UINT32 FlashAddr)
{
	unsigned char qh,ql;
//	unsigned char i;
	unsigned long foffset;
//	UINT8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数
	qh=*code;
	ql=*(++code);
//	if(qh<0xA1||ql<0xA1||ql==0xff||qh==0xff)//非 常用汉字
//	{
//	    for(i=0;i<csize;i++)*mat++=0x00;//填充满格
//	    return; //结束访问
//	}
//	if(ql<0x7f)ql-=0x40;//注意!
//	else ql-=0x41;
	ql-=0xA1;
	qh-=0xA1;

	foffset=((unsigned long)94*qh+ql)*csize;	//得到字库中的字节偏移量

	LT_ReadFlash(mat,foffset+FlashAddr,csize);
//	switch(size)
//	{
//		case 12:
//			LT268_W25QXX_Read(mat,foffset+FlashAddr,csize);
//			break;
//		case 16:
//			LT268_W25QXX_Read(mat,foffset+FlashAddr,csize);
//			break;
//		case 24:
//			LT268_W25QXX_Read(mat,foffset+FlashAddr,csize);
//			break;
//	}
}


/*显示英文字符*/
//x,y:起始坐标
//size:字体大小
//mode: 0：背景透明  1：透明不背景
//FontColor:字体颜色
//BackGroundColor:背景颜色
//num:字符
void LT268_TFT_Show_Internal_Char(UINT16 x,UINT16 y,UINT8 size,UINT8 mode,UINT16 FontColor,UINT16 BackGroundColor,UINT8 num)
{
	UINT8 temp,t1,t;
	UINT16 y0=y;
	UINT16 ii,jj;
	UINT8 csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
//	printf("csize==%d \r\n",csize);
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）

	t=0;
	if(size==32)
	{
		for(t=0;t<csize;t++)
		{
				for(jj=0;jj<size;jj++)
				{
//					temp=asc2_3216[num][t++];	//调用2412字体
//					for(ii=0;ii<8;ii++)
//					{
//						if(temp&0x80)LT268_TFT_DrawPoint(x+ii,y+jj,FontColor);
//						else if(mode==0)LT268_TFT_DrawPoint(x+ii,y+jj,BackGroundColor);
//
//						temp<<=1;
//					}
//
//					temp=asc2_3216[num][t++];	//调用2412字体
//					for(ii=8;ii<16;ii++)
//					{
//						if(temp&0x80)LT268_TFT_DrawPoint(x+ii,y+jj,FontColor);
//						else if(mode==0)LT268_TFT_DrawPoint(x+ii,y+jj,BackGroundColor);
//
//						temp<<=1;
//					}
				}
		}
	}
	else if(size==16||size==24)
	{
		for(t=0;t<csize;t++)
		{
			if(size==16)  temp=asc2_1608[num][t];	//调用1608字体
			else if(size==24) temp=asc2_2412[num][t];	//调用2412字体
	//		else if(size==32) temp=asc2_3216[num][t];	//调用2412字体
	//		else return;								//没有的字库

			for(t1=0;t1<8;t1++)
			{
				if(temp&0x80)LT268_TFT_DrawPoint(x,y,FontColor);
				else if(mode==0)LT268_TFT_DrawPoint(x,y,BackGroundColor);

				temp<<=1;
				y++;
				if(y>=LCD_YSIZE_TFT)return;		//超区域了
				if((y-y0)==size)
				{
					y=y0;
					x++;
					if(x>=LCD_XSIZE_TFT)return;	//超区域了
					break;
				}
			}
		}
	}
	else return;								//没有的字库
}

//显示一个指定大小的汉字
//x,y :汉字的坐标
//size:字体大小
//mode: 0：背景透明  1：透明不背景
//FlashAddr:字库地址
//FontColor:字体颜色
//BackGroundColor:背景颜色
//font:汉字
void LT268_TFT_Show_Outside_GB2312(UINT16 x,UINT16 y,UINT8 size,UINT8 mode,UINT32 FlashAddr,UINT16 FontColor,UINT16 BackGroundColor,UINT8 *font)
{
	UINT8 temp,t,t1;
	UINT16 x0=x;
	//UINT8 dzk[128];
	UINT8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数
	if(size!=16&&size!=24&&size!=32)return;	//不支持的size
	LT268_TFT_Get_HzMat(font,DMA_SPI_rxbuf1,csize,FlashAddr);	//得到相应大小的点阵数据

//	LT268_TFT_SetWindows(x,y,size,size);  //一个字，只开一次窗
	for(t=0;t<csize;t++)
	{
		temp=DMA_SPI_rxbuf1[t];			//得到点阵数据
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80)LT268_TFT_DrawPoint(x,y,FontColor);
			else if(mode==0)LT268_TFT_DrawPoint(x,y,BackGroundColor);
			temp<<=1;
			x++;
			if((x-x0)==size)
			{
				x=x0;
				y++;
				break;
			}
		}
	}

}

//显示Ascll字符串(内部字符)
//x,y :汉字的坐标
//size:字体大小
//mode: 0：背景透明  1：透明不背景
//FlashAddr:字库地址
//FontColor:字体颜色
//BackGroundColor:背景颜色
//str:字符串
void LT268_TFT_ShowAscll(UINT16 x,UINT16 y,UINT8 size,UINT8 mode,UINT16 FontColor,UINT16 BackGroundColor,UINT8 *str)
{
//	UINT8 x0=x;
    while((*str<='~')&&(*str>=' '))//判断是不是非法字符!
    {
        if(x+size/2>LCD_XSIZE_TFT){x=0;y+=size;}
        if(y+size>LCD_YSIZE_TFT)break;//退出
        LT268_TFT_Show_Internal_Char(x,y,size,mode,FontColor,BackGroundColor,*str);
//        LCD_ShowChar(x,y,*p,size,0);
        x+=size/2;
        str++;
    }
}


//显示一段中英文的字符串
//x,y :汉字的坐标
//size:字体大小
//mode: 0：背景透明  1：透明不背景
//FlashAddr:字库地址
//FontColor:字体颜色
//BackGroundColor:背景颜色
//String_Length:字符串长度
//str:字符串
void LT268_TFT_ShowString(UINT16 x,UINT16 y,UINT16 w,UINT8 size,UINT8 mode,UINT32 FlashAddr,UINT16 FontColor,UINT16 BackGroundColor,UINT16 String_Length,UINT8*str)
{
	UINT16 i=0,temp=0;
	INT16 count = String_Length;
	UINT16 x1=x;
	C0_gNumRow=1;

    while(count>0)//数据未结束
    {
        if(str[i]<0xA1)   //---------内部_ASCII编码--------
        {
                if(x+size/2>x1+w)//换行
				{
					y+=size;
					x=x1;
					C0_gNumRow++;
				}
		        if(str[i]==13)//换行符号
		        {
		            y+=size;
					x=x1;
		            i++;
		            count--;
		            C0_gNumRow++;
		        }
				if(y+size>LCD_YSIZE_TFT)
				{
					C0_gNumRow--;
					break;//越界返回
				}
				else
		        {
		        	LT268_TFT_Show_Internal_Char(x,y,size,mode,FontColor,BackGroundColor,str[i]);//有效部分写入
		        }
				i++;
		        x+=size/2; //字符,为全字的一半
		        count--;
        }
        else          	 //-----外部_GB2312编码-------
        {
			if(x+size>x1+w)//换行
			{
				y+=size;
				x=x1;
				C0_gNumRow++;
			}
			if(y+size>LCD_YSIZE_TFT)
			{
				C0_gNumRow--;
				break;//越界返回
			}
			 LT268_TFT_Show_Outside_GB2312(x,y,size,mode,FlashAddr,FontColor,BackGroundColor,&str[i]); //有效部分写入

			if(str[i]<0xA4)  		//(当前)字符间距
			{
				temp=str[i+1]-0xA0;
				if(size==16)	x+=gb2312_char_16[temp]+7;
				if(size==24)	x+=gb2312_char_24[temp]+6;
				if(size==32)	x+=gb2312_char_32[temp]+1;
			}
			else {x+=size;}			//(当前)中文间距
			i+=2;
			count-=2;
        }
    }
}


//----------------------------------------------------------------------背光-------------------------------------------------------------------
/*打开背光*/
void LT268_Display_ON(void)
{
	TFT_CommandWrite(0x29);
}

/*关闭背光*/
void LT268_Display_OFF(void)
{
	TFT_CommandWrite(0x28);
}

/*显示RGB*/
void disp_V_Gray(void)
{
      int i;
      int w0,w1;
      int h0,h1;

      UINT32 c;

      w0 = LCD_XSIZE_TFT/3;
      w1 = LCD_XSIZE_TFT - w0*2;

      h0 = LCD_YSIZE_TFT/32;
      h1 = LCD_YSIZE_TFT - h0*31;

      for(i=0;i<31;i++)
      {
            c = 31 - i;
            LT268_TFT_DrawSquare_Fill(0,h0*i,w0-1,h0*(i+1),(c<<11)&0xF800);
      }
      c = 0;
      LT268_TFT_DrawSquare_Fill(0,h0*31,w0-1,LCD_YSIZE_TFT-1,c);


      h0 = LCD_YSIZE_TFT/64;
      h1 = LCD_YSIZE_TFT - h0*63;
      for(i=0;i<63;i++)
      {
            c = 63 - i;
            LT268_TFT_DrawSquare_Fill(w0,h0*i,w0*2-1,h0*(i+1),(c<<5)&0x7E0);
      }
      c = 0;
      LT268_TFT_DrawSquare_Fill(w0,h0*63,w0*2-1,LCD_YSIZE_TFT-1,c);


      h0 = LCD_YSIZE_TFT/32;
      h1 = LCD_YSIZE_TFT - h0*31;

      for(i=0;i<31;i++)
      {
            c = 31 - i;
            LT268_TFT_DrawSquare_Fill(w0*2,h0*i,LCD_XSIZE_TFT-1,h0*(i+1),c&0x1F);
      }
      c = 0;
      LT268_TFT_DrawSquare_Fill(w0*2,h0*31,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,c);

}


void Send(char *c)         //发送命令函数
{

	unsigned char Sendbuff[100]={0};
	unsigned short Send_CRC = 0;
	unsigned char C_flag = 0;	        //判断是否在" "中

	int i = 0, j = 0;

	if(((c[0]>=0x30 && c[0]<=0x39) || (c[0]>=0x41 && c[0]<=0x5A))  ||  ((c[1]>=0x30 && c[1]<=0x39) || (c[1]>=0x41 && c[1]<=0x5A)))     //只有第一个和第二个字符是有效的才是命令
	{
		while(c[i] != '\0')
		{
			if(c[i] != ' ')                            //排除空格，非空格可以进入
			{
				if(c[i] == '"')							//当" "中的字符 以ASCII输出，不需要输出" 号，
				{
					C_flag++;
					i++;
				}
				if(C_flag == 1)
				{
					if(c[i] != '"')
					{
						Sendbuff[j] = c[i];    //ASCII 直接输出
						i++;
						j++;
					}

				}
				else if(C_flag == 2)    //第二次遇到"
				{
					C_flag = 0;
					i++;
				}
				if(C_flag == 0)
				{
					if(c[i] == '/') break;

					if(c[i]>=0x30 && c[i]<=0x39) //0~9
					{
						Sendbuff[j] = ((c[i] - 0x30)<< 4 );
						i++;

						if(c[i]>=0x30 && c[i]<=0x39)
						{
							Sendbuff[j] += (c[i] - 0x30);
							i++;
							j++;
						}
						else if(c[i]>=0x41 && c[i]<=0x5A)
						{
							Sendbuff[j] += (c[i] - 0x37);
							i++;
							j++;
						}
					}
					else if(c[i]>=0x41 && c[i]<=0x5A) //A~Z
					{
						Sendbuff[j] = ((c[i] - 0x37)<< 4 );
						i++;

						if(c[i]>=0x30 && c[i]<=0x39)
						{
							Sendbuff[j] += (c[i] - 0x30);
							i++;
							j++;
						}
						else if(c[i]>=0x41 && c[i]<=0x5A)
						{
							Sendbuff[j] += (c[i] - 0x37);
							i++;
							j++;
						}

					}
				}
			}
			else i++;
		}
		Sendbuff[j] = '\0';
//		printf("%s\r\n",Sendbuff);

		///***********************CRC和针头针尾***********************
		Send_CRC = Rx_CRC_CCITT(Sendbuff,j);

		Sendbuff[j] = Send_CRC>>8 & 0xff;
		Sendbuff[j+1] = Send_CRC & 0xff;

		for(i = 0;i<j+2;i++)
			Sendbuff[j+2-i]=Sendbuff[j+1-i];      //挪位

		Sendbuff[0] = 0xAA;
		Sendbuff[j+3] = 0xE4;
		Sendbuff[j+4] = 0x1B;
		Sendbuff[j+5] = 0x11;
		Sendbuff[j+6] = 0xEE;

		j+=7;

		for(i = 0; i < j; i++)
		 {
		gUsartRx.Buf[i] = Sendbuff[i];
//		LTPrintf("sendbuff ==%x\r\n",Sendbuff[i]);
		 }
		gUsartRx.Count=j;
	    LT_ReceiveCmd(gUsartRx.Buf);

	}

}

//int main (void)
//{
//	char c[] = "80 00";
//	Send(c);
//
//	while(1);
//
//}
