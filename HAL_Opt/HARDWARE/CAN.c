//CAN 通讯初始化 已经 CAN 接收和 CAN发送函数
#include "main.h"
#include "stm32f1xx_hal.h"
   
CAN_HandleTypeDef CAN_Handle;
CAN_TxHeaderTypeDef CAN_TxHeader;

void Error_Handler(void);
//CAN初始化
void OPT_CAN_Init(void)
{
 
    CAN_FilterTypeDef CAN_Filter;
//初始化CAN 模式以及基准时间长度 600Kbps
    CAN_Handle.Instance = CAN1;                            //选择CAN1的相关地址为寄存器地址
    CAN_Handle.Init.Prescaler = 6u;                        //允许输入1-1024间整数，注明一个time quanta的长度,APB1分频后频率除以Prescaler得到的频率的倒数就是一个tq
    CAN_Handle.Init.Mode = CAN_MODE_NORMAL;               //注明CAN运行的模式，当前是NORMAL
    CAN_Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;          //选择重新同步前允许缩放一个bit的time quanta, 允许输入1-4，一般默认1tq. 当控制器设置的 SJW 极限值较大时，可以吸收的误差加大，但通讯的速度会下降
    CAN_Handle.Init.TimeSeg1 = CAN_BS1_7TQ;               //允许1-16间整数
    CAN_Handle.Init.TimeSeg2 = CAN_BS1_2TQ;              //允许1-8间整数
    //SS=1,TS1=7,TS2=2,得到80%的采样率。适合500k到800k 间的baud-rate 
    CAN_Handle.Init.TimeTriggeredMode = DISABLE;         //禁止时间触发通信模式
    CAN_Handle.Init.AutoBusOff = DISABLE;                //禁止自动离线管理
    CAN_Handle.Init.AutoWakeUp = DISABLE;               //睡眠模式通过清除sleep位来唤醒
    CAN_Handle.Init.AutoRetransmission = DISABLE;        //报文不支持不自动重装
    CAN_Handle.Init.ReceiveFifoLocked = DISABLE;         //接收溢出时，FIFO未锁定 
    CAN_Handle.Init.TransmitFifoPriority= DISABLE;       //发送的优先级由标示符的大小决定
   
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)               //HAL_CAN_Init()是把上述参数装载至寄存器,使能CAN1,判断寄存器装填是否成功，若不成功则执行Error_Handler()
    Error_Handler();                                    

/*CAN1 CAN2共用筛选器组 CAN1使用0-13,CAN2使用14-27*/
/*< 使用的筛选器组 当前使用筛选器组为0,后续全部为配置此筛选器使用 */
//初始化CAN的FILTER
    CAN_Filter.FilterActivation = ENABLE;               //使能Filter
    CAN_Filter.FilterBank = 0u;                         //使用bank0 CAN1 0-13 
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; //通过Filter的消息存储在FIFO0 上
    CAN_Filter.FilterIdHigh = 0X0000u;                  
    CAN_Filter.FilterIdLow = 0X0000u;
    CAN_Filter.FilterMaskIdHigh = 0X0000u;
    CAN_Filter.FilterMaskIdLow = 0X0000u;
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      //Mask模式
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;     //32位的ID， 一个bank可以有一个ID和一个mask 各32位，mask 标注ID对应位是否必须相同
    //CAN_Filter.SlaveStartFilterBank=; For single CAN instances, this parameter is meaningless. stm32f103r8t6 单CAN: CAN1
    
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
        HAL_NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn,1,2); //抢占优先级：1 
        HAL_NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    }

}

// void HAL_CAN_MspDeInit(); deinit function


//灯控板发送的CAN 报文
void OPT_CAN_Send(uint32_t SID,uint8_t data[8])
{
    uint16_t i=0u;               //从杭州代码复制
    uint32_t CAN_Tx_Mailboxes;

    CAN_TxHeader.StdId = SID;  // Specifies the standard identifier. Min_Data = 0 and Max_Data = 0x7FF
    //CAN_TxHeader.ExtId = ;
    CAN_TxHeader.RTR = CAN_RTR_DATA;    //Remote transmission request 
    CAN_TxHeader.IDE = CAN_ID_STD;   //Identifier extension 
    CAN_TxHeader.DLC = 8u;   //Specifies the length of the frame that will be transmitted. 0-8,此处为8字节 64位
    CAN_TxHeader.TransmitGlobalTime = DISABLE;
    if(HAL_CAN_AddTxMessage(&CAN_Handle,& CAN_TxHeader,data,&CAN_Tx_Mailboxes) != HAL_OK)//CAN_Tx_Mailboxes会在HAL_CAN_AddTxMessage()调用时自动存储为使用的mailbox值
    Error_Handler();

//等待直到有空mailbox 且 i<0x7FFF, 0x7FFF这个值从杭州代码复制过来，推测代表等待时长，但不知具体时间，需调试查看
    do{
        i++;
    }while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u)&&(i<0x7FFFu));  
    
//如果在规定i范围内，没等到空mailbox, 那么就退出发送函数
    if(i==0x7FFFu)
    return;     
    
//查看CAN_Tx_Mailboxes 对应mailbox 的 状态，等待直到其不处于Pending state,  ！！！！！但如果一直在pending该怎么处理？ 
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,CAN_Tx_Mailboxes)!=0u)&&(i<0x7FFF))
    i++;
   
    CAN_Send_Fg = 1u;   //确认发送完毕后赋值
}

//如果你用的CAN引脚是PA11和PA12，接收中断用CAN1_RX0_IRQn。如果CAN引脚用的是PB8和PB9，也就是用重定义的引脚，接收中断用CAN1_RX1_IRQn。
//CAN接收中断，接收到报文后，按协议把报文解析出来并赋值
void USB_LP_CAN1_RX0_IRQHandler(void)
{

}

//Error_Handler() 还未定义，准备定义为工作指示灯闪烁
void Error_Handler(void)
{

}
