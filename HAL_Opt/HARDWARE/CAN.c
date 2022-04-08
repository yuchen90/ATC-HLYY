//CAN ͨѶ��ʼ�� �Ѿ� CAN ���պ� CAN���ͺ���
//���ذ�1s �ȷ�4�� ÿ��2֡��һ֡��5����ӣ��� ��������ô4�α���һ���� ����˸ ǰ����2��һ��Ϊ��ƣ������2��һ��Ϊ����
#include "main.h"
#include "declaration.h"

CAN_HandleTypeDef CAN_Handle;
CAN_TxHeaderTypeDef CAN_TxHeader;
CAN_RxHeaderTypeDef CAN_RxHeader;

void CAN_Error_Handler(void);

/**
  * @brief  CAN��Ӧ���蹦�ܳ�ʼ��
  * @param  None
  * @retval None
  */
void OPT_CAN_Init(void)
{

    CAN_FilterTypeDef CAN_Filter;
    //��ʼ��CAN ģʽ�Լ���׼ʱ�䳤�� 600Kbps
    CAN_Handle.Instance=CAN1;                                   //ѡ��CAN1����ص�ַΪ�Ĵ�����ַ
    CAN_Handle.Init.TimeTriggeredMode=DISABLE;                  //��ֹʱ�䴥��ͨ��ģʽ
    CAN_Handle.Init.AutoBusOff=DISABLE;                         //��ֹ�Զ����߹���
    CAN_Handle.Init.AutoWakeUp=DISABLE;                         //˯��ģʽͨ�����sleepλ������
    CAN_Handle.Init.AutoRetransmission=DISABLE;                 //���Ĳ�֧���Զ���װ
    CAN_Handle.Init.ReceiveFifoLocked=DISABLE;                  //�������ʱ��FIFOδ���� 
    CAN_Handle.Init.TransmitFifoPriority=DISABLE;               //���͵����ȼ��ɱ�ʾ���Ĵ�С����
    CAN_Handle.Init.Mode=CAN_MODE_NORMAL;                       //ע��CAN���е�ģʽ����ǰ��NORMAL
    CAN_Handle.Init.SyncJumpWidth=CAN_SJW_1TQ;                  //ѡ������ͬ��ǰ��������һ��bit��time quanta, ��������1-4��һ��Ĭ��1tq. �����������õ� SJW ����ֵ�ϴ�ʱ���������յ����Ӵ󣬵�ͨѶ���ٶȻ��½�
    CAN_Handle.Init.TimeSeg1=CAN_BS1_7TQ;                       //����1-16������ 
    CAN_Handle.Init.TimeSeg2=CAN_BS2_2TQ;                       //����1-8������ 
    CAN_Handle.Init.Prescaler=6u;                               //��������1-1024��������ע��һ��time quanta�ĳ���,APB1��Ƶ��Ƶ�ʳ���Prescaler�õ���Ƶ�ʵĵ�������һ��tq
//
   
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)                      //HAL_CAN_Init()�ǰ���������װ�����Ĵ���,ʹ��CAN1,�жϼĴ���װ���Ƿ�ɹ��������ɹ���ִ��Error_Handler()
    CAN_Error_Handler();    
                              
    //��ʼ��CAN��FILTER
    CAN_Filter.FilterBank=0u;                                   //ʹ��bank0 CAN1 0-13 
    CAN_Filter.FilterMode=CAN_FILTERMODE_IDMASK;                //Maskģʽ
    CAN_Filter.FilterScale=CAN_FILTERSCALE_32BIT;               //32λ��ID�� һ��bank������һ��ID��һ��mask ��32λ��mask ��עID��Ӧλ�Ƿ������ͬ
    CAN_Filter.FilterIdHigh=0X0000u;                  
    CAN_Filter.FilterIdLow=0X0000u;
    CAN_Filter.FilterMaskIdHigh=0Xf000u;                        //��Э��std id ��7-10λ ��Ϊ0Ϊ���ذ巢�͸��ƿذ�����Ϣ
    CAN_Filter.FilterMaskIdLow=0X0000u;
    CAN_Filter.FilterFIFOAssignment=CAN_FILTER_FIFO0;           //ͨ��Filter����Ϣ�洢��FIFO0 ��
    CAN_Filter.FilterActivation=ENABLE;                         //ʹ��Filter
    //CAN_Filter.SlaveStartFilterBank= 14; For single CAN instances, this parameter is meaningless. stm32f103r8t6 ��CAN: CAN1
    
    if(HAL_CAN_ConfigFilter(&CAN_Handle,&CAN_Filter) != HAL_OK) //������
    CAN_Error_Handler(); 
        
    if(HAL_CAN_Start(&CAN_Handle) != HAL_OK)                    //CANģ��ʹ��
    CAN_Error_Handler(); 

    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)   //ʹ���ж�
    CAN_Error_Handler(); 
}

/**
  * @brief  ��CAN�������ģ�װ������Ӧ�Ĵ��������Ͷ�ӦCAN����
  * @param  sid:��׼��ʶ����Ӧ����
  * @param  data:���������Ӧ��ָ��
  * @retval None
  */
void OPT_CAN_Send(uint32_t sid,uint8_t data[8])
{
    uint16_t i=0u;                                              //�Ӻ��ݴ��븴��
    uint32_t can_tx_mailbox;

    CAN_TxHeader.StdId=sid;                                   // Specifies the standard identifier. Min_Data = 0 and Max_Data = 0x7FF
    //CAN_TxHeader.ExtId = ;
    CAN_TxHeader.RTR=CAN_RTR_DATA;                            //Remote transmission request 
    CAN_TxHeader.IDE=CAN_ID_STD;                              //Identifier extension 
    CAN_TxHeader.DLC=8u;                                      //Specifies the length of the frame that will be transmitted. 0-8,�˴�Ϊ8�ֽ� 64λ
    CAN_TxHeader.TransmitGlobalTime=DISABLE;
    if(HAL_CAN_AddTxMessage(&CAN_Handle,& CAN_TxHeader,data,&can_tx_mailbox) != HAL_OK)//can_tx_mailbox����HAL_CAN_AddTxMessage()����ʱ�Զ��洢Ϊʹ�õ�mailboxֵ
    CAN_Error_Handler();

    //�ȴ�ֱ���п�mailbox �� i<0x7FFF, 0x7FFF���ֵ�Ӻ��ݴ��븴�ƹ������Ʋ����ȴ�ʱ��������֪����ʱ�䣬����Բ鿴
    do{
        i++;
    }while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u) && (i < 0x7FFFu));  
    
    //����ڹ涨i��Χ�ڣ�û�ȵ���mailbox, ��ô���˳����ͺ���
    if(i==0x7FFFu)
    return;     
    
    //�鿴can_tx_mailbox ��Ӧmailbox �� ״̬���ȴ�ֱ���䲻����Pending state,  ���������������һֱ��pending����ô���� 
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,can_tx_mailbox) != 0u) && (i < 0x7FFF))
    i++;
   
    // CAN_Send_Fg = 1u;   //ȷ�Ϸ�����Ϻ�ֵ
}

//������õ�CAN������PA11��PA12�������ж���CAN1_RX0_IRQn�����CAN�����õ���PB8��PB9��Ҳ�������ض�������ţ������ж���CAN1_RX1_IRQn��
//CAN�����жϣ����յ����ĺ󣬰�Э��ѱ��Ľ�����������ֵ��CAN_Buff[8]
//ʹ�ܵ���CAN_IT_RX_FIFO0_MSG_PENDING ��line 55
/**
  * @brief  FIFO 0 ��pending�жϻص���������Э��������յ���CAN���Ĳ��ѺϷ�����װ��CAN_Buff[]��
  * @param  hcan:CAN�����Ӧָ�룬Ϊ�βΡ���HAL_CAN_IRQHandler()������Ӧ��ʵ��ָ���滻
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t rx_data[8],i; //CAN_Frame_Type

    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,rx_data) != HAL_OK)//Get an CAN frame from the Rx FIFO zone into the message RAM. release fifox after read
    CAN_Error_Handler();

    // �жϽ��յ�CAN�����Ƿ�Ϸ������Ϸ���ȡ����ֵ��CAN_Buff[]��CAN_Data_Read_Fg ��1�� ����CAN��ָʾ��
    if(CAN_RxHeader.IDE == 0u)
    {
        // CAN_Frame_Type=((CAN_RxHeader.StdId>>7u)&0x0Fu); ע�͵�����Ϊ��CAN����ʱ�Ѿ�Ӳ������������֡
        CAN_Frame_ID=((CAN_RxHeader.StdId>>5u)&0x03u);
        // if(CAN_Frame_Type == 0u)
        {
            if((CAN_Frame_ID == 1u) && (Board_Address < 5u))
            {
                CAN_Rx_LED=LED_ON;
                // LED_VACheck_Fg = ((CAN_RxHeader.StdId>>Board_Address)&0x01u);    δʹ��
                for(i=0u;i<8u;i++)
                    CAN_Buff[i]=rx_data[i]; 
                CAN_DataRead_Fg=1u;  
            }
            else if((CAN_Frame_ID == 2u) && (Board_Address > 4u) && (Board_Address < 10u))
            {
                CAN_Rx_LED=LED_ON;
                // LED_VACheck_Fg = ((CAN_RxHeader.StdId>>(Board_Address-5))&0x01u); 
                for(i=0u;i<8u;i++)
                    CAN_Buff[i]=rx_data[i];  
                CAN_DataRead_Fg=1u;
            }
        }    
    }    
}

/**
  * @brief  CAN��ʼ������CAN���ͻ���մ���ʱ��Ӧ������
  * @param  None
  * @retval �޷��أ�����ͬʱ��CAN���뷢ָʾ����˸ Ƶ��1Hz
  */
void CAN_Error_Handler(void)
{
    while(1)
    {	
        CAN_Rx_LED=LED_ON;
        CAN_Tx_LED=LED_ON;
        HAL_Delay(1000u);
        CAN_Rx_LED=LED_OFF;
        CAN_Tx_LED=LED_OFF;
    }
}
