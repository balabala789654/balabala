#include "can.h"

void can1_Init(void)
{
	GPIO_InitTypeDef GPIO_Stru;
	CAN_InitTypeDef CAN_Stru;
	CAN_FilterInitTypeDef CAN_FStru;
	NVIC_InitTypeDef NVIC_Stru;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_Stru.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Stru.GPIO_Pin=GPIO_Pin_12;
	GPIO_Stru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Stru);
	
	GPIO_Stru.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Stru.GPIO_Pin=GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_Stru);
	
	CAN_Stru.CAN_ABOM=DISABLE;
	CAN_Stru.CAN_AWUM=DISABLE;
	CAN_Stru.CAN_BS1=CAN_BS1_3tq;
	CAN_Stru.CAN_BS2=CAN_BS2_3tq;
	CAN_Stru.CAN_Mode=CAN_Mode_LoopBack;
	CAN_Stru.CAN_NART=ENABLE;
	CAN_Stru.CAN_Prescaler=4;
	CAN_Stru.CAN_RFLM=DISABLE;
	CAN_Stru.CAN_SJW=CAN_SJW_3tq;
	CAN_Stru.CAN_TTCM=DISABLE;
	CAN_Stru.CAN_TXFP=DISABLE;
	CAN_Init(CAN1,&CAN_Stru);
	
	CAN_FStru.CAN_FilterActivation=ENABLE;
	CAN_FStru.CAN_FilterFIFOAssignment=CAN_Filter_FIFO0;
	CAN_FStru.CAN_FilterIdHigh=0x0000;
	CAN_FStru.CAN_FilterIdLow=0x0000;
	CAN_FStru.CAN_FilterMaskIdHigh=0x0000;
	CAN_FStru.CAN_FilterMaskIdLow=0x0000;
	CAN_FStru.CAN_FilterMode=CAN_FilterMode_IdMask;
	CAN_FStru.CAN_FilterNumber=0;
	CAN_FStru.CAN_FilterScale=CAN_FilterScale_32bit;
	CAN_FilterInit(&CAN_FStru);
	
	NVIC_Stru.NVIC_IRQChannel=USB_LP_CAN1_RX0_IRQn;
	NVIC_Stru.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Stru.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_Stru.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_Stru);
	
	CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
}






u8 can_Send(u8* msg,u8 len)
{
	u8 i;
	u8 mbox;
	CanTxMsg TxMessage;
	
	TxMessage.DLC=len;
	TxMessage.ExtId=0x12;
	TxMessage.IDE=CAN_Id_Standard;
	TxMessage.RTR=CAN_RTR_Data;
	TxMessage.StdId=0x12;
	for(i=0;i<len;i++)
	{
		TxMessage.Data[i]=msg[i];
	}
	CAN_Transmit(CAN1,&TxMessage);
	mbox =	CAN_Transmit(CAN1,&TxMessage);
	i=0;
	if(CAN_TransmitStatus(CAN1,mbox))return 1;//�ɹ�
	else return 0;//ʧ��
}

u8 can_Receive(u8* buf)
{
	u8 i;
	CanRxMsg RxMessage;
	if(CAN_MessagePending(CAN1,CAN_FIFO0)==0)return 0;
	CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);
	for(i=0;i<8;i++)
	{
		buf[i]=RxMessage.Data[i];
	}
	return RxMessage.DLC;
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;
	CAN_Receive(CAN1,0,&RxMessage);
	u8 i;
	printf("OK");
	printf("\r\n");
	printf("Receive Date: \r\n");
	for(i=0;i<6;i++)
	{
		printf("%d ",RxMessage.Data[i]);
	}
	printf("\r\n");
}







