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
// extern uint8_t LED_VACheck_Fg; 
extern uint8_t VACheck_Fg;
extern uint16_t CAN_Send_Wait_Time;
extern uint8_t CAN_VACheck_Send_Fg;

// 灯组1
extern uint16_t R1_Volatge_Count;
extern uint16_t R1_Current_Count;
extern uint16_t Y1_Volatge_Count;
extern uint16_t Y1_Current_Count;
extern uint16_t G1_Volatge_Count;
extern uint16_t G1_Current_Count;
extern uint8_t R1_Volatge_Fg;
extern uint8_t R1_Current_Fg;
extern uint8_t Y1_Volatge_Fg;
extern uint8_t Y1_Current_Fg;
extern uint8_t G1_Volatge_Fg;
extern uint8_t G1_Current_Fg;
// 灯组2
extern uint16_t R2_Volatge_Count;
extern uint16_t R2_Current_Count;
extern uint16_t Y2_Volatge_Count;
extern uint16_t Y2_Current_Count;
extern uint16_t G2_Volatge_Count;
extern uint16_t G2_Current_Count;
extern uint8_t R2_Volatge_Fg;
extern uint8_t R2_Current_Fg;
extern uint8_t Y2_Volatge_Fg;
extern uint8_t Y2_Current_Fg;
extern uint8_t G2_Volatge_Fg;
extern uint8_t G2_Current_Fg;
// 灯组3
extern uint16_t R3_Volatge_Count;
extern uint16_t R3_Current_Count;
extern uint16_t Y3_Volatge_Count;
extern uint16_t Y3_Current_Count;
extern uint16_t G3_Volatge_Count;
extern uint16_t G3_Current_Count;
extern uint8_t R3_Volatge_Fg;
extern uint8_t R3_Current_Fg;
extern uint8_t Y3_Volatge_Fg;
extern uint8_t Y3_Current_Fg;
extern uint8_t G3_Volatge_Fg;
extern uint8_t G3_Current_Fg;
// 灯组4
extern uint16_t R4_Volatge_Count;
extern uint16_t R4_Current_Count;
extern uint16_t Y4_Volatge_Count;
extern uint16_t Y4_Current_Count;
extern uint16_t G4_Volatge_Count;
extern uint16_t G4_Current_Count;
extern uint8_t R4_Volatge_Fg;
extern uint8_t R4_Current_Fg;
extern uint8_t Y4_Volatge_Fg;
extern uint8_t Y4_Current_Fg;
extern uint8_t G4_Volatge_Fg;
extern uint8_t G4_Current_Fg;

#endif
