/*---------------------------------------------------------------- 
 * �ļ����� adc12.c
 * 
 * �ļ�����������   
 *          MSP430F16x,MSP430F14Xϵ�е�Ƭ��Flash�����
 *      ˵����  
 *          ����adc12��ϵͳʹ��
 * 
 * �޸ı�ʶ��   
 * �޸�������   
**----------------------------------------------------------------*/


#include"adc12.h"
#include <msp430x16x.h>
#include "Config.h"                     //����������ͷ�ļ�����Ҫ����IO�˿���Ϣ
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
#include "RS485.h"
extern  uchar Flag;                  //Ƶ�ʱ����־��
extern uchar high;
extern uchar low;
void InitADC12()
{ 

  P6SEL|=0x02;                                    //ѡ��ADCͨ��
  ADC12CTL0|= ADC12ON + SHT0_2 + REF2_5V + REFON; //ADC��Դ���ƿ���16��CLK���ڲ���׼2.5V
  ADC12CTL1|= ADC12SSEL1 + ADC12SSEL0;            //SMCLK��ʱ��Դ
  ADC12MCTL0= SREF0 + INCH_1;                     //�ο�����λ��ͨ��ѡ������ѡ��ͨ��0
  ADC12IE|= 0x01;                                 //�ж�����
  ADC12CTL0|= ENC;  
  
   /*
   P6SEL |= 0x02;        //ʹ��A/Dͨ�� A0
 ADC12CTL0 = ADC12ON ; //��ADC12�ں�,��SHT0=2 (N=4) 
 ADC12CTL1 = SHP ;     //SAMPCON�ź�ѡΪ������ʱ�����
//ADC12�ڲ��ο���ѹ����
 ADC12CTL0 |= REF2_5V; //ѡ���ڲ��ο���ѹΪ2.5V
 ADC12CTL0 |= REFON;   //�ڲ��ο���ѹ��
 ADC12MCTL0 |= SREF_0; //R+=2.5V R-=VSS
 //ת������
   ADC12IE|= 0x01;                                 //�ж�����
 ADC12CTL0 |= ENC ;    //ת������(������)
 */
}
/*******************************************************************
			adc�¶Ȳɼ�
********************************************************************/

float Temperature=0;

#pragma vector=ADC_VECTOR
__interrupt void ADC12_ISR(void)
{

 
       
  
  while((ADC12CTL1&0x01)==1);           //���ADCæ����ȴ��������ȡADCת����ֵ
      
       
      //��ѹ������¶�

	
	
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
      Send1Char(0x03);  //485�������ǵ��¶���Ϣ
     Flag=1;
    
 
}

