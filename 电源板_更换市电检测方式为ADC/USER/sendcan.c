////////////////////////////////////////////////////////////////
/*
主动发包控制
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "common.h"
#include "data.h"

	void CAN_Send(u32 SID,unsigned char data1[8])	;


////////////////////////////////////////////////////////////////
/*
寻找当前拍
*/
////////////////////////////////////////////////////////////////
void seekPointer()
{
	uint8_t cndguodu,cndguodu2;
	int i,j;
	
	flashfg=(canbuff[7]>>4)&0x01;
	
	if((flashfgbf==1)&&(flashfg==0))
		timerfg1=0;
	flashfgbf=flashfg;
	
	for(i=0;i<7;i++)
		cmd[i]=canbuff[i];
	cndguodu=canbuff[7]&0x0f;

	for(i=0;i<8;i++)
	{
			cndguodu2=canbuff[i+8]&0x0f;
			cndguodu2=cndguodu2<<4;
			cmd[7+i]=cndguodu2+cndguodu;
			cndguodu=(canbuff[i+8]>>4)&0xf;
	}
	cndguodu=0;
	for(i=0;i<TakeOverNumbuse;i++)
	{
		for(j=0;j<15;j++)
		{
			if(cmd[j]!=TakeOverStruse[i].cmd[j])
				break;
		}
		if(j==15)
			break;
	}
	if(i<TakeOverNumbuse)
	{
		TakeOverPointeruse=i;
	}
	else
		TakeOverPointeruse=0;
}


////////////////////////////////////////////////////////////////
/*
发送灯色信息
*/
////////////////////////////////////////////////////////////////


void sendcan(uint8_t d)
{
	uint8_t sendcanbuff1[8];
	uint8_t sendcanbuff2[8];
	uint8_t i;
	uint64_t CANid;
	
	for(i=0;i<8;i++)
		Checkreplybuff[i].start=0;
	
	for(i=0;i<7;i++)
		sendcanbuff1[i]=TakeOverStruse[TakeOverPointeruse].cmd[i];
	
	sendcanbuff1[7]=(TakeOverStruse[TakeOverPointeruse].cmd[7])&0x0f;
	
	sendcanbuff2[0]=(TakeOverStruse[TakeOverPointeruse].cmd[7]>>4)&0xf;
	for(i=0;i<7;i++)
	{
		sendcanbuff2[i]=sendcanbuff2[i]+((TakeOverStruse[TakeOverPointeruse].cmd[i+8]<<4)&0xf0);		
		sendcanbuff2[i+1]=(TakeOverStruse[TakeOverPointeruse].cmd[i+8]>>4)&0xf;
	}
	
	if(d<2)//前半秒
	{	
		CANid=cheakfgf+0X20;
		CAN_Send(CANid,sendcanbuff1);
		CANid=cheakfgS+0X40;
		CAN_Send(CANid,sendcanbuff2);
		
	}
	else////后 半秒
	{
		CANid=cheakfgf+0X20;
		sendcanbuff1[7]=sendcanbuff1[7]+0x10;
		CAN_Send(CANid,sendcanbuff1);
		CANid=cheakfgS+0X40;
		sendcanbuff2[7]=sendcanbuff2[7]+0x10;
		CAN_Send(CANid,sendcanbuff2);		
	}
}

////////////////////////////////////////////////////////////////
/*
初始化发送包
*/
////////////////////////////////////////////////////////////////



void init_sendcanbuff(void)
{
	int i;
//	cheakfgf=0x01;
	TakeOverNumbuse=10;
	//第一拍  东西通行
//	00 00 00 00           
	i=0;
	TakeOverStruse[i].cmd[0]	=0x49;
	TakeOverStruse[i].cmd[1]	=0xB2;
	TakeOverStruse[i].cmd[2]	=0x6D;
	TakeOverStruse[i].cmd[3]	=0x49;
	TakeOverStruse[i].cmd[4]	=0xB2;
	TakeOverStruse[i].cmd[5]	=0x6D;
	TakeOverStruse[i].cmd[6]	=0x59;
	TakeOverStruse[i].cmd[7]	=0x96;
	TakeOverStruse[i].cmd[8]	=0x65;
	TakeOverStruse[i].cmd[9]	=0x59;
	TakeOverStruse[i].cmd[10]	=0x06;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=20;
//          
	i=1;
	TakeOverStruse[i].cmd[0]	=0x49;
	TakeOverStruse[i].cmd[1]	=0xB8;
	TakeOverStruse[i].cmd[2]	=0x6D;
	TakeOverStruse[i].cmd[3]	=0x49;
	TakeOverStruse[i].cmd[4]	=0xB8;
	TakeOverStruse[i].cmd[5]	=0x6D;
	TakeOverStruse[i].cmd[6]	=0x59;
	TakeOverStruse[i].cmd[7]	=0x96;
	TakeOverStruse[i].cmd[8]	=0x65;
	TakeOverStruse[i].cmd[9]	=0x1C;
	TakeOverStruse[i].cmd[10]	=0x07;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=2;
//          
	i=2;
	TakeOverStruse[i].cmd[0]	=0x24;
	TakeOverStruse[i].cmd[1]	=0xB9;
	TakeOverStruse[i].cmd[2]	=0x6D;
	TakeOverStruse[i].cmd[3]	=0x24;
	TakeOverStruse[i].cmd[4]	=0xB9;
	TakeOverStruse[i].cmd[5]	=0x6D;
	TakeOverStruse[i].cmd[6]	=0x1C;
	TakeOverStruse[i].cmd[7]	=0xC7;
	TakeOverStruse[i].cmd[8]	=0x71;
	TakeOverStruse[i].cmd[9]	=0x1C;
	TakeOverStruse[i].cmd[10]	=0x07;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=3;
//	00 00 00 00           
	i=3;
	TakeOverStruse[i].cmd[0]	=0x92;
	TakeOverStruse[i].cmd[1]	=0xB6;
	TakeOverStruse[i].cmd[2]	=0x6D;
	TakeOverStruse[i].cmd[3]	=0x92;
	TakeOverStruse[i].cmd[4]	=0xB6;
	TakeOverStruse[i].cmd[5]	=0x6D;
	TakeOverStruse[i].cmd[6]	=0x9A;
	TakeOverStruse[i].cmd[7]	=0xA6;
	TakeOverStruse[i].cmd[8]	=0x69;
	TakeOverStruse[i].cmd[9]	=0xDB;
	TakeOverStruse[i].cmd[10]	=0x06;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=3;
//00 00 00 00           
	i=4;
	TakeOverStruse[i].cmd[0]	=0xDB;
	TakeOverStruse[i].cmd[1]	=0xB6;
	TakeOverStruse[i].cmd[2]	=0x6D;
	TakeOverStruse[i].cmd[3]	=0xDB;
	TakeOverStruse[i].cmd[4]	=0xB6;
	TakeOverStruse[i].cmd[5]	=0x6D;
	TakeOverStruse[i].cmd[6]	=0xDB;
	TakeOverStruse[i].cmd[7]	=0xB6;
	TakeOverStruse[i].cmd[8]	=0x6D;
	TakeOverStruse[i].cmd[9]	=0xDB;
	TakeOverStruse[i].cmd[10]	=0x06;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=1;
	
//00 00 00 00           
	i=5;
	TakeOverStruse[i].cmd[0]	=0xDB;
	TakeOverStruse[i].cmd[1]	=0x96;
	TakeOverStruse[i].cmd[2]	=0x24;
	TakeOverStruse[i].cmd[3]	=0xDB;
	TakeOverStruse[i].cmd[4]	=0x96;
	TakeOverStruse[i].cmd[5]	=0x24;
	TakeOverStruse[i].cmd[6]	=0xCB;
	TakeOverStruse[i].cmd[7]	=0xB2;
	TakeOverStruse[i].cmd[8]	=0x2C;
	TakeOverStruse[i].cmd[9]	=0xCB;
	TakeOverStruse[i].cmd[10]	=0x02;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=20;
//00 00 00 00           
	i=6;
	TakeOverStruse[i].cmd[0]	=0xDB;
	TakeOverStruse[i].cmd[1]	=0x96;
	TakeOverStruse[i].cmd[2]	=0x84;
	TakeOverStruse[i].cmd[3]	=0xDB;
	TakeOverStruse[i].cmd[4]	=0x96;
	TakeOverStruse[i].cmd[5]	=0x84;
	TakeOverStruse[i].cmd[6]	=0xCB;
	TakeOverStruse[i].cmd[7]	=0xB2;
	TakeOverStruse[i].cmd[8]	=0x2C;
	TakeOverStruse[i].cmd[9]	=0xE3;
	TakeOverStruse[i].cmd[10]	=0x08;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=2;
//00 00 00 00           
	i=7;
	TakeOverStruse[i].cmd[0]	=0xDB;
	TakeOverStruse[i].cmd[1]	=0x46;
	TakeOverStruse[i].cmd[2]	=0x92;
	TakeOverStruse[i].cmd[3]	=0xDB;
	TakeOverStruse[i].cmd[4]	=0x46;
	TakeOverStruse[i].cmd[5]	=0x92;
	TakeOverStruse[i].cmd[6]	=0xE3;
	TakeOverStruse[i].cmd[7]	=0x38;
	TakeOverStruse[i].cmd[8]	=0x8E;
	TakeOverStruse[i].cmd[9]	=0xE3;
	TakeOverStruse[i].cmd[10]	=0x08;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=3;
//00 00 00 00           
	i=8;
	TakeOverStruse[i].cmd[0]	=0xDB;
	TakeOverStruse[i].cmd[1]	=0x26;
	TakeOverStruse[i].cmd[2]	=0x69;
	TakeOverStruse[i].cmd[3]	=0xDB;
	TakeOverStruse[i].cmd[4]	=0x26;
	TakeOverStruse[i].cmd[5]	=0x69;
	TakeOverStruse[i].cmd[6]	=0xD3;
	TakeOverStruse[i].cmd[7]	=0x34;
	TakeOverStruse[i].cmd[8]	=0x4D;
	TakeOverStruse[i].cmd[9]	=0xDB;
	TakeOverStruse[i].cmd[10]	=0x06;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=3;
	
	i=9;
	TakeOverStruse[i].cmd[0]	=0xDB;
	TakeOverStruse[i].cmd[1]	=0xB6;
	TakeOverStruse[i].cmd[2]	=0x6D;
	TakeOverStruse[i].cmd[3]	=0xDB;
	TakeOverStruse[i].cmd[4]	=0xB6;
	TakeOverStruse[i].cmd[5]	=0x6D;
	TakeOverStruse[i].cmd[6]	=0xDB;
	TakeOverStruse[i].cmd[7]	=0xB6;
	TakeOverStruse[i].cmd[8]	=0x6D;
	TakeOverStruse[i].cmd[9]	=0xDB;
	TakeOverStruse[i].cmd[10]	=0x06;
	TakeOverStruse[i].cmd[11]	=0x00;
	TakeOverStruse[i].cmd[12]	=0x00;
	TakeOverStruse[i].cmd[13]	=0x00;
	TakeOverStruse[i].cmd[14]	=0x00;
	TakeOverStruse[i].duration=1;
	
	for(i=0;i<4;i++)
	{
		Checkreplybuff[0].nowstartRV[i]=1;
		Checkreplybuff[0].nowstartRC[i]=1;
		Checkreplybuff[0].nowstartYV[i]=1;
		Checkreplybuff[0].nowstartYC[i]=1;
		Checkreplybuff[0].nowstartGV[i]=1;
		Checkreplybuff[0].nowstartGC[i]=1;
	}
}




