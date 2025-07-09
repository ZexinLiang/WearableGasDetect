/*
 * touch.h
 *
 *  Created on: 2025年4月29日
 *      Author: 86135
 */

#ifndef USER_TOUCH_H_
#define USER_TOUCH_H_

#include "ch32v30x_conf.h"
#include "ch32v30x_gpio.h"
#include "ch32v30x.h"
#include "lcd.h"

#define READ_TIMES 5    //读取次数
#define LOST_VAL 1      //丢弃值
#define ERR_RANGE 50    //连续读两次允许的误差范围
#define SAVE_ADDR_BASE 40 //EEPROM基地址
//IO操作
#define TCS(x)  GPIO_WriteBit(GPIOD,GPIO_Pin_7,x)
#define TCLK(x) GPIO_WriteBit(GPIOB,GPIO_Pin_3,x)
#define TDIN(x) GPIO_WriteBit(GPIOB,GPIO_Pin_4,x)

#define DOUT  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)
#define TPEN  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)

#define TP_PRES_DOWN 0x80  //触屏被按下
#define TP_CATH_PRES 0x40  //有按键按下了

//触摸屏控制器
typedef struct
{
    u8 (*init)(void);           //初始化触摸屏控制器
    u8 (*scan)(u8);             //扫描触摸屏.0,屏幕扫描;1,物理坐标;
    void (*adjust)(void);       //触摸屏校准
    u16 x0;                     //原始坐标(第一次按下时的坐标)
    u16 y0;
    u16 x;                      //当前坐标(此次扫描时,触屏的坐标)
    u16 y;
    u8  sta;                    //笔的状态
                                //b7:按下1/松开0;
                                //b6:0,没有按键按下;1,有按键按下.
////////////////////////触摸屏校准参数/////////////////////////
    float xfac;
    float yfac;
    short xoff;
    short yoff;
//新增的参数,当触摸屏的左右上下完全颠倒时需要用到.
//touchtype=0的时候,适合左右为X坐标,上下为Y坐标的TP.
//touchtype=1的时候,适合左右为Y坐标,上下为X坐标的TP.
    u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;        //触屏控制器在touch.c里面定义


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
