/*
 * touch.c
 *
 *  Created on: 2025年4月29日
 *      Author: 86135
 */

#include "touch.h"
#include <math.h>
//     LCD模块             TFTLCD插槽引脚        STM32连接引脚
//      PEN       --->          PEN                  PB15            //触摸屏触摸中断信号
//      MI        --->          MISO                 PA8             //触摸屏SPI总线读信号
//      MO        --->          MOSI                 PB3             //触摸屏SPI总线写信号
//      TCS       --->          TCS                  PC0             //触摸屏片选控制信号
//      CLK       --->          CLK                  PB4             //触摸屏SPI总线时钟信号

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
//默认为touchtype=0的数据.
uint8_t CMD_RDX=0XD0;
uint8_t CMD_RDY=0X90;
u16 ColorTab[5]={RED,GREEN,BLUE,YELLOW,BRED};//定义颜色数组
u16 ColornTab[8]={RED,MAGENTA,GREEN,DARKBLUE,BLUE,BLACK,LIGHTGREEN};

/*
  * 配置触摸IO
 * */
u8 TP_Init(void){
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);


    //这个应该后续配置成中断信号
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;            //B15 PENT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_15);//上拉


    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;             //A8->B4 MI
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;        //上拉输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_5);//上拉

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                //B3->B5  MO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);//B1推挽输出
    GPIO_SetBits(GPIOB,GPIO_Pin_4);//上拉

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;                //C0->D7  TCS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD, GPIO_Pin_7);//上拉

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;               //B4->B3    CLK
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_3);//上拉

    TP_Read_XY(&tp_dev.x,&tp_dev.y);//第一次读取初始化
//    //AT24CXX_Init();//初始化24CXX
//    if(TP_Get_Adjdata())return 0;//已经校准
//    else               //未校准?
//    {
//        LCD_Clear(WHITE);//清屏
//        TP_Adjust();  //屏幕校准
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
        TCLK(1);     //上升沿有效
    }
}

u16 TP_Read_AD(u8 CMD)
{
    u8 count=0;
    u16 Num=0;
    TCLK(0);     //先拉低时钟
    TDIN(0);     //拉低数据线
    TCS(0);      //选中触摸屏IC
    TP_Write_Byte(CMD);//发送命令字
    delay_us(6);//ADS7846的转换时间最长为6us
    TCLK(0);
    delay_us(1);
    TCLK(1);     //给1个时钟，清除BUSY
    TCLK(0);
    for(count=0;count<16;count++)//读出16位数据,只有高12位有效
    {
        Num<<=1;
        TCLK(0); //下降沿有效
        TCLK(1);
        if(DOUT)Num++;
    }
    Num>>=4;    //只有高12位有效.
    TCS(1);      //释放片选
    return(Num);
}



u16 TP_Read_XOY(u8 xy)
{
    u16 i, j;
    u16 buf[READ_TIMES];
    u16 sum=0;
    u16 temp;
    for(i=0;i<READ_TIMES;i++)buf[i]=TP_Read_AD(xy);
    for(i=0;i<READ_TIMES-1; i++)//排序
    {
        for(j=i+1;j<READ_TIMES;j++)
        {
            if(buf[i]>buf[j])//升序排列
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
    //if(xtemp<100||ytemp<100)return 0;//读数失败
    *x=xtemp;
    *y=ytemp;
    return 1;//读数成功
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
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-50内
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
    LCD_Fast_DrawPoint(x,y,BLACK);//中心点
    LCD_Fast_DrawPoint(x+1,y,BLACK);
    LCD_Fast_DrawPoint(x,y+1,BLACK);
    LCD_Fast_DrawPoint(x+1,y+1,BLACK);
}
void TP_Draw_Touch_Point(u16 x,u16 y,u16 color)
{
    POINT_COLOR=color;
    LCD_DrawLine(x-12,y,x+13,y);//横线
    LCD_DrawLine(x,y-12,x,y+13);//竖线
    LCD_Fast_DrawPoint(x+1,y+1,BLACK);
    LCD_Fast_DrawPoint(x-1,y+1,BLACK);
    LCD_Fast_DrawPoint(x+1,y-1,BLACK);
    LCD_Fast_DrawPoint(x-1,y-1,BLACK);
    LCD_DrawCircle(x,y,POINT_COLOR,6,0);//画中心圈
}

u8 TP_Scan(u8 tp)
{
    if(TPEN==0)//有按键按下
    {
        if(tp)TP_Read_XY2(&tp_dev.x,&tp_dev.y);//读取物理坐标
        else if(TP_Read_XY2(&tp_dev.x,&tp_dev.y))//读取屏幕坐标
        {
            tp_dev.x=tp_dev.xfac*tp_dev.x+tp_dev.xoff;//将结果转换为屏幕坐标
            tp_dev.y=tp_dev.yfac*tp_dev.y+tp_dev.yoff;
        }
        if((tp_dev.sta&TP_PRES_DOWN)==0)//之前没有被按下
        {
            tp_dev.sta=TP_PRES_DOWN|TP_CATH_PRES;//按键按下
            tp_dev.x0=tp_dev.x;//记录第一次按下时的坐标
            tp_dev.y0=tp_dev.y;
        }
    }else
    {
        if(tp_dev.sta&TP_PRES_DOWN)//之前是被按下的
        {
            tp_dev.sta&=~(1<<7);//标记按键松开
        }else//之前就没有被按下
        {
            tp_dev.x0=0;
            tp_dev.y0=0;
            tp_dev.x=0xffff;
            tp_dev.y=0xffff;
        }
    }
    return tp_dev.sta&TP_PRES_DOWN;//返回当前的触屏状态
}

void TP_Adjust(void)
{
    u16 pos_temp[4][2];//坐标缓存值
    u8  cnt=0;
    u16 d1,d2;
    u32 tem1,tem2;
    float fac;
    u16 outtime=0;
    cnt=0;
    POINT_COLOR=BLUE;
    BACK_COLOR =WHITE;
    LCD_Clear(WHITE);//清屏
    POINT_COLOR=RED;//红色
    LCD_Clear(WHITE);//清屏
    POINT_COLOR=BLACK;
    LCD_ShowString(10,40,200,16,16,"Please use the stylus click");//显示提示信息
    LCD_ShowString(10,56,200,16,16,"the cross on the screen.");//显示提示信息
    LCD_ShowString(10,72,200,16,16,"The cross will always move");//显示提示信息
    LCD_ShowString(10,88,200,16,16,"until the screen adjustment");//显示提示信息
    LCD_ShowString(10,104,200,16,16,"is completed.");//显示提示信息

    TP_Draw_Touch_Point(20,20,RED);//画点1
    tp_dev.sta=0;//消除触发信号
    tp_dev.xfac=0;//xfac用来标记是否校准过,所以校准之前必须清掉!以免错误
    while(1)//如果连续10秒钟没有按下,则自动退出
    {
        tp_dev.scan(1);//扫描物理坐标
        if((tp_dev.sta&0xc0)==TP_CATH_PRES)//按键按下了一次(此时按键松开了.)
        {
            outtime=0;
            tp_dev.sta&=~(1<<6);//标记按键已经被处理过了.

            pos_temp[cnt][0]=tp_dev.x;
            pos_temp[cnt][1]=tp_dev.y;
            cnt++;
            switch(cnt)
            {
                case 1:
                    TP_Draw_Touch_Point(20,20,WHITE);               //清除点1
                    TP_Draw_Touch_Point(lcddev.width-20,20,RED);    //画点2
                    break;
                case 2:
                    TP_Draw_Touch_Point(lcddev.width-20,20,WHITE);  //清除点2
                    TP_Draw_Touch_Point(20,lcddev.height-20,RED);   //画点3
                    break;
                case 3:
                    TP_Draw_Touch_Point(20,lcddev.height-20,WHITE);         //清除点3
                    TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,RED);  //画点4
                    break;
                case 4:  //全部四个点已经得到
                    //对边相等
                    tem1=abs(pos_temp[0][0]-pos_temp[1][0]);//x1-x2
                    tem2=abs(pos_temp[0][1]-pos_temp[1][1]);//y1-y2
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);//得到1,2的距离

                    tem1=abs(pos_temp[2][0]-pos_temp[3][0]);//x3-x4
                    tem2=abs(pos_temp[2][1]-pos_temp[3][1]);//y3-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);//得到3,4的距离
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05||d1==0||d2==0)//不合格
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //清除点4
                        TP_Draw_Touch_Point(20,20,RED);                             //画点1
                        TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//显示数据
                        continue;
                    }
                    tem1=abs(pos_temp[0][0]-pos_temp[2][0]);//x1-x3
                    tem2=abs(pos_temp[0][1]-pos_temp[2][1]);//y1-y3
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);//得到1,3的距离

                    tem1=abs(pos_temp[1][0]-pos_temp[3][0]);//x2-x4
                    tem2=abs(pos_temp[1][1]-pos_temp[3][1]);//y2-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);//得到2,4的距离
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05)//不合格
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //清除点4
                        TP_Draw_Touch_Point(20,20,RED);                             //画点1
                        TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//显示数据
                        continue;
                    }//正确了

                    //对角线相等
                    tem1=abs(pos_temp[1][0]-pos_temp[2][0]);//x1-x3
                    tem2=abs(pos_temp[1][1]-pos_temp[2][1]);//y1-y3
                    tem1*=tem1;
                    tem2*=tem2;
                    d1=sqrt(tem1+tem2);//得到1,4的距离

                    tem1=abs(pos_temp[0][0]-pos_temp[3][0]);//x2-x4
                    tem2=abs(pos_temp[0][1]-pos_temp[3][1]);//y2-y4
                    tem1*=tem1;
                    tem2*=tem2;
                    d2=sqrt(tem1+tem2);//得到2,3的距离
                    fac=(float)d1/d2;
                    if(fac<0.95||fac>1.05)//不合格
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //清除点4
                        TP_Draw_Touch_Point(20,20,RED);                             //画点1
                        TP_Adj_Info_Show(pos_temp[0][0],pos_temp[0][1],pos_temp[1][0],pos_temp[1][1],pos_temp[2][0],pos_temp[2][1],pos_temp[3][0],pos_temp[3][1],fac*100);//显示数据
                        continue;
                    }//正确了
                    //计算结果
                    tp_dev.xfac=(float)(lcddev.width-40)/(pos_temp[1][0]-pos_temp[0][0]);//得到xfac
                    tp_dev.xoff=(lcddev.width-tp_dev.xfac*(pos_temp[1][0]+pos_temp[0][0]))/2;//得到xoff

                    tp_dev.yfac=(float)(lcddev.height-40)/(pos_temp[2][1]-pos_temp[0][1]);//得到yfac
                    tp_dev.yoff=(lcddev.height-tp_dev.yfac*(pos_temp[2][1]+pos_temp[0][1]))/2;//得到yoff
                    if(abs(tp_dev.xfac)>2||abs(tp_dev.yfac)>2)//触屏和预设的相反了.
                    {
                        cnt=0;
                        TP_Draw_Touch_Point(lcddev.width-20,lcddev.height-20,WHITE);    //清除点4
                        TP_Draw_Touch_Point(20,20,RED);                             //画点1
                        LCD_ShowString(40,26,200,16, 16,"TP Need readjust!");
                        tp_dev.touchtype=!tp_dev.touchtype;//修改触屏类型.
                        if(tp_dev.touchtype)//X,Y方向与屏幕相反
                        {
                            CMD_RDX=0X90;
                            CMD_RDY=0XD0;
                        }else                  //X,Y方向与屏幕相同
                        {
                            CMD_RDX=0XD0;
                            CMD_RDY=0X90;
                        }
                        continue;
                    }
                    POINT_COLOR=BLUE;
                    LCD_Clear(WHITE);//清屏
                    LCD_ShowString(35,110,200,16, 16,"Touch Screen Adjust OK!");//校正完成
                    delay_ms(1000);
                    TP_Save_Adjdata();
                    LCD_Clear(WHITE);//清屏
                    return;//校正完成
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
    LCD_ShowNum(40+24,140,x0,4,16);     //显示数值
    LCD_ShowNum(40+24+80,140,y0,4,16);  //显示数值
    LCD_ShowNum(40+24,160,x1,4,16);     //显示数值
    LCD_ShowNum(40+24+80,160,y1,4,16);  //显示数值
    LCD_ShowNum(40+24,180,x2,4,16);     //显示数值
    LCD_ShowNum(40+24+80,180,y2,4,16);  //显示数值
    LCD_ShowNum(40+24,200,x3,4,16);     //显示数值
    LCD_ShowNum(40+24+80,200,y3,4,16);  //显示数值
    LCD_ShowNum(40+56,220,fac,3,16);    //显示数值,该数值必须在95~105范围之内.
}

u8 TP_Get_Adjdata(void)
{
    s32 tempfac=0;
    //tempfac=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+13);//读取标记字,看是否校准过！
    if(tempfac==0X0A)//触摸屏已经校准过了
    {
        //tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE,4);
        tp_dev.xfac=(float)tempfac/100000000;//得到x校准参数
        //tempfac=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+4,4);
        tp_dev.yfac=(float)tempfac/100000000;//得到y校准参数
        //得到x偏移量
        //tp_dev.xoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+8,2);
        //得到y偏移量
        //tp_dev.yoff=AT24CXX_ReadLenByte(SAVE_ADDR_BASE+10,2);
        //tp_dev.touchtype=AT24CXX_ReadOneByte(SAVE_ADDR_BASE+12);//读取触屏类型标记
        if(tp_dev.touchtype)//X,Y方向与屏幕相反
        {
            CMD_RDX=0X90;
            CMD_RDY=0XD0;
        }else                  //X,Y方向与屏幕相同
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
//    //保存校正结果!
//    temp=tp_dev.xfac*100000000;//保存x校正因素
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE,temp,4);
//    temp=tp_dev.yfac*100000000;//保存y校正因素
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE+4,temp,4);
//    //保存x偏移量
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE+8,tp_dev.xoff,2);
//    //保存y偏移量
//    //AT24CXX_WriteLenByte(SAVE_ADDR_BASE+10,tp_dev.yoff,2);
//    //保存触屏类型
//    //AT24CXX_WriteOneByte(SAVE_ADDR_BASE+12,tp_dev.touchtype);
//    temp=0X0A;//标记校准过了
//    //AT24CXX_WriteOneByte(SAVE_ADDR_BASE+13,temp);
}

void Touch_Test(void)
{
    //u8 key;
    u16 i=0;
    u16 j=0;
    u16 colorTemp=0;
    TP_Init();
    //DrawTestPage("测试10:Touch(按KEY0校准)      ");
    LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
    POINT_COLOR=RED;
    //LCD_Fill(lcddev.width-50,2,lcddev.width-50+22,18,RED);
    while(1)
    {
//        key=KEY_Scan();
        tp_dev.scan(0);
        if(tp_dev.sta&TP_PRES_DOWN)         //触摸屏被按下
        {
            if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
            {
                if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)
                {
                    //DrawTestPage("测试10:Touch(按KEY0校准)      ");//清除
                    LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
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

                else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,POINT_COLOR);      //画图
            }
        }else delay_ms(10); //没有按键按下的时候
        //if(key==1)  //KEY_RIGHT按下,则执行校准程序
        //{

            LCD_Clear(WHITE);//清屏
            TP_Adjust();  //屏幕校准
            TP_Save_Adjdata();
            //DrawTestPage("测试10:Touch(按KEY0校准)      ");
            LCD_ShowString(lcddev.width-24,0,200,16,16,"RST");//显示清屏区域
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

