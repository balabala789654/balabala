#ifndef __CAN_H
#define __CAN_H

#include "sys.h"
void can1_Init(void);
u8 can_Send(u8* msg,u8 len);
u8 can_Receive(u8* buf);

#endif



