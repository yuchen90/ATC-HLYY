//CAN 通讯初始化 已经 CAN 接收和 CAN发送函数
//主控板1s 匀发4次 每次2帧（一帧控5块板子）； 若常亮那么4次报文一样， 若闪烁 前半秒2次一样为灭灯，后半秒2次一样为亮灯
#include "main.h"
#include "declaration.h"

void CAN_Error_Handler(void);

/**
  * @brief  CAN对应外设功能初始化
  * @param  None
  * @retval None
  */
void OPT_CAN_Init(void)
{

    CAN_FilterTypeDef CAN_Filter;
    //初始化CAN 模式以及基准时间长度 600Kbps
    CAN_Handle.Instance=CAN1;                                   //选择CAN1的相关地址为寄存器地址
    CAN_Handle.Init.TimeTriggeredMode=DISABLE;                  //禁止时间触发通信模式
    CAN_Handle.Init.AutoBusOff=DISABLE;                         //禁止自动离线管理
    CAN_Handle.Init.AutoWakeUp=DISABLE;                         //睡眠模式通过清除sleep位来唤醒
    CAN_Handle.Init.AutoRetransmission=DISABLE;                 //报文不支持自动重装
    CAN_Handle.Init.ReceiveFifoLocked=DISABLE;                  //接收溢出时，FIFO未锁定 
    CAN_Handle.Init.TransmitFifoPriority=DISABLE;               //发送的优先级由标示符的大小决定
    CAN_Handle.Init.Mode=CAN_MODE_NORMAL;                       //注明CAN运行的模式，当前是NORMAL
    CAN_Handle.Init.SyncJumpWidth=CAN_SJW_1TQ;                  //选择重新同步前允许缩放一个bit的time quanta, 允许输入1-4，一般默认1tq. 当控制器设置的 SJW 极限值较大时，可以吸收的误差加大，但通讯的速度会下降
    CAN_Handle.Init.TimeSeg1=CAN_BS1_7TQ;                       //允许1-16间整数 
    CAN_Handle.Init.TimeSeg2=CAN_BS2_2TQ;                       //允许1-8间整数 
    CAN_Handle.Init.Prescaler=6u;                               //允许输入1-1024间整数，注明一个time quanta的长度,APB1分频后频率除以Prescaler得到的频率的倒数就是一个tq
//
   
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)                      //HAL_CAN_Init()是把上述参数装载至寄存器,使能CAN1,判断寄存器装填是否成功，若不成功则执行Error_Handler()
    CAN_Error_Handler();    
                              
    //初始化CAN的FILTER
    CAN_Filter.FilterBank=0u;                                   //使用bank0 CAN1 0-13 
    CAN_Filter.FilterMode=CAN_FILTERMODE_IDMASK;                //Mask模式
    CAN_Filter.FilterScale=CAN_FILTERSCALE_32BIT;               //32位的ID， 一个bank可以有一个ID和一个mask 各32位，mask 标注ID对应位是否必须相同
    CAN_Filter.FilterIdHigh=0X0000u;                  
    CAN_Filter.FilterIdLow=0X0000u;
    CAN_Filter.FilterMaskIdHigh=0Xf000u;                        //按协议std id 的7-10位 皆为0为主控板发送给灯控板点灯信息
    CAN_Filter.FilterMaskIdLow=0X0000u;
    CAN_Filter.FilterFIFOAssignment=CAN_FILTER_FIFO0;           //通过Filter的消息存储在FIFO0 上
    CAN_Filter.FilterActivation=ENABLE;                         //使能Filter
    //CAN_Filter.SlaveStartFilterBank= 14; For single CAN instances, this parameter is meaningless. stm32f103r8t6 单CAN: CAN1
    
    if(HAL_CAN_ConfigFilter(&CAN_Handle,&CAN_Filter) != HAL_OK) //过滤器
    CAN_Error_Handler(); 
        
    if(HAL_CAN_Start(&CAN_Handle) != HAL_OK)                    //CAN模块使能
    CAN_Error_Handler(); 

    if(HAL_CAN_ActivateNotification(&CAN_Handle,CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK)   //使能中断
    CAN_Error_Handler(); 
}

/**
  * @brief  把CAN发生报文，装载至对应寄存器，发送对应CAN报文
  * @param  sid:标准标识符对应数据
  * @param  data:数据数组对应的指针
  * @retval None
  */
void OPT_CAN_Send(uint32_t sid,uint8_t data[8])
{
    uint16_t i=0u;                                              //从杭州代码复制
    uint32_t can_tx_mailbox;

    CAN_TxHeader.StdId=sid;                                   // Specifies the standard identifier. Min_Data = 0 and Max_Data = 0x7FF
    //CAN_TxHeader.ExtId = ;
    CAN_TxHeader.RTR=CAN_RTR_DATA;                            //Remote transmission request 
    CAN_TxHeader.IDE=CAN_ID_STD;                              //Identifier extension 
    CAN_TxHeader.DLC=8u;                                      //Specifies the length of the frame that will be transmitted. 0-8,此处为8字节 64位
    CAN_TxHeader.TransmitGlobalTime=DISABLE;
    if(HAL_CAN_AddTxMessage(&CAN_Handle,& CAN_TxHeader,data,&can_tx_mailbox) != HAL_OK)//can_tx_mailbox会在HAL_CAN_AddTxMessage()调用时自动存储为使用的mailbox值
    CAN_Error_Handler();

    //等待直到有空mailbox 且 i<0x7FFF, 0x7FFF这个值从杭州代码复制过来，推测代表等待时长，但不知具体时间，需调试查看
    do{
        i++;
    }while((HAL_CAN_GetTxMailboxesFreeLevel(&CAN_Handle) == 0u) && (i < 0x7FFFu));  
    
    //如果在规定i范围内，没等到空mailbox, 那么就退出发送函数
    if(i==0x7FFFu)
    return;     
    
    //查看can_tx_mailbox 对应mailbox 的 状态，等待直到其不处于Pending state,  ！！！！！但如果一直在pending该怎么处理？ 
    i=0u;
    while((HAL_CAN_IsTxMessagePending(&CAN_Handle,can_tx_mailbox) != 0u) && (i < 0x7FFF))
    i++;
   
    // CAN_Send_Fg = 1u;   //确认发送完毕后赋值
}

//如果你用的CAN引脚是PA11和PA12，接收中断用CAN1_RX0_IRQn。如果CAN引脚用的是PB8和PB9，也就是用重定义的引脚，接收中断用CAN1_RX1_IRQn。
//CAN接收中断，接收到报文后，按协议把报文解析出来并赋值到CAN_Buff[8]
//使能的是CAN_IT_RX_FIFO0_MSG_PENDING 在line 55
/**
  * @brief  FIFO 0 的pending中断回调函数，按协议解析接收到的CAN报文并把合法数据装入CAN_Buff[]中
  * @param  hcan:CAN句柄对应指针，为形参。由HAL_CAN_IRQHandler()函数对应的实参指针替换
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t rx_data[8],i; //CAN_Frame_Type

    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,rx_data) != HAL_OK)//Get an CAN frame from the Rx FIFO zone into the message RAM. release fifox after read
    CAN_Error_Handler();

    // 判断接收的CAN报文是否合法，若合法则取出赋值给CAN_Buff[]，CAN_Data_Read_Fg 置1， 点亮CAN收指示灯
    if(CAN_RxHeader.IDE == 0u)
    {
        // CAN_Frame_Type=((CAN_RxHeader.StdId>>7u)&0x0Fu); 注释掉，因为在CAN接收时已经硬件屏蔽了其它帧
        CAN_Frame_ID=((CAN_RxHeader.StdId>>5u)&0x03u);
        // if(CAN_Frame_Type == 0u)
        {
            if((CAN_Frame_ID == 1u) && (Board_Address < 5u))
            {
                CAN_Rx_LED=LED_ON;
                // LED_VACheck_Fg = ((CAN_RxHeader.StdId>>Board_Address)&0x01u);    未使用
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
  * @brief  CAN初始化错误；CAN发送或接收错误时对应处理函数
  * @param  None
  * @retval 无返回，但是同时让CAN收与发指示灯闪烁 频率1Hz
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
