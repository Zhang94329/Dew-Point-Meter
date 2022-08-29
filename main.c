/********************************************************************
pom 172 程序设计
********************************************************************/
#include <msp430x16x.h>
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
#include "RS485.h"
#include "adc12.h"
#include "sensor_data.h"
  


long i=0;
uchar Count=0,flag=0;                    //计数保存，标志位
uchar Flag=1;                    //标志变量
double flag1=0;
double Flag2=0;                  //频率保存标志量
double Dp=0;                     //输出数据变量
static double j[6]={0};
uchar high=0,low=0;
//***********************************************************************
//               MSP430IO口初始化
//***********************************************************************
void Port_Init()
{
  P5DIR |= BIT2;                        //P52口为RS485控制口，输出模式
  P5OUT |= BIT2;                        //置高P52
  P1SEL = 0x00;                   //P1普通IO功能
  P1DIR = 0xFE;                   //P10输入模式，外部电路已接上拉电阻
  P2DIR |= 0XFB;
  P3DIR |= 0X3F;
  P4DIR |= 0XFF;
  P5DIR |= 0XFB;
  P6DIR |= 0XBC;
  P1IE  = 0x01;                   //开启P1.0中断
  P1IES = 0x01;                   //上升沿触发中断
  P1IFG = 0x00;                   //软件清零中断标志寄存器
   P6DIR |= BIT1;                 //A1作为温度补偿的adc通道
   P6OUT |= BIT1;
}
/********************************************************************
			DAC12初始化设置程序
********************************************************************/
void DAC12_Init(void)
{
  DAC12_0CTL |= DAC12CALON;             //启动校验DAC
  while((DAC12_0CTL & DAC12CALON) != 0){_NOP();}//等待校验完成
  
  ADC12CTL0 = REFON + REF2_5V;                        // 参考电压为内部2.5v
  DAC12_0CTL = DAC12AMP_5 + DAC12IR + DAC12LSEL_0;//控制寄存器设置，自动更新数据，内基准为满量程
  DAC12_0CTL |= DAC12SREF_0;
  DAC12_0CTL |= DAC12ENC; // 启动DAC模块(DAC12LSEL_0时此句可以省，这里设置为1)
  DAC12_0DAT = 0x0000;    //DAC初值为0，更新这个寄存器就可以更改DAC输出数据
}
//***********************************************************************
//             TIMERA初始化，设置为UP模式计数
//***********************************************************************
void TIMERA_Init(void)                                   //UP模式计数，计数周期为CCR0+1
{
  TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK做时钟源，8分频，增加计数模式，开中断
  TACCR0 = 9999;                                         //CCR0=9999，10ms中断一次
}
//***********************************************************************
//             TIMERA中断服务程序，需要判断中断类型
//***********************************************************************
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch(TAIV)                                  //需要判断中断的类型
  {
  case 2:break;
  case 4:break;
  case 10:Count++;break;                         //设置标志位Flag
  }
   if(Count==250)                                 //100次为1秒
 //if(Count==100)
  {
    Count=0;
    flag=1;
   // LPM1_EXIT;
  }
} 
//*******************************************************************
//	P1.0口中断服务程序，需要判断
//********************************************************************

#pragma vector = PORT1_VECTOR
__interrupt void P1_IRQ(void)
{
  
  while(P1IFG&0x01)
  {
   i++;
   P1IFG=0x00;   // 引脚0对应S1中断，必须手动清标志位，点亮D1D2
   if(flag==1)
   {
      flag=0;
      Flag2=i;
      earlier(i,j);
     // j=(j/2.5);
    
      high=i>>8;
      low=i&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x06); 
      Send1Char(0x07);  //485发送我们的频率信息
     RE;  /*
    high=(long)j[1]>>8;
      low=(long)j[1]&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x07); 
      Send1Char(0x08);  //485发送我们的频率信息
     RE;
   //delay_ms(500);  
     */	 
       i=0;
       Sensor_Info(j);        // 输入我们采集的数据数组到输出函数中
     __low_power_mode_off_on_exit();  //退出低功耗模式
       
   }
  }
}



//***********************************************************************
//                  串口中断函数
//***********************************************************************

  char str[4]={0};//指令接收数组
  int rxcount=0;

//串口接收中断,接收字符串指令.
#pragma vector=USART1RX_VECTOR
__interrupt void usart1_rx(void)
{  

     while (!(IFG2 & UTXIFG1)); 
     { 
       str[rxcount]=RXBUF1;
       rxcount++;

     }
   
}

/*******************************************************************
			主程序
********************************************************************/

   double temp=0;

void main(void)
{ 
  WDT_Init();                               // 关闭看门狗
  Clock_Init();                             //时钟系统初始化，设置为外部时钟
 // FlashInit();
   FlashInit();
  Port_Init();
  DAC12_Init();                             //初始化DAC12
  Set_UART1();
  InitADC12();
  TIMERA_Init();
  delay_ms(10);
  RE;
  _EINT();
   Flag=1;
  falsh_readData();                          //初始化falsh里面的数据到程序
  
  while(1)
  {
 
     if(str[3]==255)
     {
          temp=str[1]+str[2]/10;//将整数与小数相加
       
       get_data_count( temp,str[0] );  //传送数据给处理函数
       Send1Char( str[0]);
       Send1Char( str[1]);
       Send1Char( str[2]);
       Send1Char( str[3]);
       Send1Char(0x08); 
       Send1Char(0x09); 
    delay_ms(5);
    //测试代码 收到什么发什么.
    
          str[0]=0;
          str[1]=0;
          str[2]=0;
          str[3]=0;
          rxcount=0;
     }
  while(Flag==1)//温度adc转换开启
    {
      ADC12CTL0 |= ADC12SC;           //开启转换
      ADC12CTL0 &= ~ADC12SC;          //清零
      break;
    }

   // DAC12_0DAT=(int)((Dp+111.25)*21.63);   
   
//    DAC12_0DAT=j;
    __low_power_mode_1();//开启低功耗模式
  }
}