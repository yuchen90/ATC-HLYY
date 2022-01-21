#ifndef __DECLARARTION_H
#define __DECLARARTION_H

#include "stdint.h"

extern uint32_t Timer_Fg;        
extern uint32_t Timer_Fg1; 
extern uint8_t Blink_Id;       
extern uint8_t Blink_Id_Old;  
extern uint8_t BOARD_ADDRESS; 
extern uint8_t Can_Buff[8];   
extern uint8_t Light_Buff[4]; 
extern uint8_t CAN_Send_Fg;   
extern uint8_t CAN_Data_Read_Fg; 
extern uint8_t LED_FeedBack_Fg; 
extern uint8_t LED_Check_Fg; 

#endif
