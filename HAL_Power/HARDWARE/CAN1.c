#include "main.h"
#include "declaration.h"

void CAN_Error_Handler(void);

/**
  * @brief  CAN��Ӧ���蹦�ܳ�ʼ��
  * @param  None
  * @retval None
  */
void CAN1_Init(void)
{
    CAN_FilterTypeDef CAN_Filter;
    //��ʼ��CAN ģʽ�Լ���׼ʱ�䳤�� 600Kbps
    CAN_Handle.Instance = CAN1;                             //ѡ��CAN1����ص�ַΪ�Ĵ�����ַ
    //SS=1,TS1=7,TS2=2,�õ�80%�Ĳ����ʡ��ʺ�500k��800k ���baud-rate 
    CAN_Handle.Init.TimeTriggeredMode = DISABLE;         	  //��ֹʱ�䴥��ͨ��ģʽ
    CAN_Handle.Init.AutoBusOff = DISABLE;                	  //��ֹ�Զ����߹���
    CAN_Handle.Init.AutoWakeUp = DISABLE;               	  //˯��ģʽͨ�����sleepλ������
    CAN_Handle.Init.AutoRetransmission = ENABLE;        	  //���Ĳ�֧�ֲ��Զ���װ
    CAN_Handle.Init.ReceiveFifoLocked = DISABLE;         	  //�������ʱ��FIFOδ���� 
    CAN_Handle.Init.TransmitFifoPriority= DISABLE;       	  //���͵����ȼ��ɱ�ʾ���Ĵ�С����
    CAN_Handle.Init.Mode = CAN_MODE_NORMAL;               	//ע��CAN���е�ģʽ����ǰ��NORMAL
    CAN_Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;         	  //ѡ������ͬ��ǰ��������һ��bit��time quanta, ��������1-4��һ��Ĭ��1tq. �����������õ� SJW ����ֵ�ϴ�ʱ���������յ����Ӵ󣬵�ͨѶ���ٶȻ��½�
    CAN_Handle.Init.TimeSeg1 = CAN_BS1_7TQ;               	//����1-16������ 
    CAN_Handle.Init.TimeSeg2 = CAN_BS2_2TQ;              	  //����1-8������ 
    CAN_Handle.Init.Prescaler = 6u;                       	//��������1-1024��������ע��һ��time quanta�ĳ���,APB1��Ƶ��Ƶ�ʳ���Prescaler�õ���Ƶ�ʵĵ�������һ��tq

    #if CAN1_EN 
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)               	  //HAL_CAN_Init()�ǰ���������װ�����Ĵ���,ʹ��CAN1,�жϼĴ���װ���Ƿ�ɹ��������ɹ���ִ��Error_Handler()
        CAN_Error_Handler();    
                              
    /*CAN1 CAN2����ɸѡ���� CAN1ʹ��0-13,CAN2ʹ��14-27*/
    /*< ʹ�õ�ɸѡ���� ��ǰʹ��ɸѡ����Ϊ0,����ȫ��Ϊ���ô�ɸѡ��ʹ�� */
    //��ʼ��CAN��FILTER
    //FIFO 0 ���ý�SID
    CAN_Filter.FilterBank = 0u;                         	  //ʹ��bank0 CAN1 0-13 
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      	  //Maskģʽ
    CAN_Filter.FilterScale = CAN_FILTERSCALE_16BIT;     	  //16λ��ID�� һ��bank������һ��ID��һ��mask ��32λ��mask ��עID��Ӧλ�Ƿ������ͬ
    CAN_Filter.FilterIdHigh = 0X0000u;                  
    CAN_Filter.FilterIdLow = 0X0000u;
    CAN_Filter.FilterMaskIdHigh = 0X0008u;
    CAN_Filter.FilterMaskIdLow = 0X0008u;                   
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; 	  //ͨ��Filter����Ϣ�洢��FIFO0 ��
    CAN_Filter.FilterActivation = ENABLE;               	  //ʹ��Filter

    //FIFO 1 ���ý���EXID
    CAN_Filter.FilterBank = 1u;                         	  //ʹ��bank0 CAN1 0-13 
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      	  //Maskģʽ
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;     	  //32λ��ID�� һ��bank������һ��ID��һ��mask ��32λ��mask ��עID��Ӧλ�Ƿ������ͬ
    CAN_Filter.FilterIdHigh = 0X0004u;                  
    CAN_Filter.FilterIdLow = 0X0004u;
    CAN_Filter.FilterMaskIdHigh = 0X0004u;
    CAN_Filter.FilterMaskIdLow = 0X0004u;
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO1; 	  //ͨ��Filter����Ϣ�洢��FIFO0 ��
    CAN_Filter.FilterActivation = ENABLE;               	  //ʹ��Filter
    
    
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
  * @brief  FIFO 0 ��pending�жϻص�����    ��׼֡
  * @param  hcan:CAN�����Ӧָ�룬Ϊ�βΡ���HAL_CAN_IRQHandler()������Ӧ��ʵ��ָ���滻
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t i,rx_data[8];
    //����HAL_CAN_GetRxMessage()�������ն�ӦCAN����,���ݱ�����Rx_data[8]��
    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,rx_data) != HAL_OK)//Get an CAN frame from the Rx FIFO zone into the message RAM. release fifox after read
        CAN_Error_Handler();

    CAN_Id_CANType=(CAN_RxHeader.StdId>>7u)&0x0fu;

    //���������Ϣ
    if(CAN_Id_CANType == 0u)                                    
    {
        CAN_FrameNumber=(CAN_RxHeader.StdId>>7u)&0x0fu;         
        if(CAN_FrameNumber == 1u)                                 //��1֡
        {
            Opt_CheckReplyState_1st=CAN_RxHeader.StdId&0x1fu;
            for(i=0u;i<8u;i++)
                CAN_Buff[i]=rx_data[i];
        }
        else if(CAN_FrameNumber == 2u)                            //��2֡
        {
            Opt_CheckReplyState_2nd=CAN_RxHeader.StdId&0x1fu;
            for(i=8u;i<16u;i++)
                CAN_Buff[i]=rx_data[i];
            CAN_DataRead_Fg=1u;                                     //��2֡������ϣ����ձ�ʶ��1
        }
    }

    //�����ƿذ巴����Ϣ
    else if(CAN_Id_CANType == 1u)                              
    {
        uint8_t address,i;
        address=(CAN_RxHeader.StdId>>3u)&0x0f;
        if(address <= 9u)                                           //����������Χ,�޷����� ����ڵ���0
        {
            Opt_Reply_Buff[address].ReplyState=1u;
            for(i=0u;i<8u;i++)  
                Opt_Reply_Buff[address].Data[i]=rx_data[i];
        }
    }

    //�����ӹ�������Ϣ
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
  * @brief  FIFO 1 ��pending�жϻص����� ��չ֡
  * @param  hcan:CAN�����Ӧָ�룬Ϊ�βΡ���HAL_CAN_IRQHandler()������Ӧ��ʵ��ָ���滻
  * @retval None
  */
void HAL_CAN_RxFifo1FullCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t i,j,rx_data[8];
    uint32_t tmp=0u;

    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO1,&CAN_RxHeader1,rx_data) != HAL_OK)
        CAN_Error_Handler();
    // CAN_Id_CANType=(CAN_RxHeader.ExtId>>25u)&0x07u;    //Ӳ������
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
            if(CAN_FrameNumber%2u == 0u)                      //��2������
            {
                for(i=0u;i<7u;i++)
                    TakeOver_Structure_Buff[(CAN_FrameNumber-1u)/2u].Cmd[i+8u]=rx_data[i];
                TakeOver_Structure_Buff[(CAN_FrameNumber-1u)/2u].Duration=rx_data[7];
            }
            else                                              //��1������
            {
                for(i=0u;i<8u;i++)
                TakeOver_Structure_Buff[(CAN_FrameNumber-1u)/2u].Cmd[i]=rx_data[i];
            }
        
            //У��
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
  * @brief  ����һ��CAN����֡����׼֡��
  * @param  sid:StdId
  * @param  data:����������ʼ��ַ
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

    //����Ƿ��п���ķ���mailbox
    while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u) && (i < 0x7fffu))
        i++;
    if(i == 0x7fffu)
        return;

    //������
    i=0u;
    while((HAL_CAN_AddTxMessage(&CAN_Handle,&CAN_TxHeader,data,mailbox) != HAL_OK) && (i < 0x7fffu))
        i++;
    if(i == 0x7fffu)
        return;

    //ȷ�Ϸ����Ƿ����
    txmailbox=*mailbox;
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,txmailbox) != 0u) && (i < 0x7fffu))
        i++;
    if(i == 0x7fffu)
        return;
}

/**
  * @brief  CAN��ʼ������CAN_Rx_LED����
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
