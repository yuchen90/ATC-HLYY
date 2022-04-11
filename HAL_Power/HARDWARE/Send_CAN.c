#include "main.h"
#include "declaration.h"

extern void Power_CAN_Send(uint16_t sid,uint8_t data[8]);
extern void JSY_DataRequest(void);

/**
  * @brief  寻找节拍
  * @param  None
  * @retval None
  */
void Seek_Pointer(void)
{
    uint8_t i,j;
    //解析CAN_Buff 到 CMD中
    for(i=0u;i<7u;i++)
        CMD[i]=CAN_Buff[i];
    for(i=7u;i<15u;i++)
    {
        CMD[i]=(CAN_Buff[i]&0x0fu)+((CAN_Buff[i+1]&0x0fu)<<4u);
    }

    //比较CMD 与接管信息的Cmd 寻找节拍
    for(j=0u;j<TakeOver_DataNum;j++)
    {
        for(i=0u;i<15u;i++)
        {
            if(TakeOver_Structure_Use[j].Cmd[i] != CMD[i])
                break;
        }
        if(i == 15u)
            break;
    }

    if(j < TakeOver_DataNum)
        TakeOver_Pointer=j;
    else
        TakeOver_Pointer=0u;    //最后一个节拍直接重新开始
}

/**
  * @brief  发送电源板反馈信息给主控板
  * @param  None
  * @retval None
  */
void Power_Reply(void)
{
    uint16_t canid;
    uint8_t data[8];

    if(System_Time_Fg >=1200u)
    {
        if(JSY_MK163_ReadBuff[2] > 4u)
        {
            canid=(0x80u+0x50u+VERSION);
            data[7]=JSY_MK163_ReadBuff[3];
            data[6]=JSY_MK163_ReadBuff[4];
            data[5]=JSY_MK163_ReadBuff[5];
            data[4]=JSY_MK163_ReadBuff[6];

            data[3]=0u;
            data[2]=0u;
            data[1]=0u;
            data[0]=0u;

            YBlink_Count1=YBlink_Count2+YBlink_Count1;
            YBlink_Count1=YBlink_Count1/2;
            if(YBlink_Count1 < 0x1000u)
            {
                data[0]=0;
                YBlink_Fg++;
                if(YBlink_Fg > 4u)
                    YBlink_Fg=4u;
            }
            else
            {   
                data[0]=1u;
                YBlink_Fg=0u;
            }

            YBlink_Count1=0u;
            YBlink_Count2=0u;
            YBlink_Count3=0u;
            YBlink_Count4=0u;

            if(YBlink_Fg < 4u)
                data[0]+=0x02;
            if(Error_YBlink_Enable == 1u)
                data[0]+=0x04u;
            if(TakeOver_Enable == 1u)
                data[0]+=0x08u;
            if(TakeOver_DataNum > 0u)
                data[0]+=0x10u;
            
            Power_CAN_Send(canid,data);
        }
        Power_Reply_Fg=0u;
        if(JSY_MK163_ReadRequest_Fg == 0u)              //1 秒查询一次市电输入
            JSY_DataRequest();
    }
}

/**
  * @brief  接管发送点灯CAN
  * @param  n 帧数，从1开始
  * @retval None
  */
 void Light_Opt(uint8_t n)
 {
    uint8_t sendcanbuff1[8]={0},sendcanbuff2[8]={0},i;
    uint16_t canid=0;   //StdId
    
    //清除点灯反馈接收标识
    for(i=0;i<10u;i++)
        Opt_Reply_Buff[i].ReplyState=0u;
    
    //按节拍，从TakeOver_Structure_Use[]中解析出需发送点灯信息的第1和2帧           ！！！！！！此处需与杭州代码比较，看运算速度
    for(i=0u;i<7u;i++)
        sendcanbuff1[i]=TakeOver_Structure_Use[TakeOver_Pointer].Cmd[i];
    sendcanbuff1[7]=TakeOver_Structure_Use[TakeOver_Pointer].Cmd[7]&0x0fu;
    for(i=0u;i<7u;i++)
        sendcanbuff2[i]=((TakeOver_Structure_Use[TakeOver_Pointer].Cmd[i+7u]>>4u)&0x0fu)+((TakeOver_Structure_Use[TakeOver_Pointer].Cmd[i+8u]&0x0fu)<<4u);
    sendcanbuff2[7]=(TakeOver_Structure_Use[TakeOver_Pointer].Cmd[14]>>4u)&0x0fu;

    //按前半秒或是后半秒，发送点灯信息
    //前半秒
    if(n < 3u)                              
    {
        canid=0u;
        canid=Opt_CheckReplyState_1st+0x20u;
        Power_CAN_Send(canid,sendcanbuff1);
        canid=0u;
        canid=Opt_CheckReplyState_2nd+0x40u;
        Power_CAN_Send(canid,sendcanbuff2);
    }
    //后半秒
    else
    {
        canid=0u;
        canid=Opt_CheckReplyState_1st+0x20u;
        sendcanbuff1[7]=sendcanbuff1[7]+0x10u;
        Power_CAN_Send(canid,sendcanbuff1);
        canid=0u;
        canid=Opt_CheckReplyState_2nd+0x40u;
        sendcanbuff2[7]=sendcanbuff2[7]+0x10u;
        Power_CAN_Send(canid,sendcanbuff2);
    }
 }
