#include "main.h"
#include "declaration.h"

void CAN_Error_Handler(void);

/**
  * @brief  CAN对应外设功能初始化
  * @param  None
  * @retval None
  */
void CAN1_Init(void)
{
    CAN_FilterTypeDef CAN_Filter;
    //初始化CAN 模式以及基准时间长度 600Kbps
    CAN_Handle.Instance = CAN1;                             //选择CAN1的相关地址为寄存器地址
    //SS=1,TS1=7,TS2=2,得到80%的采样率。适合500k到800k 间的baud-rate 
    CAN_Handle.Init.TimeTriggeredMode = DISABLE;         	  //禁止时间触发通信模式
    CAN_Handle.Init.AutoBusOff = DISABLE;                	  //禁止自动离线管理
    CAN_Handle.Init.AutoWakeUp = DISABLE;               	  //睡眠模式通过清除sleep位来唤醒
    CAN_Handle.Init.AutoRetransmission = ENABLE;        	  //报文不支持不自动重装
    CAN_Handle.Init.ReceiveFifoLocked = DISABLE;         	  //接收溢出时，FIFO未锁定 
    CAN_Handle.Init.TransmitFifoPriority= DISABLE;       	  //发送的优先级由标示符的大小决定
    CAN_Handle.Init.Mode = CAN_MODE_NORMAL;               	//注明CAN运行的模式，当前是NORMAL
    CAN_Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;         	  //选择重新同步前允许缩放一个bit的time quanta, 允许输入1-4，一般默认1tq. 当控制器设置的 SJW 极限值较大时，可以吸收的误差加大，但通讯的速度会下降
    CAN_Handle.Init.TimeSeg1 = CAN_BS1_7TQ;               	//允许1-16间整数 
    CAN_Handle.Init.TimeSeg2 = CAN_BS2_2TQ;              	  //允许1-8间整数 
    CAN_Handle.Init.Prescaler = 6u;                       	//允许输入1-1024间整数，注明一个time quanta的长度,APB1分频后频率除以Prescaler得到的频率的倒数就是一个tq

    #if CAN1_EN 
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)               	  //HAL_CAN_Init()是把上述参数装载至寄存器,使能CAN1,判断寄存器装填是否成功，若不成功则执行Error_Handler()
        CAN_Error_Handler();    
                              
    /*CAN1 CAN2共用筛选器组 CAN1使用0-13,CAN2使用14-27*/
    /*< 使用的筛选器组 当前使用筛选器组为0,后续全部为配置此筛选器使用 */
    //初始化CAN的FILTER
    //FIFO 0 配置接SID
    CAN_Filter.FilterBank = 0u;                         	  //使用bank0 CAN1 0-13 
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      	  //Mask模式
    CAN_Filter.FilterScale = CAN_FILTERSCALE_16BIT;     	  //16位的ID， 一个bank可以有一个ID和一个mask 各32位，mask 标注ID对应位是否必须相同
    CAN_Filter.FilterIdHigh = 0X0000u;                  
    CAN_Filter.FilterIdLow = 0X0000u;
    CAN_Filter.FilterMaskIdHigh = 0X0008u;
    CAN_Filter.FilterMaskIdLow = 0X0008u;                   
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; 	  //通过Filter的消息存储在FIFO0 上
    CAN_Filter.FilterActivation = ENABLE;               	  //使能Filter

    //FIFO 1 配置接收EXID
    CAN_Filter.FilterBank = 1u;                         	  //使用bank0 CAN1 0-13 
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      	  //Mask模式
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;     	  //32位的ID， 一个bank可以有一个ID和一个mask 各32位，mask 标注ID对应位是否必须相同
    CAN_Filter.FilterIdHigh = 0X0004u;                  
    CAN_Filter.FilterIdLow = 0X0004u;
    CAN_Filter.FilterMaskIdHigh = 0X0004u;
    CAN_Filter.FilterMaskIdLow = 0X0004u;
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO1; 	  //通过Filter的消息存储在FIFO0 上
    CAN_Filter.FilterActivation = ENABLE;               	  //使能Filter
    
    
    //Configures the CAN reception filter according to the specified parameters in the CAN_FilterInitStruct. 
    if(HAL_CAN_ConfigFilter(&CAN_Handle,&CAN_Filter) != HAL_OK) 
        CAN_Error_Handler(); 
        
    //Start the CAN module
    if(HAL_CAN_Start(&CAN_Handle) != HAL_OK)
        CAN_Error_Handler(); 

    //Active CAN Rx notification(interrupt). 
    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)   //FIFO 0  receive interrupt
        CAN_Error_Handler();

    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)   //FIFO 1  receive interrupt
        CAN_Error_Handler();  
    #endif
}

/**
  * @brief  FIFO 0 的pending中断回调函数    标准帧
  * @param  hcan:CAN句柄对应指针，为形参。由HAL_CAN_IRQHandler()函数对应的实参指针替换
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t i,rx_data[8];
    //利用HAL_CAN_GetRxMessage()函数接收对应CAN报文,数据保存在Rx_data[8]中
    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,rx_data) != HAL_OK)//Get an CAN frame from the Rx FIFO zone into the message RAM. release fifox after read
        CAN_Error_Handler();

    CAN_Id_CANType=(CAN_RxHeader.StdId>>7u)&0x0fu;

    //解析点灯信息
    if(CAN_Id_CANType == 0u)                                    
    {
        CAN_FrameNumber=(CAN_RxHeader.StdId>>7u)&0x0fu;         
        if(CAN_FrameNumber == 1u)                                 //第1帧
        {
            Opt_CheckReplyState_1st=CAN_RxHeader.StdId&0x1fu;
            for(i=0u;i<8u;i++)
                CAN_Buff[i]=rx_data[i];
        }
        else if(CAN_FrameNumber == 2u)                            //第2帧
        {
            Opt_CheckReplyState_2nd=CAN_RxHeader.StdId&0x1fu;
            for(i=8u;i<16u;i++)
                CAN_Buff[i]=rx_data[i];
            CAN_DataRead_Fg=1u;                                     //第2帧接收完毕，接收标识置1
        }
    }

    //解析灯控板反馈信息
    else if(CAN_Id_CANType == 1u)                              
    {
        uint8_t address,i;
        address=(CAN_RxHeader.StdId>>3u)&0x0f;
        if(address <= 9u)                                           //限制索引范围,无符号数 恒大于等于0
        {
            Opt_Reply_Buff[address].ReplyState=1u;
            for(i=0u;i<8u;i++)  
                Opt_Reply_Buff[address].Data[i]=rx_data[i];
        }
    }

    //解析接管配置信息
    else if(CAN_Id_CANType == 3u)                   
    {
        TakeOver_Enable=(CAN_RxHeader.StdId>>6u)&0x01u;    
        YBlink_Enable=(CAN_RxHeader.StdId>>2u)&0x01u;      
        Error_YBlink_Enable=(CAN_RxHeader.StdId>>5u)&0x01u;
        Opt_VCheck_Enable=(CAN_RxHeader.StdId>>4u)&0x01u;  
        Opt_ACheck_Enable=(CAN_RxHeader.StdId>>3u)&0x01u;  
    }
}

/**
  * @brief  FIFO 1 的pending中断回调函数 扩展帧
  * @param  hcan:CAN句柄对应指针，为形参。由HAL_CAN_IRQHandler()函数对应的实参指针替换
  * @retval None
  */
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t i,j,rx_data[8];
    uint32_t tmp=0u;

    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO1,&CAN_RxHeader1,rx_data) != HAL_OK)
        CAN_Error_Handler();
    // CAN_Id_CANType=(CAN_RxHeader.ExtId>>25u)&0x07u;    //硬件过滤
    CAN_FrameNumber=CAN_RxHeader1.ExtId&0x1ffffffu;
    
    // if(CAN_Id_CANType == 2u)
    {
        if(CAN_FrameNumber == 0u)
        {
            CheckSum=rx_data[3];
            CheckSum=CheckSum<<8u;
            CheckSum+=rx_data[2];
            CheckSum=CheckSum<<8u;
            CheckSum+=rx_data[1];
            CheckSum=CheckSum<<8u;
            CheckSum+=rx_data[0];

            ArrayNum=rx_data[5];
            ArrayNum=ArrayNum<<8u;
            ArrayNum+=rx_data[4];

            FrameNum=rx_data[7];
            FrameNum=ArrayNum<<8u;
            FrameNum+=rx_data[6];

        if(ArrayNum > 160u)
        {
            ArrayNum=0u;
            FrameNum=0u;
        }
        }
        else if(CAN_FrameNumber <= FrameNum)
        {
            if(CAN_FrameNumber%2u == 0u)                      //第2包数据
            {
                for(i=0u;i<7u;i++)
                    TakeOver_Structure_Buff[(CAN_FrameNumber-1u)/2u].Cmd[i+8u]=rx_data[i];
                TakeOver_Structure_Buff[(CAN_FrameNumber-1u)/2u].Duration=rx_data[7];
            }
            else                                              //第1包数据
            {
                for(i=0u;i<8u;i++)
                TakeOver_Structure_Buff[(CAN_FrameNumber-1u)/2u].Cmd[i]=rx_data[i];
            }
        
            //校验
            if(CAN_FrameNumber == FrameNum)
            {
                for(j=0u;j<ArrayNum;j++)
                {
                    for(i=0u;i<15u;i++)
                        tmp+=TakeOver_Structure_Buff[j].Cmd[i];
                    tmp+=TakeOver_Structure_Buff[j].Duration;
                }
                if(tmp == CheckSum)
                {
                    for(j=0u;j<ArrayNum;j++)
                    {
                        for(i=0u;i<15u;i++)
                            TakeOver_Structure_Use[j].Cmd[i]=TakeOver_Structure_Buff[j].Cmd[i];
                        TakeOver_Structure_Use[j].Duration=TakeOver_Structure_Buff[j].Duration;
                    }
                    TakeOver_DataNum=ArrayNum;
                }
            } 
        }
    }
}

/**
  * @brief  发送一条CAN数据帧（标准帧）
  * @param  sid:StdId
  * @param  data:发送数据起始地址
  * @retval None
  */
void Power_CAN_Send(uint16_t sid,uint8_t data[8])
{
    uint32_t *mailbox,txmailbox;
    uint16_t i;
    CAN_TxHeader.StdId=sid;
    CAN_TxHeader.IDE=0u;
    CAN_TxHeader.RTR=0u;
    CAN_TxHeader.DLC=8u;
    CAN_TxHeader.TransmitGlobalTime=DISABLE;

    //检查是否有空余的发送mailbox
    while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u) && (i < 0x7fffu))
        i++;
    if(i == 0x7fffu)
        return;

    //请求发送
    i=0u;
    while((HAL_CAN_AddTxMessage(&CAN_Handle,&CAN_TxHeader,data,mailbox) != HAL_OK) && (i < 0x7fffu))
        i++;
    if(i == 0x7fffu)
        return;

    //确认发送是否完成
    txmailbox=*mailbox;
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,txmailbox) != 0u) && (i < 0x7fffu))
        i++;
    if(i == 0x7fffu)
        return;
}

/**
  * @brief  CAN初始化错误，CAN_Rx_LED常亮
  * @param  None
  * @retval None
  */
void CAN_Error_Handler(void)
{
    while(1)
    {
  	    CAN_Rx_LED=LED_ON;
    }
}
