#include "main.h"
#include "declaration.h"

CAN_HandleTypeDef CAN_Handle;
CAN_TxHeaderTypeDef CAN_TxHeader;
CAN_RxHeaderTypeDef CAN_RxHeader;
extern void Error_Handler(void);

/**
  * @brief  CAN对应外设功能初始化
  * @param  None
  * @retval None
  */
void OPT_CAN_Init(void)
{

    CAN_FilterTypeDef CAN_Filter;
    //初始化CAN 模式以及基准时间长度 600Kbps
    CAN_Handle.Instance = CANx;                             //选择CAN1的相关地址为寄存器地址
    //SS=1,TS1=7,TS2=2,得到80%的采样率。适合500k到800k 间的baud-rate 
    CAN_Handle.Init.TimeTriggeredMode = DISABLE;         	//禁止时间触发通信模式
    CAN_Handle.Init.AutoBusOff = DISABLE;                	//禁止自动离线管理
    CAN_Handle.Init.AutoWakeUp = DISABLE;               	//睡眠模式通过清除sleep位来唤醒
    CAN_Handle.Init.AutoRetransmission = ENABLE;        	//报文不支持不自动重装
    CAN_Handle.Init.ReceiveFifoLocked = DISABLE;         	//接收溢出时，FIFO未锁定 
    CAN_Handle.Init.TransmitFifoPriority= DISABLE;       	//发送的优先级由标示符的大小决定
    CAN_Handle.Init.Mode = CAN_MODE_NORMAL;               	//注明CAN运行的模式，当前是NORMAL
    CAN_Handle.Init.SyncJumpWidth = CAN_SJW_1TQ;         	//选择重新同步前允许缩放一个bit的time quanta, 允许输入1-4，一般默认1tq. 当控制器设置的 SJW 极限值较大时，可以吸收的误差加大，但通讯的速度会下降
    CAN_Handle.Init.TimeSeg1 = CAN_BS1_7TQ;               	//允许1-16间整数 
    CAN_Handle.Init.TimeSeg2 = CAN_BS2_2TQ;              	//允许1-8间整数 
    CAN_Handle.Init.Prescaler = 6u;                       	//允许输入1-1024间整数，注明一个time quanta的长度,APB1分频后频率除以Prescaler得到的频率的倒数就是一个tq

    #if CAN1_EN 
    if(HAL_CAN_Init(&CAN_Handle)!= HAL_OK)               	//HAL_CAN_Init()是把上述参数装载至寄存器,使能CAN1,判断寄存器装填是否成功，若不成功则执行Error_Handler()
    Error_Handler();    
                              
    /*CAN1 CAN2共用筛选器组 CAN1使用0-13,CAN2使用14-27*/
    /*< 使用的筛选器组 当前使用筛选器组为0,后续全部为配置此筛选器使用 */
    //初始化CAN的FILTER
    CAN_Filter.FilterBank = 0u;                         	//使用bank0 CAN1 0-13 
    CAN_Filter.FilterMode = CAN_FILTERMODE_IDMASK;      	//Mask模式
    CAN_Filter.FilterScale = CAN_FILTERSCALE_32BIT;     	//32位的ID， 一个bank可以有一个ID和一个mask 各32位，mask 标注ID对应位是否必须相同
    CAN_Filter.FilterIdHigh = 0X0000u;                  
    CAN_Filter.FilterIdLow = 0X0000u;
    CAN_Filter.FilterMaskIdHigh = 0X0000u;
    CAN_Filter.FilterMaskIdLow = 0X0000u;
    CAN_Filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; 	//通过Filter的消息存储在FIFO0 上
    CAN_Filter.FilterActivation = ENABLE;               	//使能Filter
    //CAN_Filter.SlaveStartFilterBank= 14; For single CAN instances, this parameter is meaningless. stm32f103r8t6 单CAN: CAN1
    
    
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
   #endif
}

/**
  * @brief  FIFO 0 的pending中断回调函数，按协议解析接收到的CAN报文并把合法数据装入Can_Buff[]中
  * @param  hcan:CAN句柄对应指针，为形参。由HAL_CAN_IRQHandler()函数对应的实参指针替换
  * @retval None
  */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    uint8_t Rx_data[8];
    //利用HAL_CAN_GetRxMessage()函数接收对应CAN报文,数据保存在Rx_data[8]中
    if(HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&CAN_RxHeader,Rx_data) != HAL_OK)//Get an CAN frame from the Rx FIFO zone into the message RAM. release fifox after read
    Error_Handler();
  
}
