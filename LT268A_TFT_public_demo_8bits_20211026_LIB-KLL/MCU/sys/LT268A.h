#ifndef _REG_H
#define _REG_H

#include "type.h"

#define MCU_SysFreq 	(7200*10000)
#define MCU_SYSDIV	1			//value between 1 to 64
#define MCU_IPSDIV	1			//value between 1 to 4
#define MCU_ADCDIV	1			//value between 1 to 16

#define SysFreq 	(MCU_SysFreq/MCU_SYSDIV)
#define PeripheralFreq 	(SysFreq/MCU_IPSDIV)


//////////////////////////////////////////////////////
//EIC
//////////////////////////////////////////////////////
#define IRQ(x)	((1<<x)&0xffffffff)

typedef enum
{
	DISABLE = 0,
	ENABLE = !DISABLE,
}FunctionalState;


typedef struct
{
	union {
		volatile UINT32 ICSR;//0x0000
		struct {
			volatile UINT32 VEC : 7;
			volatile UINT32 RESERVED0 : 20;
			volatile UINT32 ClrPTrap : 1;
			volatile UINT32 SetPTrap : 1;
			volatile UINT32 RESERVED1 : 2;
			volatile UINT32 SRST : 1;
		}U32ICSR;
  	};

	volatile UINT32 RESERVED0[3];//0x0004~0x000C

	union {
		volatile UINT32 IER;//0x0010
		struct {
			volatile UINT32 IE_ADC   : 1;	//0
			volatile UINT32 IE_SCM   : 1;	//1
			volatile UINT32 IE_SCI0  : 1;	//2
			volatile UINT32 IE_COMP0 : 1;	//3
			volatile UINT32 IE_COMP1 : 1;	//4
			volatile UINT32 IE_LDMAC : 1;	//5
			volatile UINT32 IE_WDT0  : 1;	//6
			volatile UINT32 IE_PWM0  : 1;	//7
			volatile UINT32 IE_PWM1  : 1;	//8
			volatile UINT32 IE_PIT   : 4;	//9-12
			volatile UINT32 IE_WDT1  : 1;	//13
			volatile UINT32 IE_USB   : 1;	//14
			volatile UINT32 IE_I2C 	 : 1;	//15
			volatile UINT32 IE_EPORT0 : 8;//16-23
			volatile UINT32 IE_EPORT1 : 8;//24-31
		}U32IER;
	};

	  volatile UINT32 RESERVED1[1];//0x0014
	  volatile UINT32 IPSR;//0x0018
	  volatile UINT32 IPCR;//0x001c
	  volatile UINT32 RESERVED2[8];//0x0020

	union {
		volatile UINT8 PLSR[32];//0x0040
		struct {
			volatile UINT8 RESERVED0 : 6;
			volatile UINT8 EICPLSR : 2;
		}U8PLSR[32];
	  };

  	union {
		volatile UINT32 SYSPLSR;//0x0060
		struct {
			volatile UINT32 RESERVED0 : 22;
			volatile UINT32 SIPRI : 2;
			volatile UINT32 RESERVED1 : 6;
			volatile UINT32 EPTPRI : 2;
		}U32SYSPLSR;
  	};

	volatile UINT32 RESERVED3[7];//0x0064
} eic;
#define EIC_BASE_T	((UINT32) 0xe0000000)
#define EIC          	(( eic *) (EIC_BASE_T))

//////////////////////////////////////////////////////
//EPT
//////////////////////////////////////////////////////
typedef struct
{
	union {
		volatile UINT32 EPTCSR;			//0x0000
		struct {
			volatile UINT32 CNTEN : 1;
			volatile UINT32 INTEN : 1;
			volatile UINT32 CLKSRC : 1;
			volatile UINT32 reserved0 : 13;
			volatile UINT32 CNTFLAG : 1;
			volatile UINT32 reserved1 : 15;
			}U32EPTCSR;
	};
	union {
		volatile UINT32 EPTRLD;				//0x0004
		struct {
			volatile UINT32 RLD : 24;
			volatile UINT32 reserved0 : 8;
		}U32EPTRLD;
	};
	union {
		volatile UINT32 EPTCNT;			//0x0008
		struct {
			volatile UINT32 CNT : 24;
			volatile UINT32 reserved0 : 8;
		}U32EPTCNT;
	};
	
	volatile UINT32 RESERVED0[1];		//0x000c
} ept;
#define EPT_BASE_T	((UINT32) 0xE0001000)
#define EPT          	(( ept *) (EPT_BASE_T))

//////////////////////////////////////////////////////
//CCM
//////////////////////////////////////////////////////
typedef struct
{
	union {
		volatile UINT32 WKUPC; //0x0000
		struct {
			volatile UINT32 WKUPSEN : 23;
			volatile UINT32 reserved0 : 8;
			volatile UINT32 WKUPFILTEREN : 1;
			}U32WKUPC;
	};

	volatile UINT32 CRPDC;//0x0004
	volatile UINT32 CPSRC;// 0x0008
	volatile UINT32 CPPDC;//0x000c
	volatile UINT16 CTR;//0x0010

	union {
		volatile UINT16 CIR;//0x0012
		struct{
			 volatile UINT16 PRN : 8;
			 volatile UINT16 PIN : 8;
		}U16CIR;
	};
} ccm;
#define CCM_BASE_T		((UINT32) 0x40010000)
#define CCM          		(( ccm *) (CCM_BASE_T))

//////////////////////////////////////////////////////
//CLOCK
//////////////////////////////////////////////////////
typedef struct
{
	union {
		volatile UINT32 SYNCR; //0x0000
		struct {
			volatile UINT32 LOSCLPE   : 1;
			volatile UINT32 FLSLPE 	  : 1;
			volatile UINT32 ADCEN 	  : 1;
			volatile UINT32 FXOSCLPEN : 1;
			volatile UINT32 STBYMD    : 2;
			volatile UINT32 CLKOUTSEL : 2;
			volatile UINT32 SLEEP     : 1;
			volatile UINT32 RESERVED1 : 1;
			volatile UINT32 FXOSCON : 1;
			volatile UINT32 LOSCEN  : 1;
			volatile UINT32 ADCDIV  : 4;
			volatile UINT32 IPSDIV  : 2;
			volatile UINT32 SYSDIV  : 6;
			volatile UINT32 ENLOW_POWER   : 1;
			volatile UINT32 USBREF_CLKRDY : 1;
			volatile UINT32 RESERVED2 : 4;
			volatile UINT32 SYNCTEST  : 2;
			}U32SYNCR;
	};

	union {
		volatile UINT32 LOSCCSR;//0x0004
		struct {
			volatile UINT32 SXOSCEN   : 1;
			volatile UINT32 WDTCLKSEL : 1;
			volatile UINT32 SXOSC3V5V : 1;
			volatile UINT32 WDT1TIMERCLKEN : 1;
			volatile UINT32 WDT0TIMERCLKEN : 1;
			volatile UINT32 WDTCLKCHGDONE  : 1;
			volatile UINT32 SXOSCRDY : 1;
			volatile UINT32 SIRCRDY  : 1;			
			volatile UINT32 SXOSCST  : 16;			
			volatile UINT32 SIRCST   : 5;			
			volatile UINT32 RESERVED1  : 1;
			volatile UINT32 LOSCCSTEST : 2;
		}U32LOSCCSR;
	};
	
	volatile UINT32 RESERVED0[1];//0x0008

	union {
		volatile UINT32 MSCR;// 0x000c
		struct {
			volatile UINT32 MS        : 21;
			volatile UINT32 RESERVED0 : 2;
			volatile UINT32 MS23      : 1;
			volatile UINT32 RESERVED1 : 6;
			volatile UINT32 MSCRTEST  : 2;
		}U32MSCR;
	};
	
	union {
		volatile UINT32 ECSECR;// 0x0010
		struct {
			volatile UINT32 RESERVED0 : 23;
			volatile UINT32 EPTEN     : 1;
			volatile UINT32 EPTDIV    : 8;
		}U32ECSECR;
	};
	
	
}clock;
#define CLOCK_BASE_T	((UINT32) 0x40030000)
#define CLOCK          		(( clock *) (CLOCK_BASE_T))

//////////////////////////////////////////////////////
//RESET
//////////////////////////////////////////////////////
typedef struct
{
	UINT8 RESERVED0[1];//0x0000
	union {
		volatile UINT8 RTR;//0x0001
		struct {
			UINT8 FPOR : 1;
			UINT8 reserved0 : 5;
			UINT8 TEST : 2;
		}U8RTR;
	};

	union {
		volatile UINT8 RSR;//0x0002
		struct {
			UINT8 reserved0 : 2;
			UINT8 WD1R : 1;
			UINT8 POR : 1;
			UINT8 WD0R : 1;
			UINT8 SOFT : 1;
			UINT8 PVD : 1;
			UINT8 ERST : 1;
		}U8RSR;
	};

	union {
		volatile UINT8 RCR;//0x0003
		struct {
			UINT8 FRCRSTOUT : 1;
			UINT8 reserved0 : 7;
		}U8RCR;
	};
} reset;
#define RESET_BASE_T	((UINT32) 0x40020000)
#define RESET          		(( reset *) (RESET_BASE_T))

//////////////////////////////////////////////////////
//EFM
//////////////////////////////////////////////////////
typedef struct
{
	union {
		volatile UINT32 EFMCR;//0x0000
		struct {
			volatile UINT32 WS : 4;
			volatile UINT32 RESERVED0 : 4;
			volatile UINT32 OEBATS_R : 3;
			volatile UINT32 RESERVED1 : 1;
			volatile UINT32 OEBATS_RW : 3;
			volatile UINT32 RESERVED2 : 1;
			volatile UINT32 VREAD1 : 1;
			volatile UINT32 VREAD0 : 1;
			volatile UINT32 RESERVED3 : 6;
			volatile UINT32 DIVSEL : 7;
			volatile UINT32 RESERVED4 : 1;
		}U32EFMCR;
	};
	union {
		volatile UINT32 EFMSEC0;//0x0004
		struct {
			volatile UINT32 RDNEN : 8;
			volatile UINT32 RESERVED0 : 24;
		}U32EFMSEC0;
	};
	union {
		volatile UINT32 EFMSEC1;//0x0008
		struct {
			volatile UINT32 RDN4INFO : 8;
			volatile UINT32 RDN3INFO : 8;
			volatile UINT32 RDN2INFO : 8;
			volatile UINT32 RDN1INFO : 8;
		}U32EFMSEC1;
	};
	union {
		volatile UINT32 EFMSEC2;//0x0008
		struct {
			volatile UINT32 RDN8INFO : 8;
			volatile UINT32 RDN7INFO : 8;
			volatile UINT32 RDN6INFO : 8;
			volatile UINT32 RDN5INFO : 8;
		}U32EFMSEC2;
	};

	union {
		volatile UINT32 EFMTIM0;//0x0010
		struct {
			volatile UINT32 TERASE_SMALL : 13;
			volatile UINT32 RESERVED0 : 3;
			volatile UINT32 TPGS : 9;
			volatile UINT32 RESERVED1 : 7;
		}U32EFMTIM0;
	};
	union {
		volatile UINT32 EFMTIM1;//0x0014
		struct {
			volatile UINT32 TERASE : 16;
			volatile UINT32 TPROG : 16;
		}U32EFMTIM1;
	};
	
	//volatile UINT8 RESERVED0[1];//0x0018
	union {
		volatile UINT8 EFMCMD;//0x0018
		struct {
			volatile UINT8 CMD      : 7;
			volatile UINT8 RESERVED : 1;
		}U8EFMCMD;
	};
	
	volatile UINT8 RESERVED1[1];//0x0019
	
	union {
		volatile UINT8 EFMSTAT;//0x001A
		struct {
			volatile UINT8 RESERVED0 : 4;
			volatile UINT8 ACCERR : 1;
			volatile UINT8 CCIF : 1;
			volatile UINT8 DONE : 1;
			volatile UINT8 RESERVED1 : 1;
		}U8EFMSTAT;
	};
	
	volatile UINT8 RESERVED2[1];//0x001B


	union {
		volatile UINT16 PVDC;//0x001c
		struct{
			volatile UINT16 PVDC : 3;
			volatile UINT16 RESERVED0 : 5;			
			volatile UINT16 PVDE  : 1;			
			volatile UINT16 PVDIE : 1;			
			volatile UINT16 PVDRE : 1;
			volatile UINT16 PVDOE : 1;	
			volatile UINT16 PVDTEST : 2;			
			volatile UINT16 PVDPORRE :1;
			volatile UINT16 PVDF :1;
		  }U16PVDC;
	};
	
	union {
		volatile UINT16 CCR;//0x001e
		struct{
			volatile UINT16 CCRTEST : 2;
			volatile UINT16 EOSCSTE :1;
			volatile UINT16 IOSCSTE :1;
			volatile UINT16 PVDCE :1;
			volatile UINT16 ADCCSPOR :1;
			volatile UINT16 STBDLDIS :1;
			volatile UINT16 EXTALBYP :1;
			volatile UINT16 RESERVED1 : 1;
			volatile UINT16 CLKMD :1;
			volatile UINT16 CLKOUTDIS :1;
			volatile UINT16 RSTOUTDIS :1;
			volatile UINT16 SWDDIS :1;
			volatile UINT16 EXTALDIS :1;
			volatile UINT16 CIAPEDIS :1;
			volatile UINT16 CIAPPDIS :1;
		  }U16CCR;
	};

	union {
		volatile UINT16 EOSCST;//0x0020
		struct{
			volatile UINT16 EOSCST : 10;
			volatile UINT16 RESERVED0 :4;
			volatile UINT16 EOSCTEST :2;
		  }U16EOSCST;
	};

	union {
		volatile UINT16 IOSCST;//0x0022
		struct{
			volatile UINT16 IOSCST : 10;
			volatile UINT16 RESERVED0 :4;
			volatile UINT16 IOSCTEST :2;
		  }U16IOSCST;
	};

	union {
		volatile UINT16 RFEVR;//0x0024
		struct{
			volatile UINT16 RFV : 8;
			volatile UINT16 RESERVED0 :4;
			volatile UINT16 RFEVRTEST :2;
			volatile UINT16 RESERVED1 :2;
		  }U16RFEVR;
	};

	union {
		volatile UINT16 PVDFEVR;//0x0026
		struct{
			volatile UINT16 PVDFV : 8;
			volatile UINT16 RESERVED0 :4;
			volatile UINT16 RVDFTEST :2;
			volatile UINT16 RESERVED1 :1;
			volatile UINT16 PVDFE :1;
		  }U16PVDFEVR;
	};

	volatile UINT16 RESERVED3[2];//0x0028

	union {
		volatile UINT16 FCR;//0x002e
		struct{
			volatile UINT16 BIGENDIAN : 1;
			volatile UINT16 RESERVED0 : 5;
			volatile UINT16 MPUEDIS  : 1;
			volatile UINT16 MPUPDIS  : 1;
			volatile UINT16 LDO3P3TE : 1;
			volatile UINT16 VREFTE   : 1;
			volatile UINT16 LDO1P5TE : 1;
			volatile UINT16 IOSCTE   : 1;
			volatile UINT16 TMDIS    : 1;
			volatile UINT16 RESERVED1 : 1;
			volatile UINT16 FIAPEDIS  : 1;
			volatile UINT16 FIAPPDIS  : 1;
		  }U16FCR;
	};

	union{
		volatile UINT32 IOSCTC;//0x0030
		struct{
			volatile UINT32 TEMPTRIM_LV : 3;
			volatile UINT32 FTRIM_LV : 5;
			volatile UINT32 CTRIM_TD_LV : 7;
			volatile UINT32 CTRIM_LV : 2;
			volatile UINT32 RESERVED0 : 13;
			volatile UINT32 IOSCTCTEST : 2;
		  }U32IOSCTC;
	};
	union{
		volatile UINT16 ADCCDISR;//0x0034
		struct{
			volatile UINT16 RESERVED0 : 3;
			volatile UINT16 ADCCDIS : 5;
			volatile UINT16 RESERVED1 : 6;
			volatile UINT16 ADCCDISTEST : 2;
		  }U16ADCCDISR;
	};

	union{
		volatile UINT8 VREFTCR;//0x0036
		struct{
			volatile UINT8 VREFTRIM : 5;
			volatile UINT8 VREFPD : 1;
			volatile UINT8 VREFTCTEST : 2;
		  }U8VREFTCR;
	};

	union{
		volatile UINT8 LDOTC;//0x0037
		struct{
			volatile UINT8 LDO1P5TC   : 6;
			volatile UINT8 LDO1P5TEST : 2;
		  }U8LDOTC;
	};

	union{
		volatile UINT32 MPUCONFR;//0x0038
		struct{
			volatile UINT32 MPU_L_PAGE_ADDR : 7;
			volatile UINT32 RESERVED0 : 8;
			volatile UINT32 MPULREN : 1;
			volatile UINT32 MPU_H_PAGE_ADDR : 7;
			volatile UINT32 RESERVED1 : 7;
			volatile UINT32 OVMPU : 1;
			volatile UINT32 MPU_EN : 1;
		  }U32MPUCONFR;
	};

	volatile UINT16 RESERVED4[1];//0x003c

	union{
		volatile UINT16 LDO3P3TC;//0x003e
		struct{
			volatile UINT16 LDO3P3TC  : 2;
			volatile UINT16 RESERVED0 : 4;
			volatile UINT16 LDO3P3BYP : 1;
			volatile UINT16 LDO3P3PD  : 1;
			volatile UINT16 RESERVED1 : 6;			
			volatile UINT16 LDO3P3TEST : 2;
		  }U16LDO3P3TC;
	};
} efm;
#define EFM_BASE_T     	((UINT32) 0x40120000)
#define EFM			(( efm*) (EFM_BASE_T))

//////////////////////////////////////////////////////
//LDMA
//////////////////////////////////////////////////////
typedef struct
{
	union{
		volatile UINT32 LDMASR;                       //0x00
		struct{
			volatile UINT32 TCIF0 : 1;
			volatile UINT32 HTIF0 : 1;
			volatile UINT32 TCIF1 : 1;
			volatile UINT32 HTIF1 : 1;
			volatile UINT32 TCIF2 : 1;
			volatile UINT32 HTIF2 : 1;
			volatile UINT32 TCIF3 : 1;
			volatile UINT32 HTIF3 : 1;
			volatile UINT32 TCIF4 : 1;
			volatile UINT32 HTIF4 : 1;
			volatile UINT32 reserved0 : 22;
		  }U32LDMASR;
	 };

	union{
		volatile UINT32 LDMAMBAR0;                    //0x04
		struct{
			volatile UINT32 reserved0 : 2;
			volatile UINT32 MBAR0 : 14;
			volatile UINT32 reserved1 : 16;
		  }U32LDMAMBAR0;
	 };
	 
	union{
		volatile UINT32 LDMABCR0;                     //0x08
		struct{
			volatile UINT32 BCR0 : 16;
			volatile UINT32 reserved0 : 16;
		  }U32LDMABCR0;
	 };
	union{                                       //0x0c
		volatile UINT32 LDMACR0;
		struct{
			volatile UINT32 START0 : 1;
			volatile UINT32 LBFE0 : 1;
			volatile UINT32 PTS0 : 2;
			volatile UINT32 TD0 : 1;
			volatile UINT32 MDEC0 : 1;
			volatile UINT32 MINC0 : 1;
			volatile UINT32 CIRC0 : 1;
			volatile UINT32 EHR0 : 1;
			volatile UINT32 PS0 : 2;
			volatile UINT32 reserved0 : 5;
			volatile UINT32 TCIE0 : 1;
			volatile UINT32 HTIE0 : 1;
			volatile UINT32 reserved1 : 12;
			volatile UINT32 CE0 : 1;
			volatile UINT32 BUSY0 : 1;
		  }U32LDMACR0;
	 };

	union{
		volatile UINT32 LDMAMBAR1;                    //0x04
		struct{
			volatile UINT32 reserved0 : 2;
			volatile UINT32 MBAR1 : 14;
			volatile UINT32 reserved1 : 16;
		  }U32LDMAMBAR1;
	 };
	union{
		volatile UINT32 LDMABCR1;                     //0x08
		struct{
			volatile UINT32 BCR1 : 16;
			volatile UINT32 reserved0 : 16;
		  }U32LDMABCR1;
	 };
	union{                                       //0x0c
		volatile UINT32 LDMACR1;
		struct{
			volatile UINT32 START1 : 1;
			volatile UINT32 LBFE1 : 1;
			volatile UINT32 PTS1 : 2;
			volatile UINT32 TD1 : 1;
			volatile UINT32 MDEC1 : 1;
			volatile UINT32 MINC1 : 1;
			volatile UINT32 CIRC1 : 1;
			volatile UINT32 EHR1 : 1;
			volatile UINT32 PS1 : 2;
			volatile UINT32 reserved0 : 5;
			volatile UINT32 TCIE1 : 1;
			volatile UINT32 HTIE1 : 1;
			volatile UINT32 reserved1 : 12;
			volatile UINT32 CE1 : 1;
			volatile UINT32 BUSY1 : 1;
		  }U32LDMACR1;
	 };

	union{
		volatile UINT32 LDMAMBAR2;                    //0x04
		struct{
			volatile UINT32 reserved0 : 2;
			volatile UINT32 MBAR2 : 14;
			volatile UINT32 reserved1 : 16;
		  }U32LDMAMBAR2;
	 };
	union{
		volatile UINT32 LDMABCR2;                     //0x08
		struct{
			volatile UINT32 BCR2 : 16;
			volatile UINT32 reserved0 : 16;
		  }U32LDMABCR2;
	 };
	union{                                       //0x0c
		volatile UINT32 LDMACR2;
		struct{
			volatile UINT32 START2 : 1;
			volatile UINT32 LBFE2 : 1;
			volatile UINT32 PTS2 : 2;
			volatile UINT32 TD2 : 1;
			volatile UINT32 MDEC2 : 1;
			volatile UINT32 MINC2 : 1;
			volatile UINT32 CIRC2 : 1;
			volatile UINT32 EHR2 : 1;
			volatile UINT32 PS2 : 2;
			volatile UINT32 reserved0 : 5;
			volatile UINT32 TCIE2 : 1;
			volatile UINT32 HTIE2 : 1;
			volatile UINT32 reserved1 : 12;
			volatile UINT32 CE2 : 1;
			volatile UINT32 BUSY2 : 1;
		  }U32LDMACR2;
	 };

	union{
		volatile UINT32 LDMAMBAR3;                    //0x04
		struct{
			volatile UINT32 reserved0 : 2;
			volatile UINT32 MBAR3 : 14;
			volatile UINT32 reserved1 : 16;
		  }U32LDMAMBAR3;
	 };
	union{
		volatile UINT32 LDMABCR3;                     //0x08
		struct{
			volatile UINT32 BCR3 : 16;
			volatile UINT32 reserved0 : 16;
		  }U32LDMABCR3;
	 };
	union{                                       //0x0c
		volatile UINT32 LDMACR3;
		struct{
			volatile UINT32 START3 : 1;
			volatile UINT32 LBFE3 : 1;
			volatile UINT32 PTS3 : 2;
			volatile UINT32 TD3 : 1;
			volatile UINT32 MDEC3 : 1;
			volatile UINT32 MINC3 : 1;
			volatile UINT32 CIRC3 : 1;
			volatile UINT32 EHR3 : 1;
			volatile UINT32 PS3 : 2;
			volatile UINT32 reserved0 : 5;
			volatile UINT32 TCIE3 : 1;
			volatile UINT32 HTIE3 : 1;
			volatile UINT32 reserved1 : 12;
			volatile UINT32 CE3 : 1;
			volatile UINT32 BUSY3 : 1;
		  }U32LDMACR3;
	 };

	union{
		volatile UINT32 LDMAMBAR4;                    //0x04
		struct{
			volatile UINT32 reserved0 : 2;
			volatile UINT32 MBAR4 : 14;
			volatile UINT32 reserved1 : 16;
		  }U32LDMAMBAR4;
	 };
	union{
		volatile UINT32 LDMABCR4;                     //0x08
		struct{
			volatile UINT32 BCR4 : 16;
			volatile UINT32 reserved0 : 16;
		  }U32LDMABCR4;
	 };
	union{                                       //0x0c
		volatile UINT32 LDMACR4;
		struct{
			volatile UINT32 START4 : 1;
			volatile UINT32 LBFE4 : 1;
			volatile UINT32 PTS4 : 2;
			volatile UINT32 TD4 : 1;
			volatile UINT32 MDEC4 : 1;
			volatile UINT32 MINC4 : 1;
			volatile UINT32 CIRC4 : 1;
			volatile UINT32 EHR4 : 1;
			volatile UINT32 PS4 : 2;
			volatile UINT32 reserved0 : 5;
			volatile UINT32 TCIE4 : 1;
			volatile UINT32 HTIE4 : 1;
			volatile UINT32 reserved1 : 12;
			volatile UINT32 CE4 : 1;
			volatile UINT32 BUSY4 : 1;
		  }U32LDMACR4;
	 };

}ldma;
#define LDMA_BASE_T      	((UINT32) 0x40000000)
#define LDMA             		(( ldma *) (LDMA_BASE_T))

//////////////////////////////////////////////////////
//PIT
//////////////////////////////////////////////////////
typedef struct
{
	volatile UINT16 PMR;//0x0000

	union {
		volatile UINT16 PCSR;//0x0002
		struct {
		   	volatile UINT16 EN : 1;
		   	volatile UINT16 RLD : 1;
		   	volatile UINT16 PIF : 1;
		   	volatile UINT16 PIE : 1;
		   	volatile UINT16 OVW : 1;
		   	volatile UINT16 PDBG : 1;
		   	volatile UINT16 PDOZE : 1;
		   	volatile UINT16 reserved0 : 1;
		   	volatile UINT16 PRE : 4;
		   	volatile UINT16 reserved1 : 4;
		}U16PCSR;
	};

	volatile UINT16 RESERVED0[1];//0x0004
	volatile UINT16 PCNTR;//0x0006
} pit;

#define PIT0_BASE_T	((UINT32) 0x40040000)
#define PIT1_BASE_T	((UINT32) 0x40050000)
#define PIT2_BASE_T	((UINT32) 0x40060000)
#define PIT3_BASE_T	((UINT32) 0x40070000)
#define PIT0          		(( pit *) (PIT0_BASE_T))
#define PIT1         	 	(( pit *) (PIT1_BASE_T))
#define PIT2          		(( pit *) (PIT2_BASE_T))
#define PIT3          		(( pit *) (PIT3_BASE_T))

//////////////////////////////////////////////////////
//WDT
//////////////////////////////////////////////////////
typedef struct
{
	volatile UINT16 WMR;                   //0x00

	union{                                  //0x02
		volatile UINT16 WCR;
		struct{
			volatile UINT16 EN : 1;
			volatile UINT16 CU : 1;
			volatile UINT16 IE : 1;
			volatile UINT16 IF : 1;
			volatile UINT16 WDP : 3;
			volatile UINT16 IS : 1;
			volatile UINT16 DBG : 1;
			volatile UINT16 STOP : 1;
			volatile UINT16 DOZE : 1;
			volatile UINT16 WAIT : 1;
			volatile UINT16 RESERVED0 : 4;
		  }U16WCR;
	 };

	volatile UINT16 WSR;                 //0x04
	volatile UINT16 WCNTR;            //0x06
}wdt;
#define WDT0_BASE_T  ((UINT32) 0x40130000)
#define WDT1_BASE_T  ((UINT32) 0x40140000)
#define WDT0         (( wdt *) (WDT0_BASE_T))
#define WDT1         (( wdt *) (WDT1_BASE_T))
//////////////////////////////////////////////////////
//EPORT
//////////////////////////////////////////////////////
typedef struct
{
	volatile UINT8 EPIER;
	volatile UINT8 EPDDR;
	volatile UINT16 EPPAR;
	volatile UINT8 EPPUE;
	volatile UINT8 EPFR;
	volatile UINT8 EPPDR;

	union{
		volatile UINT8 EPDR;
		struct {
			volatile UINT8 int0 : 1;
			volatile UINT8 int1 : 1;
			volatile UINT8 int2 : 1;
			volatile UINT8 int3 : 1;
			volatile UINT8 int4 : 1;
			volatile UINT8 int5 : 1;
			volatile UINT8 int6 : 1;
			volatile UINT8 int7 : 1;
	   }U8EPDR;
	 };
	
	volatile UINT8 EPBSR;
	union{
		volatile UINT8 EPFC;
		struct{
			volatile UINT8 Filter_En : 1;
			volatile UINT8 Filter_Width : 7;
		}U8EPFC;
	 };

	volatile UINT8 EPODE;
	volatile UINT8 EPLPR;
	volatile UINT8 RESERVED[2];
	volatile UINT8 EPBCR;
}eport;
#define EPORT0_BASE_T	((UINT32) 0x400f0000)
#define EPORT1_BASE_T	((UINT32) 0x40100000)
#define EPORT0		(( eport *) (EPORT0_BASE_T))
#define EPORT1		(( eport *) (EPORT1_BASE_T))

//////////////////////////////////////////////////////
//SPI
//////////////////////////////////////////////////////
typedef struct
{
	union {
	volatile UINT32 SPCR;//0x0000
	struct {
			volatile UINT32 GT   : 7;
			volatile UINT32 GTCS : 1;			
			volatile UINT32 SP1E : 1;
			volatile UINT32 SP1IE   : 1;
			volatile UINT32 SPISS1  : 1;
			volatile UINT32 RCOL1IE : 1;
			volatile UINT32 WCOL1IE : 1;
			volatile UINT32 WFEMPTY1IE : 1;
			volatile UINT32 ICNT1 : 2;
			volatile UINT32 SP0E : 1;
			volatile UINT32 SP0IE   : 1;
			volatile UINT32 SPISS0  : 1;
			volatile UINT32 RCOL0IE : 1;
			volatile UINT32 WCOL0IE : 1;
			volatile UINT32 WFEMPTY0IE : 1;
			volatile UINT32 ICNT0 : 2;
			volatile UINT32 CS_VARCLK_EN : 1;
			volatile UINT32 RESERVED0  : 1;
			volatile UINT32 CS_CLKP : 1;
			volatile UINT32 SPLSBFE : 1;
			volatile UINT32 SPBROE : 1;
			volatile UINT32 STC : 1;
			volatile UINT32 DW : 2;			
		}U32SPCR;
	};

	union {
		volatile UINT32 SPSR;//0x0004
		struct {
		   	volatile UINT32 RESERVED0 : 16;
		   	volatile UINT32 REMPTY1 : 1;
		   	volatile UINT32 RFULL1  : 1;
		   	volatile UINT32 WEMPTY1 : 1;
		   	volatile UINT32 WFULL1  : 1;
		   	volatile UINT32 RESERVED1 : 1;
		   	volatile UINT32 RCOL1 : 1;
			volatile UINT32 WCOL1 : 1;
			volatile UINT32 SPI1F : 1;
			volatile UINT32 REMPTY0 : 1;
		   	volatile UINT32 RFULL0  : 1;
		   	volatile UINT32 WEMPTY0 : 1;
		   	volatile UINT32 WFULL0  : 1;
		   	volatile UINT32 RESERVED2 : 1;
		   	volatile UINT32 RCOL0 : 1;
			volatile UINT32 WCOL0 : 1;
			volatile UINT32 SPI0F : 1;
			
		}U32SPSR;
	};
	
	volatile UINT32 SPB0R;	//SPB0R 0x0008	
	volatile UINT32 SPB1R;	//SPB0R 0x000C
	volatile UINT16 SPIBR0;	//SPB0R 0x0010
	volatile UINT16 SPIBR1;	//SPB0R 0x0012
	volatile UINT32 SPIBPSR;	//SPB0R 0x0014
	
	union {
		volatile UINT32 SPIGPIOCSR;//0x0018
		struct {
		   	volatile UINT32 SCMPUEN   : 7; 	   	
		   	volatile UINT32 RESERVED0 : 1;
		   	volatile UINT32 SCMGPIODR : 7; 	   	
		   	volatile UINT32 RESERVED1 : 1;
		   	volatile UINT32 SCMGPIODDR : 7; 	   	
		   	volatile UINT32 RESERVED2 : 1;
		   	volatile UINT32 SCMGPIOEN : 7; 	   	
		   	volatile UINT32 RESERVED3 : 1;	   		
		}U32SPIGPIOCSR;
	};

	union {
		volatile UINT32 SPIDMACR;//0x001c
		struct {
		   	volatile UINT32 RXDMAEN1  : 1;
		   	volatile UINT32 TXDMAEN1  : 1;
		   	volatile UINT32 RXDMAEN0  : 1;
		   	volatile UINT32 TXDMAEN0  : 1;
		   	volatile UINT32 RESERVED0 : 28;
		}U32SPIDMACR;
	};
} spi;
#define SPI_BASE_T	((UINT32) 0x400c0000)
#define SPI          	(( spi *) (SPI_BASE_T))

//////////////////////////////////////////////////////
//UART
//////////////////////////////////////////////////////
typedef struct
{
	union{
		volatile UINT8 SCICR2;
		struct{
			volatile UINT8 SBK : 1;
			volatile UINT8 RWU : 1;
			volatile UINT8 RE : 1;
			volatile UINT8 TE : 1;
			volatile UINT8 ILIE : 1;
			volatile UINT8 RIE : 1;
			volatile UINT8 TCIE : 1;
			volatile UINT8 TIE : 1;
		  }U8SCICR2;
	 };

	union{
		volatile UINT8 SCICR1;
		struct{
			volatile UINT8 PT : 1;
			volatile UINT8 PE : 1;
			volatile UINT8 ILT : 1;
			volatile UINT8 WAKE : 1;
			volatile UINT8 M : 1;
			volatile UINT8 RSRC : 1;
			volatile UINT8 WOMS : 1;
			volatile UINT8 LOOPS : 1;
		  }U8SCICR1;
	 };


	volatile UINT8 SCIBRDIL;
	volatile UINT8 SCIBRDIH;
	volatile UINT8 SCIDRL;

	union{
		volatile UINT8 SCIDRH;
		struct{
			volatile UINT8 RESERVED0 : 6;
			volatile UINT8 T8 : 1;
			volatile UINT8 R8 : 1;
		  }U8SCIDRH;
	 };

	union{
		volatile UINT8 SCISR2;
		struct{
			volatile UINT8 RAF : 1;
			volatile UINT8 RESERVED0 : 7;
		  }U8SCISR2;
	 };

	union{
		volatile UINT8 SCISR1;
		struct{
			volatile UINT8 PF : 1;
			volatile UINT8 FE : 1;
			volatile UINT8 NF : 1;
			volatile UINT8 OR : 1;
			volatile UINT8 IDLE : 1;
			volatile UINT8 RDRF : 1;
			volatile UINT8 TC : 1;
			volatile UINT8 TDRE : 1;
		  }U8SCISR1;
	 };

	union{
		volatile UINT8 SCIBRDF;
		struct{
			volatile UINT8 SBRDF : 6;
			volatile UINT8 RESERVED0 : 2;
		  }U8SCIBRDF;
	 };

	union{
		volatile UINT8 SCIDDR;
		struct{
			volatile UINT8 DDRSC : 2;
			volatile UINT8 RESERVED0 : 6;
		  }U8SCIDDR;
	 };

	union{
		volatile UINT8 SCIPORT;
		struct{
			volatile UINT8 PORTSC : 2;
			volatile UINT8 RESERVED0 : 6;
		  }U8SCIPORT;
	 };

	union{
		volatile UINT8 SCIPURD;
		struct{
			volatile UINT8 PUPSCI : 1;
			volatile UINT8 RESERVED0 : 6;
			volatile UINT8 SCISDOZ : 1;
		  }U8SCIPURD;
	 };

	volatile UINT8 RESERVED;      //ц╩сп
	volatile UINT8 SCIIRDR;

	union{
		volatile UINT8 SCIIRCR;
		struct{
			volatile UINT8 IREN : 1;
			volatile UINT8 IRSC : 1;
			volatile UINT8 RINV : 1;
			volatile UINT8 TINV : 1;
			volatile UINT8 RNUM : 2;
			volatile UINT8 TNUM : 2;
		  }U8SCIIRCR;
	 };

	volatile UINT8 SCITR;
}uart;
#define UART0_BASE_T      ((UINT32) 0x40090000)
#define UART0             	(( uart *) (UART0_BASE_T))

//////////////////////////////////////////////////////
//IIC
//////////////////////////////////////////////////////
typedef struct
{
	union {
		volatile UINT8 I2CS;// 0x0000
		struct {
				volatile UINT8 TF : 1;
				volatile UINT8 RC : 1;
				volatile UINT8 AASLV : 1;
				volatile UINT8 BBUSY : 1;
				volatile UINT8 ARBL : 1;
				volatile UINT8 RXTX : 1;
				volatile UINT8 DACK : 1;
				volatile UINT8 AACK : 1;
			}U8I2CS;
	};

	union {
		volatile UINT8 I2CP;// 0x0001
		struct {
			volatile UINT8 PRE : 6;
			volatile UINT8 TEST : 1;
			volatile UINT8 reserved0 : 1;
		}U8I2CP;
	};

	union {
		volatile UINT8 I2CC;// 0x0002
		struct {

			volatile UINT8 EN : 1;
			volatile UINT8 IEN : 1;
			volatile UINT8 MSMOD : 1;
			volatile UINT8 ACKEN : 1;
			volatile UINT8 REPSTA : 1;
			volatile UINT8 AMIE : 1;
			volatile UINT8 HMS_EN  : 1;
			volatile UINT8 SLV_HSIE : 1;
		}U8I2CC;
	};

	union {
		volatile UINT8 I2CSA;// 0x0003
		struct{
			volatile UINT8 reserved0 : 1;
			volatile UINT8 ADDR : 7;
		}U8I2CSA;
	};

	union {
		volatile UINT8 I2CPCR;// 0x0004
		struct{
			volatile UINT8 PUI2C : 2;
			volatile UINT8 PDI2C : 2;
			volatile UINT8 WOMI2C : 2;
			volatile UINT8 SCLPA : 1;
			volatile UINT8 SDAPA : 1;
		}U8I2CPCR;
	};

	union {
		volatile UINT8 I2CSHIR;// 0x0005
		struct{
			volatile UINT8 SLV_HS : 1;
			volatile UINT8 reserved0 : 7;
		}U8I2CSHIR;
	};

	union {
		volatile UINT8 I2CSHT;// 0x0006
		struct{
			volatile UINT8 SLVHT : 6;
			volatile UINT8 SDA_FILTER_EN : 1;
			volatile UINT8 SCL_FILTER_EN  : 1;
		}U8I2CSHT;
	};

	volatile UINT8 I2CD;// 0x0007
	volatile UINT8 RESERVED0[2];// 0x0008~0x0009
	
	union {
		volatile UINT8 I2CDDR;// 0x000a
		struct{
			//volatile UINT8 DDRI2C : 2;
			volatile UINT8 SCL : 1;
			volatile UINT8 SDA : 1;
			volatile UINT8 reserved0 : 6;
		  }U8I2CDDR;
	};

	union {
		volatile UINT8 I2CPDR;// 0x000b
		struct{
			//volatile UINT8 PORTI2C : 2;
			volatile UINT8 SCL : 1;
			volatile UINT8 SDA : 1;
			volatile UINT8 reserved0 : 6;
		  }U8I2CPDR;
	};
} i2c;
#define I2C_BASE_T	((UINT32) 0x40150000)
#define I2C          	(( i2c *) (I2C_BASE_T))

//////////////////////////////////////////////////////
//PWM
//////////////////////////////////////////////////////
typedef struct
{
	union {
		volatile UINT32 PPR;//0x0000
		struct {
		  volatile UINT32 CP0 : 8;
		  volatile UINT32 CP1 : 8;
		  volatile UINT32 DZI0 : 8;
		  volatile UINT32 DZI1 : 8;
		}U32PPR;
	};

	union {
		volatile UINT32 PCSR;//0x0004
		struct {
		  volatile UINT32 CSR0 : 3;
		  volatile UINT32 RESERVED0 : 1;
		  volatile UINT32 CSR1 : 3;
		  volatile UINT32 RESERVED1 : 1;
		  volatile UINT32 CSR2 : 3;
		  volatile UINT32 RESERVED2 : 1;
		  volatile UINT32 CSR3 : 3;
		  volatile UINT32 RESERVED3 : 17;
		}U32PCSR;
	};

	union {
		volatile UINT32 PCR;//0x0008
		struct {
			volatile UINT32 CH0EN : 1;
			volatile UINT32 RESERVED0 : 1;
			volatile UINT32 CH0INV : 1;
			volatile UINT32 CH0MOD : 1;
			volatile UINT32 DZEN0 : 1;
			volatile UINT32 DZEN1 : 1;
			volatile UINT32 RESERVED1 : 2;

			volatile UINT32 CH1EN : 1;
			volatile UINT32 RESERVED2 : 1;
			volatile UINT32 CH1INV : 1;
			volatile UINT32 CH1MOD : 1;
			volatile UINT32 RESERVED3 : 4;

			volatile UINT32 CH2EN : 1;
			volatile UINT32 RESERVED4 : 1;
			volatile UINT32 CH2INV : 1;
			volatile UINT32 CH2MOD : 1;
			volatile UINT32 RESERVED5 : 4;

			volatile UINT32 CH3EN : 1;
			volatile UINT32 RESERVED6 : 1;
			volatile UINT32 CH3INV : 1;
			volatile UINT32 CH3MOD : 1;
			volatile UINT32 RESERVED7 : 4;
		}U32PCR;
	};

	union {
		volatile UINT32 PCNR0;//0x000C
		struct {
			volatile UINT32 CNR0 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCNR0;
	};

	union {
		volatile UINT32 PCMR0;//0x0010
		struct {
			volatile UINT32 CMR0 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCMR0;
	};

	union {
		volatile UINT32 PTR0;//0x0014
		struct {
				volatile UINT32 PTR0 : 16;
				volatile UINT32 RESERVED0 : 16;
		}U32PTR0;
	};

	union {
		volatile UINT32 PCNR1;//0x0018
		struct {
			volatile UINT32 CNR1 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCNR1;
	};

	union {
		volatile UINT32 PCMR1;//0x001C
		struct {
			volatile UINT32 CMR1 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCMR1;
	};
	union {
		volatile UINT32 PTR1;//0x0020
		struct {
			volatile UINT32 PTR1 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PTR1;
	};

	union {
		volatile UINT32 PCNR2;//0x0024
		struct {
			volatile UINT32 CNR2 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCNR2;
	};

	union {
		volatile UINT32 PCMR2;//0x0028
		struct {
			volatile UINT32 CMR2 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCMR2;
	};

	union {
		volatile UINT32 PTR2;//0x002C
		struct {
			volatile UINT32 PTR2 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PTR2;
	};

	union {
		volatile UINT32 PCNR3;//0x0030
		struct {
			volatile UINT32 CNR3 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCNR3;
	};

	union {
		volatile UINT32 PCMR3;//0x0034
		struct {
			volatile UINT32 CMR3 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCMR3;
	};

	union {
		volatile UINT32 PTR3;//0x0038
		struct {
			volatile UINT32 PTR3 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PTR3;
	};

	union {
		volatile UINT32 PIER;//0x003C
		 struct {
			volatile UINT32 PIER0 : 1;
			volatile UINT32 PIER1 : 1;
			volatile UINT32 PIER2 : 1;
			volatile UINT32 PIER3 : 1;
			volatile UINT32 RESERVED0 : 28;
		}U32PIER;
	};

	union {
		volatile UINT32 PIFR;//0x0040
		struct {
			volatile UINT32 PIFR0 : 1;
			volatile UINT32 PIFR1 : 1;
			volatile UINT32 PIFR2 : 1;
			volatile UINT32 PIFR3 : 1;
			volatile UINT32 RESERVED0 : 28;
		}U32PIFR;
	};

	union {
		volatile UINT32 PCCR0;//0x0044
		struct {
			volatile UINT32 INV0 : 1;
			volatile UINT32 RL_IE0 : 1;
			volatile UINT32 FL_IE0  : 1;
			volatile UINT32 CAPCH0EN : 1;
			volatile UINT32 CAPIF0 : 1;
			volatile UINT32 RESERVED0 : 1;
			volatile UINT32 CRLRD0 : 1;
			volatile UINT32 CFLRD0 : 1;
			volatile UINT32 RESERVED1 : 8;

			volatile UINT32 INV1 : 1;
			volatile UINT32 RL_IE1 : 1;
			volatile UINT32 FL_IE1  : 1;
			volatile UINT32 CAPCH1EN : 1;
			volatile UINT32 CAPIF1 : 1;
			volatile UINT32 RESERVED2 : 1;
			volatile UINT32 CRLRD1 : 1;
			volatile UINT32 CFLRD1 : 1;
			volatile UINT32 RESERVED3 : 8;
		}U32PCCR0;
	};

	union {
		volatile UINT32 PCCR1;//0x0048
		struct {
			volatile UINT32 INV2 : 1;
			volatile UINT32 RL_IE2 : 1;
			volatile UINT32 FL_IE2  : 1;
			volatile UINT32 CAPCH2EN : 1;
			volatile UINT32 CAPIF2 : 1;
			volatile UINT32 RESERVED0 : 1;
			volatile UINT32 CRLRD2 : 1;
			volatile UINT32 CFLRD2 : 1;
			volatile UINT32 RESERVED1 : 8;

			volatile UINT32 INV3 : 1;
			volatile UINT32 RL_IE3 : 1;
			volatile UINT32 FL_IE3  : 1;
			volatile UINT32 CAPCH3EN : 1;
			volatile UINT32 CAPIF3 : 1;
			volatile UINT32 RESERVED2 : 1;
			volatile UINT32 CRLRD3 : 1;
			volatile UINT32 CFLRD3 : 1;
			volatile UINT32 RESERVED3 : 8;
		}U32PCCR1;
	};

	union {
		volatile UINT32 PCRLR0;//0x004C
		struct {
			volatile UINT32 CRLR0 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCRLR0;
	};

	union {
		volatile UINT32 PCFLR0;//0x0050
		struct {
			volatile UINT32 CFLR0 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCFLR0;
	};
	union {
		volatile UINT32 PCRLR1;//0x0054
		struct {
			volatile UINT32 CRLR1 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCRLR1;
	};

	union {
		volatile UINT32 PCFLR1;//0x0058
		struct {
			volatile UINT32 CFLR1 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCFLR1;
	};

	union {
		volatile UINT32 PCRLR2;//0x005C
		struct {
			volatile UINT32 CRLR2 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCRLR2;
	};

	union {
		volatile UINT32 PCFLR2;//0x0060
		struct {
			volatile UINT32 CFLR2 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCFLR2;
	};

	union {
		volatile UINT32 PCRLR3;//0x0064
		struct {
			volatile UINT32 CRLR3 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCRLR3;
	};

	union {
		volatile UINT32 PCFLR3;//0x0068
		struct {
			volatile UINT32 CFLR3 : 16;
			volatile UINT32 RESERVED0 : 16;
		}U32PCFLR3;
	};

	union {
		 volatile UINT32 PPCR;//0x006C
		 struct {
//			  volatile UINT32 PDR : 4;
			  volatile UINT32 PDR0 : 1;
			  volatile UINT32 PDR1 : 1;
			  volatile UINT32 PDR2 : 1;
			  volatile UINT32 PDR3 : 1;
			  volatile UINT32 RESERVED0 : 4;
			  volatile UINT32 PULLUP_EN : 4;
			  volatile UINT32 RESERVED1 : 4;
			  volatile UINT32 PDDR : 4;
			  volatile UINT32 RESERVED2 : 12;
		  }U32PPCR;
	};
} pwm;
#define PWM0_BASE_T	((UINT32) 0x400d0000)
#define PWM1_BASE_T	((UINT32) 0x400e0000)
#define PWM0           		(( pwm *) (PWM0_BASE_T ))
#define PWM1           		(( pwm *) (PWM1_BASE_T ))

//////////////////////////////////////////////////////
//ADC
//////////////////////////////////////////////////////
typedef struct
{
	union{                                        //0x0000
		volatile UINT32 ISR;
		struct{
			volatile UINT32 ADRDY : 1;
			volatile UINT32 EOSMP : 1;
			volatile UINT32 EOC : 1;
			volatile UINT32 EOSEQ : 1;
			volatile UINT32 OVR : 1;
			volatile UINT32 FULL : 1;
			volatile UINT32 EMPTY : 1;
			volatile UINT32 AWD : 1;
			volatile UINT32 reserved0 : 24;
		  }U32ISR;
	 };
	
	union{                                        //0x0004
		volatile UINT32 ADC_IER1;
		struct{
			volatile UINT32 ADRDYIE : 1;
			volatile UINT32 EOSMPIE : 1;
			volatile UINT32 EOCIE : 1;
			volatile UINT32 EOSEQIE : 1;
			volatile UINT32 OVRIE : 1;
			volatile UINT32 reserved0 : 2;
			volatile UINT32 AWDIE : 1;
			volatile UINT32 reserved1 : 24;
		  }U32IER;
	 };
	
	union{                                        //0x0008
		volatile UINT32 CR;
		struct{
			volatile UINT32 ADEN : 1;
			volatile UINT32 ADDIS : 1;
			volatile UINT32 ADSTART : 1;
			volatile UINT32 ADSTP : 1;
			volatile UINT32 reserved0 : 28;
		  }U32CR;
	 };
	
	union{                                        //0x000c
		volatile UINT32 CFGR1;
		struct{
			volatile UINT32 DMAEN : 1;
			volatile UINT32 reserved0 : 7;
			volatile UINT32 RES : 2;
			volatile UINT32 ALIGN : 1;
			volatile UINT32 TRIGMODE : 3;
			volatile UINT32 reserved1 : 2;
			volatile UINT32 TRIGSCR : 3;
			volatile UINT32 reserved2 : 1;
			volatile UINT32 CONT : 1;
			volatile UINT32 WAIT : 1;
			volatile UINT32 AUTOFF : 1;
			volatile UINT32 DISCEN : 1;
			volatile UINT32 SEQ_LEN : 3;
			volatile UINT32 reserved3 : 3;
			volatile UINT32 OVRMOD : 1;
			volatile UINT32 DIFF : 1;
		  }U32CFGR1;
	 };
	
	union{                                        //0x0010
		volatile UINT32 CFGR2;
		struct{
			volatile UINT32 STCNT : 8;
			volatile UINT32 QPR : 4;
			volatile UINT32 reserved0 : 20;
		  }U32CFGR2;
	 };
	
	union{                                        //0x0014
		volatile UINT32 SMPR;
		struct{
			volatile UINT32 SMP : 8;
			volatile UINT32 reserved0 : 24;
		  }U32SMPR;
	 };
	
	union{                                        //0x0018
		volatile UINT32 WDG;
		struct{
			volatile UINT32 AWDCH : 4;
			volatile UINT32 reserved0 : 2;
			volatile UINT32 AWDSGL : 1;
			volatile UINT32 AWDEN : 1;
			volatile UINT32 reserved1 : 24;
		  }U32WDG;
	 };
	
	union{										 //0x001c
		volatile UINT32 TR;
		struct{
			volatile UINT32 LT : 12;
			volatile UINT32 reserved0 : 4;
			volatile UINT32 HT : 12;
			volatile UINT32 reserved1 : 4;
		  }U32TR;
	 };

	volatile UINT32 reserved0[3];

	union{                                       //0x002c
		volatile UINT32 CHSELR1;
		struct{
			volatile UINT32 CCW0 : 4;
			volatile UINT32 reserved0 : 4;
			volatile UINT32 CCW1 : 4;
			volatile UINT32 reserved1 : 4;
			volatile UINT32 CCW2 : 4;
			volatile UINT32 reserved2 : 4;
			volatile UINT32 CCW3 : 4;
			volatile UINT32 reserved3 : 4;
		  }U32CHSELR1;
	 };
	
	union{                                        //0x0030
		volatile UINT32 CHSELR2;
		struct{
			volatile UINT32 CCW4 : 4;
			volatile UINT32 reserved0 : 4;
			volatile UINT32 CCW5 : 4;
			volatile UINT32 reserved1 : 4;
			volatile UINT32 CCW6 : 4;
			volatile UINT32 reserved2 : 4;
			volatile UINT32 CCW7 : 4;
			volatile UINT32 reserved3 : 4;
		  }U32CHSELR2;
	 };

	volatile UINT32 reserved1[6];

	union{                                        //0x004c
		volatile UINT32 FIFO;
		struct{
			volatile UINT32 DATA : 16;
			volatile UINT32 reserved0 : 16;
		  }U32FIFO;
	 };
}adc;
#define ADC_BASE_T      	((UINT32) 0x40110000)
#define ADC             		(( adc *) (ADC_BASE_T))


#endif






