#include "tp.h"
#include "bsp.h"
//#include "eport_lib.h"
//#include "misc.h"
#include "math.h"
#include "data.h"
#include "w25qxx.h"
#include "pwm.h"
#include "function.h"
#include "delay.h"

//X+:AIN[4]
//X-:AIN[6]
//Y+:AIN[5]
//Y-:AIN[7]

UINT8 Yp_Pulldown_Flag=1;
UINT8 RTP_read_Flag=0;
UINT16 RTP_time=0;

void ADC_Init(void)
{
	CLOCK->U32SYNCR.SYNCTEST = 1;
	CLOCK->U32SYNCR.SYNCTEST = 2;
	CLOCK->U32SYNCR.SYNCTEST = 3;
	CLOCK->U32SYNCR.ADCDIV= 12-1;				//72MHz/12=6MHz

	ADC->U32CFGR2.QPR = 12-1;         	 		//6MHz/12=500kHz
	ADC->U32CFGR2.STCNT = 2*72/12/12; 			// 启动计数位

	ADC->U32CFGR1.CONT = 0;						//不连续转换
	ADC->U32CFGR1.SEQ_LEN = 1-1;				//序列长度为1单位
	ADC->U32CFGR1.RES = 0;						//分辨率:12
	ADC->U32CFGR1.ALIGN = 0;					//右对齐
//	ADC->U32CHSELR1.CCW0 = ADC_Channel_x;					//X+:AIN[4]

	ADC->U32SMPR.SMP = 4-2;						//采样时间

	ADC->U32CR.ADEN = 1;						//使能ADC

	while(ADC->U32ISR.ADRDY != 1);					//等待转换准备
}

UINT16 Get_ADC_Val(UINT8 ADC_Channel_x)
{
	UINT16 Val = 0;

	ADC->U32CHSELR1.CCW0 = ADC_Channel_x;
	ADC->U32CR.ADSTART = 1;     // 启动转换
	while(ADC->U32ISR.EOC != 1);
	ADC->U32ISR.EOC= 1;		//清标志
	Val = ADC->FIFO;

	Delay_us(30);

	return Val;
}

//X+:AIN[4]
//X-:AIN[6]
//Y+:AIN[5]
//Y-:AIN[7]

 UINT8  TP_IF_PenDown(void)
{
	UINT16 ain7_Value;
	//need to configure corresponding port as GPIO first
	EFM->U16ADCCDISR.ADCCDISTEST = 1;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 2;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 3;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDIS =((0x02)|(0x04)|(0x08));	//AIN4,AIN6,AIN5 GPIO; AINT7 ADC

	EPORT0->EPDDR &= 0x0F;
	EPORT0->EPDDR |=((1<<4)|(1<<6));	//X+,X- 配置为GPIO输出

	EPORT0->U8EPDR.int4 = 0;			//X+配置为低电平
	EPORT0->U8EPDR.int6 = 0;			//X-配置为低电平

	EPORT0->EPDDR &=~(1<<5);			//Y+配置为GPIO输入
	EPORT0->EPPUE |= (1<<5);			//Y+配置为上拉

	Delay_ms(2);

	ain7_Value = Get_ADC_Val(7);

//	LTPrintf("AIN7=%d\n",ain7_Value);

	if(ain7_Value<3200)
	{
		return 0;
	}
	else return 1;

}


//void Int05_Handler(void)
//{
//	//EIC->IE_EPORT0 &= ~(1<<7);
//	EIC->IER &= ~IRQ(21);					//打开外部中断向量
//
//	EPORT0->EPIER &= ~(1<<5);			//取消外部中断
//	EPORT0->EPFR |= (1<<5);				//清中断
//	//do something here
//	Yp_Pulldown_Flag=0;
//	LTPrintf("in\r\n");
//
//}



//X+:AIN[4]
//X-:AIN[6]
//Y+:AIN[5]
//Y-:AIN[7]




UINT16 TP_ReadX_Ver(void)
{
	UINT16 xValue0;
	UINT16 tmpX;

	//need to configure corresponding port as GPIO first
	EFM->U16ADCCDISR.ADCCDISTEST = 1;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 2;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 3;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDIS =((0x02)|(0x08));
	//EFM->U16ADCCDISR.ADCCDIS &=~(1<<2);

	//EPORT0->EPDDR &= 0x0F;
	EPORT0->EPDDR |= (1<<4)|(1<<6);		//X+,X- 配置为GPIO输出
	EPORT0->U8EPDR.int4 = 1;				//X+配置为高电平
	EPORT0->U8EPDR.int6 = 0;				//X-配置为低电平

	Delay_ms(1);

	xValue0 =Get_ADC_Val(5);
	xValue0+=Get_ADC_Val(7);
	xValue0+=Get_ADC_Val(5);
	xValue0+=Get_ADC_Val(7);
	xValue0+=Get_ADC_Val(5);
	xValue0+=Get_ADC_Val(7);

	tmpX= xValue0/6;

	return tmpX;
}

UINT16 TP_ReadY_Ver(void)
{
	UINT16 yValue0;
	UINT16 tmpY;

	//YP_GPIO_Init();
	EFM->U16ADCCDISR.ADCCDISTEST = 1;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 2;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 3;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDIS =((0x04)|(0x10));
	//EFM->U16ADCCDISR.ADCCDIS &=~(1<<1);

	//EPORT0->EPDDR &= 0x0F;
	EPORT0->EPDDR |= (1<<5)|(1<<7);		//Y+,Y- 配置为GPIO输出
	EPORT0->U8EPDR.int5 = 0;			//Y+配置为高电平
	EPORT0->U8EPDR.int7 = 1;			//Y-配置为低电平
	Delay_ms(1);

	yValue0 =Get_ADC_Val(4);
	yValue0+=Get_ADC_Val(6);
	yValue0+=Get_ADC_Val(4);
	yValue0+=Get_ADC_Val(6);
	yValue0+=Get_ADC_Val(4);
	yValue0+=Get_ADC_Val(6);

	tmpY= yValue0/6;

	return tmpY;
}

UINT16 TP_ReadX_Hor(void)
{
	UINT16 xValue0;
	UINT16 tmpX;

	//YP_GPIO_Init();
	EFM->U16ADCCDISR.ADCCDISTEST = 1;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 2;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 3;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDIS =((0x04)|(0x10));
	//EFM->U16ADCCDISR.ADCCDIS &=~(1<<1);

	//EPORT0->EPDDR &= 0x0F;
	EPORT0->EPDDR |= (1<<5)|(1<<7);		//Y+,Y- 配置为GPIO输出
	EPORT0->U8EPDR.int5 = 1;			//Y+配置为高电平
	EPORT0->U8EPDR.int7 = 0;			//Y-配置为低电平
	Delay_ms(1);

	xValue0 =Get_ADC_Val(4);
	xValue0+=Get_ADC_Val(6);
	xValue0+=Get_ADC_Val(4);
	xValue0+=Get_ADC_Val(6);
	xValue0+=Get_ADC_Val(4);
	xValue0+=Get_ADC_Val(6);

	tmpX= xValue0/6;

	return tmpX;
}

UINT16 TP_ReadY_Hor(void)
{
	UINT16 yValue0;
	UINT16 tmpY;

	//need to configure corresponding port as GPIO first
	EFM->U16ADCCDISR.ADCCDISTEST = 1;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 2;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDISTEST = 3;
	//for(k=0;k<20;k++);
	EFM->U16ADCCDISR.ADCCDIS =((0x02)|(0x08));
	//EFM->U16ADCCDISR.ADCCDIS &=~(1<<2);

	//EPORT0->EPDDR &= 0x0F;
	EPORT0->EPDDR |= (1<<4)|(1<<6);		//X+,X- 配置为GPIO输出
	EPORT0->U8EPDR.int4 = 1;				//X+配置为高电平
	EPORT0->U8EPDR.int6 = 0;				//X-配置为低电平

	Delay_ms(1);

	yValue0 =Get_ADC_Val(5);
	yValue0+=Get_ADC_Val(7);
	yValue0+=Get_ADC_Val(5);
	yValue0+=Get_ADC_Val(7);
	yValue0+=Get_ADC_Val(5);
	yValue0+=Get_ADC_Val(7);

	tmpY= yValue0/6;

	return tmpY;
}



void LT_TpDelay(void)
{
	UINT8 t = 1;
	while(t--)
	{
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");
		asm("nop");

	}
}

UINT8 LT_TpInit(void)
{
	UINT8 i=0;
	UINT32 tmp;
//	tmp=EIC->IER;
//	EIC->IER=0;
//	for(i=0;i<WBUF_NUM;i++) IO_WRITE32(0x00801F00+i*4,EFM_WAIT_BUF[i]);
//	EIC->IER=tmp;
//
//	ADC_Init();
//	Delay_ms(10);
//
//	if(LT_TpGetAdjdata()!=1)
//	{
//		Delay_ms(100);
//		LCD_BL_Init(400);			//背光初始化
//		//LT_TpAdjust();
//	}
	gTpInfo.scan = LT_TpScan;

	return 1;
}



//SPI写数据
//向触摸屏IC写入1byte数据    
//num:要写入的数据
void TP_Write_Byte(UINT8 num)
{  
	UINT8 count=0;
	for(count=0;count<8;count++)  
	{ 	  
		if(num&0x80) {TDIN=1;}
		else        { TDIN=0;}
		num<<=1;    
		TCLK=0;
		LT_TpDelay();
		TCLK=1;
	}		 			    
}


//SPI读数据 
//从触摸屏IC读取adc值
//CMD:指令
//返回值:读到的数据	   
UINT16 TP_Read_AD(UINT8 CMD)
{ 	 
	UINT8 count=0;
	UINT16 Num=0;
	TCLK=0;		//先拉低时钟
	TDIN=0; 	//拉低数据线
	TCS=0; 		//选中触摸屏IC
	TP_Write_Byte(CMD);//发送命令字
	LT_TpDelay();//ADS7846的转换时间最长为6us
	TCLK=0;
	LT_TpDelay();
	TCLK=1;		//给1个时钟，清除BUSY
	LT_TpDelay();
	TCLK=0;
	for(count=0;count<16;count++)//读出16位数据,只有高12位有效 
	{ 				  
		Num<<=1; 	 
		TCLK=0;	//下降沿有效
		LT_TpDelay();
 		TCLK=1;
 		if(DOUT)Num++;
	}  	
	Num>>=4;   	//只有高12位有效.
	TCS=1;		//释放片选
	return(Num);   
}

//读取一个坐标值(x或者y)
//连续读取READ_TIMES次数据,对这些数据升序排列,
//然后去掉最低和最高LOST_VAL个数,取平均值 
//xy:指令（CMD_RDX/CMD_RDY）
//返回值:读到的数据
#define READ_TIMES 20 	  //读取次数
#define LOST_VAL 2	  	//丢弃值
UINT16 TP_Read_XOY(UINT8 xy)
{
	UINT16 i, j;
	UINT16 buf[READ_TIMES];
	UINT16 sum=0;
	UINT16 temp;
	for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);		 		    
	for(i=0;i<READ_TIMES-1; i++)//排序
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//升序排列
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);

	return temp;   
} 

//读取x,y坐标
//x,y:读取到的坐标值
UINT8 TP_Read_XY(UINT16 *x,UINT16 *y)
{
#if Horizontal_screen
	*x=TP_ReadX_Hor();//TP_Read_XOY(CMD_RDX);
	*y=TP_ReadY_Hor();//TP_Read_XOY(CMD_RDY);
#else
	*x=TP_ReadX_Ver();
	*y=TP_ReadY_Ver();
#endif

//	LTPrintf("XAD:%d  ",*x);
//	LTPrintf("YAD:%d\r\n\r\n",*y);
	if(*x>4095||*y>4095)	return 0;//读数失败
	return 1;
}

//连续2次读取触摸屏IC,且这两次的偏差不能超过
//ERR_RANGE,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
//x,y:读取到的坐标值
//返回值:0,失败;1,成功。
#define ERR_RANGE 50 //误差范围 
UINT8 TP_Read_XY2(UINT16 *x,UINT16 *y)
{
	UINT16 x1,y1;
 	UINT16 x2,y2;
 	UINT8 flag;

	flag=TP_Read_XY(&x1,&y1);   
	if(flag==0)return(0);
	flag=TP_Read_XY(&x2,&y2);
	if(flag==0)return(0);   

//	LTPrintf("X:%d  ",*x);
//	LTPrintf("Y:%d\r\n\r\n",*y);

	if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))&&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))//前后两次采样在+-50内
	{
		*x=(x1+x2)/2;
		*y=(y1+y2)/2;
//		LTPrintf("X:%d\r\n",*x);
//		LTPrintf("Y:%d\r\n",*y);
			return 1;
	}
	else 
	{
		return 0;
	}
} 


//显示校正点
void LT_TpDrawTouchPoint(UINT16 x,UINT16 y,UINT32 color)
{
	LT268_TFT_DrawLine(x-12,y,x+13,y,color); //横线
	LT268_TFT_DrawLine(x,y-12,x,y+13,color); //竖线
	LT268_TFT_DrawCircle(x,y,6,color);       //画中心圈
}

//保存校准参数
void LT_TpSaveAdjdata(void)
{

	gTpInfo.flag=0x5a;
	EFM_init(); //初始化 FLASH
	EFM_EFlashSectorErase(127); //擦除第 127 个 FLASH 扇区
	FLASH_ProgramWord(0xFE00,gTpInfo.flag);
	FLASH_ProgramWord(0xFE00+20,gTpxfac.s[0]);
	FLASH_ProgramWord(0xFE00+24,gTpxfac.s[1]);
	FLASH_ProgramWord(0xFE00+28,gTpxfac.s[2]);
	FLASH_ProgramWord(0xFE00+32,gTpxfac.s[3]);//xfac

	FLASH_ProgramWord(0xFE00+36,gTpxoff.s[0]);
	FLASH_ProgramWord(0xFE00+40,gTpxoff.s[1]);
	FLASH_ProgramWord(0xFE00+44,gTpxoff.s[2]);
	FLASH_ProgramWord(0xFE00+48,gTpxoff.s[3]);//xoff

	FLASH_ProgramWord(0xFE00+52,gTpyfac.s[0]);
	FLASH_ProgramWord(0xFE00+56,gTpyfac.s[1]);
	FLASH_ProgramWord(0xFE00+60,gTpyfac.s[2]);
	FLASH_ProgramWord(0xFE00+64,gTpyfac.s[3]);//yfac

	FLASH_ProgramWord(0xFE00+68,gTpyoff.s[0]);
	FLASH_ProgramWord(0xFE00+72,gTpyoff.s[1]);
	FLASH_ProgramWord(0xFE00+76,gTpyoff.s[2]);
	FLASH_ProgramWord(0xFE00+80,gTpyoff.s[3]);//yoff

}

//读取校准参数
UINT8 LT_TpGetAdjdata(void)
{

	gTpxfac.s[0]=IO_READ32(0xFE00+20);
	gTpxfac.s[1]=IO_READ32(0xFE00+24);
	gTpxfac.s[2]=IO_READ32(0xFE00+28);
	gTpxfac.s[3]=IO_READ32(0xFE00+32);

	gTpxoff.s[0]=IO_READ32(0xFE00+36);
	gTpxoff.s[1]=IO_READ32(0xFE00+40);
	gTpxoff.s[2]=IO_READ32(0xFE00+44);
	gTpxoff.s[3]=IO_READ32(0xFE00+48);

	gTpyfac.s[0]=IO_READ32(0xFE00+52);
	gTpyfac.s[1]=IO_READ32(0xFE00+56);
	gTpyfac.s[2]=IO_READ32(0xFE00+60);
	gTpyfac.s[3]=IO_READ32(0xFE00+64);

	gTpyoff.s[0]=IO_READ32(0xFE00+68);
	gTpyoff.s[1]=IO_READ32(0xFE00+72);
	gTpyoff.s[2]=IO_READ32(0xFE00+76);
	gTpyoff.s[3]=IO_READ32(0xFE00+80);

	if(IO_READ32(0xFE00)==0x5a)
		{
		gTpxfac.s[0]=IO_READ32(0xFE00+20);
		gTpxfac.s[1]=IO_READ32(0xFE00+24);
		gTpxfac.s[2]=IO_READ32(0xFE00+28);
		gTpxfac.s[3]=IO_READ32(0xFE00+32);

		gTpxoff.s[0]=IO_READ32(0xFE00+36);
		gTpxoff.s[1]=IO_READ32(0xFE00+40);
		gTpxoff.s[2]=IO_READ32(0xFE00+44);
		gTpxoff.s[3]=IO_READ32(0xFE00+48);

		gTpyfac.s[0]=IO_READ32(0xFE00+52);
		gTpyfac.s[1]=IO_READ32(0xFE00+56);
		gTpyfac.s[2]=IO_READ32(0xFE00+60);
		gTpyfac.s[3]=IO_READ32(0xFE00+64);

		gTpyoff.s[0]=IO_READ32(0xFE00+68);
		gTpyoff.s[1]=IO_READ32(0xFE00+72);
		gTpyoff.s[2]=IO_READ32(0xFE00+76);
		gTpyoff.s[3]=IO_READ32(0xFE00+80);

		gTpInfo.xfac=gTpxfac.xfac;
		gTpInfo.xoff=gTpxoff.xoff;
		gTpInfo.yfac=gTpyfac.yfac;
		gTpInfo.yoff=gTpyoff.yoff;
		return 1;
		}
	else										return 0;
}

//扫描TP
//返回：1->触摸  0->无触摸
UINT8 LT_TpScan(void)
{

//	Yp_Pulldown_Flag = TP_IF_PenDown();
//
//	if(Yp_Pulldown_Flag==0 && RTP_read_Flag==0)
//	{
//		RTP_time=0;
//		RTP_read_Flag=1;
//
////		TP_Read_XY2(&gTpInfo.px,&gTpInfo.py);
//		if(	TP_Read_XY2(&gTpInfo.px,&gTpInfo.py))
//		{
//			gTpInfo.x[1] = gTpInfo.xfac * gTpInfo.px + gTpInfo.xoff;
//			gTpInfo.y[1] = gTpInfo.yfac * gTpInfo.py + gTpInfo.yoff;
//
//		}
//		if(gTpInfo.x[1]>LCD_XSIZE_TFT)	gTpInfo.x[1] = LCD_XSIZE_TFT;
//		if(gTpInfo.y[1]>LCD_YSIZE_TFT)	gTpInfo.y[1] = LCD_YSIZE_TFT;
//
//		if(gTpInfo.x[1]==0 &&(gTpInfo.y[1]==320||gTpInfo.y[1]==319))  { return 0; }//松手瞬间坐标丢失
//
//		if(First_press==0)
//		{
//			First_press=1;
//			First_pressX= gTpInfo.x[1];
//			First_pressY= gTpInfo.y[1];
//		}
//
//		gTpInfo.x[0] = gTpInfo.x[1];
//		gTpInfo.y[0] = gTpInfo.y[1];
//				//LTPrintf("X0: %d   Y0:  %d  \r\n",First_pressX,First_pressY);
//				//LTPrintf("X: %d   Y:  %d  \r\n",gTpInfo.x[0],gTpInfo.y[0]);
//
//		if(gTpInfo.sta == 0)	gTpInfo.sta = 1;
//
//		return 1;
// 	}
//	else if(RTP_read_Flag)
//	{
//		return 0;
//	}
//	else
//	{
//		First_press=0;
//		RTP_read_Flag=0;
//		gTpInfo.sta = 0;
		return 0;   
//	}
}

//提示字符串
UINT8* const TP_REMIND_MSG_TBL=(UINT8 *)"Please correct the resistance screen";


//触摸屏校准代码
//得到四个校准参数
UINT8 LT_TpAdjust(void)
{
	UINT8 cnt = 0;
	UINT16 outTime = 0;
	UINT16 d1,d2;
	UINT32 temp1,temp2;
	UINT16 posTemp[2][4] ;
	float fac;

	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
	LT268_TFT_ShowAscll(40,40,24,1,Red,Red,(UINT8*)"Please correct the resistance screen");

	LT_TpDrawTouchPoint(20,20,Red);
	Delay_ms(100);

	while(1)
	{
		LT_TpScan();

//		LTPrintf("sta:%d\r\n",gTpInfo.sta);
//		Delay_ms(140);

		if(gTpInfo.sta)
		{

			outTime = 0;
			gTpInfo.sta = 0;

			posTemp[0][cnt] = gTpInfo.px;
			posTemp[1][cnt] = gTpInfo.py;
			cnt++;
//			LTPrintf("cnt:%d\r\n",cnt);
			switch(cnt)
			{
				case 1:	LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
								LT_TpDrawTouchPoint(LCD_XSIZE_TFT-20,20,Red);

								break;

				case 2: LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
								LT_TpDrawTouchPoint(20,LCD_YSIZE_TFT-20,Red);

								break;

				case 3: LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
								LT_TpDrawTouchPoint(LCD_XSIZE_TFT-20,LCD_YSIZE_TFT-20,Red);

								break;

				case 4: //计算上下两条边长的比例
								temp1=abs(posTemp[0][0]-posTemp[0][1]);
								temp2=abs(posTemp[1][0]-posTemp[1][1]);
								temp1*=temp1;
								temp2*=temp2;
								d1=sqrt(temp1+temp2);

				        temp1=abs(posTemp[0][2]-posTemp[0][3]);
								temp2=abs(posTemp[1][2]-posTemp[1][3]);
								temp1*=temp1;
								temp2*=temp2;
								d2=sqrt(temp1+temp2);
								fac = (float)d1/d2;

								if(fac<0.85f||fac>1.15f||d1==0||d2==0)
								{
									cnt=0;
									LT_TpDrawTouchPoint(LCD_XSIZE_TFT-20,LCD_YSIZE_TFT-20,White);
									LT_TpDrawTouchPoint(20,20,Red);
									LT268_TFT_ShowAscll(40,40,24,1,Red,Red,(UINT8*)"Check Failure,Please recheck!");
									continue;
								}

								//计算左右两条边长的比例
								temp1=abs(posTemp[0][0]-posTemp[0][2]);
								temp2=abs(posTemp[1][0]-posTemp[1][2]);
								temp1*=temp1;
								temp2*=temp2;
								d1=sqrt(temp1+temp2);

				        temp1=abs(posTemp[0][1]-posTemp[0][3]);
								temp2=abs(posTemp[1][1]-posTemp[1][3]);
								temp1*=temp1;
								temp2*=temp2;
								d2=sqrt(temp1+temp2);

//								LTPrintf("fac:%d \r\n",fac);
								if(fac<0.85f||fac>1.15f||d1==0||d2==0)
								{
									cnt=0;
									LT_TpDrawTouchPoint(LCD_XSIZE_TFT-20,LCD_YSIZE_TFT-20,White);
									LT_TpDrawTouchPoint(20,20,Red);
									LT268_TFT_ShowAscll(40,40,24,1,Red,Red,(UINT8*)"Check Failure,Please recheck!");
									continue;
								}

								//计算对边长度的比例
						temp1=abs(posTemp[0][0]-posTemp[0][3]);
								temp2=abs(posTemp[1][0]-posTemp[1][3]);
								temp1*=temp1;
								temp2*=temp2;
								d1=sqrt(temp1+temp2);

								temp1=abs(posTemp[0][1]-posTemp[0][2]);
								temp2=abs(posTemp[1][1]-posTemp[1][2]);
								temp1*=temp1;
								temp2*=temp2;
								d2=sqrt(temp1+temp2);

								fac = (float)d1/d2;

								if(fac<0.85f||fac>1.15f||d1==0||d2==0)    //不合格
								{
									cnt=0;
									LT_TpDrawTouchPoint(LCD_XSIZE_TFT-20,LCD_YSIZE_TFT-20,White);
									LT_TpDrawTouchPoint(20,20,Red);
									LT268_TFT_ShowAscll(40,40,24,1,Red,Red,(UINT8*)"Check Failure,Please recheck!");
									continue;
								}

								//上下两边比例、左右两边比例、对角边的比例，都在范围内，则4个校正点符合要求
								gTpInfo.xfac=(float)(LCD_XSIZE_TFT-40)/(posTemp[0][1]-posTemp[0][0]);
								gTpInfo.xoff=(LCD_XSIZE_TFT-gTpInfo.xfac*(posTemp[0][1]+posTemp[0][0]))/2;
								gTpInfo.yfac=(float)(LCD_YSIZE_TFT-40)/(posTemp[1][2]-posTemp[1][0]);
								gTpInfo.yoff=(LCD_YSIZE_TFT-gTpInfo.yfac*(posTemp[1][2]+posTemp[1][0]))/2;

									gTpxfac.xfac=gTpInfo.xfac;
									gTpxoff.xoff=gTpInfo.xoff;
									gTpyfac.yfac=gTpInfo.yfac;
									gTpyoff.yoff=gTpInfo.yoff;

								LT268_TFT_DrawSquare_Fill(0,0,LCD_XSIZE_TFT-1,LCD_YSIZE_TFT-1,White);
								LT268_TFT_ShowAscll(40,40,24,1,Red,Red,(UINT8*)"Touch Screen Adjust OK!");//校正成功

								//保存4个参数
								LT_TpSaveAdjdata();
								Delay_ms(1000);

								return 1;
			}
		}
		Delay_ms(150);

		outTime++;
//		if(outTime>1000)
//		{
//			//获取之前保存的4个参数
//			LT_TpGetAdjdata();
//			return 1;
//		}
	}

}


