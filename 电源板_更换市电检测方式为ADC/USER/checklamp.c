////////////////////////////////////////////////////////////////
/*
检测回码
*/
////////////////////////////////////////////////////////////////
#include "stm32f10x.h"
#include "common.h"
#include "data.h"


void checklampreply()
{
	int i;
	for(i=0;i<5;i++)
	{
		if((cheakfgf>>i)&0x01)
			Checkrstatebuff[i].CheckorNO=1;
		else
			Checkrstatebuff[i].CheckorNO=0;
		
		if((cheakfgS>>i)&0x01)
			Checkrstatebuff[i+5].CheckorNO=1;
		else
			Checkrstatebuff[i+5].CheckorNO=0;
	}
	for(i=0;i<10;i++)
	{
		if(Checkrstatebuff[i].CheckorNO==1)//需要检测
		{
			if(Checkreplybuff[i].start==0)//没有回码
			{
				Checkrstatebuff[i].Replytime+=1;
				if(Checkrstatebuff[i].Replytime>Errortime)
				{
					TakeOverorder=0;
					Y_FLASHorder=0;
					return;
				}
			}
			else		//有回码
			{
				uint64_t cheakdatanowe;
				int j;
				cheakdatanowe=0;
				//解析回码
				for(j=0;j<8;j++)
				{
					cheakdatanowe=cheakdatanowe<<8;
					cheakdatanowe+=Checkreplybuff[i].cmd[7-j];
				}
				for(j=0;j<4;j++)	
				{
					Checkreplybuff[i].nowcolour[j]	=(cheakdatanowe>>(j*16))&0x07;
					Checkreplybuff[i].nowstart[j]		=(cheakdatanowe>>(j*16+3))&0x01;
					
					Checkreplybuff[i].nowstartRC[j]	=(cheakdatanowe>>(j*16+6))&0x01;
					Checkreplybuff[i].nowstartRV[j]	=(cheakdatanowe>>(j*16+7))&0x01;
					
					Checkreplybuff[i].nowstartYC[j]	=(cheakdatanowe>>(j*16+8))&0x01;
					Checkreplybuff[i].nowstartYV[j]	=(cheakdatanowe>>(j*16+9))&0x01;
					
					Checkreplybuff[i].nowstartGC[j]	=(cheakdatanowe>>(j*16+10))&0x01;
					Checkreplybuff[i].nowstartGV[j]	=(cheakdatanowe>>(j*16+11))&0x01;
				}
				//校验分析
				for(j=0;j<4;j++)
				{
					if(Checkreplybuff[i].nowcolour[j]==0)//灭灯
					{
						if(Checkreplybuff[i].nowstartRC[j]==1)//红电流
						{
							Checkrstatebuff[i].FRedCtime[j]=Checkrstatebuff[i].FRedCtime[j]+1;
							if(Checkrstatebuff[i].FRedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FRedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
							//		TakeOverorder=OrderOFF;
							//		Y_FLASHorder=OrderOFF;
							//		return;
								}								
							}
						}
						else
							Checkrstatebuff[i].FRedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartRV[j]==1)	//红电压
						{
							Checkrstatebuff[i].FRedVtime[j]=Checkrstatebuff[i].FRedVtime[j]+1;
							if(Checkrstatebuff[i].FRedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FRedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
								//	TakeOverorder=OrderOFF;
								//	Y_FLASHorder=OrderOFF;
								//	return;
								}

							}
						}
						else
							Checkrstatebuff[i].FRedVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYC[j]==1)//黄电流
						{
							Checkrstatebuff[i].FYellowCtime[j]=Checkrstatebuff[i].FYellowCtime[j]+1;
							if(Checkrstatebuff[i].FYellowCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FYellowCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
								//	TakeOverorder=OrderOFF;
								//	Y_FLASHorder=OrderOFF;
								//	return;
								}
							}
						}
						else
							Checkrstatebuff[i].FYellowCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYV[j]==1)	//黄电压
						{
							Checkrstatebuff[i].FYellowVtime[j]=Checkrstatebuff[i].FYellowVtime[j]+1;
							if(Checkrstatebuff[i].FYellowVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FYellowVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
								//	TakeOverorder=OrderOFF;
								//	Y_FLASHorder=OrderOFF;
								//	return;
								}
							}
						}
						else
							Checkrstatebuff[i].FYellowVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGC[j]==1)//绿电流
						{
							Checkrstatebuff[i].FGreedCtime[j]=Checkrstatebuff[i].FGreedCtime[j]+1;
							if(Checkrstatebuff[i].FGreedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
								//	TakeOverorder=OrderOFF;
								//	Y_FLASHorder=OrderOFF;
								//	return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGV[j]==1)	//绿电压
						{
							Checkrstatebuff[i].FGreedVtime[j]=Checkrstatebuff[i].FGreedVtime[j]+1;
							if(Checkrstatebuff[i].FGreedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
							//		TakeOverorder=OrderOFF;
							//		Y_FLASHorder=OrderOFF;
							//		return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedVtime[j]=0;
					}
					else if((Checkreplybuff[i].nowcolour[j]==1)||(Checkreplybuff[i].nowcolour[j]==4))//绿灯
					{
						if(Checkreplybuff[i].nowstartRC[j]==1)//红电流
						{
							Checkrstatebuff[i].FRedCtime[j]=Checkrstatebuff[i].FRedCtime[j]+1;
							if(Checkrstatebuff[i].FRedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FRedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}								
							}
						}
						else
							Checkrstatebuff[i].FRedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartRV[j]==1)	//红电压
						{
							Checkrstatebuff[i].FRedVtime[j]=Checkrstatebuff[i].FRedVtime[j]+1;
							if(Checkrstatebuff[i].FRedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FRedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}

							}
						}
						else
							Checkrstatebuff[i].FRedVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYC[j]==1)//黄电流
						{
							Checkrstatebuff[i].FYellowCtime[j]=Checkrstatebuff[i].FYellowCtime[j]+1;
							if(Checkrstatebuff[i].FYellowCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FYellowCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FYellowCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYV[j]==1)	//黄电压
						{
							Checkrstatebuff[i].FYellowVtime[j]=Checkrstatebuff[i].FYellowVtime[j]+1;
							if(Checkrstatebuff[i].FYellowVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FYellowVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FYellowVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGC[j]==0)//绿电流
						{
							Checkrstatebuff[i].GreedCtime[j]=Checkrstatebuff[i].GreedCtime[j]+1;
							if(Checkrstatebuff[i].GreedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].GreedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].GreedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGV[j]==0)	//绿电压
						{
							Checkrstatebuff[i].GreedVtime[j]=Checkrstatebuff[i].GreedVtime[j]+1;
							if(Checkrstatebuff[i].GreedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].GreedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].GreedVtime[j]=0;
					}
					else if((Checkreplybuff[i].nowcolour[j]==2)||(Checkreplybuff[i].nowcolour[j]==5))//黄灯
					{
						if(Checkreplybuff[i].nowstartRC[j]==1)//红电流
						{
							Checkrstatebuff[i].FRedCtime[j]=Checkrstatebuff[i].FRedCtime[j]+1;
							if(Checkrstatebuff[i].FRedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FRedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}								
							}
						}
						else
							Checkrstatebuff[i].FRedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartRV[j]==1)	//红电压
						{
							Checkrstatebuff[i].FRedVtime[j]=Checkrstatebuff[i].FRedVtime[j]+1;
							if(Checkrstatebuff[i].FRedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FRedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}

							}
						}
						else
							Checkrstatebuff[i].FRedVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYC[j]==0)//黄电流
						{
							Checkrstatebuff[i].YellowCtime[j]=Checkrstatebuff[i].YellowCtime[j]+1;
							if(Checkrstatebuff[i].YellowCtime[j]>Errortime)
							{
								Checkrstatebuff[i].YellowCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].YellowCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYV[j]==0)	//黄电压
						{
							Checkrstatebuff[i].YellowVtime[j]=Checkrstatebuff[i].YellowVtime[j]+1;
							if(Checkrstatebuff[i].YellowVtime[j]>Errortime)
							{
								Checkrstatebuff[i].YellowVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].YellowVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGC[j]==1)//绿电流
						{
							Checkrstatebuff[i].FGreedCtime[j]=Checkrstatebuff[i].FGreedCtime[j]+1;
							if(Checkrstatebuff[i].FGreedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGV[j]==1)	//绿电压
						{
							Checkrstatebuff[i].FGreedVtime[j]=Checkrstatebuff[i].FGreedVtime[j]+1;
							if(Checkrstatebuff[i].FGreedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedVtime[j]=0;
					}
					else if((Checkreplybuff[i].nowcolour[j]==3)||(Checkreplybuff[i].nowcolour[j]==6))//红灯
					{
						if(Checkreplybuff[i].nowstartRC[j]==0)//红电流
						{
							Checkrstatebuff[i].RedCtime[j]=Checkrstatebuff[i].RedCtime[j]+1;
							if(Checkrstatebuff[i].RedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].RedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}								
							}
						}
						else
							Checkrstatebuff[i].RedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartRV[j]==0)	//红电压
						{
							Checkrstatebuff[i].RedVtime[j]=Checkrstatebuff[i].RedVtime[j]+1;
							if(Checkrstatebuff[i].RedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].RedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].RedVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYC[j]==1)//黄电流
						{
							Checkrstatebuff[i].FYellowCtime[j]=Checkrstatebuff[i].FYellowCtime[j]+1;
							if(Checkrstatebuff[i].FYellowCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FYellowCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FYellowCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYV[j]==1)	//黄电压
						{
							Checkrstatebuff[i].FYellowVtime[j]=Checkrstatebuff[i].FYellowVtime[j]+1;
							if(Checkrstatebuff[i].FYellowVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FYellowVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FYellowVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGC[j]==1)//绿电流
						{
							Checkrstatebuff[i].FGreedCtime[j]=Checkrstatebuff[i].FGreedCtime[j]+1;
							if(Checkrstatebuff[i].FGreedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGV[j]==1)	//绿电压
						{
							Checkrstatebuff[i].FGreedVtime[j]=Checkrstatebuff[i].FGreedVtime[j]+1;
							if(Checkrstatebuff[i].FGreedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedVtime[j]=0;
					}
					else if(Checkreplybuff[i].nowcolour[j]==7)//红灯 黄灯
					{
						if(Checkreplybuff[i].nowstartRC[j]==0)//红电流
						{
							Checkrstatebuff[i].RedCtime[j]=Checkrstatebuff[i].RedCtime[j]+1;
							if(Checkrstatebuff[i].RedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].RedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}								
							}
						}
						else
							Checkrstatebuff[i].RedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartRV[j]==0)	//红电压
						{
							Checkrstatebuff[i].RedVtime[j]=Checkrstatebuff[i].RedVtime[j]+1;
							if(Checkrstatebuff[i].RedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].RedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}

							}
						}
						else
							Checkrstatebuff[i].RedVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYC[j]==0)//黄电流
						{
							Checkrstatebuff[i].YellowCtime[j]=Checkrstatebuff[i].YellowCtime[j]+1;
							if(Checkrstatebuff[i].YellowCtime[j]>Errortime)
							{
								Checkrstatebuff[i].YellowCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].YellowCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartYV[j]==0)	//黄电压
						{
							Checkrstatebuff[i].YellowVtime[j]=Checkrstatebuff[i].YellowVtime[j]+1;
							if(Checkrstatebuff[i].YellowVtime[j]>Errortime)
							{
								Checkrstatebuff[i].YellowVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].YellowVtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGC[j]==1)//绿电流
						{
							Checkrstatebuff[i].FGreedCtime[j]=Checkrstatebuff[i].FGreedCtime[j]+1;
							if(Checkrstatebuff[i].FGreedCtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedCtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkCurrentorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedCtime[j]=0;
						
						if(Checkreplybuff[i].nowstartGV[j]==1)	//绿电压
						{
							Checkrstatebuff[i].FGreedVtime[j]=Checkrstatebuff[i].FGreedVtime[j]+1;
							if(Checkrstatebuff[i].FGreedVtime[j]>Errortime)
							{
								Checkrstatebuff[i].FGreedVtime[j]=Errortime;
								if((checkY_FLASHorder==OrderON)&&(checkVoltageorder==OrderON))
								{
									TakeOverorder=OrderOFF;
									Y_FLASHorder=OrderOFF;
									return;
								}
							}
						}
						else
							Checkrstatebuff[i].FGreedVtime[j]=0;
					}
					
				}
			}
		}
	}
}