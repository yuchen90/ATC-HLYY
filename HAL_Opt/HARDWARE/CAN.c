//CAN ͨѶ��ʼ�� �Ѿ� CAN ���պ� CAN���ͺ���
#include "main.h"
#include "stm32f1xx_hal.h"
   
CAN_HandleTypeDef CAN_Handle;
CAN_TxHeaderTypeDef CAN_TxHeader;

void Error_Handler(void);
//CAN��ʼ��
void OPT_CAN_Init(void)
{
 
    CAN_FilterTypeDef CAN_Filter;
//��ʼ��CAN ģʽ�Լ���׼ʱ�䳤�� 600Kbps
    CAN_Handle.Instance = CAN1;                            //ѡ��CAN1����ص�ַΪ�Ĵ�����ַ
    CAN_Handle.Init.Prescaler = 6u;                        //��������1-1024��������ע��һ��time quanta�ĳ���,APB1��Ƶ��Ƶ�ʳ���Prescaler�õ���Ƶ�ʵĵ�������һ��tq
    CAN_Handle.Init.Mode = CAN_MODE_NORMAL;               //ע��CAN���е�ģʽ����ǰ��NORMAL
    CAN_Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;          //ѡ������ͬ��ǰ��������һ��bit��time quanta, ��������1-4��һ��Ĭ��1tq. �����������õ� SJW ����ֵ�ϴ�ʱ���������յ����Ӵ󣬵�ͨѶ���ٶȻ��½�
    CAN_Handle.Init.TimeSeg1 = CAN_BS1_7TQ;               //����1-16������
    CAN_Handle.Init.TimeSeg2 = CAN_BS1_2TQ;              //����1-8������
    //SS=1,TS1=7,TS2=2,�õ�80%�Ĳ����ʡ��ʺ�500k��800k ���baud-rate 
    CAN_Handle.Init.TimeTriggeredMode = DISABLE;         //��ֹʱ�䴥��ͨ��ģʽ
    CAN_Handle.Init.AutoBusOff = DISABLE;                //��ֹ�Զ����߹���
    CAN_Handle.Init.AutoWakeUp = DISABLE;               //˯��ģʽͨ�����sleepλ������
    CAN_Handle.Init.AutoRetransmission = DISABLE;        //���Ĳ�֧�ֲ��Զ���װ
    CAN_Handle.Init.ReceiveFifoLocked = DISABLE;         //�������ʱ��FIFOδ���� 
    CAN_Handle.Init.TransmitFifoPriority= DISABLE;       //���͵����ȼ��ɱ�ʾ���Ĵ�С����
   
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)               //HAL_CAN_Init()�ǰ���������װ�����Ĵ���,ʹ��CAN1,�жϼĴ���װ���Ƿ�ɹ��������ɹ���ִ��Error_Handler()
    Error_Handler();                                    

/*CAN1 CAN2����ɸѡ���� CAN1ʹ��0-13,CAN2ʹ��14-27*/
/*< ʹ�õ�ɸѡ���� ��ǰʹ��ɸѡ����Ϊ0,����ȫ��Ϊ���ô�ɸѡ��ʹ�� */
//��ʼ��CAN��FILTER
    CAN_Filter.FilterActivation = ENABLE;               //ʹ��Filter
    CAN_Filter.FilterBank = 0u;                         //ʹ��bank0 CAN1 0-13 
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; //ͨ��Filter����Ϣ�洢��FIFO0 ��
    CAN_Filter.FilterIdHigh = 0X0000u;                  
    CAN_Filter.FilterIdLow = 0X0000u;
    CAN_Filter.FilterMaskIdHigh = 0X0000u;
    CAN_Filter.FilterMaskIdLow = 0X0000u;
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      //Maskģʽ
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;     //32λ��ID�� һ��bank������һ��ID��һ��mask ��32λ��mask ��עID��Ӧλ�Ƿ������ͬ
    //CAN_Filter.SlaveStartFilterBank=; For single CAN instances, this parameter is meaningless. stm32f103r8t6 ��CAN: CAN1
    
//Configures the CAN reception filter according to the specified parameters in the CAN_FilterInitStruct. 
    if(HAL_CAN_ConfigFilter(&CAN_Handle,&CAN_Filter)!= HAL_OK) 
    Error_Handler(); 
    
//Start the CAN module
    if(HAL_CAN_Start(&CAN_Handle)!= HAL_OK)
    Error_Handler(); 

//Active CAN Rx notification.
    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_RX_FIFO0_MSG_PENDING)!= HAL_OK)   //FIFO 0  receive interrupt
    Error_Handler(); 
/*Enable Bus-off interrupts
    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_BUSOFF)!= HAL_OK)   
    Error_Handler(); 
*/
}

/* Init the low level hardware: CLOCK, NVIC */
void HAL_CAN_MspInit(CAN_HandleTypeDef *hcan)
{
    GPIO_InitTypeDef GPIO_Init;
    if(hcan->Instance==CAN1)
    {
        __HAL_RCC_CAN1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
    //PA11 Rx
        GPIO_Init.Mode = GPIO_MODE_INPUT;
        GPIO_Init.Pin = GPIO_PIN_11;
        GPIO_Init.Pull = GPIO_PULLUP;
        GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&GPIO_Init);

    //PA12 Tx
        GPIO_Init.Mode = GPIO_MODE_AF_PP;
        GPIO_Init.Pin = GPIO_PIN_12;
        //GPIO_Init.Pull = GPIO_PULLUP;
        GPIO_Init.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA,&GPIO_Init); 

    //CAN1 Rx Interrupt Init
        HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn,1,2); //��ռ���ȼ���1 
        HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    }

}

// void HAL_CAN_MspDeInit(); deinit function


//�ƿذ巢�͵�CAN ����
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
    }while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u)&&(i<0x7FFFu));  
    
//����ڹ涨i��Χ�ڣ�û�ȵ���mailbox, ��ô���˳����ͺ���
    if(i==0x7FFFu)
    return;     
    
//�鿴CAN_Tx_Mailboxes ��Ӧmailbox �� ״̬���ȴ�ֱ���䲻����Pending state,  ���������������һֱ��pending����ô���� 
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,CAN_Tx_Mailboxes)!=0u)&&(i<0x7FFF))
    i++;
   
    CAN_Send_Fg = 1u;   //ȷ�Ϸ�����Ϻ�ֵ
}

//������õ�CAN������PA11��PA12�������ж���CAN1_RX0_IRQn�����CAN�����õ���PB8��PB9��Ҳ�������ض�������ţ������ж���CAN1_RX1_IRQn��
//CAN�����жϣ����յ����ĺ󣬰�Э��ѱ��Ľ�����������ֵ��CAN_Buff[8]
void USB_LP_CAN1_RX0_IRQHandler(void)
{

}

//Error_Handler() ��δ���壬׼������Ϊ����ָʾ����˸
void Error_Handler(void)
{

}
