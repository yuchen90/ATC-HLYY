#include "main.h"
#include "declaration.h"

/**
  * @brief  接管后检查灯控板反馈电流，电压信息
  * @param  None
  * @retval None
  */
void Check_Opt_Reply(void)
{
    uint8_t i,j;
    uint64_t tmp;

    //读取10块灯控板 是否需电压、流反馈，并存储于 Opt_Reply_State[i].Check_Enable
    for(i=0u;i<5u;i++)
    {
        if((Opt_CheckReplyState_1st>>i) & 0x10u)
            Opt_Reply_State[i].Check_Enable=1u;
        else
            Opt_Reply_State[i].Check_Enable=0u;

        if((Opt_CheckReplyState_1st>>i) & 0x10u)
            Opt_Reply_State[i+5u].Check_Enable=1u;
        else
            Opt_Reply_State[i+5u].Check_Enable=0u;
    }

    //检查反馈电流，电压信息
    for(i=0u;i<10u;i++)
    {
        if(Opt_Reply_State[i].Check_Enable == 1u)
        {
            if(Opt_Reply_Buff[i].ReplyState == 0u)                                      //没回码
            {
                Opt_Reply_State[i].No_Reply_Times+=1u;
                if(Opt_Reply_State[i].No_Reply_Times > ERROR_TIME)
                {
                    TakeOver_Enable=0u;
                    YBlink_Enable=0u;
                    return;
                }
            }
            else                                                                        //有回码
            {
                tmp=0u;
                
                //解析反馈信息
                for(j=0u;j<8u;j++)
                {
                    tmp=tmp<<8u;
                    tmp+=Opt_Reply_Buff[i].Data[7u-j];
                }
                for(j=0u;j<4u;j++)                                                      
                {
                    Opt_Reply_Buff[i].LightColour[j]=(tmp>>(j*16u))&0x07u;              //第i块灯控板第j个通道的点灯状态
                    Opt_Reply_Buff[i].LightState[j]=(tmp>>(j*16u+3u))&0x01u;            //第i块灯控板第j个通道是否正常 0：正常； 1：异常

                    Opt_Reply_Buff[i].RedCurrent[j]=(tmp>>(j+16u+6u))&0x01u;            //第i块灯控板第j个通道的红灯电流状况 0：无，1：有
                    Opt_Reply_Buff[i].RedVoltage[j]=(tmp>>(j+16u+7u))&0x01u;            //第i块灯控板第j个通道的红灯电压状况

                    Opt_Reply_Buff[i].YellowCurrent[j]=(tmp>>(j+16u+8u))&0x01u;         //第i块灯控板第j个通道的黄灯电流状况 0：无，1：有      
                    Opt_Reply_Buff[i].YellowVoltage[j]=(tmp>>(j+16u+9u))&0x01u;         //第i块灯控板第j个通道的黄灯电压状况

                    Opt_Reply_Buff[i].GreenCurrent[j]=(tmp>>(j+16u+10u))&0x01u;         //第i块灯控板第j个通道的绿灯电流状况 0：无，1：有
                    Opt_Reply_Buff[i].GreenVoltage[j]=(tmp>>(j+16u+11u))&0x01u;         //第i块灯控板第j个通道的绿灯电压状况
                }

                //校验分析
                for(j=0u;j<4u;j++)
                {
                    if(Opt_Reply_Buff[i].LightColour[j] == 0u)                          //灭灯
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //红电流
                        {
                            Opt_Reply_State[i].Received_RC_times[j]=Opt_Reply_State[i].Received_RC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RC_times[j]=ERROR_TIME;
                                //此处有判断，但是杭州代码 注释掉了
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //红电压
                        {
                            Opt_Reply_State[i].Received_RV_times[j]=Opt_Reply_State[i].Received_RV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RV_times[j]=ERROR_TIME;
                                //此处有判断，但是杭州代码 注释掉了
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RV_times[j]=0u;

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //黄电流
                        {
                            Opt_Reply_State[i].Received_YC_times[j]=Opt_Reply_State[i].Received_YC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YC_times[j]=ERROR_TIME;
                                //此处有判断，但是杭州代码 注释掉了
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //黄电压
                        {
                            Opt_Reply_State[i].Received_YV_times[j]=Opt_Reply_State[i].Received_YV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YV_times[j]=ERROR_TIME;
                                //此处有判断，但是杭州代码 注释掉了
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YV_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //绿电流
                        {
                            Opt_Reply_State[i].Received_GC_times[j]=Opt_Reply_State[i].Received_GC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GC_times[j]=ERROR_TIME;
                                //此处有判断，但是杭州代码 注释掉了
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //绿电压
                        {
                            Opt_Reply_State[i].Received_GV_times[j]=Opt_Reply_State[i].Received_GV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GV_times[j]=ERROR_TIME;
                                //此处有判断，但是杭州代码 注释掉了
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GV_times[j]=0u;
                    }

                    //绿灯，含绿闪
                    else if((Opt_Reply_Buff[i].LightColour[j] == 1u) || (Opt_Reply_Buff[i].LightColour[j] == 4u))         
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //红电流
                        {
                            Opt_Reply_State[i].Received_RC_times[j]=Opt_Reply_State[i].Received_RC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //红电压
                        {
                            Opt_Reply_State[i].Received_RV_times[j]=Opt_Reply_State[i].Received_RV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RV_times[j]=0u;

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //黄电流
                        {
                            Opt_Reply_State[i].Received_YC_times[j]=Opt_Reply_State[i].Received_YC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //黄电压
                        {
                            Opt_Reply_State[i].Received_YV_times[j]=Opt_Reply_State[i].Received_YV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YV_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 0u)           //绿电流
                        {
                            Opt_Reply_State[i].Green_Received_GC_times[j]=Opt_Reply_State[i].Green_Received_GC_times[j]+1u;
                            if(Opt_Reply_State[i].Green_Received_GC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Green_Received_GC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Green_Received_GC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 0u)           //绿电压
                        {
                            Opt_Reply_State[i].Green_Received_GV_times[j]=Opt_Reply_State[i].Green_Received_GV_times[j]+1u;
                            if(Opt_Reply_State[i].Green_Received_GV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Green_Received_GV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Green_Received_GV_times[j]=0u;
                    }

                    //黄灯
                    else if((Opt_Reply_Buff[i].LightColour[j] == 2u) || (Opt_Reply_Buff[i].LightColour[j] == 5u))
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //红电流
                        {
                            Opt_Reply_State[i].Received_RC_times[j]=Opt_Reply_State[i].Received_RC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //红电压
                        {
                            Opt_Reply_State[i].Received_RV_times[j]=Opt_Reply_State[i].Received_RV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RV_times[j]=0u;

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //黄电流
                        {
                            Opt_Reply_State[i].Yellow_Received_YC_times[j]=Opt_Reply_State[i].Yellow_Received_YC_times[j]+1u;
                            if(Opt_Reply_State[i].Yellow_Received_YC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Yellow_Received_YC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Yellow_Received_YC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //黄电压
                        {
                            Opt_Reply_State[i].Yellow_Received_YV_times[j]=Opt_Reply_State[i].Yellow_Received_YV_times[j]+1u;
                            if(Opt_Reply_State[i].Yellow_Received_YV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Yellow_Received_YV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Yellow_Received_YV_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //绿电流
                        {
                            Opt_Reply_State[i].Received_GC_times[j]=Opt_Reply_State[i].Received_GC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //绿电压
                        {
                            Opt_Reply_State[i].Received_GV_times[j]=Opt_Reply_State[i].Received_GV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GV_times[j]=0u;
                    }

                    //红灯
                    else if((Opt_Reply_Buff[i].LightColour[j] == 3u) || (Opt_Reply_Buff[i].LightColour[j] == 6u))
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //红电流
                        {
                            Opt_Reply_State[i].Red_Received_RC_times[j]=Opt_Reply_State[i].Red_Received_RC_times[j]+1u;
                            if(Opt_Reply_State[i].Red_Received_RC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Red_Received_RC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Red_Received_RC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //红电压
                        {
                            Opt_Reply_State[i].Red_Received_RV_times[j]=Opt_Reply_State[i].Red_Received_RV_times[j]+1u;
                            if(Opt_Reply_State[i].Red_Received_RV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Red_Received_RV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Red_Received_RV_times[j]=0u;

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //黄电流
                        {
                            Opt_Reply_State[i].Received_YC_times[j]=Opt_Reply_State[i].Received_YC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //黄电压
                        {
                            Opt_Reply_State[i].Received_YV_times[j]=Opt_Reply_State[i].Received_YV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YV_times[j]=0u;

                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //绿电流
                        {
                            Opt_Reply_State[i].Received_GC_times[j]=Opt_Reply_State[i].Received_GC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //绿电压
                        {
                            Opt_Reply_State[i].Received_GV_times[j]=Opt_Reply_State[i].Received_GV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GV_times[j]=0u;
                    }

                    //红黄
                    else if(Opt_Reply_Buff[i].LightColour[j] == 7u)
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //红电流
                        {
                            Opt_Reply_State[i].Red_Received_RC_times[j]=Opt_Reply_State[i].Red_Received_RC_times[j]+1u;
                            if(Opt_Reply_State[i].Red_Received_RC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Red_Received_RC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Red_Received_RC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //红电压
                        {
                            Opt_Reply_State[i].Red_Received_RV_times[j]=Opt_Reply_State[i].Red_Received_RV_times[j]+1u;
                            if(Opt_Reply_State[i].Red_Received_RV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Red_Received_RV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Red_Received_RV_times[j]=0u;

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //黄电流
                        {
                            Opt_Reply_State[i].Yellow_Received_YC_times[j]=Opt_Reply_State[i].Yellow_Received_YC_times[j]+1u;
                            if(Opt_Reply_State[i].Yellow_Received_YC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Yellow_Received_YC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Yellow_Received_YC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //黄电压
                        {
                            Opt_Reply_State[i].Yellow_Received_YV_times[j]=Opt_Reply_State[i].Yellow_Received_YV_times[j]+1u;
                            if(Opt_Reply_State[i].Yellow_Received_YV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Yellow_Received_YV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Yellow_Received_YV_times[j]=0u;

                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //绿电流
                        {
                            Opt_Reply_State[i].Received_GC_times[j]=Opt_Reply_State[i].Received_GC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GC_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_ACheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //绿电压
                        {
                            Opt_Reply_State[i].Received_GV_times[j]=Opt_Reply_State[i].Received_GV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GV_times[j]=ERROR_TIME;
                                if((Error_YBlink_Enable == 1u) && (Opt_VCheck_Enable == 1u))
                                {
                                    TakeOver_Enable=0u;
                                    Y_FLASH_ENABLE=0u;
                                    return;
                                }
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GV_times[j]=0u;
                    }
                }
            }
        }
    }
}
