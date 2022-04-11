#include "main.h"
#include "declaration.h"

/**
  * @brief  �ӹܺ���ƿذ巴����������ѹ��Ϣ
  * @param  None
  * @retval None
  */
void Check_Opt_Reply(void)
{
    uint8_t i,j;
    uint64_t tmp;

    //��ȡ10��ƿذ� �Ƿ����ѹ�������������洢�� Opt_Reply_State[i].Check_Enable
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

    //��鷴����������ѹ��Ϣ
    for(i=0u;i<10u;i++)
    {
        if(Opt_Reply_State[i].Check_Enable == 1u)
        {
            if(Opt_Reply_Buff[i].ReplyState == 0u)                                      //û����
            {
                Opt_Reply_State[i].No_Reply_Times+=1u;
                if(Opt_Reply_State[i].No_Reply_Times > ERROR_TIME)
                {
                    TakeOver_Enable=0u;
                    YBlink_Enable=0u;
                    return;
                }
            }
            else                                                                        //�л���
            {
                tmp=0u;
                
                //����������Ϣ
                for(j=0u;j<8u;j++)
                {
                    tmp=tmp<<8u;
                    tmp+=Opt_Reply_Buff[i].Data[7u-j];
                }
                for(j=0u;j<4u;j++)                                                      
                {
                    Opt_Reply_Buff[i].LightColour[j]=(tmp>>(j*16u))&0x07u;              //��i��ƿذ��j��ͨ���ĵ��״̬
                    Opt_Reply_Buff[i].LightState[j]=(tmp>>(j*16u+3u))&0x01u;            //��i��ƿذ��j��ͨ���Ƿ����� 0�������� 1���쳣

                    Opt_Reply_Buff[i].RedCurrent[j]=(tmp>>(j+16u+6u))&0x01u;            //��i��ƿذ��j��ͨ���ĺ�Ƶ���״�� 0���ޣ�1����
                    Opt_Reply_Buff[i].RedVoltage[j]=(tmp>>(j+16u+7u))&0x01u;            //��i��ƿذ��j��ͨ���ĺ�Ƶ�ѹ״��

                    Opt_Reply_Buff[i].YellowCurrent[j]=(tmp>>(j+16u+8u))&0x01u;         //��i��ƿذ��j��ͨ���ĻƵƵ���״�� 0���ޣ�1����      
                    Opt_Reply_Buff[i].YellowVoltage[j]=(tmp>>(j+16u+9u))&0x01u;         //��i��ƿذ��j��ͨ���ĻƵƵ�ѹ״��

                    Opt_Reply_Buff[i].GreenCurrent[j]=(tmp>>(j+16u+10u))&0x01u;         //��i��ƿذ��j��ͨ�����̵Ƶ���״�� 0���ޣ�1����
                    Opt_Reply_Buff[i].GreenVoltage[j]=(tmp>>(j+16u+11u))&0x01u;         //��i��ƿذ��j��ͨ�����̵Ƶ�ѹ״��
                }

                //У�����
                for(j=0u;j<4u;j++)
                {
                    if(Opt_Reply_Buff[i].LightColour[j] == 0u)                          //���
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //�����
                        {
                            Opt_Reply_State[i].Received_RC_times[j]=Opt_Reply_State[i].Received_RC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RC_times[j]=ERROR_TIME;
                                //�˴����жϣ����Ǻ��ݴ��� ע�͵���
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //���ѹ
                        {
                            Opt_Reply_State[i].Received_RV_times[j]=Opt_Reply_State[i].Received_RV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_RV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_RV_times[j]=ERROR_TIME;
                                //�˴����жϣ����Ǻ��ݴ��� ע�͵���
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_RV_times[j]=0u;

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //�Ƶ���
                        {
                            Opt_Reply_State[i].Received_YC_times[j]=Opt_Reply_State[i].Received_YC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YC_times[j]=ERROR_TIME;
                                //�˴����жϣ����Ǻ��ݴ��� ע�͵���
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //�Ƶ�ѹ
                        {
                            Opt_Reply_State[i].Received_YV_times[j]=Opt_Reply_State[i].Received_YV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_YV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_YV_times[j]=ERROR_TIME;
                                //�˴����жϣ����Ǻ��ݴ��� ע�͵���
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_YV_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //�̵���
                        {
                            Opt_Reply_State[i].Received_GC_times[j]=Opt_Reply_State[i].Received_GC_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GC_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GC_times[j]=ERROR_TIME;
                                //�˴����жϣ����Ǻ��ݴ��� ע�͵���
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GC_times[j]=0u;
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //�̵�ѹ
                        {
                            Opt_Reply_State[i].Received_GV_times[j]=Opt_Reply_State[i].Received_GV_times[j]+1u;
                            if(Opt_Reply_State[i].Received_GV_times[j]>ERROR_TIME)
                            {
                                Opt_Reply_State[i].Received_GV_times[j]=ERROR_TIME;
                                //�˴����жϣ����Ǻ��ݴ��� ע�͵���
                            }
                        }
                        else
                            Opt_Reply_State[i].Received_GV_times[j]=0u;
                    }

                    //�̵ƣ�������
                    else if((Opt_Reply_Buff[i].LightColour[j] == 1u) || (Opt_Reply_Buff[i].LightColour[j] == 4u))         
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //�����
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
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //���ѹ
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

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //�Ƶ���
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
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //�Ƶ�ѹ
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
                        
                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 0u)           //�̵���
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
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 0u)           //�̵�ѹ
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

                    //�Ƶ�
                    else if((Opt_Reply_Buff[i].LightColour[j] == 2u) || (Opt_Reply_Buff[i].LightColour[j] == 5u))
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //�����
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
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //���ѹ
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

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //�Ƶ���
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
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //�Ƶ�ѹ
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
                        
                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //�̵���
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
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //�̵�ѹ
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

                    //���
                    else if((Opt_Reply_Buff[i].LightColour[j] == 3u) || (Opt_Reply_Buff[i].LightColour[j] == 6u))
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //�����
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
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //���ѹ
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

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //�Ƶ���
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
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //�Ƶ�ѹ
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

                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //�̵���
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
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //�̵�ѹ
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

                    //���
                    else if(Opt_Reply_Buff[i].LightColour[j] == 7u)
                    {
                        if(Opt_Reply_Buff[i].RedCurrent[j] == 1u)           //�����
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
                        
                        if(Opt_Reply_Buff[i].RedVoltage[j] == 1u)           //���ѹ
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

                        if(Opt_Reply_Buff[i].YellowCurrent[j] == 1u)           //�Ƶ���
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
                        
                        if(Opt_Reply_Buff[i].YellowVoltage[j] == 1u)           //�Ƶ�ѹ
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

                        if(Opt_Reply_Buff[i].GreenCurrent[j] == 1u)           //�̵���
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
                        
                        if(Opt_Reply_Buff[i].GreenVoltage[j] == 1u)           //�̵�ѹ
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
