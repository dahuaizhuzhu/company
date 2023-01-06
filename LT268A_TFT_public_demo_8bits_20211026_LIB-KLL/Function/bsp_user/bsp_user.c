/*
 * bsp_user.c
 *
 *  Created on: 2020Äê3ÔÂ30ÈÕ
 *      Author: cjc59
 */
#include "bsp_user.h"

UINT8 User_Function(UINT8 cmd,UINT8 *RxBuf)
{
	UINT8 command;
	switch(cmd)
	{
		case 0:
	#if   MODULE_60
					 command=LT_ManageCmd_60(RxBuf);  		break;									//---0x80
	#endif
	#if  !(MODULE_60)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 1:
	#if   MODULE_61
					 command=LT_ManageCmd_61(RxBuf);  		break;	    							//---0x81
	#endif
	#if  !(MODULE_61)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 2:
	#if   MODULE_62
					 command=LT_ManageCmd_62(RxBuf);		break;	 								//---0x82
	#endif
	#if  !(MODULE_62)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 3:
	#if   MODULE_63
					 command=LT_ManageCmd_63(RxBuf);		break;	 								//---0x82
	#endif
	#if  !(MODULE_63)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 4:
	#if   MODULE_64
					 command=LT_ManageCmd_64(RxBuf);		break;	 								//---0x84
	#endif
	#if  !(MODULE_64)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 5:
	#if   MODULE_65
					 command=LT_ManageCmd_65(RxBuf);    	break;      							//---0x85
	#endif
	#if  !(MODULE_65)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 6:
	#if   MODULE_66
					 command=LT_ManageCmd_66(RxBuf);    	break;     								//---0x86
	#endif
	#if   !(MODULE_66)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 7:
	#if   MODULE_67
					 command=LT_ManageCmd_67(RxBuf);   		break;    								//---0x87
	#endif
	#if   !(MODULE_67)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 8:
	#if   MODULE_68
					 command=LT_ManageCmd_68(RxBuf);   		break;    								//---0x88
	#endif
	#if  !(MODULE_68)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 9:
	#if   MODULE_69
					 command=LT_ManageCmd_69(RxBuf);   		break;    								//---0x89
	#endif
	#if  !(MODULE_69)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 10:   								//0x8a
	#if   MODULE_6A
					 command=LT_ManageCmd_6A(RxBuf); 		break;									//---0x8a
	#endif
	#if  !(MODULE_6A)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 11:
	#if   MODULE_6B
					 command=LT_ManageCmd_6B(RxBuf); 		break;									//---0x8b
	#endif
	#if  !(MODULE_6B)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 12:
	#if   MODULE_6C
					 command=LT_ManageCmd_6C(RxBuf); 		break;	 								//---0x8c
	#endif
	#if   !(MODULE_6C)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 13:
	#if   MODULE_6D
					 command=LT_ManageCmd_6D(RxBuf); 		break;									//---0x8d
	#endif
	#if   !(MODULE_6D)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 14:
	#if   MODULE_6E
					 command=LT_ManageCmd_6E(RxBuf); 		break;									//---0x8e
	#endif
	#if   !(MODULE_6E)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 15:
	#if   MODULE_6F
					 command=LT_ManageCmd_6F(RxBuf); 		break;									//---0x8f
	#endif
	#if   !(MODULE_6F)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif
		case 16:
	#if   MODULE_70
					 command=LT_ManageCmd_70(RxBuf);    	break;      							//---0x90
	#endif
	#if  !(MODULE_70)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 17:
	#if   MODULE_71
					 command=LT_ManageCmd_71(RxBuf);    	break;      							//---0x91
	#endif
	#if  !(MODULE_71)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 18:
	#if   MODULE_72
					 command=LT_ManageCmd_72(RxBuf);    	break;      							//---0x91
	#endif
	#if  !(MODULE_72)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 19:
	#if   MODULE_73
					 command=LT_ManageCmd_73(RxBuf);    	break;      							//---0x91
	#endif
	#if  !(MODULE_73)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 20:
	#if   MODULE_74
					 command=LT_ManageCmd_74(RxBuf);		break;	 								//---0x84
	#endif
	#if  !(MODULE_74)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif
		case 21:
	#if   MODULE_75
					 command=LT_ManageCmd_75(RxBuf);    	break;      							//---0x85
	#endif
	#if  !(MODULE_75)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 22:
	#if   MODULE_76
					 command=LT_ManageCmd_76(RxBuf);    	break;     								//---0x86
	#endif
	#if   !(MODULE_76)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 23:
	#if   MODULE_77
					 command=LT_ManageCmd_77(RxBuf);   		break;    								//---0x87
	#endif
	#if   !(MODULE_77)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 24:
	#if   MODULE_78
					 command=LT_ManageCmd_78(RxBuf);   		break;    								//---0x88
	#endif
	#if  !(MODULE_78)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 25:
	#if   MODULE_79
					 command=LT_ManageCmd_79(RxBuf);   		break;    								//---0x89
	#endif
	#if  !(MODULE_79)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 26:   								//0x8a
	#if   MODULE_7A
					 command=LT_ManageCmd_7A(RxBuf); 		break;									//---0x8a
	#endif
	#if  !(MODULE_7A)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 27:
	#if   MODULE_7B
					 command=LT_ManageCmd_7B(RxBuf); 		break;									//---0x8b
	#endif
	#if  !(MODULE_7B)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 28:
	#if   MODULE_7C
					 command=LT_ManageCmd_7C(RxBuf); 		break;	 								//---0x8c
	#endif
	#if   !(MODULE_7C)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 29:
	#if   MODULE_7D
					 command=LT_ManageCmd_7D(RxBuf); 		break;									//---0x8d
	#endif
	#if   !(MODULE_7D)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 30:
	#if   MODULE_7E
					 command=LT_ManageCmd_7E(RxBuf); 		break;									//---0x8e
	#endif
	#if   !(MODULE_7E)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif

		case 31:
	#if   MODULE_7F
					 command=LT_ManageCmd_7F(RxBuf); 		break;									//---0x8f
	#endif
	#if   !(MODULE_7F)
					 command=LT_Idle(RxBuf);    	   		break;
	#endif
	}
	return command;
}


#if   MODULE_60
typedef struct
{
	UINT16 x;
	UINT16 y;
	UINT16 w;
	UINT16 h;
	UINT32 addr;
	UINT8 flag;
}Pic_my_info;

Pic_my_info Mypic[2]={
		{0,0,240,320,0x000DFC84,0},
		{0,0,240,320,0x00105484,1}
};

UINT8 LT_ManageCmd_60(UINT8 *rxBuf)
{
	UINT8 buf[3];
	UINT8 oper = 0;
	if((gUsartRx.Count==9)||(cmd_flag== 1))
	{
		oper = rxBuf[1];
		if(Mypic[oper].flag == 0)  	   LT268_TFT_ShowPicture(Mypic[oper].x,Mypic[oper].y,Mypic[oper].w,Mypic[oper].h,Mypic[oper].addr);
		else if(Mypic[oper].flag == 1)   LT268_TFT_ShowPicture_Png(Mypic[oper].x,Mypic[oper].y,Mypic[oper].w,Mypic[oper].h,Mypic[oper].addr);
		else if(Mypic[oper].flag == 2)   LT268_TFT_ShowPicture_Png(Mypic[oper].x,Mypic[oper].y,gPictureInfo.w,gPictureInfo.h,gPictureInfo.addr);

		buf[0] = rxBuf[0];
		buf[1] = rxBuf[1];
		buf[2] = 0x00;
		LT_DataToPc(buf,3);
	}

	return OK;
}
#endif

#if   MODULE_61
UINT8 LT_ManageCmd_61(UINT8 *rxBuf)
{
	return OK;

}
#endif

#if   MODULE_62
UINT8 LT_ManageCmd_62(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_63
UINT8 LT_ManageCmd_63(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_64
UINT8 LT_ManageCmd_64(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_65
UINT8 LT_ManageCmd_65(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_66
UINT8 LT_ManageCmd_66(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_67
UINT8 LT_ManageCmd_67(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_68
UINT8 LT_ManageCmd_68(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_69
UINT8 LT_ManageCmd_69(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_6A
UINT8 LT_ManageCmd_6A(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_6B
UINT8 LT_ManageCmd_6B(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_6C
UINT8 LT_ManageCmd_6C(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_6D
UINT8 LT_ManageCmd_6D(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_6E
UINT8 LT_ManageCmd_6E(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_6F
UINT8 LT_ManageCmd_6F(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_70
UINT8 LT_ManageCmd_70(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_71
UINT8 LT_ManageCmd_71(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_72
UINT8 LT_ManageCmd_72(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_73
UINT8 LT_ManageCmd_73(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_74
UINT8 LT_ManageCmd_74(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_75
UINT8 LT_ManageCmd_75(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_76
UINT8 LT_ManageCmd_76(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_77
UINT8 LT_ManageCmd_77(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_78
UINT8 LT_ManageCmd_78(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_79
UINT8 LT_ManageCmd_79(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_7A
UINT8 LT_ManageCmd_7A(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_7B
UINT8 LT_ManageCmd_7B(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_7C
UINT8 LT_ManageCmd_7C(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_7D
UINT8 LT_ManageCmd_7D(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_7E
UINT8 LT_ManageCmd_7E(UINT8 *rxBuf)
{

	return OK;
}
#endif

#if   MODULE_7F
UINT8 LT_ManageCmd_7F(UINT8 *rxBuf)
{

	return OK;
}
#endif
