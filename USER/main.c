#include "stm32f10x.h"                  // Device header
#include "can.h"
#include "usart1.h"
#include "key.h"
#include "delay.h"

int main()
{	u8 rec[6]={20,21,22,23,24,25};
	u8 i,len;
	u8 key;
	u8 b; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	usart_Init();
	can1_Init();
	KEY_Init();
	delay_init();
	while(1)
	{
		key=KEY_Scan();
		if(key==5)
		{
			delay_ms(10);
			if(key==5)
			{		
				printf("Send Date:\r\n");
				len=sizeof(rec);
				for(i=0;i<len;i++)
				{
					printf("%d ",rec[i]);
				}
				printf("\r\n");
				b=can_Send(rec,6);
				if(b==0)
				{
					printf("Failed");
					printf("\r\n");

				}
			}
			
		}
	}
}
