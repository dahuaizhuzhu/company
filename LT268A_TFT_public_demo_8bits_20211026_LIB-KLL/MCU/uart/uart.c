
#include "uart.h"
#include "data.h"
#include "bsp.h"

Communication_Handle RS485_Handle;
Alldata_Handle_ST Alldata_RS485_Handle;
Allobj_Handle_ST  Allobj_RS485_Handle;
//static uint8_t Receive_E_Battery_Check(Communication_Handle *p);
void N_BatteryData_Filling(uint8_t cmdbyte);
unsigned char Receive_E_Handle(Communication_Handle *p);
void show(Communication_Handle *p);
void show_icon(Allobj_Handle_ST Allobj_RS485_Handle);
void show_number(Allobj_Handle_ST Allobj_RS485_Handle);
void show_electricity(Allobj_Handle_ST Allobj_RS485_Handle);

UINT8 Frame_AA_OK = 0;
UINT16 Frame_count = 0;

UINT8 Rx_Buffer_short[256]={0};
UINT8 Rx_Buffer_long[1024+2]={0};
UINT16  Rx_Count_short=0;
UINT16 Rx_Count_long=0;
UINT16 Rx_Num =0;
UINT16 Respond_Num = 0;
UINT16 Respond_Count= 0;

UINT8 Respond_AA_OK = 0;
//UINT8  gRxBuf[RX_SIZE] ;
UINT16 gRxfist ;

//UINT32 BAUDRATE=38400;	//���ò����ʣ�38400
//uint32_t history_tick=0;
//uint32_t tickcount=0;
//uint8_t usart_send_flag=0;
UINT8 show_flag=0;			//״̬��ʶ  0:�ŵ磬1����磬2���쳣
UINT8 show_lastflag=3;
UINT8 electricity=1;
UINT8 last_electricity=0;
UINT8 buff_81[3];	//80,90����
uint16_t vol,current,temp,soc;
UINT8 cut=0;			//�쳣�л���־λ

void Uart_Init(void)
{
	UINT32 band_rate=0;
	//���ò����ʣ�115200
	UART0->SCIBRDF =(((PeripheralFreq*8/gBaudrate)+1)/2)&0x003f;
	band_rate =(PeripheralFreq*4/gBaudrate)>>6;
	UART0->SCIBRDIH  =(UINT8)((band_rate>>8)&0x00ff);
	UART0->SCIBRDIL  =(UINT8)(band_rate&0x00ff);

	UART0->U8SCICR2.TE = 1;

	UART0->U8SCICR2.RE = 1;

	UART0->U8SCICR2.RIE =1;

	EIC->IER|=IRQ(2);

//	UART0->SCICR1 = 0x00;
//	UART0->SCICR2 = 0x00;
//	UART0->U8SCICR2.RIE=1;//ʹ�ܽ����ж�
//	UART0->U8SCICR2.RE=1;//ʹ�ܽ���
//	UART0->U8SCICR2.TE=1 ;
//
// 	EIC->U32IER.IE_SCI0=1; //enable SCI interrupt�ж�����

}
void SCI0_Handler(void)
{
	UINT8 i = 0;
	if(FF_Update_Flag==0)
	{
		if(UART0->U8SCISR1.RDRF ==1)
		{
			i = UART0->SCIDRL;
			if(!Frame_AA_OK && i == 0x90)
			{
				Frame_AA_OK = 1;
			}

			if(Frame_AA_OK)
			{
				if(Rx_Count_long>= 1024+2)
				{
					Rx_Count_long = 0;
				}
				Rx_Buffer_short[Rx_Count_short++]= i;
				Rx_Buffer_long[Rx_Count_long++]= i;
//				RS485_Handle.RxBuf[Rx_Count_short++]=i;
//				RS485_Handle.ucCmdDataN[Rx_Count_short++]=i;
				Rx_Num++;
				RS485_Handle.RxCount++;

				if(Rx_Count_short > 25 && Rx_Buffer_short[Rx_Count_short-1]!=0 && Rx_Buffer_short[Rx_Count_short-2]!=0)
				{
					Frame_AA_OK = 0;
					Rx_Count_short = 0;
					RS485_Handle.RxCount=0;
					RS485_Handle.RxEndFlag=0;
				}
			}
			if(Frame_AA_OK && Rx_Count_short >= 255)
			{
				Frame_AA_OK = 0;
				Rx_Count_short = 0;
			}

		}

	}
	else if(FF_Update_Flag==1)
	{
		if(UART0->U8SCISR1.RDRF ==1)
		{
			gUsartRx.Buf[gUsartRx.Count++] = UART0->SCIDRL;

			if(gUsartRx.Count>=RX_SIZE)
			{
				LT_UsartTimeDisable();
				PIT1->U16PCSR.PIF =1;
				gUsartRx.Flag=1;
			}
			else LT_UsartTimeSetCounter(16874);
		}
	}
}
void SerialOutChar(char c)
{
	if (c == '\n')
		SerialOutChar('\r');

    while(UART0->U8SCISR1.TDRE==0);
	UART0->SCIDRL = c;
	while(UART0->U8SCISR1.TC ==0);
}
void SerialOutString(char *c)
{
	char *p = c;
	while(*p)
		SerialOutChar(*p++);
}


void SendData(UINT16 data)
{
	if(UART0->U8SCICR1.M==0)
	{
		UART0->SCIDRL =(UINT8)data;
	}
	else if(UART0->U8SCICR1.M==1)
	{
		UART0->SCIDRL = (UINT8)data;
		UART0->U8SCIDRH.T8 = (UINT8)(data>>8);
	}
}


void LT_UsartRxDisable(void)
{
	UART0->U8SCICR2.RIE =0;
	//UART_ITConfig(UART_IE_ILIE,DISABLE);
}

void LT_UsartRxEnable(void)
{
//	UART_ITConfig(UART_IE_RIE,ENABLE);
	UART0->U8SCICR2.RIE =1;
	//UART_ITConfig(UART_IE_ILIE,ENABLE);
}

void LT_ClearRxBuf(void)
{
	UINT16 i = 0;
	for(i = 0 ; i < RX_SIZE ; i++)
	{
		gUsartRx.Buf[i] = 0;
	}
}

void LT_SingleByteToPc(UINT8 val)
{
	UART0->SCIDRL =val;
	while (UART0->U8SCISR1.TC == 0){};
}

//void LT_DataToPc(UINT8 *buf,UINT8 len)
//{
//	UINT16 i = 0;
//
//		for(i = 0 ; i < len ; i++)
//		{
//			 SendData((UINT8) buf[i]);
//			while (UART_GetFlagStatus(UART_FLAG_TC) == 0){};
//		}
//}

void LT_DataToPc(UINT8 *buf,UINT8 len)
{
	UINT16 i = 0;

	UINT16 TxToPc_crc;
	UINT8 crc[2] = {0};
	UINT8 buff[50] = {0};
	TxToPc_crc = Rx_CRC_CCITT(buf,len);
	crc[0] = (UINT8)((TxToPc_crc >> 8) & 0x00ff);
	crc[1] = (UINT8)(TxToPc_crc & 0x00ff);
	buff[0] = 0xAA;
	for(i = 1 ; i <= len ; i++)
	{
		buff[i] = buf[i-1];
	}
	buff[len+1] = crc[0];
	buff[len + 2] = crc[1];
	buff[len + 3] = 0xE4;
	buff[len + 4] = 0x1B;
	buff[len + 5] = 0x11;
	buff[len + 6] = 0xEE;


	if(cmd_9A_flag==0)
	{
		for(i = 0 ; i < len +7; i++)
		{
			UART0->SCIDRL = buff[i];
			while (UART0->U8SCISR1.TC == 0){};
		}
	}
	else if(cmd_9A_flag==1)
	{
		for(i = 1 ; i < len +3; i++)
		{
			UART0->SCIDRL = buff[i];
			while (UART0->U8SCISR1.TC == 0){};
		}
	}
}

void LT_DataToPc_NoFrame(UINT8 *buf,UINT8 len)
{
	UINT16 i = 0;

	UINT16 TxToPc_crc;
	UINT8 crc[2] = {0};
	UINT8 buff[30] = {0};
	TxToPc_crc = Rx_CRC_CCITT(buf,len);
	crc[0] = (UINT8)((TxToPc_crc >> 8) & 0x00ff);
	crc[1] = (UINT8)(TxToPc_crc & 0x00ff);
	for(i = 0 ; i < len ; i++)
	{
		buff[i] = buf[i];
	}
	buff[len] = crc[0];
	buff[len + 1] = crc[1];

	for(i = 0 ; i < len +2; i++)
	{
		SendData((UINT8) buff[i]);
		while (UART0->U8SCISR1.TC == 0){};
	}
}

/* CRC ��λ�ֽ�ֵ�� */
const uint8_t crc_byte_hi[] =
{ 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01,
        0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
        0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00,
        0xC1, 0x81, 0x40 };

/* CRC��λ�ֽ�ֵ��*/
const uint8_t crc_byte_lo[] =
{ 0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05,
        0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A,
        0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B,
        0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14,
        0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11,
        0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36,
        0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF,
        0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28,
        0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D,
        0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22,
        0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63,
        0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C,
        0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69,
        0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE,
        0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5, 0x77,
        0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50,
        0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55,
        0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A,
        0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B,
        0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C, 0x44,
        0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41,
        0x81, 0x80, 0x40 };

/* USART3 init function */





/* USER CODE BEGIN 1 */
//0x28 0x04 0xXX 0xE9 -----------0x29


/************************************************************************
 * @brief           crc16_check
 * @note            CRCУ��
 * @param[in]       ��
 * @param[out]      ��
 * @return          CRCУ����
 ***********************************************************************/
uint16_t crc16_check(const uint8_t* msg, uint16_t len)
{
        uint8_t uCRCByteHi = 0xFF; /* ��CRC�ֽڳ�ʼ�� */
        uint8_t uCRCByteLo = 0xFF; /* ��CRC �ֽڳ�ʼ�� */
        uint32_t uIdx; /* CRCѭ���е����� */
    while (len--) /* ������Ϣ������ */
    {
        uIdx = uCRCByteLo ^ (*msg++); /* ����CRC */
        uCRCByteLo = uCRCByteHi ^ crc_byte_hi[uIdx];
        uCRCByteHi = crc_byte_lo[uIdx];
    }
    return (uCRCByteHi << 8 | uCRCByteLo);
}

//static uint8_t Receive_E_Battery_Check(Communication_Handle *p)
//{
//	uint8_t ch, i = 0;
//	p->cmdStepN = 0;
//	p->cmdPtrN = 0;
//	p->RxHeadPoint = 0;
//	for (i = 0; i < p->RxTailPoint; i++) //     p->RxTailPoint
//	{
//		if (Read_RxBuf(p, &ch, p->RxTailPoint))
//		{
//			switch (p->cmdStepN)
//			{
//				case 0: //��վ��ַ
//					if (ch == EP_BATTERY_ADDR)
//					{
//						p->cmdPtrN = 0;
//						p->cmdStepN++;
//						p->ucCmdDataN[p->cmdPtrN++] = ch; //0
//					}
//					else
//					{
//						p->cmdStepN = 0;
//						p->cmdPtrN = 0;
//						return 0;
//					}
//					break;
//
//				case 1: //������
//					if (ch == EP_BATTERY_FUNCODE)
//					{
//						p->cmdStepN++;
//						p->ucCmdDataN[p->cmdPtrN++] = ch; //1=N_FUNCYION;
//					}
//					else
//					{
//						p->cmdStepN = 0;
//						p->cmdPtrN = 0;
//					}
//
//					break;
//
//				case 2: //������
//					if (ch == EP_BATTERY_CMD)
//					{
//						p->cmdStepN++;
//						p->ucCmdDataN[p->cmdPtrN++] = ch; //`   //2  N_COMMAND;
//					}
//					else
//					{
//						p->cmdStepN = 0;
//						p->cmdPtrN = 0;
//					}
//					break;
//
//				case 3: //���ݳ���
//					if (ch == EP_BATTERY_LENGTH)
//					{
//						p->cmdStepN++;
//						p->ucCmdDataN[p->cmdPtrN++] = ch; //3
//					}
//					else
//					{
//						p->cmdStepN = 0;
//						p->cmdPtrN = 0;
//					}
//
//					break;
//
//				case 4:								  //���ص�����
//					p->ucCmdDataN[p->cmdPtrN++] = ch; //4-------> 5-----11
//					if (p->cmdPtrN >= (EP_BATTERY_LENGTH + 4))
//					{
//						p->cmdStepN++;
//					}
//					break;
//
//				case 5: //β��
//						//CRCУ����
//					if (((crc16_check(p->ucCmdDataN, p->cmdPtrN) & 0xff00) >> 8) == ch)
//					{
//						p->cmdStepN++;
//					}
//					else
//					{
//						p->cmdPtrN = 0;
//						p->cmdStepN = 0;
//						return 0;
//					}
//					break;
//
//				case 6: //β��
//						//CRCУ����
//					if (((crc16_check(p->ucCmdDataN, p->cmdPtrN) & 0x00ff)) == ch)
//					{
//						p->cmdStepN = 0;
//						p->cmdPtrN = 0;
//						return p->ucCmdDataN[2]; //У��ͨ��������ͷ�룬�������룻
//					}
//					else
//					{
//						p->cmdPtrN = 0;
//						p->cmdStepN = 0;
//					}
//					break;
//
//				default:
//					p->cmdPtrN = 0;
//					p->cmdStepN = 0;
//					break;
//			}
//		}
//	}
//	return 0;
//}

void N_BatteryData_Filling(uint8_t cmdbyte)
{
	uint8_t ipos = 0;
	uint8_t cmdtxCS = 0;
	uint8_t cmdTxBuf[10];
	uint8_t temp;

	cmdTxBuf[ipos++] = EP_BATTERY_ADDR;	   //�Ի���ַ��
	cmdTxBuf[ipos++] = EP_BATTERY_FUNCODE; //������
	cmdTxBuf[ipos++] = EP_BATTERY_CMD;		//������
	cmdTxBuf[ipos++] = EP_BATTERY_LENGTH;	//���ݳ���
	//CRCУ����
	cmdTxBuf[ipos++] = (crc16_check(cmdTxBuf, 4) & 0xff00) >> 8;
	cmdTxBuf[ipos++] = (crc16_check(cmdTxBuf, 4) & 0x00ff);
	for (cmdtxCS = 0; cmdtxCS < ipos; cmdtxCS++)
	{
		temp = cmdTxBuf[cmdtxCS];
		UART0->SCIDRL = temp;
		while (UART0->U8SCISR1.TC == 0){};
	}
}

unsigned char Receive_E_Handle(Communication_Handle *p)//Eϵ�е�ؽ���
{
    unsigned char cmdbyte;
//    if(Receive_E_Battery_Check(p))
    {
        cmdbyte = p->ucCmdDataN[2];
        RS485_Handle.E_Cnt = 0;
        RS485_Handle.E_Battery_CommFailCnt = 0;
        RS485_Handle.E_Battery_CommFail_Flag = 0;

        //ͨ�ż���
        switch(cmdbyte)
        {
			case EP_BATTERY_CMD:
				Allobj_RS485_Handle.battery_soc=p->ucCmdDataN[10];		//soc
				Allobj_RS485_Handle.battery_temp=p->ucCmdDataN[16];		//ƽ���¶�
				Allobj_RS485_Handle.battery_vol=((p->ucCmdDataN[4]<<8)+p->ucCmdDataN[5]);
				Allobj_RS485_Handle.battery_vol = Allobj_RS485_Handle.battery_vol/10;		//��ѹ
                Allobj_RS485_Handle.battery_current=((p->ucCmdDataN[6]<<8)+p->ucCmdDataN[7]);
                Allobj_RS485_Handle.battery_current = (Allobj_RS485_Handle.battery_current+50)/100;	//����
                Allobj_RS485_Handle.battery_err =p->ucCmdDataN[11];

				Allobj_RS485_Handle.battery_max_power=((p->ucCmdDataN[8]<<8)+p->ucCmdDataN[9])/10;//����������
				Allobj_RS485_Handle.battery_id=(p->ucCmdDataN[14]<<24)+(p->ucCmdDataN[15]<<16)+(p->ucCmdDataN[16]<<8)+p->ucCmdDataN[17];
				Allobj_RS485_Handle.battery_remain_time_avg=(p->ucCmdDataN[20]<<8)+p->ucCmdDataN[21];//ƽ��ʣ��ʱ��
				Allobj_RS485_Handle.battery_max_temp= p->ucCmdDataN[22];
				Allobj_RS485_Handle.battery_min_temp= p->ucCmdDataN[23];
				break;

			default:
				break;
        }
    }
    return 0;
}

void show(Communication_Handle *p)
{
	Receive_E_Handle(p);
	if(Allobj_RS485_Handle.battery_err==32)		//���״̬
	{
		show_flag=1;
	}
	else if(Allobj_RS485_Handle.battery_err==0)		//�����ŵ�״̬
	{
		show_flag=0;
	}
	else										//�쳣����״̬
	{
		show_flag=2;
	}
	if(show_flag!=show_lastflag)		//�л�״̬
	{
		change();
	}

	//��ʾ��������ͼ��Ͳ���
	show_electricity(Allobj_RS485_Handle);
	show_icon(Allobj_RS485_Handle);
	show_number(Allobj_RS485_Handle);

	show_lastflag=show_flag;

}

void change(void)
{
	uint8_t buff_80[1024+2];
	if(show_flag==0)	//�л����ŵ�״̬
	{
		//������������
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x00;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		//��ʾVA
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x2C;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		//��ʾDischarge
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x07;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

//		//��ʾ��������ͼ��Ͳ���
//		show_electricity(Allobj_RS485_Handle);
////		show_icon(Allobj_RS485_Handle);
//		show_number(Allobj_RS485_Handle);
	}

	else if(show_flag==1)	//�л������״̬
	{
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x00;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		//��ʾVA
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x2C;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		//��ʾCharging
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x08;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

//		show_electricity(Allobj_RS485_Handle);
////		show_icon(Allobj_RS485_Handle);
//		show_number(Allobj_RS485_Handle);
	}

	else if(show_flag==2)	//�л����쳣״̬
	{
		//�쳣��������
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x23;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		//��ʾVA
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x2C;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		//��ʾError
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x25;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

//		show_electricity(Allobj_RS485_Handle);
////		show_icon(Allobj_RS485_Handle);
//		show_number(Allobj_RS485_Handle);
	}
}

void show_icon(Allobj_Handle_ST Allobj_RS485_Handle)
{
	uint8_t buff_80[1024+2];
	if(show_flag==1)	//���״̬
	{
		//����ȡ������ͼ����˸
		if(Allobj_RS485_Handle.battery_soc==100)
		{
			cmd_flag=1;
			buff_80[0] = 0x84;
			buff_80[1] = 0x00;
			if(LT_ManageCmd_84(buff_80)==OK)	cmd_flag=0;

		}
		else
		{
			//���ͼ����˸
			cmd_flag=1;
			buff_81[0] = 0x81;
			buff_81[1] = 0x00;
			if(LT_ManageCmd_81(buff_81)==OK)	cmd_flag=0;
		}

	}
	else if(show_flag==2)	//�쳣״̬
	{
		//�쳣ͼ��
		cmd_flag=1;
		buff_80[0] = 0x80;
		buff_80[1] = 0x24;
		if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
	}

}

void show_temp(Allobj_Handle_ST Allobj_RS485_Handle)
{
	uint8_t ge,shi;
	uint8_t buff_90[1024+2],buff_80[1024+2];
	if(show_flag==2)
	{
		if(cut==1)
		{
			cut=0;
			//��ʾtemp
			temp=Allobj_RS485_Handle.battery_max_temp;
			if(temp>99)
			{
				temp=99;
			}
			ge=temp%10;
			shi= (uint8_t)((temp%100)/10);
			buff_90[0] = 0x90;
			buff_90[1] = 0x05;  //���
			gUsartRx.Count=11;
			buff_90[2] = 0x30+shi;	//ʮλ
			buff_90[3] = 0x30+ge;	//��λ

			//�쳣��Ƭ����
			cmd_flag=1;
			buff_80[0] = 0x80;
			buff_80[1] = 0x28;
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
			cmd_flag=1;
			if(New_Function(buff_90[0]-0x80,buff_90)==OK)
			{
				cmd_flag=0;
			}
			//��ɫ��
			cmd_flag=1;
			buff_80[0] = 0x80;
			buff_80[1] = 0x26;
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

		}
		else
		{
			cut=1;
			//�쳣��Ƭ����
			cmd_flag=1;
			buff_80[0] = 0x80;
			buff_80[1] = 0x28;
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
			//���ϴ���
			cmd_flag=1;
			buff_80[0] = 0x80;
			buff_80[1] = 0x27;
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
		}
	}

}

void show_number(Allobj_Handle_ST Allobj_RS485_Handle)
{

	uint8_t ge,shi,bai;
	uint8_t buff_90[1024+2],buff_80[1024+2];
	buff_90[0] = 0x90;
	//��ʾSOC
	if(soc != Allobj_RS485_Handle.battery_soc || show_flag != show_lastflag)
	{
		soc=Allobj_RS485_Handle.battery_soc;
		ge=soc%10;
		shi= (uint16_t)((soc%100)/10);
		bai=(uint16_t)(soc/100);

		if(soc<100)
		{
			if(show_flag==1)
			{
				buff_90[1] = 0x04;  //���
			}
			else
			{
				buff_90[1] = 0x03;  //���
			}

			gUsartRx.Count=11;
			buff_90[2] = 0x30+shi;	//ʮλ
			buff_90[3] = 0x30+ge;	//��λ

			cmd_flag=1;
			if(LT_ManageCmd_90(buff_90)==OK)	cmd_flag=0;

			cmd_flag=1;
			buff_80[0] = 0x80;
			if(show_flag==1)
			{
				buff_80[1] = 0x06;
			}
			else
			{
				buff_80[1] = 0x05;
			}
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
		}
		else
		{
			if(show_flag==1)
			{
				buff_90[1] = 0x07;  //���
			}
			else
			{
				buff_90[1] = 0x06;  //���
			}

			gUsartRx.Count=12;
			buff_90[2] = 0x30+bai;
			buff_90[3] = 0x30+shi;
			buff_90[4] = 0x30+ge;

			//100%������
			cmd_flag=1;
			buff_80[0] = 0x80;
			buff_80[1] = 0x22;
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
			cmd_flag=1;
			if(LT_ManageCmd_90(buff_90)==OK)    cmd_flag=0;

			if(show_flag==1)
			{
				buff_80[1] = 0x2B;	//��ɫ%
			}
			else
			{
				buff_80[1] = 0x2A;	//��ɫ%
			}
			cmd_flag=1;
			if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;

			if(show_flag==1)
			{
				//����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = 0x02;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
			}
		}

	}
	//��ʾvol
//	if(vol != Allobj_RS485_Handle.battery_vol)
	{
		vol=Allobj_RS485_Handle.battery_vol;
		ge=vol%10;
		shi= (uint16_t)((vol%100)/10);
		bai=(uint16_t)(vol/100);
		buff_90[1] = 0x00;  //���
		if(vol<100)
		{
			gUsartRx.Count=12;
			buff_90[2] = 0x30+shi;	//ʮλ
			buff_90[3] = 0x2E;
			buff_90[4] = 0x30+ge;	//��λ
		}
		else
		{
			gUsartRx.Count=13;
			buff_90[2] = 0x30+bai;
			buff_90[3] = 0x30+shi;
			buff_90[4] = 0x2E;
			buff_90[5] = 0x30+ge;
		}

		cmd_flag=1;
		if(New_Function(buff_90[0]-0x80,buff_90)==OK)
		{
			cmd_flag=0;
		}

	}
	//��ʾcurrent
//	if(current != Allobj_RS485_Handle.battery_current)
	{
		current=Allobj_RS485_Handle.battery_current;
		ge=current%10;
		shi= (uint16_t)((current%100)/10);
		bai=(uint16_t)(current/100);
		buff_90[1] = 0x01;  //���
		if(current<100)
		{
			gUsartRx.Count=11;
			buff_90[2] = 0x30+shi;	//ʮλ
			buff_90[3] = 0x30+ge;	//��λ
		}
		else
		{
			gUsartRx.Count=12;
			buff_90[2] = 0x30+bai;
			buff_90[3] = 0x30+shi;
			buff_90[4] = 0x30+ge;
		}

		cmd_flag=1;
		if(New_Function(buff_90[0]-0x80,buff_90)==OK)
		{
			cmd_flag=0;
		}

	}
}

void show_electricity(Allobj_Handle_ST Allobj_RS485_Handle)
{
	uint8_t buff_80[1024+2];
	uint8_t num=0x0B;		//5%�澯�������
//	if(soc%5==0) electricity=soc/5-1;
//	else
//	electricity=soc/5;
	if(soc != Allobj_RS485_Handle.battery_soc || show_flag != show_lastflag)
	{
		last_electricity=electricity;
		if((Allobj_RS485_Handle.battery_soc >= 0)&&(Allobj_RS485_Handle.battery_soc <=5))
		{
			if(show_flag==1)
			{
				//5%������ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+1;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=1;
			}
			else
			{
				//5%�澯����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=1;
			}
		}
		if((Allobj_RS485_Handle.battery_soc > 5)&&(Allobj_RS485_Handle.battery_soc <=10))
		{
			if(show_flag==1)
			{
				//10%������ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+3;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=2;
			}
			else
			{
				//10%�澯����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+2;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=2;
			}
		}
		if((Allobj_RS485_Handle.battery_soc > 10)&&(Allobj_RS485_Handle.battery_soc <= 15))
		{
			if(show_flag==1)
			{
				//15%������ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+5;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=3;
			}
			else
			{
				//15%�澯����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+4;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=3;
			}
		}
		if((Allobj_RS485_Handle.battery_soc > 15)&&(Allobj_RS485_Handle.battery_soc <= 20))
		{
			if(show_flag==1)
			{
				//20%������ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+7;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=4;
			}
			else
			{
				//20%�澯����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+6;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=4;
			}
		}
		if((Allobj_RS485_Handle.battery_soc > 20)&&(Allobj_RS485_Handle.battery_soc <= 25))
		{
				//25%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+8;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=5;
		}
		if((Allobj_RS485_Handle.battery_soc > 25)&&(Allobj_RS485_Handle.battery_soc <= 30))
		{
				//30%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+9;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=6;
		}
		if((Allobj_RS485_Handle.battery_soc > 30)&&(Allobj_RS485_Handle.battery_soc <= 35))
		{
				//35%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+10;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=7;
		}
		if((Allobj_RS485_Handle.battery_soc > 35)&&(Allobj_RS485_Handle.battery_soc <= 40))
		{
				//40%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+11;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=8;
		}
		if((Allobj_RS485_Handle.battery_soc > 40)&&(Allobj_RS485_Handle.battery_soc <= 45))
		{
				//45%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+12;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=9;
		}
		if((Allobj_RS485_Handle.battery_soc > 45)&&(Allobj_RS485_Handle.battery_soc <= 50))
		{
				//50%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+13;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=10;
		}
		if((Allobj_RS485_Handle.battery_soc > 50)&&(Allobj_RS485_Handle.battery_soc <= 55))
		{
				//55%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+14;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=11;
		}
		if((Allobj_RS485_Handle.battery_soc > 55)&&(Allobj_RS485_Handle.battery_soc <= 60))
		{
				//60%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+15;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=12;
		}
		if((Allobj_RS485_Handle.battery_soc > 60)&&(Allobj_RS485_Handle.battery_soc <= 65))
		{
				//65%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+16;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=13;
		}
		if((Allobj_RS485_Handle.battery_soc > 65)&&(Allobj_RS485_Handle.battery_soc <= 70))
		{
				//70%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+17;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=14;
		}
		if((Allobj_RS485_Handle.battery_soc > 70)&&(Allobj_RS485_Handle.battery_soc <= 75))
		{
				//75%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+18;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=15;
		}
		if((Allobj_RS485_Handle.battery_soc > 75)&&(Allobj_RS485_Handle.battery_soc <= 80))
		{
				//80%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+19;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=16;
		}
		if((Allobj_RS485_Handle.battery_soc > 80)&&(Allobj_RS485_Handle.battery_soc <= 85))
		{
				//85%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+20;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=17;
		}
		if((Allobj_RS485_Handle.battery_soc > 85)&&(Allobj_RS485_Handle.battery_soc <= 90))
		{
				//90%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+21;
				if(LT_ManageCmd_80(buff_80)==OK) cmd_flag=0;
//				electricity=18;
		}
		if((Allobj_RS485_Handle.battery_soc > 90)&&(Allobj_RS485_Handle.battery_soc <= 95))
		{
				//95%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+22;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=19;
		}
		if((Allobj_RS485_Handle.battery_soc > 95)&&(Allobj_RS485_Handle.battery_soc <= 100))
		{
				//100%����ͼ��
				cmd_flag=1;
				buff_80[0] = 0x80;
				buff_80[1] = num+23;
				if(LT_ManageCmd_80(buff_80)==OK)	cmd_flag=0;
//				electricity=20;
		}
	}

}
