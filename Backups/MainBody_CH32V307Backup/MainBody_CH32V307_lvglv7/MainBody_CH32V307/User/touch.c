/*
 * touch.c
 *
 *  Created on: 2025��4��29��
 *      Author: 86135
 */

#include "touch.h"
#include <math.h>
//     LCDģ��             TFTLCD�������        STM32��������
//      PEN       --->          PEN                  PB15            //�����������ж��ź�
//      MI        --->          MISO                 PA8             //������SPI���߶��ź�
//      MO        --->          MOSI                 PB3             //������SPI����д�ź�
//      TCS       --->          TCS                  PC0             //������Ƭѡ�����ź�
//      CLK       --->          CLK                  PB4             //������SPI����ʱ���ź�

_m_tp_dev tp_dev=
{
    TP_Init,
    TP_Scan,
    TP_Adjust,
    0,
    0,
    0,
    0,
    0,
    .xfac=-0.0653594807f,
    .yfac=0.0897435918f,
    .xoff=256,
    .yoff=-8,
    0,
};
//Ĭ��Ϊtouchtype=0������.
uint8_t CMD_RDX=0XD0;
uint8_t CMD_RDY=0X90;
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//������ɫ����
u16 ColornTab[8]={RED,MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN};

/*
  * ���ô���IO
 * */
u8 TP_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);


    //���Ӧ�ú������ó��ж��ź�
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;            //B15 PENT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_15);//����


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;             //A8->B4 MI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);//����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                //B3->B5  MO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//B1�������
    GPIO_SetBits(GPIOB,GPIO_Pin_4);//����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                //C0->D7  TCS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD, GPIO_Pin_7);//����

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;               //B4->B3    CLK
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_3);//����

    TP_Read_XY(&tp_dev.x,&tp_dev.y);//��һ�ζ�ȡ��ʼ��
//    //AT24CXX_Init();//��ʼ��24CXX
//    if(TP_Get_Adjdata())return 0;//�Ѿ�У׼
//    else               //δУ׼?
//    {
//        LCD_Clear(WHITE);//����
//        TP_Adjust();  //��ĻУ׼
//        TP_Save_Adjdata();
//    }
//    TP_Get_Adjdata();
    return 1;
}

void TP_Write_Byte(u8 num){
    u8 count=0;
    for(count=0;count<8;count++)
    {
        if(num&0x80)TDIN(1);
        else TDIN(0);
        num<<=1;
        TCLK(0);
        TCLK(1);     //��������Ч
    }
}

u16 TP_Read_AD(u8 CMD)
{
    u8 count=0;
    u16 Num=0;
    TCLK(0);     //������ʱ��
    TDIN(0);     //����������
    TCS(0);      //ѡ�д�����IC
    TP_Write_Byte(CMD);//����������
    delay_us(6);//ADS7846��ת��ʱ���Ϊ6us
    TCLK(0);
    delay_us(1);
    TCLK(1);     //��1��ʱ�ӣ����BUSY
    TCLK(0);
    for(count=0;count<16;count++)//����16λ����,ֻ�и�12λ��Ч
    {
        Num<<=1;
        TCLK(0); //�½�����Ч
        TCLK(1);
        if(DOUT)Num++;
    }
    Num>>=4;    //ֻ�и�12λ��Ч.
    TCS(1);      //�ͷ�Ƭѡ
    return(Num);
}



u16 TP_Read_XOY(u8 xy)
{
    u16 i, j;
    u16 buf[READ_TIMES];
    u16 sum=0;
    u16 temp;
    for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);
    for(i=0;i<READ_TIMES-1; i++)//����
    {
        for(j=i+1;j<READ_TIMES;j++)
        {
            if(buf[i]>buf[j])//��������
            {
                temp=buf[i];
                buf[i]=buf[j];
                buf[j]=temp;
            }
        }
    }
    sum=0;
    for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
    temp=sum/(READ_TIMES-2*LOST_VAL);
    return temp;
}

u8 TP_Read_XY(u16 *x,u16 *y)
{
    u16 xtemp,ytemp;
    xtemp=TP_Read_XOY(CMD_RDX);
    ytemp=TP_Read_XOY(CMD_RDY);
    //if(xtemp<100||ytemp<100)return 0;//����ʧ��
    *x=xtemp;
    *y=ytemp;
    return 1;//�����ɹ�
}

u8 TP_Read_XY2(u16 *x,u16 *y)
{
    u16 x1,y1;
    u16 x2,y2;
    u8 flag;
    flag=TP_Read_XY(&x1,&y1);
    if(flag==0)return(0);
    flag=TP_Read_XY(&x2,&y2);
    if(flag==0)return(0);
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-50��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        *x=(x1+x2)/2;
        *y=(y1+y2)/2;
        return 1;
    }else return 0;
}
void TP_Draw_Big_Point(u16 x,u16 y,u16 color)
{
    POINT_COLOR=color;
    LCD_Fast_DrawPoint(x,y,BLACK);//���ĵ�
    LCD_Fast_DrawPoint(x+1,y,BLACK);
    LCD_Fast_DrawPoint(x,y+1,BLACK);
    LCD_Fast_DrawPoint(x+1,y+1,BLACK);
}
void TP_Draw_Touch_Point(u16 x,u16 y,u16 color)
{
    POINT_COLOR=color;
    LCD_DrawLine(x-12,y,x+13,y);//����
    LCD_DrawLine(x,y-12,x,y+13);//����
    LCD_Fast_DrawPoint(x+1,y+1,BLACK);
    LCD_Fast_DrawPoint(x-1,y+1,BLACK);
    LCD_Fast_DrawPoint(x+1,y-1,BLACK);
    LCD_Fast_DrawPoint(x-1,y-1,BLACK);
    LCD_DrawCircle(x,y,POINT_COLOR,6,0);//������Ȧ
}

u8 TP_Scan(u8 tp)
{
    if(TPEN==0)//�а�������
    {
        if(tp)TP_Read_XY2(&tp_dev.x,&tp_dev.y);//��ȡ��������
        else if(TP_Read_XY2(&tp_dev.x,&tp_dev.y))//��ȡ��Ļ����
        {
            tp_dev.x=tp_dev.xfac*tp_dev.x+tp_dev.xoff;//�����ת��Ϊ��Ļ����
            tp_dev.y=tp_dev.yfac*tp_dev.y+tp_dev.yoff;
        }
        if((tp_dev.sta&TP_PRES_DOWN)==0)//֮ǰû�б�����
        {
            tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//��������
            tp_dev.x0=tp_dev.x;//��¼��һ�ΰ���ʱ������
            tp_dev.y0=tp_dev.y;
        }
    }else
    {
        if(tp_dev.sta&TP_PRES_DOWN)//֮ǰ�Ǳ����µ�
        {
            tp_dev.sta&=~(1<<7);//��ǰ����ɿ�
        }else//֮ǰ��û�б�����
        {
            tp_dev.x0=0;
            tp_dev.y0=0;
            tp_dev.x=0xffff;
            tp_dev.y=0xffff;
        }
    }
    return tp_dev.sta&TP_PRES_DOWN;//���ص�ǰ�Ĵ���״̬
}

void TP_Adjust(void)
{
    u16 pos_temp[4][2];//���껺��ֵ
    u8  cnt=0;
    u16 d1,d2;
    u32 tem1,tem2;
    float fac;
    u16 outtime=0;
    cnt=0;
    POINT_COLOR=BLUE;
    BACK_COLOR =WHITE;
    LCD_Clear(WHITE);//����
    POINT_COLOR=RED;//��ɫ
    LCD_Clear(WHITE);//����
    POINT_COLOR=BLACK;
    LCD_ShowString(10,40,200,16,16,"Please use the stylus click");//��ʾ��ʾ��Ϣ
    LCD_ShowString(10,56,200,16,16,"the cross on the screen.");//��ʾ��ʾ��Ϣ
    LCD_ShowString(10,72,200,16,16,"The cross will always move");//��ʾ��ʾ��Ϣ
    LCD_ShowString(10,88,200,16,16,"until the screen adjustment");//��ʾ��ʾ��Ϣ
    LCD_ShowString(10,104,200,16,16,"is completed.");//��ʾ��ʾ��Ϣ

    TP_Draw_Touch_Point(20,20,RED);//����1
    tp_dev.sta=0;//���������ź�
    tp_dev.xfac=0;//xfac��������Ƿ�У׼��,����У׼֮ǰ�������!�������
    while(1)//�������10����û�а���,���Զ��˳�
    {
        tp_dev.scan(1);//ɨ����������
        if((tp_dev.sta&0xc0)==TP_CATH_PRES)//����������һ��(��ʱ�����ɿ���.)
        {
            outtime=0;
            tp_dev.sta&=~(1<<6);//��ǰ����Ѿ����������.

            pos_temp[cnt][0]=tp_dev.x;
            pos_temp[cnt][1]=tp_dev.y;
            cnt++;
            switch(cnt)
            {
                case 1:
                    TP_Draw_Touch_Point(20,20,WHITE);               //�����1
                    TP_Draw_Touch_Point(lcddev.width-20,20,RED);    //����2
                    break;
                case 2:
                    TP_Draw_Touch_Point(lcddev.width-20,20,WHITE);  //�����2
                    TP_Draw_Touch_Point(20,lcddev.height-20,RED);   //����3
                    break;
                case 3:
                    TP_Draw_Touch_Point(20,lcddev.height-20,WHITE);         //�����3
                    TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,RED);  //����4
                    break;
                case 4:  //ȫ���ĸ����Ѿ��õ�
                    //�Ա����
                    tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
                    tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);//�õ�1,2�ľ���

                    tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
                    tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);//�õ�3,4�ľ���
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05||d1==0||d2==0)//���ϸ�
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //�����4
                        TP_Draw_Touch_Point(20,20,RED);                             //����1
                        TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����
                        continue;
                    }
                    tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
                    tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);//�õ�1,3�ľ���

                    tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
                    tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);//�õ�2,4�ľ���
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05)//���ϸ�
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //�����4
                        TP_Draw_Touch_Point(20,20,RED);                             //����1
                        TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����
                        continue;
                    }//��ȷ��

                    //�Խ������
                    tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
                    tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);//�õ�1,4�ľ���

                    tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
                    tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);//�õ�2,3�ľ���
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05)//���ϸ�
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //�����4
                        TP_Draw_Touch_Point(20,20,RED);                             //����1
                        TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//��ʾ����
                        continue;
                    }//��ȷ��
                    //������
                    tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]);//�õ�xfac
                    tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//�õ�xoff

                    tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//�õ�yfac
                    tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//�õ�yoff
                    if(abs(tp_dev.xfac)>2||abs(tp_dev.yfac)>2)//������Ԥ����෴��.
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //�����4
                        TP_Draw_Touch_Point(20,20,RED);                             //����1
                        LCD_ShowString(40,26,200,16, 16,"TP Need readjust!");
                        tp_dev.touchtype=!tp_dev.touchtype;//�޸Ĵ�������.
                        if(tp_dev.touchtype)//X,Y��������Ļ�෴
                        {
                            CMD_RDX=0X90;
                            CMD_RDY=0XD0;
                        }else                  //X,Y��������Ļ��ͬ
                        {
                            CMD_RDX=0XD0;
                            CMD_RDY=0X90;
                        }
                        continue;
                    }
                    POINT_COLOR=BLUE;
                    LCD_Clear(WHITE);//����
                    LCD_ShowString(35,110,200,16, 16,"Touch Screen Adjust OK!");//У�����
                    delay_ms(1000);
                    TP_Save_Adjdata();
                    LCD_Clear(WHITE);//����
                    return;//У�����
            }
        }
        delay_ms(10);
        outtime++;
        if(outtime>1000)
        {
            TP_Get_Adjdata();
            break;
        }
    }
}

void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac)
{
    POINT_COLOR=RED;
    LCD_ShowString(40,140,200,16,16,"x1:");
    LCD_ShowString(40+80,140,200,16,16,"y1:");
    LCD_ShowString(40,160,200,16,16,"x2:");
    LCD_ShowString(40+80,160,200,16, 16,"y2:");
    LCD_ShowString(40,180,200,16, 16,"x3:");
    LCD_ShowString(40+80,180,200,16, 16,"y3:");
    LCD_ShowString(40,200,200,16, 16,"x4:");
    LCD_ShowString(40+80,200,200,16, 16,"y4:");
    LCD_ShowString(40,220,200,16, 16,"fac is:");
    LCD_ShowNum(40+24,140,x0,4,16);     //��ʾ��ֵ
    LCD_ShowNum(40+24+80,140,y0,4,16);  //��ʾ��ֵ
    LCD_ShowNum(40+24,160,x1,4,16);     //��ʾ��ֵ
    LCD_ShowNum(40+24+80,160,y1,4,16);  //��ʾ��ֵ
    LCD_ShowNum(40+24,180,x2,4,16);     //��ʾ��ֵ
    LCD_ShowNum(40+24+80,180,y2,4,16);  //��ʾ��ֵ
    LCD_ShowNum(40+24,200,x3,4,16);     //��ʾ��ֵ
    LCD_ShowNum(40+24+80,200,y3,4,16);  //��ʾ��ֵ
    LCD_ShowNum(40+56,220,fac,3,16);    //��ʾ��ֵ,����ֵ������95~105��Χ֮��.
}

u8 TP_Get_Adjdata(void)
{
    s32 tempfac=0;
    //tempfac=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+13);//��ȡ�����,���Ƿ�У׼����
    if(tempfac==0X0A)//�������Ѿ�У׼����
    {
        //tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE,4);
        tp_dev.xfac=(float)tempfac/100000000;//�õ�xУ׼����
        //tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);
        tp_dev.yfac=(float)tempfac/100000000;//�õ�yУ׼����
        //�õ�xƫ����
        //tp_dev.xoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+8,2);
        //�õ�yƫ����
        //tp_dev.yoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+10,2);
        //tp_dev.touchtype=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+12);//��ȡ�������ͱ��
        if(tp_dev.touchtype)//X,Y��������Ļ�෴
        {
            CMD_RDX=0X90;
            CMD_RDY=0XD0;
        }else                  //X,Y��������Ļ��ͬ
        {
            CMD_RDX=0XD0;
            CMD_RDY=0X90;
        }
        return 1;
    }
    return 0;
}

void TP_Save_Adjdata(void)
{
//    s32 temp=0;
//    //����У�����!
//    temp=tp_dev.xfac*100000000;//����xУ������
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE,temp,4);
//    temp=tp_dev.yfac*100000000;//����yУ������
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,temp,4);
//    //����xƫ����
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE+8,tp_dev.xoff,2);
//    //����yƫ����
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE+10,tp_dev.yoff,2);
//    //���津������
//    //AT24CXX_WriteOneByte(SAVE_ADDR_BASE+12,tp_dev.touchtype);
//    temp=0X0A;//���У׼����
//    //AT24CXX_WriteOneByte(SAVE_ADDR_BASE+13,temp);
}

void Touch_Test(void)
{
    //u8 key;
    u16 i=0;
    u16 j=0;
    u16 colorTemp=0;
    TP_Init();
    //DrawTestPage("����10:Touch(��KEY0У׼)      ");
    LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
    POINT_COLOR=RED;
    //LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,RED);
    while(1)
    {
//        key=KEY_Scan();
        tp_dev.scan(0);
        if(tp_dev.sta&TP_PRES_DOWN)         //������������
        {
            if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
            {
                if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)
                {
                    //DrawTestPage("����10:Touch(��KEY0У׼)      ");//���
                    LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
                    POINT_COLOR=colorTemp;
                    //LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,POINT_COLOR);
                }
                else if((tp_dev.x>(lcddev.width-50)&&tp_dev.x<(lcddev.width-50+22))&&tp_dev.y<20)
                {
                //LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,ColorTab[j%5]);
                POINT_COLOR=ColorTab[(j++)%5];
                colorTemp=POINT_COLOR;
                delay_ms(10);
                }

                else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,POINT_COLOR);      //��ͼ
            }
        }else delay_ms(10); //û�а������µ�ʱ��
        //if(key==1)  //KEY_RIGHT����,��ִ��У׼����
        //{

            LCD_Clear(WHITE);//����
            TP_Adjust();  //��ĻУ׼
            TP_Save_Adjdata();
            //DrawTestPage("����10:Touch(��KEY0У׼)      ");
            LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//��ʾ��������
            POINT_COLOR=colorTemp;
            //LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,POINT_COLOR);
        //}
        i++;
        if(i==30)
        {
            i=0;
            //break;
        }
    }
}

