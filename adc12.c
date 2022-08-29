/*---------------------------------------------------------------- 
 * 文件名： adc12.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          驱动adc12供系统使用
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/


#include"adc12.h"
#include <msp430x16x.h>
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
#include "RS485.h"
extern  uchar Flag;                  //频率保存标志量
extern uchar high;
extern uchar low;
void InitADC12()
{ 

  P6SEL|=0x02;                                    //选择ADC通道
  ADC12CTL0|= ADC12ON + SHT0_2 + REF2_5V + REFON; //ADC电源控制开，16个CLK，内部基准2.5V
  ADC12CTL1|= ADC12SSEL1 + ADC12SSEL0;            //SMCLK做时钟源
  ADC12MCTL0= SREF0 + INCH_1;                     //参考控制位及通道选择，这里选择通道0
  ADC12IE|= 0x01;                                 //中断允许
  ADC12CTL0|= ENC;  
  
   /*
   P6SEL |= 0x02;        //使用A/D通道 A0
 ADC12CTL0 = ADC12ON ; //开ADC12内核,设SHT0=2 (N=4) 
 ADC12CTL1 = SHP ;     //SAMPCON信号选为采样定时器输出
//ADC12内部参考电压设置
 ADC12CTL0 |= REF2_5V; //选用内部参考电压为2.5V
 ADC12CTL0 |= REFON;   //内部参考电压打开
 ADC12MCTL0 |= SREF_0; //R+=2.5V R-=VSS
 //转换允许
   ADC12IE|= 0x01;                                 //中断允许
 ADC12CTL0 |= ENC ;    //转换允许(上升沿)
 */
}
/*******************************************************************
			adc温度采集
********************************************************************/

float Temperature=0;

#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{

 
       
  
  while((ADC12CTL1&0x01)==1);           //如果ADC忙，则等待，否则读取ADC转换数值
      
       
      //电压换算成温度

	
	
   float Rt=0;
   float Rp=10000;
   float T2=273.15+25;
   float Bx=3470;//3950;//
   float Ka=273.15;
   float vol=0;
   vol=(float)ADC12MEM0*(3.3/4096);
   Rt=(10000*vol)/(3.3-vol);
  // Rt=(3.3-vol)*10000/vol;
   Temperature=1/(1/T2+log(Rt/Rp)/Bx)-Ka+sysParam .temperature_void;
	
       
     high= (long)ADC12MEM0>>8;
      low= (long)ADC12MEM0 &0xFF;
      
      
      Send1Char(high);  
       Send1Char(low);  
      high= (long)Temperature>>8;
      low= (long)Temperature &0xFF;
       Send1Char(high);  
       Send1Char(low); 
       Send1Char(0xf4); 
      Send1Char(0x03);  //485发送我们的温度信息
     Flag=1;
    
 
}

