#ifndef FLASH_H_
#define FLASH_H_

#include "LT268A.h"


//512 Bytes each sector
//(0x7E00--0x7FFF)=512Byte
#define FMC_LDROM_BASE 0x7E00

#define ASM  __asm

#define IO_READ32(p)     (UINT32)(*(volatile UINT32 *)(p))
#define IO_WRITE32(p,v)  (*((volatile UINT32 *)(p)) = (UINT32)(v))
#define WBUF_NUM 22
extern const UINT32 EFM_WAIT_BUF[WBUF_NUM];
void LT_WriteFlash(UINT32 addr,UINT32 *buf,UINT16 len);
void LT_ReadMcuFlash(UINT16 addr,UINT32 *buf,UINT16 len);
void EFM_EFlashSectorErase(UINT8 sector);
void EFM_init(void);
void FLASH_ProgramWord(UINT32 EFMaddr,UINT32 data);
#endif
