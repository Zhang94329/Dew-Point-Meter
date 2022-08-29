/********************************************************************
pom 172 �������
********************************************************************/
#include <msp430x16x.h>
#include "Config.h"                     //����������ͷ�ļ�����Ҫ����IO�˿���Ϣ
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
#include "RS485.h"
#include "adc12.h"
#include "sensor_data.h"
  


long i=0;
uchar Count=0,flag=0;                    //�������棬��־λ
uchar Flag=1;                    //��־����
double flag1=0;
double Flag2=0;                  //Ƶ�ʱ����־��
double Dp=0;                     //������ݱ���
static double j[6]={0};
uchar high=0,low=0;
//***********************************************************************
//               MSP430IO�ڳ�ʼ��
//***********************************************************************
void Port_Init()
{
  P5DIR |= BIT2;                        //P52��ΪRS485���ƿڣ����ģʽ
  P5OUT |= BIT2;                        //�ø�P52
  P1SEL = 0x00;                   //P1��ͨIO����
  P1DIR = 0xFE;                   //P10����ģʽ���ⲿ��·�ѽ���������
  P2DIR |= 0XFB;
  P3DIR |= 0X3F;
  P4DIR |= 0XFF;
  P5DIR |= 0XFB;
  P6DIR |= 0XBC;
  P1IE  = 0x01;                   //����P1.0�ж�
  P1IES = 0x01;                   //�����ش����ж�
  P1IFG = 0x00;                   //��������жϱ�־�Ĵ���
   P6DIR |= BIT1;                 //A1��Ϊ�¶Ȳ�����adcͨ��
   P6OUT |= BIT1;
}
/********************************************************************
			DAC12��ʼ�����ó���
********************************************************************/
void DAC12_Init(void)
{
  DAC12_0CTL |= DAC12CALON;             //����У��DAC
  while((DAC12_0CTL & DAC12CALON) != 0){_NOP();}//�ȴ�У�����
  
  ADC12CTL0 = REFON + REF2_5V;                        // �ο���ѹΪ�ڲ�2.5v
  DAC12_0CTL = DAC12AMP_5 + DAC12IR + DAC12LSEL_0;//���ƼĴ������ã��Զ��������ݣ��ڻ�׼Ϊ������
  DAC12_0CTL |= DAC12SREF_0;
  DAC12_0CTL |= DAC12ENC; // ����DACģ��(DAC12LSEL_0ʱ�˾����ʡ����������Ϊ1)
  DAC12_0DAT = 0x0000;    //DAC��ֵΪ0����������Ĵ����Ϳ��Ը���DAC�������
}
//***********************************************************************
//             TIMERA��ʼ��������ΪUPģʽ����
//***********************************************************************
void TIMERA_Init(void)                                   //UPģʽ��������������ΪCCR0+1
{
  TACTL |= TASSEL1 + TACLR + ID0 + ID1 + MC0 + TAIE;     //SMCLK��ʱ��Դ��8��Ƶ�����Ӽ���ģʽ�����ж�
  TACCR0 = 9999;                                         //CCR0=9999��10ms�ж�һ��
}
//***********************************************************************
//             TIMERA�жϷ��������Ҫ�ж��ж�����
//***********************************************************************
#pragma vector = TIMERA1_VECTOR
__interrupt void Timer_A(void)
{
  switch(TAIV)                                  //��Ҫ�ж��жϵ�����
  {
  case 2:break;
  case 4:break;
  case 10:Count++;break;                         //���ñ�־λFlag
  }
   if(Count==250)                                 //100��Ϊ1��
 //if(Count==100)
  {
    Count=0;
    flag=1;
   // LPM1_EXIT;
  }
} 
//*******************************************************************
//	P1.0���жϷ��������Ҫ�ж�
//********************************************************************

#pragma vector = PORT1_VECTOR
__interrupt void P1_IRQ(void)
{
  
  while(P1IFG&0x01)
  {
   i++;
   P1IFG=0x00;   // ����0��ӦS1�жϣ������ֶ����־λ������D1D2
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
      Send1Char(0x07);  //485�������ǵ�Ƶ����Ϣ
     RE;  /*
    high=(long)j[1]>>8;
      low=(long)j[1]&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x07); 
      Send1Char(0x08);  //485�������ǵ�Ƶ����Ϣ
     RE;
   //delay_ms(500);  
     */	 
       i=0;
       Sensor_Info(j);        // �������ǲɼ����������鵽���������
     __low_power_mode_off_on_exit();  //�˳��͹���ģʽ
       
   }
  }
}



//***********************************************************************
//                  �����жϺ���
//***********************************************************************

  char str[4]={0};//ָ���������
  int rxcount=0;

//���ڽ����ж�,�����ַ���ָ��.
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
			������
********************************************************************/

   double temp=0;

void main(void)
{ 
  WDT_Init();                               // �رտ��Ź�
  Clock_Init();                             //ʱ��ϵͳ��ʼ��������Ϊ�ⲿʱ��
 // FlashInit();
   FlashInit();
  Port_Init();
  DAC12_Init();                             //��ʼ��DAC12
  Set_UART1();
  InitADC12();
  TIMERA_Init();
  delay_ms(10);
  RE;
  _EINT();
   Flag=1;
  falsh_readData();                          //��ʼ��falsh��������ݵ�����
  
  while(1)
  {
 
     if(str[3]==255)
     {
          temp=str[1]+str[2]/10;//��������С�����
       
       get_data_count( temp,str[0] );  //�������ݸ�������
       Send1Char( str[0]);
       Send1Char( str[1]);
       Send1Char( str[2]);
       Send1Char( str[3]);
       Send1Char(0x08); 
       Send1Char(0x09); 
    delay_ms(5);
    //���Դ��� �յ�ʲô��ʲô.
    
          str[0]=0;
          str[1]=0;
          str[2]=0;
          str[3]=0;
          rxcount=0;
     }
  while(Flag==1)//�¶�adcת������
    {
      ADC12CTL0 |= ADC12SC;           //����ת��
      ADC12CTL0 &= ~ADC12SC;          //����
      break;
    }

   // DAC12_0DAT=(int)((Dp+111.25)*21.63);   
   
//    DAC12_0DAT=j;
    __low_power_mode_1();//�����͹���ģʽ
  }
}