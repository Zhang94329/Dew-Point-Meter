/*---------------------------------------------------------------- 
 * 文件名： rs485.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          驱动串口，提供485通讯
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "stdio.h"
#include "string.h"
#include "RS485.h"
void Set_UART1(void)
{
  
      U1CTL|=SWRST + CHAR;                //复位SWRST，8位数据模式
      U1TCTL|=SSEL1;                      //SMCLK为串口时钟
      U1BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
      U1BR0=baud_l;                       //N=UBR+(UxMCTL)/8
      U1MCTL=0x00;                        //微调寄存器为0，波特率9600bps
      ME2|=UTXE1;                         //UART1发送使能
      ME2|=URXE1;                         //UART1接收使能
      U1CTL&=~SWRST;
      IE2|=URXIE1;                        //接收中断使能位
  
   
      P3SEL|= BIT6 + BIT7;                //设置IO口为第二功能模式，启用UART功能
      P3DIR|= BIT6;                       //设置TXD1口方向为输出
  
}

void Send1Char(uchar sendchar)//发送一个字符
{
    DE;
	while (!(IFG2 & UTXIFG1)); //等待发送寄存器为空
	U1TXBUF = sendchar;
       delay_ms(5);
   RE;
}

void PutString0(char *ptr)//基于发送一个字符函数实现发送字符串
{
	while (*ptr != '\0')
	  Send1Char(*ptr++); // 发送数据         
}

