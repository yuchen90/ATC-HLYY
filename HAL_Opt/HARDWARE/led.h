//灯控板四个灯组点灯头文件

#ifndef __LED_H__
#define __LED_H__

//灯组1点灯与灭灯定义
#define R1_ON PCout(13)=1
#define Y1_ON PCout(15)=1
#define G1_ON PCout(1)=1
#define R1_OFF PCout(13)=0
#define Y1_OFF PCout(15)=0
#define G1_OFF PCout(1)=0

//灯组2点灯与灭灯定义
#define R2_ON PCout(3)=1
#define Y2_ON PAout(3)=1
#define G2_ON PAout(5)=1
#define R2_OFF PCout(3)=0
#define Y2_OFF PAout(3)=0
#define G2_OFF PAout(5)=0

//灯组3点灯与灭灯定义
#define R3_ON PAout(7)=1
#define Y3_ON PCout(5)=1
#define G3_ON PBout(1)=1
#define R3_OFF PAout(7)=0
#define Y3_OFF PCout(5)=0
#define G3_OFF PBout(1)=0

//灯组4点灯与灭灯定义
#define R4_ON PBout(11)=1
#define Y4_ON PBout(13)=1
#define G4_ON PBout(15)=1
#define R4_OFF PBout(11)=0
#define Y4_OFF PBout(13)=0
#define G4_OFF PBout(15)=0

#endif
