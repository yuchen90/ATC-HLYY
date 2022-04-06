//以电流与电压反馈的占比时间来判断电流与电压是否正常
#include "main.h"
#include "declaration.h"

void OPT_CAN_Send(unsigned int SID,unsigned char data[]);

/**
  * @brief  对应电流与电压读取引脚初始化
  * @param  None
  * @retval None
  */
void VACheck_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_Init;

    __HAL_RCC_GPIOA_CLK_ENABLE();           	//开启GPIOA时钟
	__HAL_RCC_GPIOB_CLK_ENABLE();               //开启GPIOB时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();               //开启GPIOC时钟
    __HAL_RCC_GPIOD_CLK_ENABLE();               //开启GPIOD时钟

    //PA 2,4,6,8，15
    GPIO_Init.Pin = GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_15; 	
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PB 0，3，4，5，10，12，14
    GPIO_Init.Pin = GPIO_PIN_0|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_14; 
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOB,&GPIO_Init);

    //PC 0，2，4，6，7，8，9，10，11，12，14
    GPIO_Init.Pin = GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_14;
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	     //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOC,&GPIO_Init);

    //PD 2
    GPIO_Init.Pin = GPIO_PIN_2; 	
    GPIO_Init.Mode = GPIO_MODE_INPUT;  	    //输入
    GPIO_Init.Pull = GPIO_PULLUP;          	//上拉
    GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;    //高速
    HAL_GPIO_Init(GPIOD,&GPIO_Init);
}

/**
  * @brief  对应电流与电压读取引脚初始化
  * @param  None
  * @retval None
  */
void VACheck(void)
{
    if(Sytem_Timer_Fg < 400)      //40ms查询400次，0.1ms一次
    {
        if(Sytem_Timer_Fg == 10u)
            CAN_Rx_LED = LED_OFF;
        if(VACheck_Fg == 0u)
        {
            VACheck_Fg = 1u;    
        // 灯组1    
            {
                if(R1_Volatge_State == 0u)
                {
                    if(R1_Volatge_Count < 400u)
                    R1_Volatge_Count++;
                }
                if(R1_Current_State == 0u)
                {
                    if(R1_Current_Count < 400u)
                    R1_Current_Count++;
                }
                if(Y1_Volatge_State == 0u)
                {
                    if(Y1_Volatge_Count < 400u)
                    Y1_Volatge_Count++;
                }
                if(Y1_Current_State == 0u)
                {
                    if(Y1_Current_Count < 400u)
                    Y1_Current_Count++;
                }
                if(G1_Volatge_State == 0u)
                {
                    if(G1_Volatge_Count < 400u)
                    G1_Volatge_Count++;
                }
                if(G1_Current_State == 0u)
                {
                    if(G1_Current_Count < 400u)
                    G1_Current_Count++;
                }
            }
            // 灯组2    
            {
                if(R2_Volatge_State == 0u)
                {
                    if(R2_Volatge_Count < 400u)
                    R2_Volatge_Count++;
                }
                if(R2_Current_State == 0u)
                {
                    if(R2_Current_Count < 400u)
                    R2_Current_Count++;
                }
                if(Y2_Volatge_State == 0u)
                {
                    if(Y2_Volatge_Count < 400u)
                    Y2_Volatge_Count++;
                }
                if(Y2_Current_State == 0u)
                {
                    if(Y2_Current_Count < 400u)
                    Y2_Current_Count++;
                }
                if(G2_Volatge_State == 0u)
                {
                    if(G2_Volatge_Count < 400u)
                    G2_Volatge_Count++;
                }
                if(G2_Current_State == 0u)
                {
                    if(G2_Current_Count < 400u)
                    G2_Current_Count++;
                }
            }
            // 灯组3    
            {
                if(R3_Volatge_State == 0u)
                {
                    if(R3_Volatge_Count < 400u)
                    R3_Volatge_Count++;
                }
                if(R3_Current_State == 0u)
                {
                    if(R3_Current_Count < 400u)
                    R3_Current_Count++;
                }
                if(Y3_Volatge_State == 0u)
                {
                    if(Y3_Volatge_Count < 400u)
                    Y3_Volatge_Count++;
                }
                if(Y3_Current_State == 0u)
                {
                    if(Y3_Current_Count < 400u)
                    Y3_Current_Count++;
                }
                if(G3_Volatge_State == 0u)
                {
                    if(G3_Volatge_Count < 400u)
                    G3_Volatge_Count++;
                }
                if(G3_Current_State == 0u)
                {
                    if(G3_Current_Count < 400u)
                    G3_Current_Count++;
                }
            }
            // 灯组4    
            {
                if(R4_Volatge_State == 0u)
                {
                    if(R4_Volatge_Count < 400u)
                    R4_Volatge_Count++;
                }
                if(R4_Current_State == 0u)
                {
                    if(R4_Current_Count < 400u)
                    R4_Current_Count++;
                }
                if(Y4_Volatge_State == 0u)
                {
                    if(Y4_Volatge_Count < 400u)
                    Y4_Volatge_Count++;
                }
                if(Y4_Current_State == 0u)
                {
                    if(Y4_Current_Count < 400u)
                    Y4_Current_Count++;
                }
                if(G4_Volatge_State == 0u)
                {
                    if(G4_Volatge_Count < 400u)
                    G4_Volatge_Count++;
                }
                if(G4_Current_State == 0u)
                {
                    if(G4_Current_Count < 400u)
                    G4_Current_Count++;
                }
            }
        }   
    }
    else if(Sytem_Timer_Fg == CAN_Send_Wait_Time) // 到达回码时间后计算电压，电流占比，1：正常， 0：异常
    {
        if(R1_Volatge_Count > Voltage_Count)    R1_Volatge_Fg = 1u; else    R1_Volatge_Fg = 0u;   
        if(R1_Current_Count > Current_Count)    R1_Current_Fg = 1u; else    R1_Current_Fg = 0u;   
        if(Y1_Volatge_Count > Voltage_Count)    Y1_Volatge_Fg = 1u; else    Y1_Volatge_Fg = 0u;   
        if(Y1_Current_Count > Current_Count)    Y1_Current_Fg = 1u; else    Y1_Current_Fg = 0u;   
        if(G1_Volatge_Count > Voltage_Count)    G1_Volatge_Fg = 1u; else    G1_Volatge_Fg = 0u;   
        if(G1_Current_Count > Current_Count)    G1_Current_Fg = 1u; else    G1_Current_Fg = 0u;  

        if(R2_Volatge_Count > Voltage_Count)    R2_Volatge_Fg = 1u; else    R2_Volatge_Fg = 0u;   
        if(R2_Current_Count > Current_Count)    R2_Current_Fg = 1u; else    R2_Current_Fg = 0u;   
        if(Y2_Volatge_Count > Voltage_Count)    Y2_Volatge_Fg = 1u; else    Y2_Volatge_Fg = 0u;   
        if(Y2_Current_Count > Current_Count)    Y2_Current_Fg = 1u; else    Y2_Current_Fg = 0u;   
        if(G2_Volatge_Count > Voltage_Count)    G2_Volatge_Fg = 1u; else    G2_Volatge_Fg = 0u;   
        if(G2_Current_Count > Current_Count)    G2_Current_Fg = 1u; else    G2_Current_Fg = 0u;

        if(R3_Volatge_Count > Voltage_Count)    R3_Volatge_Fg = 1u; else    R3_Volatge_Fg = 0u;   
        if(R3_Current_Count > Current_Count)    R3_Current_Fg = 1u; else    R3_Current_Fg = 0u;   
        if(Y3_Volatge_Count > Voltage_Count)    Y3_Volatge_Fg = 1u; else    Y3_Volatge_Fg = 0u;   
        if(Y3_Current_Count > Current_Count)    Y3_Current_Fg = 1u; else    Y3_Current_Fg = 0u;   
        if(G3_Volatge_Count > Voltage_Count)    G3_Volatge_Fg = 1u; else    G3_Volatge_Fg = 0u;   
        if(G3_Current_Count > Current_Count)    G3_Current_Fg = 1u; else    G3_Current_Fg = 0u;

        if(R4_Volatge_Count > Voltage_Count)    R4_Volatge_Fg = 1u; else    R4_Volatge_Fg = 0u;   
        if(R4_Current_Count > Current_Count)    R4_Current_Fg = 1u; else    R4_Current_Fg = 0u;   
        if(Y4_Volatge_Count > Voltage_Count)    Y4_Volatge_Fg = 1u; else    Y4_Volatge_Fg = 0u;   
        if(Y4_Current_Count > Current_Count)    Y4_Current_Fg = 1u; else    Y4_Current_Fg = 0u;   
        if(G4_Volatge_Count > Voltage_Count)    G4_Volatge_Fg = 1u; else    G4_Volatge_Fg = 0u;   
        if(G4_Current_Count > Current_Count)    G4_Current_Fg = 1u; else    G4_Current_Fg = 0u; 
    
        // 按反馈情况添加反馈CAN数据到相应位置
        {
            uint16_t VACheck_Data[4];
            uint16_t i,j;
            
            for(i=0u;i<4u;i++)  {VACheck_Data[i] = 0u;}

        //    灯组1 按协议判断对应电流与电压状态 由低位到高位左移 
            i = 0u;
            if(R1_Current_Fg == 1u) {i+=1u;}     i=i<<1u;
            if(R1_Volatge_Fg == 1u) {i+=1u;}     i=i<<1u;       
            if(Y1_Current_Fg == 1u) {i+=1u;}     i=i<<1u;
            if(Y1_Volatge_Fg == 1u) {i+=1u;}     i=i<<1u;
            if(G1_Current_Fg == 1u) {i+=1u;}     i=i<<1u;
            if(G1_Volatge_Fg == 1u) {i+=1u;}     i=i<<1u;
            VACheck_Data[0] = i;
            // 灯组2
            i = 0u;
            if(R2_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(R2_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;       
            if(Y2_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(Y2_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(G2_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(G2_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            VACheck_Data[1] = i;
            // 灯组3
            i = 0u;
            if(R3_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(R3_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(Y3_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(Y3_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(G3_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(G3_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            VACheck_Data[2] = i;
            // 灯组4
            i = 0u;
            if(R4_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(R4_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(Y4_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(Y4_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(G4_Current_Fg == 1u) {i+=1u;}    i=i<<1u;
            if(G4_Volatge_Fg == 1u) {i+=1u;}    i=i<<1u;
            VACheck_Data[3] = i;

            // 按协议判断上面4个灯组具体情况，组装CAN数据
            for(i=0u;i<4u;i++)
            {
                j = 0u;
                j =  VACheck_Data[i];
                switch(Channel_State[i])                           //注意组装最低3位时，杭州代码没有加对应点灯编号，都默认为0，此处把其加入最低3位
                {
                    case 0:                     //灭灯
                        if(j==0u)
                        {
                            j=j<<6u;
                            j+=Channel_State[i];
                        }
                        else
                        {
                            j=j<<6u;
                            j=j+0x08u;          
                            j+=Channel_State[i];
                        }
                    break;

                    case 1:                    //绿灯
                        if(j==0x30u)            //正常
                        {
                            j=j<<6u;
                            j+=Channel_State[i];
                        }
                        else                    //异常
                        {
                            if((j&0x30u)==0x30u) //电压电流正常，但其它值异常
                            {                        
                                j=j<<6u;
                                j=j+0x08u;      
                                j+=Channel_State[i];
                            }
                            else if((j&0x30u)==0x10u) //有电流，无电压
                            {
                                j=j<<6u;
                                j=j+0x28u;          
                                j+=Channel_State[i];
                            }
                            else if((j&0x30u)==0x20u) //有电压，无电流
                            {                            
                                j=j<<6u;
                                j=j+0x18u;          
                                j+=Channel_State[i]; 
                            }
                            else
                            {
                                j=j<<6u;
                                j=j+0x38u;          
                                j+=Channel_State[i]; 
                            }
                        }
                    break;

                    case 2:                     //黄灯
                        if(j==0x0cu)            //正常
                        {
                            j=j<<6u;
                            j+=Channel_State[i];
                        }
                        else                    //异常
                        {
                            if((j&0x0cu)==0x0cu) //电压电流正常，但其它值异常
                            {                        
                                j=j<<6u;
                                j=j+0x08u;      
                                j+=Channel_State[i];
                            }
                            else if((j&0x0cu)==0x04u) //有电流，无电压
                            {
                                j=j<<6u;
                                j=j+0x28u;          
                                j+=Channel_State[i];
                            }
                            else if((j&0x0cu)==0x08u) //有电压，无电流
                            {                            
                                j=j<<6u;
                                j=j+0x18u;          
                                j+=Channel_State[i]; 
                            }
                            else
                            {
                                j=j<<6u;
                                j=j+0x38u;          
                                j+=Channel_State[i]; 
                            }
                        }
                    break;

                    case 3:                     //红灯
                        if(j==0x03u)            //正常
                        {
                            j=j<<6u;
                            j+=Channel_State[i];
                        }
                        else                    //异常
                        {
                            if((j&0x03u)==0x03u) //电压电流正常，但其它值异常
                            {                        
                                j=j<<6u;
                                j=j+0x08u;      
                                j+=Channel_State[i];
                            }
                            else if((j&0x03u)==0x04u) //有电流，无电压
                            {
                                j=j<<6u;
                                j=j+0x28u;          
                                j+=Channel_State[i];
                            }
                            else if((j&0x03u)==0x08u) //有电压，无电流
                            {                            
                                j=j<<6u;
                                j=j+0x18u;          
                                j+=Channel_State[i]; 
                            }
                            else
                            {
                                j=j<<6u;
                                j=j+0x38u;          
                                j+=Channel_State[i]; 
                            }
                        }
                    break;

                    case 4:                     //绿闪
                        if(Blink_Id==0u)        //灭
                        {
                            if (j==0u)             //正常
                            {
                                j+=Channel_State[i]; 
                            }
                            else                   //异常
                            {
                                j=j<<6u;
                                j=j+0x08u;         
                                j+=Channel_State[i]; 
                            }
                        }
                        else                   //亮
                        {
                            if(j==0x30u)            //正常
                            {
                                j=j<<6u;
                                j=j+0x08u;
                                j+=Channel_State[i];
                            }
                            else                    //异常
                            {
                                if((j&0x30u)==0x30u) //电压电流正常，但其它值异常
                                {                        
                                    j=j<<6u;
                                    j=j+0x08u;      
                                    j+=Channel_State[i];
                                }
                                else if((j&0x30u)==0x10u) //有电流，无电压
                                {
                                    j=j<<6u;
                                    j=j+0x28u;          
                                    j+=Channel_State[i];
                                }
                                else if((j&0x30u)==0x20u) //有电压，无电流
                                {                            
                                    j=j<<6u;
                                    j=j+0x18u;          
                                    j+=Channel_State[i]; 
                                }
                                else
                                {
                                    j=j<<6u;
                                    j=j+0x38u;          
                                    j+=Channel_State[i]; 
                                }
                            }  
                        }
                    break;

                    case 5:                     //黄闪   
                        if(Blink_Id == 0u)
                        {
                            if(j==0u)               //正常
                            {
                                j=j<<6u;
                                j+=Channel_State[i];
                            }
                            else
                            {
                                j=j<<6u;
                                j=j+0x08u;
                                j+=Channel_State[i];
                            }
                        }
                        else
                        {
                            if(j==0x0cu)            //正常
                            {
                                j=j<<6u;
                                j+=Channel_State[i];
                            }
                            else                    //异常
                            {
                                if((j&0x0cu)==0x0cu) //电压电流正常，但其它值异常
                                {                        
                                    j=j<<6u;
                                    j=j+0x08u;      
                                    j+=Channel_State[i];
                                }
                                else if((j&0x0cu)==0x04u) //有电流，无电压
                                {
                                    j=j<<6u;
                                    j=j+0x28u;          
                                    j+=Channel_State[i];
                                }
                                else if((j&0x0cu)==0x08u) //有电压，无电流
                                {                            
                                    j=j<<6u;
                                    j=j+0x18u;          
                                    j+=Channel_State[i]; 
                                }
                                else
                                {
                                    j=j<<6u;
                                    j=j+0x38u;          
                                    j+=Channel_State[i]; 
                                }
                            }
                        }
                    break;

                    case 6:                             //红闪
                        if(Blink_Id == 0u)
                        {
                            if(j==0u)
                            {
                                j=j<<6u;
                                j+=Channel_State[i];
                            }
                            else
                            {
                                j=j<<6u;
                                j+=0x08u;
                                j+=Channel_State[i];
                            }
                        }
                        else
                        {
                            if(j==0x03u)            //正常
                            {
                                j=j<<6u;
                                j+=Channel_State[i];
                            }
                            else                    //异常
                            {
                                if((j&0x03u)==0x03u) //电压电流正常，但其它值异常
                                {                        
                                    j=j<<6u;
                                    j=j+0x08u;      
                                    j+=Channel_State[i];
                                }
                                else if((j&0x03u)==0x04u) //有电流，无电压
                                {
                                    j=j<<6u;
                                    j=j+0x28u;          
                                    j+=Channel_State[i];
                                }
                                else if((j&0x03u)==0x08u) //有电压，无电流
                                {                            
                                    j=j<<6u;
                                    j=j+0x18u;          
                                    j+=Channel_State[i]; 
                                }
                                else
                                {
                                    j=j<<6u;
                                    j=j+0x38u;          
                                    j+=Channel_State[i]; 
                                }
                            }
                        }
                    break;

                    case 7:                         //红黄
                        if(j==0x0fu)
                        {
                            j=j<<6u;
                            j+=Channel_State[i];
                        }
                        else
                        {
                            j=j<<6u;
                            j+=0x08u;
                            j+=Channel_State[i];
                        }
                    break;
                }
                VACheck_Data[i] = j;
            }

            // 把点灯结果以CAN结构发送
            {
                int32_t sid;
                uint8_t tx_data[8];
                CAN_Tx_LED = LED_ON;

                sid = Board_Address;
                sid = sid<<3;
                sid += 0x80u;
                sid += VERSION;

                tx_data[0] = VACheck_Data[0]&0xff;
                tx_data[1] = (VACheck_Data[0]>>8)&0xff;
                tx_data[2] = VACheck_Data[1]&0xff;
                tx_data[3] = (VACheck_Data[1]>>8)&0xff;
                tx_data[4] = VACheck_Data[2]&0xff;
                tx_data[5] = (VACheck_Data[2]>>8)&0xff;
                tx_data[6] = VACheck_Data[3]&0xff;
                tx_data[7] = (VACheck_Data[3]>>8)&0xff;

                OPT_CAN_Send(sid,tx_data);
                CAN_VACheck_Send_Fg = 0u;
                CAN_Tx_LED = LED_OFF;
            }
        }
    }
}

/**
  * @brief  所有路灯对应电压与电流占比计数清零
  * @param  None
  * @retval None
  */
void Clear_Check_Count(void)
{
    R1_Volatge_Count = 0u;
    R1_Current_Count = 0u;
    Y1_Volatge_Count = 0u;
    Y1_Current_Count = 0u;
    G1_Volatge_Count = 0u;
    G1_Current_Count = 0u;
    R2_Volatge_Count = 0u;
    R2_Current_Count = 0u;
    Y2_Volatge_Count = 0u;
    Y2_Current_Count = 0u;
    G2_Volatge_Count = 0u;
    G2_Current_Count = 0u;
    R3_Volatge_Count = 0u;
    R3_Current_Count = 0u;
    Y3_Volatge_Count = 0u;
    Y3_Current_Count = 0u;
    G3_Volatge_Count = 0u;
    G3_Current_Count = 0u;
    R4_Volatge_Count = 0u;
    R4_Current_Count = 0u;
    Y4_Volatge_Count = 0u;
    Y4_Current_Count = 0u;
    G4_Volatge_Count = 0u;
    G4_Current_Count = 0u;
}
