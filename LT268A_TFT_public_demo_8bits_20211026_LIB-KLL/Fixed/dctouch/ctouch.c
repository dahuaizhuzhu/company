#include "ctouch.h"
#include "delay.h"
#include "data.h"

#if !R_TOUCH_FLAG

#define     SDA_High                  EPORT0->U8EPDR.int6=1
#define     SDA_Low                   EPORT0->U8EPDR.int6=0
#define     SCL_High                  EPORT0->U8EPDR.int7=1
#define     SCL_Low                   EPORT0->U8EPDR.int7=0
//#define     GetSDABit                 (EPORT0->EPPDR&0x40)
UINT8 GetSDABit(void)
{
	if(EPORT0->EPPDR&0x40)
			return 1;
	else 	return 0;
}

UINT8 Ctp_INT_DN_Index=0, Ctp_INT_Active=0, Ctp_INT_OverTime=0;

UINT8 READ_BUFF[128];
UINT8 WRITE_BUFF[20];
UINT8  fingerNumber =0;
UINT8  tp_event =0; //0x00-����  0x40��̧��  0x80-����  0xc0-���¼�

void CT_DELAY_US(UINT8 val)//            Delay_us(val)							//����֮һ΢����ʱ����
{
	UINT32 i;
	for(i=0;i<12;i++)asm("NOP");//12 -- 390KHZ
}

/*****************���ݴ��������IO�ڳ�ʼ������************************/
void TP_Port_Init(void)
{
	//need to configure corresponding port as GPIO first
	EFM->ADCCDISR=0x4000;
	//for(k=0;k<20;k++);
	EFM->ADCCDISR=0x8000;
	//for(k=0;k<20;k++);
	EFM->ADCCDISR=0xC000;
	//for(k=0;k<20;k++);
	//ain[3] ain[4] ain[5]the adc channel is used as GPIO
	EFM->ADCCDISR=0xC000|(1<<4)|(1<<5)|(1<<7)|(1<<6);
/*
	EPORT0->EPDDR |= (1<<7);//scl
	EPORT0->EPDDR |= (1<<6);//sda
	EPORT0->EPDDR &=~(1<<5);//INI����
	//��λ
	EPORT0->EPDDR |=(1<<4);//���
	EPORT0->EPPUE |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	EPORT0->U8EPDR.int4=0;
	Delay_ms(20);
	EPORT0->U8EPDR.int4=1;
	Delay_ms(20);

	//����INT05Ϊ�½��ж�
//	EPORT0->EPLPR &= ~(1<<5);		// �͵�ƽ����
//	EPORT0->EPPAR &= ~(3<<10);		//����INT05�½�Դ�ж�
//	EPORT0->EPPAR |= ~(2<<10);
//	EPORT0->EPIER |= (1<<5); 		// ʹ���ж�
//	EIC->IER |= (1<<21);        	// ��INT05 �ж�
*/
	 EPORT0->EPDDR |= (1<<7);//scl
	 EPORT0->EPDDR |= (1<<6);//sda
	 EPORT0->EPDDR &=~(1<<5);//����
	 /**��λ**/
	 EPORT0->EPDDR |=(1<<4);//���
	 EPORT0->EPPUE |= (1<<4)|(1<<5)|(1<<6)|(1<<7);
	 EPORT0->U8EPDR.int4=0;
	 Delay_ms(20);
	 EPORT0->U8EPDR.int4=1;
	 Delay_ms(20);

	 //����INT05Ϊ�½��ж�
	 EPORT0->EPLPR &= ~(1<<5);  // �͵�ƽ����
	 EPORT0->EPPAR &= ~(3<<10);  //����INT05�½�Դ�ж�
	 EPORT0->EPPAR |= ~(2<<10);

	 EPORT0->EPIER |= (1<<5);   // ʹ���ж�
	 EIC->IER |= (1<<21);         // ��INT05 �ж�
}
/*************����SDA����Ϊ���********************/
void SDA_OUTPUT()
{
//	I2C->U8I2CDDR.SDA=1;
	EPORT0->EPDDR |=(1<<6);//���
}
/**************����SDA����Ϊ����*****************/
void SDA_INPUT(void)
{
//	I2C->U8I2CDDR.SDA=0;
	EPORT0->EPDDR &=~(1<<6);//����
}
/*******************��ȡ�жϽŵ�ƽ���������д���������ʱ����ֵΪ0************************/
UINT8 TP_Get_INT(void)
{
	if(EPORT0->EPPDR&0x20)
					return 1;
			else	return 0;
}
static void CTI2C_start(void)//CTI2C��������
{
	SDA_OUTPUT();
	SDA_High;
    SCL_High;
    CT_DELAY_US(1);
    SDA_Low;
    CT_DELAY_US(1);
    SCL_Low;
	CT_DELAY_US(1);
}

/**************************/
static void CTI2C_stop(void)// CTI2Cֹͣ����
{
    SDA_OUTPUT();
	SCL_Low;
    SDA_Low;
    CT_DELAY_US(1); 
	SCL_High;
	CT_DELAY_US(1);
    SDA_High;
	CT_DELAY_US(1);
//    SDA_Low;
//    SCL_Low;
}






/**************************/
static UINT8 CTI2C_check_ack(void)//CTI2CӦ��λ��麯��,����Ӧ�𷵻�0�����򷵻�1
{
    UINT8 sdain;
    SDA_INPUT();
    SDA_High;//��SDAΪ����
	CT_DELAY_US(1);
    SCL_High;//ʹSDA�ϵ�������Ч
    CT_DELAY_US(1);//��ʱһ�£���֤SDA�Ѿ��ȶ�
    sdain = GetSDABit()  ;//ȡ��SDA�ϵ�����
  
    if(1==sdain)
        return 1;
    SCL_Low; 
    return 0;   
}
//�ȴ��ӻ�Ӧ���ź�
//����ֵ��1 ����Ӧ��ʧ��
//		  0 ����Ӧ��ɹ�

/**************************/
UINT8 CTI2C_write_byte(const UINT8 s)//CTI2Cд1byte����,SΪ��Ҫд������
{
	UINT8 ch_data,iii=0;

   	SDA_OUTPUT();			//set output
   	ch_data=s;
   	SCL_Low;
   	for(iii=0;iii<8;iii++)
   	{
       		if(ch_data&0x80)//if((ch_data&0x80)==0x80)
       	       	  SDA_High;
       		else    SDA_Low;
       		CT_DELAY_US(1);
       		SCL_High;
       		CT_DELAY_US(1);
       		SCL_Low;                       //Write bit6
       		ch_data=ch_data<<1;
   	}
   	//Read ACK
   	SDA_INPUT();			//set inout.sda to input
   	SDA_High;
   	CT_DELAY_US(1);
   	SCL_High;
   	CT_DELAY_US(1);
   	//ch_ack=eep;
   	if(GetSDABit()==0)
   	{
       		SCL_Low;
       		return 0;
   	}
   	else
   	{
       		SCL_Low;
       		return 1;
   	}
}


///**************************/
UINT8 CTI2C_read_byte(UINT8 ack)//CTI2C��1byte����������ֵΪ��������
{
		UINT8 ch_data,iii=0;

   	SDA_INPUT();
   	ch_data=0x00;                //??????
   	for(iii=0;iii<8;iii++)
   	{
   		ch_data=ch_data<<1;
   		SCL_Low;            	 //read bit7
   		//SDA_High;				//       ???????????????????????? /
   		CT_DELAY_US(1);
   		SCL_High;
   		CT_DELAY_US(1);
   		if(GetSDABit()==1)  ch_data=ch_data|0x01;
   	}
   	SCL_Low;
   	SDA_OUTPUT();
   	SCL_Low;
   	if(!ack)
   	{
   		SDA_Low;		//to ack
   		CT_DELAY_US(1);
   		SCL_High;
   		CT_DELAY_US(1);
   		SCL_Low;
   	}
   	else
   	{
   		SDA_High;		//no ack
   		CT_DELAY_US(1);
   		SCL_High;
   		CT_DELAY_US(1);
   		SCL_Low;
   	}

   	return ch_data;
}


/******************************************************************************
 * FUNCTION: CT_Write_Nbyte ( )
 * DESCRIPTION: д�������Ĵ���
 *    Input the description of function: 
 * Input Parameters: ������ַ����д�Ĵ�����ַ����д�����������洢��д�����ݵĵ�ַ
 * Output Parameters: ��
 * Returns Value: 
 * 
 * Author: FuDongQiang @ 2015/05/22
 * 
 * modification history
 *   ...
 ******************************************************************************/
UINT8 CT_Write_Nbyte(const UINT8 sla_add,const UINT8 add,UINT16 n,const UINT8 *s)//CTI2Cдnbyte������д�������β����鴫�룬�ɹ�����1��ʧ�ܷ���0
{
    UINT8 temps,ack=1;
    UINT16 tempn;
    UINT16 cack_time=0;
    CTI2C_start();//����CTI2C����
    CTI2C_write_byte(sla_add | CT_WRITE_MASK);//����Ѱַ�ֽ�
    CTI2C_write_byte(add);//����Ҫд�����ʼ��ַ

    for(tempn=0;tempn<n;tempn++)
    {
        ack=1;//Ӧ��λ
        cack_time=0;
        temps=*(s+tempn);
        while(ack)
        {
            CTI2C_write_byte(temps);
            ack=CTI2C_check_ack();//���Ӧ���źţ���Ӧ�����ط����ֽ�
            cack_time++;
            if(cack_time>CT_CACK_TIMEOUT)//�ڹ涨ʱ��cack_timeout���ղ���Ӧ���źţ����س����ź�
                return CT_ACK_FAIL;
        }
    }
    CTI2C_stop();// CTI2Cֹͣ
    return CT_COM_OK;
}
 
/******************************************************************************
 * FUNCTION: CT_Read_Nbyte ( )
 * DESCRIPTION: �Ӵ������ж�������
 *    Input the description of function: 
 * Input Parameters: ������ַ�������Ĵ�����ַ�����������������洢���������ݵĵ�ַ
 * Output Parameters: ��ȡ������
 * Returns Value: 
 * 
 * Author: FuDongQiang @ 2015/05/22
 * 
 * modification history
 *   ...
 ******************************************************************************/
UINT8 CT_Read_Nbyte(const UINT8 sla_add,const UINT8 add,UINT16 n,UINT8 *s)//CTI2C��nbyte����,�������ݷ����β������У��ɳ���Ա���ú��ʵ������С�����ɹ�����1��ʧ�ܷ���0
{
    UINT8 temps;
    UINT16 tempn;
    CTI2C_start();//����CTI2C����
    CTI2C_write_byte(sla_add | CT_WRITE_MASK);
		
		CTI2C_write_byte(add);
		CTI2C_stop();
		CTI2C_start();//�ٴ�����CTI2C����
		CTI2C_write_byte(sla_add | CT_READ_MASK);
    for(tempn=0;tempn<n;tempn++)
    {
			
        if(tempn+1<n)//����Ѿ��������������ˣ��Ͳ�Ҫ��Ӧ���źţ�ֱ�ӷ���Ӧ��λ��ֹͣλ
				{
					temps = CTI2C_read_byte(0);
					*(s+tempn)=temps;
				}
    }
		temps = CTI2C_read_byte(1);
		*(s+tempn)=temps;
    CTI2C_stop();
    return CT_COM_OK;
}

/*************��XY�ắ��***********************/
extern UINT8 First_press;
extern UINT16 First_pressX,First_pressY;

void TP_read_XY(void)
{
	UINT16 x,y;
	UINT8 i=0;
	UINT8 event;

	CTI2C_start();																																				//����CTI2C����
	CTI2C_write_byte(0x70);
	CTI2C_write_byte(0x02);
	CTI2C_stop();

	CTI2C_start();																																				//�ٴ�����CTI2C����
	CTI2C_write_byte(0x71);
	fingerNumber = CTI2C_read_byte(0)&0xF;  //ACK

   if(fingerNumber != 1 )
   {
	   fingerNumber=1;
	   for(i=0;i<(fingerNumber*6);i++) READ_BUFF[i] = CTI2C_read_byte(0);
		CTI2C_read_byte(1);    //NACK
		CTI2C_stop();

		for(i=0;i<fingerNumber;i++)
		{
			event = READ_BUFF[i*6+0]&0xC0;

		}
		tp_event=event;
   }
   else if(fingerNumber == 1 )
   {
	fingerNumber=1;
	   for(i=0;i<(fingerNumber*6);i++) READ_BUFF[i] = CTI2C_read_byte(0);
	   CTI2C_read_byte(1);    //NACK
	   CTI2C_stop();

		for(i=0;i<fingerNumber;i++)
		{
			event = READ_BUFF[i*6+0]&0xC0;
			x  = READ_BUFF[i*6+0]&0xF;  //����X��
			x  = x<<8;
			x += READ_BUFF[i*6+1];

			y  = READ_BUFF[i*6+2]&0xF;
			y  = y<<8;
			y += READ_BUFF[i*6+3];

			gTpInfo.x[0] = x;
			gTpInfo.y[0] = y;

			if(gTpInfo.x[0]>LCD_XSIZE_TFT)	gTpInfo.x[0] = LCD_XSIZE_TFT;
			if(gTpInfo.y[0]>LCD_YSIZE_TFT)	gTpInfo.y[0] = LCD_YSIZE_TFT;
		}
		tp_event=event;
		if(tp_event==0)
		{
			First_pressX=gTpInfo.x[0];
			First_pressY=gTpInfo.y[0];
		}
		if(tp_event==1)
		{


		}
   }

//	LTPrintf("e=0x%x f=%d x= %d,y= %d\r\n",event,fingerNumber,gTpInfo.x[0],gTpInfo.y[0]);

}

void Int05_Handler(void)
{
   EPORT0->EPFR |= (1<<5);

	Ctp_INT_DN_Index = 1;
	Ctp_INT_Active = 1;
	Ctp_INT_OverTime = 0;

	FT5216_Scan();
 //LTPrintf("INT05\r\n");
}

UINT8 FT5216_Scan(void)
{
	if(Ctp_INT_Active)
	{
		Ctp_INT_Active = 0;
			TP_read_XY();
			if(gTpInfo.sta == 0)	gTpInfo.sta = 1;
	}
	else
	{
		if(Ctp_INT_DN_Index)
		{
			Delay_ms(1);
			Ctp_INT_OverTime++;
			if(Ctp_INT_OverTime>20)
			{
				gTpInfo.sta = 0;		//����
				Ctp_INT_OverTime = 0;
				Ctp_INT_Active   = 0;
			}
		}
	}
	return gTpInfo.sta;
}
void CTP_Init(void)
{
	TP_Port_Init();
	gTpInfo.scan = FT5216_Scan;
}

/*
////�ж�
void Int05_Handler(void)
{
	EPORT0->EPFR |= (1<<5);
	//tpActive = 1;
	Ctp_INT_DN_Index = 1;
	Ctp_INT_Active = 1;
	Ctp_INT_OverTime = 0;
}
UINT8 FT5216_Scan(void)
{
	if(Ctp_INT_Active)
		{
			Ctp_INT_Active = 0;
			TP_read_XY();
			if(gTpInfo.x[0]>LCD_XSIZE_TFT)	gTpInfo.x[0] = LCD_XSIZE_TFT;
			if(gTpInfo.y[0]>LCD_YSIZE_TFT)	gTpInfo.y[0] = LCD_YSIZE_TFT;
//				LTPrintf("NEW_Xpos=%d   NEW_Ypos=%d\r\n",gTpInfo.x[0],gTpInfo.y[0] );
			if(gTpInfo.sta == 0) 	gTpInfo.sta = 1;
		}
		else
		{
			if(Ctp_INT_DN_Index)
			{
				//Delay_ms(1);
				Delay_us(100);
				Ctp_INT_OverTime++;
				if(Ctp_INT_OverTime>200)
				{
					gTpInfo.sta = 0;		//����
					Ctp_INT_OverTime = 0;
					Ctp_INT_Active   = 0;
					Ctp_INT_DN_Index = 0;
				}
			}
		}
	 //LTPrintf("INT= %d\r\n",Ctp_INT_Active );
	//	LTPrintf("gTp= %d\r\n",gTpInfo.sta );
	return gTpInfo.sta;
}
*/


#endif

