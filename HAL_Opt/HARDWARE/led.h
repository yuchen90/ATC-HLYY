//�ƿذ��ĸ�������ͷ�ļ�

#ifndef __LED_H__
#define __LED_H__

//����1��Ӧbit-band��ַ
#define R1 PCout(13)
#define Y1 PCout(15)
#define G1 PCout(1)

//����2��Ӧbit-band��ַ
#define R2 PCout(3)
#define Y2 PAout(3)
#define G2 PAout(5)

//����3��Ӧbit-band��ַ
#define R3 PAout(7)
#define Y3 PCout(5)
#define G3 PBout(1)

//����4��Ӧbit-band��ַ
#define R4 PBout(11)
#define Y4 PBout(13)
#define G4 PBout(15)

//��ɫ״̬����
typedef enum
{
    LED_OFF = 0u,
    LED_ON  = 1u
}LED_STATE;



/* ���ʺ����¶��壬��Ϊ�����CANЭ�������λ����Ϣ�õ���ֻ���Ӧ��ַ������Ҫ��ֵ
//����1�������ƶ���
#define R1_ON PCout(13)=1
#define Y1_ON PCout(15)=1
#define G1_ON PCout(1)=1
#define R1_OFF PCout(13)=0
#define Y1_OFF PCout(15)=0
#define G1_OFF PCout(1)=0

//����2�������ƶ���
#define R2_ON PCout(3)=1
#define Y2_ON PAout(3)=1
#define G2_ON PAout(5)=1
#define R2_OFF PCout(3)=0
#define Y2_OFF PAout(3)=0
#define G2_OFF PAout(5)=0

//����3�������ƶ���
#define R3_ON PAout(7)=1
#define Y3_ON PCout(5)=1
#define G3_ON PBout(1)=1
#define R3_OFF PAout(7)=0
#define Y3_OFF PCout(5)=0
#define G3_OFF PBout(1)=0

//����4�������ƶ���
#define R4_ON PBout(11)=1
#define Y4_ON PBout(13)=1
#define G4_ON PBout(15)=1
#define R4_OFF PBout(11)=0
#define Y4_OFF PBout(13)=0
#define G4_OFF PBout(15)=0
*/

//�ƿذ��ַ��Ӧ�ܽ�
#define ADDR0 PBin(9)
#define ADDR1 PBin(8)
#define ADDR2 PBin(7)
#define ADDR3 PBin(6)

//�ƿذ幤��ָʾ����ʾ
#define MCU_RUN PAout(9)

//CAN�գ���ָʾ��
#define CAN_Tx_LED PAout(0)
#define CAN_Rx_LED PAout(1)

#endif
