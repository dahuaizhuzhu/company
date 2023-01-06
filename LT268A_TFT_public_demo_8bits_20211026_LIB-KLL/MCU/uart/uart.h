
#ifndef UART_H_
#define UART_H_

#include "LT268A.h"
//#include "bsp.h"

//#define BAUDRATE	115200
#define RS485_RXBUFSIZE      40    //�����ֽ���23
#define RS485_TXBUFSIZE      40    //�����ֽ���23

#define THROTTLE_MSG            	0x2c
#define MOTOR_STATUS_MSG          	0x10
#define MOTOR_STATUS_MSG_1          0x25
#define MOTOR_STATUS_MSG_2          0x27
#define BATTERY_STATUS_MSG          0x23
#define DRIVER_VERSION_MSG          0x11
#define GPS_MSG         			0x20
#define PINBOARD_VERSION_MSG        0x22
#define VERSION_MSG        			0x24
#define MOTOR_VERSION_MSG          	0x26
#define BATTERY_UNDER_VOL_MSG      	0x2a
#define PROHIBIT_RECHARGE_MSG     	0x2d  //��ػ�����Ϣ
#define SCREEN_MSG_1     			0xe8  //������Ļ����
#define SCREEN_MSG_2     			0xe9  //������Ļ����
#define NEED_ACK_MSG_1     			0xe2  //������Ҫ��Ӧ�����ݣ�1ms��
#define NEED_ACK_MSG_2     			0xe3  //������Ҫ��Ӧ�����ݣ�1ms��
#define RESET_BOOT                  0xA0  //��λ

//Eϵ�е�ط��͵�����֡��ʽ
#define EP_BATTERY_ADDR			(0x90)
#define EP_BATTERY_FUNCODE		(0x03)
#define EP_BATTERY_CMD			(0xa0)
//���ݳ���
#define EP_BATTERY_LENGTH		21

typedef struct  //ͨ�Žṹ��
{
	uint8_t                 	RxBuf[RS485_RXBUFSIZE];
    uint8_t                  	TxBuf[RS485_TXBUFSIZE];
    uint8_t                  	RxHeadPoint;           	//����ͷ
    uint8_t                  	RxTailPoint;           	//����β
    uint8_t                 	TxHeadPoint;           	//����ͷ
    uint8_t                  	TxTailPoint;           	//����β
    uint8_t						RxEndFlag;				//��������2msδ���յ�����-��־λ
    uint8_t                 	TxCount;
    uint8_t                   	RxCount;				//��������2msδ���յ�����-����
    uint8_t                   	TempCount;				//�¶��л�10ms����

	uint8_t						cmdStepN;
    uint8_t                  	cmdPtrN;
    uint8_t                  	cmdFlatN;				//E��������־

    uint8_t                  	cmdStep;
    uint8_t                 	cmdPtr;
    uint16_t                  	ucCheckSum;
    uint8_t                    	ucCmdData[RS485_RXBUFSIZE];
	uint8_t                  	ucCmdDataN[RS485_RXBUFSIZE];

	uint8_t                    	RecTmp;
    uint8_t  			      	Evo_CommFailCnt;		//EVOͨ�ż���
    uint8_t  			      	E_Battery_CommFailCnt;  //E���ͨ�ż���
uint16_t						E_Cnt;					//��������10ms����
    uint8_t                     Evo_CommFail_Flag;
    uint8_t  			      	E_Battery_CommFail_Flag;

}Communication_Handle;
//extern Communication_Handle  RS485_Handle;
typedef struct  //��������
{
    uint8_t                       battery_status_buf[14+2];

}Alldata_Handle_ST;

typedef struct  //���в���
{
	//battery_status_buf
    int16_t                       	battery_temp;//0.1��C
    uint16_t                       	battery_vol;//0.1V
    int16_t                       	battery_current;//A
    //int16_t                       battery_current_avg;//mA
    uint16_t                       	battery_err;
    uint8_t                       	battery_type;
    uint8_t                       	battery_soc;
    uint16_t                       	battery_remain_cap;//ʣ������
    uint16_t                       	battery_remain_time_avg;//ʣ��ʱ��
	uint32_t 						battery_id;
	uint16_t 						battery_max_power;
	int8_t							battery_max_temp;
	int8_t							battery_min_temp;
}Allobj_Handle_ST;

extern Communication_Handle RS485_Handle;
extern Alldata_Handle_ST Alldata_RS485_Handle;
extern Allobj_Handle_ST Allobj_RS485_Handle;

//static uint8_t Receive_E_Battery_Check(Communication_Handle *p);
void N_BatteryData_Filling(uint8_t cmdbyte);
unsigned char Receive_E_Handle(Communication_Handle *p);
void show(Communication_Handle *p);
void change(void);
void show_icon(Allobj_Handle_ST Allobj_RS485_Handle);
void show_temp(Allobj_Handle_ST Allobj_RS485_Handle);
void show_number(Allobj_Handle_ST Allobj_RS485_Handle);
void show_electricity(Allobj_Handle_ST Allobj_RS485_Handle);

extern UINT8  gRxFlag;
//extern UINT8  gRxBuf[];
extern UINT16 gRxfist;
extern UINT8 busyflag;
extern UINT8 show_flag;			//״̬��ʶ  0:�ŵ磬1����磬2���쳣

extern UINT8 Frame_AA_OK;
extern UINT16 Frame_count;

extern UINT8 Rx_Buffer_short[256];
extern UINT8 Rx_Buffer_long[1024+2];
extern UINT16  Rx_Count_short;
extern UINT16 Rx_Count_long;
extern UINT16 Rx_Num;
extern UINT16 Respond_Num ;
extern UINT16 Respond_Count;

extern UINT8 Respond_AA_OK;

void LT_UsartRxEnable(void);
void LT_UsartRxDisable(void);

void Uart_Init(void);
void SCI0_Handler(void);
void SerialOutChar(char c);
void SerialOutString(char *c);

void SendData(UINT16 data);
void LT_SingleByteToPc(UINT8 val);
void LT_ClearRxBuf(void);
void LT_DataToPc(UINT8 *buf,UINT8 len);
void LT_DataToPc_NoFrame(UINT8 *buf,UINT8 len);

#endif /* UART_H_ */
