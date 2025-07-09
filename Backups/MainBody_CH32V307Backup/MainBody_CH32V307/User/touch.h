/*
 * touch.h
 *
 *  Created on: 2025��4��29��
 *      Author: 86135
 */

#ifndef USER_TOUCH_H_
#define USER_TOUCH_H_

#include "ch32v30x_conf.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x.h"
#include "lcd.h"

#define READ_TIMES 5    //��ȡ����
#define LOST_VAL 1      //����ֵ
#define ERR_RANGE 50    //�����������������Χ
#define SAVE_ADDR_BASE 40 //EEPROM����ַ
//IO����
#define TCS(x)  GPIO_WriteBit(GPIOD,GPIO_Pin_7,x)
#define TCLK(x) GPIO_WriteBit(GPIOB,GPIO_Pin_3,x)
#define TDIN(x) GPIO_WriteBit(GPIOB,GPIO_Pin_4,x)

#define DOUT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define TPEN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)

#define TP_PRES_DOWN 0x80  //����������
#define TP_CATH_PRES 0x40  //�а���������

//������������
typedef struct
{
    u8 (*init)(void);           //��ʼ��������������
    u8 (*scan)(u8);             //ɨ�败����.0,��Ļɨ��;1,��������;
    void (*adjust)(void);       //������У׼
    u16 x0;                     //ԭʼ����(��һ�ΰ���ʱ������)
    u16 y0;
    u16 x;                      //��ǰ����(�˴�ɨ��ʱ,����������)
    u16 y;
    u8  sta;                    //�ʵ�״̬
                                //b7:����1/�ɿ�0;
                                //b6:0,û�а�������;1,�а�������.
////////////////////////������У׼����/////////////////////////
    float xfac;
    float yfac;
    short xoff;
    short yoff;
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
    u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;        //������������touch.c���涨��


u8 TP_Init(void);
void TP_Write_Byte(u8 num);
u16 TP_Read_AD(u8 CMD);
u16 TP_Read_XOY(u8 xy);
u8 TP_Read_XY(u16 *x,u16 *y);
u8 TP_Read_XY2(u16 *x,u16 *y);
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);
void TP_Draw_Touch_Point(u16 x,u16 y,u16 color);
u8 TP_Scan(u8 tp);
void TP_Adjust(void);
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);
u8 TP_Get_Adjdata(void);
void TP_Save_Adjdata(void);

#endif /* USER_TOUCH_H_ */
