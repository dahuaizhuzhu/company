#include "flash.h"
#include "delay.h"
#include "iostring.h"

#define EFM_Addr	(*(volatile UINT32 *)(0x801F80))
#define EFM_Data	(*(volatile UINT32 *)(0x801F84))
#define EFM_Cmd     (*(volatile UINT32 *)(0x801F88))
#define CMDPROG					0x20
#define CMDSERA      			0x40

#define EFM0_BASE		0x40120000
#define EFM0CR			(EFM0_BASE+0x00)
#define EFM0TIM0		(EFM0_BASE+0x10)
#define EFM0TIM1		(EFM0_BASE+0x14)
#define EFM0CMD			(EFM0_BASE+0x1b)
#define EFM0STAT		(EFM0_BASE+0x19)
#define EFM0CCR			(EFM0_BASE+0x1C)


const UINT32 EFM_WAIT_BUF[WBUF_NUM]={
		0xF7FF7F01, 0x00801F44, 0x8707770A, 0x8606760A,
		0x77099607, 0x01468607, 0xB6077709, 0xA6077709,
		0x16566405, 0xEFFB2A06, 0xB5077706, 0x000000CF,
		0x00801F80, 0x00801F84, 0x00801F88, 0x4012001B,
		0x40120019, 0x9F002430, 0x8F007F02, 0x00CF2030,
		0x00801F08, 0xBEBEBEBE
};
void EFM_init(void)
{
	IO_WRITE32(EFM0CR,0x23000002);
	IO_WRITE32(EFM0TIM0,0x651170);
	IO_WRITE32(EFM0TIM1,0xf187a2);
}
void FLASH_ProgramWord(UINT32 EFMaddr,UINT32 data)
{
	EFM_Addr = EFMaddr;
	EFM_Data = data;
	EFM_Cmd  = CMDPROG;
	delay(30);
	asm("jsri 0x00801F08");

	delay(150);
}

void EFM_EFlashSectorErase(UINT8 sector)
{
	EFM_Addr = 512*sector;
	EFM_Data = 0xFFFFFFFF;

	EFM_Cmd  = CMDSERA;
	delay(30);
	asm("jsri 0x00801F08");

	delay(150);
}


void LT_WriteFlash(UINT32 addr,UINT32 *buf,UINT16 len)
{
	UINT8 i;

	EFM_EFlashSectorErase(127);
	for(i = 0 ; i < len ; i++)
	{
		FLASH_ProgramWord(addr+4*i,buf[i]);
	}


}

//功能：读flash
//输入：读地址
void LT_ReadMcuFlash(UINT16 addr,UINT32 *buf,UINT16 len)
{
	UINT8 i;
		UINT32 address;

		address =addr;

		for(i=0;i<len;i++)
		{
			buf[i] =IO_READ32(address+i*4);

		}

}



