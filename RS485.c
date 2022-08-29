/*---------------------------------------------------------------- 
 * �ļ����� rs485.c
 * 
 * �ļ�����������   
 *          MSP430F16x,MSP430F14Xϵ�е�Ƭ��Flash�����
 *      ˵����  
 *          �������ڣ��ṩ485ͨѶ
 * 
 * �޸ı�ʶ��   
 * �޸�������   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "stdio.h"
#include "string.h"
#include "RS485.h"
void Set_UART1(void)
{
  
      U1CTL|=SWRST + CHAR;                //��λSWRST��8λ����ģʽ
      U1TCTL|=SSEL1;                      //SMCLKΪ����ʱ��
      U1BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
      U1BR0=baud_l;                       //N=UBR+(UxMCTL)/8
      U1MCTL=0x00;                        //΢���Ĵ���Ϊ0��������9600bps
      ME2|=UTXE1;                         //UART1����ʹ��
      ME2|=URXE1;                         //UART1����ʹ��
      U1CTL&=~SWRST;
      IE2|=URXIE1;                        //�����ж�ʹ��λ
  
   
      P3SEL|= BIT6 + BIT7;                //����IO��Ϊ�ڶ�����ģʽ������UART����
      P3DIR|= BIT6;                       //����TXD1�ڷ���Ϊ���
  
}

void Send1Char(uchar sendchar)//����һ���ַ�
{
    DE;
	while (!(IFG2 & UTXIFG1)); //�ȴ����ͼĴ���Ϊ��
	U1TXBUF = sendchar;
       delay_ms(5);
   RE;
}

void PutString0(char *ptr)//���ڷ���һ���ַ�����ʵ�ַ����ַ���
{
	while (*ptr != '\0')
	  Send1Char(*ptr++); // ��������         
}

