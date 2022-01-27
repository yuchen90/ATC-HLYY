//CAN ͨѶ��ʼ�� �Ѿ� CAN ���պ� CAN���ͺ���
//���ذ�1s �ȷ�4�� ÿ��2֡��һ֡��5����ӣ��� ��������ô4�α���һ���� ����˸ ǰ����2��һ��Ϊ��ƣ������2��һ��Ϊ����
#include "main.h"
#include "declaration.h"

CAN_HandleTypeDef CAN_Handle;
CAN_TxHeaderTypeDef CAN_TxHeader;
CAN_RxHeaderTypeDef CAN_RxHeader;

void Error_Handler(void);

/**
  * @brief  CAN��Ӧ���蹦�ܳ�ʼ��
  * @param  None
  * @retval None
  */
void OPT_CAN_Init(void)
{

    CAN_FilterTypeDef CAN_Filter;
    //��ʼ��CAN ģʽ�Լ���׼ʱ�䳤�� 600Kbps
    CAN_Handle.Instance = CANx;                            //ѡ��CAN1����ص�ַΪ�Ĵ�����ַ
    //SS=1,TS1=7,TS2=2,�õ�80%�Ĳ����ʡ��ʺ�500k��800k ���baud-rate 
    CAN_Handle.Init.TimeTriggeredMode = DISABLE;         //��ֹʱ�䴥��ͨ��ģʽ
    CAN_Handle.Init.AutoBusOff = DISABLE;                //��ֹ�Զ����߹���
    CAN_Handle.Init.AutoWakeUp = DISABLE;               //˯��ģʽͨ�����sleepλ������
    CAN_Handle.Init.AutoRetransmission = ENABLE;        //���Ĳ�֧�ֲ��Զ���װ
    CAN_Handle.Init.ReceiveFifoLocked = DISABLE;         //�������ʱ��FIFOδ���� 
    CAN_Handle.Init.TransmitFifoPriority= DISABLE;       //���͵����ȼ��ɱ�ʾ���Ĵ�С����
    CAN_Handle.Init.Mode = CAN_MODE_NORMAL;               //ע��CAN���е�ģʽ����ǰ��NORMAL
    CAN_Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;          //ѡ������ͬ��ǰ��������һ��bit��time quanta, ��������1-4��һ��Ĭ��1tq. �����������õ� SJW ����ֵ�ϴ�ʱ���������յ����Ӵ󣬵�ͨѶ���ٶȻ��½�
    CAN_Handle.Init.TimeSeg1 = CAN_BS1_7TQ;               //����1-16������ 
    CAN_Handle.Init.TimeSeg2 = CAN_BS2_2TQ;              //����1-8������ 
    CAN_Handle.Init.Prescaler = 6u;                        //��������1-1024��������ע��һ��time quanta�ĳ���,APB1��Ƶ��Ƶ�ʳ���Prescaler�õ���Ƶ�ʵĵ�������һ��tq

   
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)               //HAL_CAN_Init()�ǰ���������װ�����Ĵ���,ʹ��CAN1,�жϼĴ���װ���Ƿ�ɹ��������ɹ���ִ��Error_Handler()
    Error_Handler();    
                              
    /*CAN1 CAN2����ɸѡ���� CAN1ʹ��0-13,CAN2ʹ��14-27*/
    /*< ʹ�õ�ɸѡ���� ��ǰʹ��ɸѡ����Ϊ0,����ȫ��Ϊ���ô�ɸѡ��ʹ�� */
    //��ʼ��CAN��FILTER
    CAN_Filter.FilterBank = 0u;                         //ʹ��bank0 CAN1 0-13 
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      //Maskģʽ
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;     //32λ��ID�� һ��bank������һ��ID��һ��mask ��32λ��mask ��עID��Ӧλ�Ƿ������ͬ
    CAN_Filter.FilterIdHigh = 0X0000u;                  
    CAN_Filter.FilterIdLow = 0X0000u;
    CAN_Filter.FilterMaskIdHigh = 0X0000u;
    CAN_Filter.FilterMaskIdLow = 0X0000u;
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; //ͨ��Filter����Ϣ�洢��FIFO0 ��
    CAN_Filter.FilterActivation = ENABLE;               //ʹ��Filter
    //CAN_Filter.SlaveStartFilterBank= 14; For single CAN instances, this parameter is meaningless. stm32f103r8t6 ��CAN: CAN1
    
    //Configures the CAN reception filter according to the specified parameters in the CAN_FilterInitStruct. 
    if(HAL_CAN_ConfigFilter(&CAN_Handle,&CAN_Filter) != HAL_OK) 
    Error_Handler(); 
        
    //Start the CAN module
    if(HAL_CAN_Start(&CAN_Handle) != HAL_OK)
    Error_Handler(); 

    //Active CAN Rx notification(interrupt). 
    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)   //FIFO 0  receive interrupt
    Error_Handler(); 
    /*Enable Bus-off interrupts
    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_BUSOFF)!= HAL_OK)   
    Error_Handler(); 
    */
}

/**
  * @brief  ��CAN�������ģ�װ������Ӧ�Ĵ��������Ͷ�ӦCAN����
  * @param  SID:��׼��ʶ����Ӧ����
  * @param  data:���������Ӧ��ָ��
  * @retval None
  */
void OPT_CAN_Send(uint32_t SID,uint8_t data[8])
{
    uint16_t i=0u;               //�Ӻ��ݴ��븴��
    uint32_t CAN_Tx_Mailboxes;

    CAN_TxHeader.StdId = SID;  // Specifies the standard identifier. Min_Data = 0 and Max_Data = 0x7FF
    //CAN_TxHeader.ExtId = ;
    CAN_TxHeader.RTR = CAN_RTR_DATA;    //Remote transmission request 
    CAN_TxHeader.IDE = CAN_ID_STD;   //Identifier extension 
    CAN_TxHeader.DLC = 8u;   //Specifies the length of the frame that will be transmitted. 0-8,�˴�Ϊ8�ֽ� 64λ
    CAN_TxHeader.TransmitGlobalTime = DISABLE;
    if(HAL_CAN_AddTxMessage(&CAN_Handle,& CAN_TxHeader,data,&CAN_Tx_Mailboxes) != HAL_OK)//CAN_Tx_Mailboxes����HAL_CAN_AddTxMessage()����ʱ�Զ��洢Ϊʹ�õ�mailboxֵ
    Error_Handler();

    //�ȴ�ֱ���п�mailbox �� i<0x7FFF, 0x7FFF���ֵ�Ӻ��ݴ��븴�ƹ������Ʋ����ȴ�ʱ��������֪����ʱ�䣬����Բ鿴
    do{
        i++;
    }while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u) && (i < 0x7FFFu));  
    
    //����ڹ涨i��Χ�ڣ�û�ȵ���mailbox, ��ô���˳����ͺ���
    if(i==0x7FFFu)
    return;     
    
    //�鿴CAN_Tx_Mailboxes ��Ӧmailbox �� ״̬���ȴ�ֱ���䲻����Pending state,  ���������������һֱ��pending����ô���� 
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,CAN_Tx_Mailboxes) != 0u) && (i < 0x7FFF))
    i++;
   
    CAN_Send_Fg = 1u;   //ȷ�Ϸ�����Ϻ�ֵ
}

//������õ�CAN������PA11��PA12�������ж���CAN1_RX0_IRQn�����CAN�����õ���PB8��PB9��Ҳ�������ض�������ţ������ж���CAN1_RX1_IRQn��
//CAN�����жϣ����յ����ĺ󣬰�Э��ѱ��Ľ�����������ֵ��CAN_Buff[8]
//ʹ�ܵ���CAN_IT_RX_FIFO0_MSG_PENDING ��line 55
/**
  * @brief  FIFO 0 ��pending�жϻص���������Э��������յ���CAN���Ĳ��ѺϷ�����װ��Can_Buff[]��
  * @param  hcan:CAN�����Ӧָ�룬Ϊ�βΡ���HAL_CAN_IRQHandler()������Ӧ��ʵ��ָ���滻
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t Rx_data[8],CAN_Frame_Type,CAN_Frame_ID,i;

    //����HAL_CAN_GetRxMessage()�������ն�ӦCAN����,���ݱ�����Rx_data[8]��
    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,Rx_data) != HAL_OK)//Get an CAN frame from the Rx FIFO zone into the message RAM. release fifox after read
    Error_Handler();

    //�жϽ��յ�CAN�����Ƿ�Ϸ������Ϸ���ȡ����ֵ��CAN_Buff[]��CAN_Data_Read_Fg ��1�� ����CAN��ָʾ��
    if(CAN_RxHeader.IDE == 0u)
    {
        CAN_Frame_Type = ((CAN_RxHeader.StdId>>7u)&0x0Fu);
        CAN_Frame_ID = ((CAN_RxHeader.StdId>>5u)&0x03u);
        if(CAN_Frame_Type == 0u)
        {
            if((CAN_Frame_ID == 1u)&&(BOARD_ADDRESS<5))
            {
                // LED_VACheck_Fg = ((CAN_RxHeader.StdId>>BOARD_ADDRESS)&0x01u);
                for(i=0u;i<8u;i++)
                    Can_Buff[i] = Rx_data[i]; 
                CAN_Data_Read_Fg = 1u;
                CAN_Rx_LED = LED_ON;
            }
            else if((CAN_Frame_ID == 2u) && (BOARD_ADDRESS > 4u) && (BOARD_ADDRESS < 10u))
            {
                // LED_VACheck_Fg = ((CAN_RxHeader.StdId>>(BOARD_ADDRESS-5))&0x01u); 
                for(i=0u;i<8u;i++)
                    Can_Buff[i] = Rx_data[i];  
                CAN_Data_Read_Fg = 1u;
                CAN_Rx_LED = LED_ON;
            }
        }    
    }    
}

/**
  * @brief  CAN��ʼ������CAN���ͻ���մ���ʱ��Ӧ������
  * @param  None
  * @retval �޷��أ�����ͬʱ��CAN���뷢ָʾ����˸ Ƶ��1Hz
  */
void Error_Handler(void)
{
    while(1)
    {	
        CAN_Rx_LED = LED_ON;
        CAN_Tx_LED = LED_ON;
        HAL_Delay(1000);
        CAN_Rx_LED = LED_OFF;
        CAN_Tx_LED = LED_OFF;
    }
}
