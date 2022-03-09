#include "usart.h"
//#include "led.h"
#include "stm32f10x.h"                  // Device header

void usart_Init(void)
{
	GPIO_InitTypeDef GPIO_Stru;
	USART_InitTypeDef USART_Stru;
	NVIC_InitTypeDef NVIC_Stru;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
	USART_DeInit(USART1);
	GPIO_Stru.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Stru.GPIO_Pin=GPIO_Pin_9;
	GPIO_Stru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Stru);
	
	GPIO_Stru.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Stru.GPIO_Pin=GPIO_Pin_10;
	GPIO_Stru.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Stru);
	
	USART_Stru.USART_BaudRate=115200;
	USART_Stru.USART_WordLength=USART_WordLength_8b;
	USART_Stru.USART_StopBits=USART_StopBits_1;
	USART_Stru.USART_Parity=USART_Parity_No;
	USART_Stru.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Stru.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_Stru);
	
	NVIC_Stru.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Stru.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Stru.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Stru.NVIC_IRQChannelSubPriority=0;
	NVIC_Init(&NVIC_Stru);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
}



//void USART1_IRQHandler(void)
//{
//	extern int c;
//	if(USART_GetITStatus(USART1,USART_IT_RXNE))
//	{
//		c=USART_ReceiveData(USART1);
//		if(c=='1')
//		{
//			LED0=0;
//			USART_SendData(USART1,c);
//		}
//	}
//	
//}




