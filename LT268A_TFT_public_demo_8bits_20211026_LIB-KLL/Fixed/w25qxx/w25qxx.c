/*
 * w25qxx.c
 *
 *  Created on: 2019��5��13��
 *      Author: cjc59
 */

#include "w25qxx.h"

UINT8  Flash_Type = 0;	  	//Flash_Type = 0, 24bits��ַ��NorFlash
                          	//Flash_Type = 1, 32bits��ַ��NorFlash W25Q256 NorFlash�ı�־ ������ʶ��256��ʱ����4Byte ��ַ
                          	//Flash_Type = 2, Nand Flash��W25N01GV��


void SPI1_Init(void)
{
	SPI->U32SPIGPIOCSR.SCMGPIOEN = 0x00;	//All for main funtion
	SPI->U32SPIGPIOCSR.SCMGPIODDR = 0x7F;

	SPI->SPIBR0 = 0x0002;	//4Mhz  //��CS_VARCLK_EN=0��fixed clock=72MHz/2(SPIBR0[15:0] + 1)
	//SPI->SPIBR0 = 0x0FFF;

	SPI->U32SPCR.CS_CLKP = 0;			//Active-high clock, msck idle low
	SPI->U32SPCR.DW = 0;				// 0 -- 8bits, 1 -- 16bits, 2 -- 24bits, 3 -- 32bits
	SPI->U32SPCR.CS_VARCLK_EN = 0;		//1 = SPI variable clock mode enabled
																	//0 = SPI fixed clock mode enabled
								//00 : SPI0F is set after every completed transfer
								//01 : SPI0F is set after every two completed transfers
								//10 : SPI0F is set after every three completed transfers
								//11 : SPI0F is set after every four completed transfers
	SPI->U32SPCR.ICNT1 = 0;
	//˫ͨ������ʱ��STC=0��channel0���Ʒ��ͣ�STC=1��channel1���Ʒ���
	SPI->U32SPCR.STC = 1;	//0 = SPI channel-0 write fifo not empty will start data transfer
								//1 = SPI channel-1 write fifo not empty will start data transfer
	SPI->U32SPCR.SPBROE = 0;
	SPI->U32SPCR.SPLSBFE = 0;		//1 = SPI channel-0 LSB enabled
															//0 = SPI channel-0 MSB enabled
	SPI->U32SPCR.SPISS1 = 0;		//SS0 = 1

	SPI->U32SPCR.WFEMPTY1IE = 0;	//0 = SPI channel-0 write fifo empty interrupt Disabled

	SPI->U32SPCR.WCOL1IE = 0;	//0 = SPI channel-0 write fifo overrun interrupt Disabled

	SPI->U32SPCR.RCOL1IE = 0;		//0 = SPI channel-0 read fifo overrun interrupt Disabled

	SPI->U32SPCR.SP1IE = 0;	//0 = SPI channel-0 interrupt disabled

	SPI->U32SPIDMACR.RXDMAEN1 = 0;
	SPI->U32SPIDMACR.TXDMAEN1 = 0;

	SPI->U32SPCR.SP1E = 1;	//1 = SPI channel-0 enabled

	SPI->U32SPCR.GTCS = 0;

	SPI->U32SPCR.GT = 0;

	SPI->SPSR = 0xffffffff;

	Flash_SS_SET;
}

/**
 * @file   SPIx_ReadWriteByte
 * @brief  ��дһ���ֽ�
 * @param  TxData:Ҫд����ֽ�
 * @reV ��ȡ�����ֽ�
 */
UINT8 SPI1_ReadWriteByte(UINT8 TxData)
{
	unsigned char reV;
	SPI->SPSR = 0xffffffff;
	SPI->SPB1R = TxData;
	while((SPI->U32SPSR.SPI1F)==0);
	reV = SPI->SPB1R; //��������
	return reV;
}


//��ȡW25QXX��״̬�Ĵ���
//BIT7  6   5   4   3   2   1   0
//SPR   RV  TB BP2 BP1 BP0 WEL BUSY
//SPR:Ĭ��0,״̬�Ĵ�������λ,���WPʹ��
//TB,BP2,BP1,BP0:FLASH����д��������
//WEL:дʹ������
//BUSY:æ���λ(1,æ;0,����)
//Ĭ��:0x00
UINT8 LT268_W25QXX_ReadSR(void)   //��ȡW25QXX��״̬�Ĵ���
{
	UINT8 byte=0;
	Flash_SS_RESET                            		//ʹ������
	SPI1_ReadWriteByte(W25X_ReadStatusReg); 	//���Ͷ�ȡ״̬�Ĵ�������
	byte=SPI1_ReadWriteByte(0Xff);          	//��ȡһ���ֽ�
	Flash_SS_SET                            		//ȡ��Ƭѡ
	return byte;
}

//��WEL��λ
void LT268_W25QXX_Write_Enable(void)   //W25QXXдʹ��
{
	Flash_SS_RESET                          			//ʹ������
    SPI1_ReadWriteByte(W25X_WriteEnable); 	//����дʹ��
	Flash_SS_SET                           		//ȡ��Ƭѡ
}

//��WEL����
void LT268_W25QXX_Write_Disable(void)   //W25QXXд��ֹ
{
	Flash_SS_RESET                            		//ʹ������
    SPI1_ReadWriteByte(W25X_WriteDisable); 	//����д��ָֹ��
	Flash_SS_SET                            		//ȡ��Ƭѡ
}


void LT268_W25QXX_Wait_Busy(void)   		//�ȴ�����
{
	while((LT268_W25QXX_ReadSR()&0x01)==0x01);  		// �ȴ�BUSYλ���
}


//��ȡоƬID
//����ֵ����:
//0XEF13,��ʾоƬ�ͺ�ΪW25Q80
//0XEF14,��ʾоƬ�ͺ�ΪW25Q16
//0XEF15,��ʾоƬ�ͺ�ΪW25Q32
//0XEF16,��ʾоƬ�ͺ�ΪW25Q64
//0XEF17,��ʾоƬ�ͺ�ΪW25Q128
//0XEF18,��ʾоƬ�ͺ�ΪW25Q256
UINT16 LT268_W25QXX_ReadID(void)
{
//	SPI->SPIBR0 = 0x0008;
	SPI->U32SPCR.STC = 1;

	UINT16 Temp = 0;
	Flash_SS_RESET
	SPI1_ReadWriteByte(0x90);//���Ͷ�ȡID����
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(0x00);
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;
	Temp|=SPI1_ReadWriteByte(0xFF);
	Flash_SS_SET
	return Temp;
	SPI->U32SPCR.STC = 0;
}


void LT268_W25QXX_4Byte_addr(void)
{
	Flash_SS_RESET;//nSS_Active();
	SPI1_ReadWriteByte(0xB7);
	Flash_SS_SET;//nSS_Inactive();
}


//��ȡSPI FLASH
//��ָ����ַ��ʼ��ȡָ�����ȵ�����
//pBuffer:���ݴ洢��
//ReadAddr:��ʼ��ȡ�ĵ�ַ(24bit)
//NumByteToRead:Ҫ��ȡ���ֽ���(���65535)
void LT268_W25QXX_Read(UINT8* pBuffer,UINT32 ReadAddr,UINT16 NumByteToRead)
{
//	SPI->SPIBR0 = 0x0001;
	SPI->U32SPCR.STC = 1;

	UINT16 i;
 	Flash_SS_RESET                            			//ʹ������
    SPI1_ReadWriteByte(W25X_ReadData);         	//���Ͷ�ȡ����
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(ReadAddr>>24));    //����32bit��ַ
    SPI1_ReadWriteByte((UINT8)((ReadAddr)>>16));  	//����24bit��ַ
    SPI1_ReadWriteByte((UINT8)((ReadAddr)>>8));
    SPI1_ReadWriteByte((UINT8)ReadAddr);

    for(i=0;i<NumByteToRead;i++)
	{
        pBuffer[i]=SPI1_ReadWriteByte(0XFF);   	//ѭ������
    }
    Flash_SS_SET
	SPI->U32SPCR.STC = 0;
}


//SPI��һҳ(0~65535)��д������256���ֽڵ�����
//��ָ����ַ��ʼд�����256�ֽڵ�����
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���256),������Ӧ�ó�����ҳ��ʣ���ֽ���!!!
void LT268_W25QXX_Write_Page(UINT8* pBuffer,UINT32 WriteAddr,UINT16 NumByteToWrite)
{
	UINT16 i;
	LT268_W25QXX_Write_Enable();                  							//SET WEL
    Flash_SS_RESET                            							//ʹ������
    SPI1_ReadWriteByte(W25X_PageProgram);      					//����дҳ����
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(WriteAddr>>24));    //����32bit��ַ
    SPI1_ReadWriteByte((UINT8)((WriteAddr)>>16)); 					//����24bit��ַ
    SPI1_ReadWriteByte((UINT8)((WriteAddr)>>8));
    SPI1_ReadWriteByte((UINT8)WriteAddr);

    for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);	//ѭ��д��
    Flash_SS_SET                            							//ȡ��Ƭѡ
    LT268_W25QXX_Wait_Busy();					   								//�ȴ�д�����
}


//�޼���дSPI FLASH
//����ȷ����д�ĵ�ַ��Χ�ڵ�����ȫ��Ϊ0XFF,�����ڷ�0XFF��д������ݽ�ʧ��!
//�����Զ���ҳ����
//��ָ����ַ��ʼд��ָ�����ȵ�����,����Ҫȷ����ַ��Խ��!
//pBuffer:���ݴ洢��
//WriteAddr:��ʼд��ĵ�ַ(24bit)
//NumByteToWrite:Ҫд����ֽ���(���65535)
//CHECK OK
void LT268_W25QXX_Write_NoCheck(UINT8* pBuffer,UINT32 WriteAddr,UINT16 NumByteToWrite)
{
	UINT16 pageremain;

//	SPI->SPIBR0 = 0x0001;
	SPI->U32SPCR.STC = 1;

	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{
		LT268_W25QXX_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	}
	SPI->U32SPCR.STC = 0;
}


void LT268_W25QXX_BlockErase64KB(UINT32 addr)
{
	SPI->U32SPCR.STC = 1;

	addr*=65536;
	LT268_W25QXX_Write_Enable();                 	//SET WEL
	LT268_W25QXX_Wait_Busy();
	Flash_SS_RESET;                            	  	//ʹ������
	SPI1_ReadWriteByte(W25X_BlockErase);   			//����Ƭ��������
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(addr>>24));    //����32bit��ַ
    SPI1_ReadWriteByte((UINT8)((addr)>>16)); 			//����24bit��ַ
    SPI1_ReadWriteByte((UINT8)((addr)>>8));
    SPI1_ReadWriteByte((UINT8)addr);
    Flash_SS_SET;                           	//ȡ��Ƭѡ
    LT268_W25QXX_Wait_Busy();   				   	//�ȴ�оƬ��������

	SPI->U32SPCR.STC = 0;
}


void LT268_W25QXX_SectorErase4KB(UINT32 addr)
{
	SPI->U32SPCR.STC = 1;

	addr*=4096;
	LT268_W25QXX_Write_Enable();                 	//SET WEL
	LT268_W25QXX_Wait_Busy();
	Flash_SS_RESET;                           	  	//ʹ������
	SPI1_ReadWriteByte(W25X_SectorErase);   			//����Ƭ��������
	if(Flash_Type==1)SPI1_ReadWriteByte((UINT8)(addr>>24));    //����32bit��ַ
    SPI1_ReadWriteByte((UINT8)((addr)>>16)); 			//����24bit��ַ
    SPI1_ReadWriteByte((UINT8)((addr)>>8));
    SPI1_ReadWriteByte((UINT8)addr);
    Flash_SS_SET;                            	//ȡ��Ƭѡ
    LT268_W25QXX_Wait_Busy();   				   	//�ȴ�оƬ��������

	SPI->U32SPCR.STC = 0;
}


//��������оƬ
//�ȴ�ʱ�䳬��...
void LT268_W25QXX_Erase_Chip(void)
{
	LT268_W25QXX_Write_Enable();                 	 	  //SET WEL
	LT268_W25QXX_Wait_Busy();
	Flash_SS_RESET;                            	  //ʹ������
	SPI1_ReadWriteByte(W25X_ChipErase);   //����Ƭ��������
	Flash_SS_RESET;                           	//ȡ��Ƭѡ
	LT268_W25QXX_Wait_Busy();   				   		        //�ȴ�оƬ��������

}
