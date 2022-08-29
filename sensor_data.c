
/*---------------------------------------------------------------- 
 * �ļ�����sensor_data.c
 * 
 * �ļ�����������   
 *          MSP430F16x,MSP430F14Xϵ�е�Ƭ��Flash�����
 *      ˵����  
 *          ���ݵĴ���궨���������
 *     
 * 
 * �޸ı�ʶ��   
 * �޸�������   
**----------------------------------------------------------------*/
#include"sensor_data.h"
#include <msp430x16x.h>
#include "Config.h"                     //����������ͷ�ļ�����Ҫ����IO�˿���Ϣ
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
#include "RS485.h"
#include "adc12.h"
extern double flag1;
extern double Flag2;                  //Ƶ�ʱ����־��
extern float Temperature;
extern uchar high;
extern uchar low;
//*******************************************************************
//	�������㺯��
//********************************************************************



  double  earlier(double x,double *arr)
  {
   
    double truevalue=0;
         for(int a=0;a<6;a++)
         {
              if(a==0)
              {
                 if(x>=sysParam.sysParam_30.ConcentParam_50.Value)
             {
             
                                double x1 = sysParam.sysParam_30.ConcentParam_50.Value, y1 = sysParam.sysParam_30.ConcentParam_50.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_60.Value, y2 = sysParam.sysParam_30.ConcentParam_60.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_30.ConcentParam_40.Value&&x<sysParam.sysParam_30.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_30.ConcentParam_40.Value, y1 = sysParam.sysParam_30.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_50.Value, y2 = sysParam.sysParam_30.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_30.ConcentParam_30.Value&&x<sysParam.sysParam_30.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_30.ConcentParam_30.Value, y1 = sysParam.sysParam_30.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_40.Value, y2 = sysParam.sysParam_30.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_30.ConcentParam_20.Value&&x<sysParam.sysParam_30.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_30.ConcentParam_20.Value, y1 = sysParam.sysParam_30.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_30.Value, y2 = sysParam.sysParam_30.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_30.ConcentParam_10.Value&&x<sysParam.sysParam_30.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_30.ConcentParam_10.Value, y1 = sysParam.sysParam_30.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_20.Value, y2 = sysParam.sysParam_30.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_30.ConcentParam_0.Value&&x<sysParam.sysParam_30.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_30.ConcentParam_0.Value, y1 = sysParam.sysParam_30.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_10.Value, y2 = sysParam.sysParam_30.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_30.ConcentParam_h.Value&&x<sysParam.sysParam_30.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_30.ConcentParam_h.Value, y1 = sysParam.sysParam_30.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_0.Value, y2 = sysParam.sysParam_30.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_30.ConcentParam_h20.Value&&x<sysParam.sysParam_30.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_30.ConcentParam_h20.Value, y1 = sysParam.sysParam_30.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_30.ConcentParam_h.Value, y2 = sysParam.sysParam_30.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
               arr[a]=truevalue;
               
              }
              else if(a==1)
              {
               if(x>=sysParam.sysParam_20.ConcentParam_50.Value)
             {
             
                                double x1 = sysParam.sysParam_20.ConcentParam_50.Value, y1 = sysParam.sysParam_20.ConcentParam_50.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_60.Value, y2 = sysParam.sysParam_20.ConcentParam_60.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_20.ConcentParam_40.Value&&x<sysParam.sysParam_20.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_20.ConcentParam_40.Value, y1 = sysParam.sysParam_20.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_50.Value, y2 = sysParam.sysParam_20.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_20.ConcentParam_30.Value&&x<sysParam.sysParam_20.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_20.ConcentParam_30.Value, y1 = sysParam.sysParam_20.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_40.Value, y2 = sysParam.sysParam_20.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_20.ConcentParam_20.Value&&x<sysParam.sysParam_20.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_20.ConcentParam_20.Value, y1 = sysParam.sysParam_20.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_30.Value, y2 = sysParam.sysParam_20.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_20.ConcentParam_10.Value&&x<sysParam.sysParam_20.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_20.ConcentParam_10.Value, y1 = sysParam.sysParam_20.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_20.Value, y2 = sysParam.sysParam_20.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_20.ConcentParam_0.Value&&x<sysParam.sysParam_20.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_20.ConcentParam_0.Value, y1 = sysParam.sysParam_20.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_10.Value, y2 = sysParam.sysParam_20.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_20.ConcentParam_h.Value&&x<sysParam.sysParam_20.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_20.ConcentParam_h.Value, y1 = sysParam.sysParam_20.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_0.Value, y2 = sysParam.sysParam_20.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_20.ConcentParam_h20.Value&&x<sysParam.sysParam_20.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_20.ConcentParam_h20.Value, y1 = sysParam.sysParam_20.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_20.ConcentParam_h.Value, y2 = sysParam.sysParam_20.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
               arr[a]=truevalue;
               /* high=(long)arr[a]>>8;
      low=(long)arr[a]&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x0b); 
      Send1Char(0x0b);  //485�������ǵ�Ƶ����Ϣ
     RE;*/
              }
              else if(a==2)
              {
                if(x>=sysParam.sysParam_10.ConcentParam_50.Value)
             {
             
                                double x1 = sysParam.sysParam_10.ConcentParam_50.Value, y1 = sysParam.sysParam_10.ConcentParam_50.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_60.Value, y2 = sysParam.sysParam_10.ConcentParam_60.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_10.ConcentParam_40.Value&&x<sysParam.sysParam_10.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_10.ConcentParam_40.Value, y1 = sysParam.sysParam_10.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_50.Value, y2 = sysParam.sysParam_10.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_10.ConcentParam_30.Value&&x<sysParam.sysParam_10.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_10.ConcentParam_30.Value, y1 = sysParam.sysParam_10.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_40.Value, y2 = sysParam.sysParam_10.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_10.ConcentParam_20.Value&&x<sysParam.sysParam_10.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_10.ConcentParam_20.Value, y1 = sysParam.sysParam_10.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_30.Value, y2 = sysParam.sysParam_10.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_10.ConcentParam_10.Value&&x<sysParam.sysParam_10.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_10.ConcentParam_10.Value, y1 = sysParam.sysParam_10.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_20.Value, y2 = sysParam.sysParam_10.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_10.ConcentParam_0.Value&&x<sysParam.sysParam_10.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_10.ConcentParam_0.Value, y1 = sysParam.sysParam_10.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_10.Value, y2 = sysParam.sysParam_10.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_10.ConcentParam_h.Value&&x<sysParam.sysParam_10.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_10.ConcentParam_h.Value, y1 = sysParam.sysParam_10.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_0.Value, y2 = sysParam.sysParam_10.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_10.ConcentParam_h20.Value&&x<sysParam.sysParam_10.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_10.ConcentParam_h20.Value, y1 = sysParam.sysParam_10.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_10.ConcentParam_h.Value, y2 = sysParam.sysParam_10.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
              arr[a]=truevalue;
              }
              else if(a==3)
              {
                 if(x>=sysParam.sysParam_0.ConcentParam_50.Value)
             {
             
                                double x1 = sysParam.sysParam_0.ConcentParam_50.Value, y1 = sysParam.sysParam_0.ConcentParam_50.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_60.Value, y2 = sysParam.sysParam_0.ConcentParam_60.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_0.ConcentParam_40.Value&&x<sysParam.sysParam_0.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_0.ConcentParam_40.Value, y1 = sysParam.sysParam_0.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_50.Value, y2 = sysParam.sysParam_0.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_0.ConcentParam_30.Value&&x<sysParam.sysParam_0.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_0.ConcentParam_30.Value, y1 = sysParam.sysParam_0.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_40.Value, y2 = sysParam.sysParam_0.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_0.ConcentParam_20.Value&&x<sysParam.sysParam_0.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_0.ConcentParam_20.Value, y1 = sysParam.sysParam_0.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_30.Value, y2 = sysParam.sysParam_0.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_0.ConcentParam_10.Value&&x<sysParam.sysParam_0.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_0.ConcentParam_10.Value, y1 = sysParam.sysParam_0.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_20.Value, y2 = sysParam.sysParam_0.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_0.ConcentParam_0.Value&&x<sysParam.sysParam_0.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_0.ConcentParam_0.Value, y1 = sysParam.sysParam_0.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_10.Value, y2 = sysParam.sysParam_0.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_0.ConcentParam_h.Value&&x<sysParam.sysParam_0.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_0.ConcentParam_h.Value, y1 = sysParam.sysParam_0.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_0.Value, y2 = sysParam.sysParam_0.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_0.ConcentParam_h20.Value&&x<sysParam.sysParam_0.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_0.ConcentParam_h20.Value, y1 = sysParam.sysParam_0.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_0.ConcentParam_h.Value, y2 = sysParam.sysParam_0.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
               arr[a]=truevalue;
              }
              
              else if(a==4)
                    {
                      if(x>=sysParam.sysParam_l_10.ConcentParam_50.Value)
                   {
                   
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_50.Value, y1 = sysParam.sysParam_l_10.ConcentParam_50.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_60.Value, y2 = sysParam.sysParam_l_10.ConcentParam_60.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                   
                   }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_40.Value&&x<sysParam.sysParam_l_10.ConcentParam_50.Value)
                 {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_40.Value, y1 = sysParam.sysParam_l_10.ConcentParam_40.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_50.Value, y2 = sysParam.sysParam_l_10.ConcentParam_50.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                 }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_30.Value&&x<sysParam.sysParam_l_10.ConcentParam_40.Value)
                 {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_30.Value, y1 = sysParam.sysParam_l_10.ConcentParam_30.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_40.Value, y2 = sysParam.sysParam_l_10.ConcentParam_40.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                       
                 }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_20.Value&&x<sysParam.sysParam_l_10.ConcentParam_30.Value)
                 {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_20.Value, y1 = sysParam.sysParam_l_10.ConcentParam_20.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_30.Value, y2 = sysParam.sysParam_l_10.ConcentParam_30.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                 }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_10.Value&&x<sysParam.sysParam_l_10.ConcentParam_20.Value)
                   {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_10.Value, y1 = sysParam.sysParam_l_10.ConcentParam_10.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_20.Value, y2 = sysParam.sysParam_l_10.ConcentParam_20.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                   }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_0.Value&&x<sysParam.sysParam_l_10.ConcentParam_10.Value)
                     {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_0.Value, y1 = sysParam.sysParam_l_10.ConcentParam_0.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_10.Value, y2 = sysParam.sysParam_l_10.ConcentParam_10.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                     
                     }
                  else if(x>=sysParam.sysParam_l_10.ConcentParam_h.Value&&x<sysParam.sysParam_l_10.ConcentParam_0.Value)
                     {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_h.Value, y1 = sysParam.sysParam_l_10.ConcentParam_h.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_0.Value, y2 = sysParam.sysParam_l_10.ConcentParam_0.concentration;
                                      
                                      truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                     
                     } 
                else if(x>=sysParam.sysParam_l_10.ConcentParam_h20.Value&&x<sysParam.sysParam_l_10.ConcentParam_h.Value)
                     {
                                     
                                       double x1 = sysParam.sysParam_l_10.ConcentParam_h20.Value, y1 = sysParam.sysParam_l_10.ConcentParam_h20.concentration;
                                       double x2 = sysParam.sysParam_l_10.ConcentParam_h.Value, y2 = sysParam.sysParam_l_10.ConcentParam_h.concentration;
                                       
                                      truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                     
                     } 
                     arr[a]=truevalue;
              }
              else if(a==5)
              {
                
                if(x>=sysParam.sysParam_l_20.ConcentParam_50.Value)
             {
             
                                double x1 = sysParam.sysParam_l_20.ConcentParam_50.Value, y1 = sysParam.sysParam_l_20.ConcentParam_50.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_60.Value, y2 = sysParam.sysParam_l_20.ConcentParam_60.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_40.Value&&x<sysParam.sysParam_l_20.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_40.Value, y1 = sysParam.sysParam_l_20.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_50.Value, y2 = sysParam.sysParam_l_20.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_30.Value&&x<sysParam.sysParam_l_20.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_30.Value, y1 = sysParam.sysParam_l_20.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_40.Value, y2 = sysParam.sysParam_l_20.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_20.Value&&x<sysParam.sysParam_l_20.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_20.Value, y1 = sysParam.sysParam_l_20.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_30.Value, y2 = sysParam.sysParam_l_20.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_10.Value&&x<sysParam.sysParam_l_20.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_10.Value, y1 = sysParam.sysParam_l_20.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_20.Value, y2 = sysParam.sysParam_l_20.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_0.Value&&x<sysParam.sysParam_l_20.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_0.Value, y1 = sysParam.sysParam_l_20.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_10.Value, y2 = sysParam.sysParam_l_20.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_l_20.ConcentParam_h.Value&&x<sysParam.sysParam_l_20.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_h.Value, y1 = sysParam.sysParam_l_20.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_0.Value, y2 = sysParam.sysParam_l_20.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_l_20.ConcentParam_h20.Value&&x<sysParam.sysParam_l_20.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_l_20.ConcentParam_h20.Value, y1 = sysParam.sysParam_l_20.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_l_20.ConcentParam_h.Value, y2 = sysParam.sysParam_l_20.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //��������Ҫ��Ƶ��ֵ
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
               arr[a]=truevalue;
              }
              
         
         }
         
    
 return 0;
  }

/*******************************************************************
			����ֵ����
* ��    �ƣ� revalue
* ��    �ܣ����ؼ���ֵƵ��
* ��ڲ�����¶��ֵ 
* ���ڲ�����������Ƶ��ֵ
* ˵    ��: 
********************************************************************/




   double revalue(double x)
   {
            double m=100,n=4000;
            double i,sum;
            double eps=0.001;//1e-6;//eps�Ǿ��ȿ��ƣ��˴�Ϊ10^-6����ʾ����С
            double  a=0.00000005003,b=-0.0004086,c=1.115,d=x; //a=0.00000005003,b=-0.0004086,c=1.115,d=x;
            double f1,f2;
            f1=a*pow(m,3)+b*pow(m,2)+c*m+d;//pow(x,y)=x^y���ݺ���
            f2=a*pow(n,3)+b*pow(n,2)+c*n+d;
            //�ж�f1*f2<0����Ҫ����
                if(f1*f2<0)
                    {
                        while(fabs(m-n)>eps)
                        {
                            i=(m+n)/2;
                            sum=a*pow(i,3)+b*pow(i,2)+c*i+d;
                                  if(fabs(sum)<eps)//�������f(i)�ľ���ֵ|sum|С������С
                                    {
                                       // printf("���̵�һ�����ƽ�Ϊx*=%lf\n",i);
                                        break;
                                    }
                                          else if(f1*sum<0)
                                          {
                                              n=i;
                                               // break;
                                                              }
                                                else if(f2*sum<0)
                                                {
                                                    m=i;
                                                     // break;
                                                }
                        }
                    }
                  //����պ�����ȡֵΪ���̽�
                  else if(f1*f2==0)
                  {
                      if(f1==0)
                      {// printf("���̵�һ����Ϊx*=%lf\n",m);
                      }
                      if(f2==0)
                      {//printf("���̵�һ����Ϊx*=%lf\n",n);
                      }
                  }          
                    else
                    {// printf("�����ڸ��������޽⣡\n");
                    }
         
   return i;
   
   }


/*******************************************************************
			У׼���ݴ�����
               
********************************************************************/
  extern uchar high;
extern uchar low;
  
double get_data_count(double data,int n )
{
   
      double s;
      if(n==255)   //У׼��������
      {
         if(Temperature>31||(21<Temperature&&Temperature<29)||(11<Temperature&&Temperature<19)||(1<Temperature&&Temperature<9)||(-9<Temperature&&Temperature<-1)||(-19<Temperature&&Temperature<-11)||Temperature<-21)//�жϵ�ǰ�¶��Ƿ���Ա궨������������궨�����򷵻�
      {
        Send1Char(0x33); 
        Send1Char(0x44);
        return 0;
      }
        if(31>Temperature&&Temperature>29)
      { 
            if(data>=60)
                  
                  {
                     s=5;
                     flag1= revalue(-1002-data-s);
                     falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                     sysParam .sysParam_30.ConcentParam_60.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                     sysParam .sysParam_30.ConcentParam_60.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                     falsh_writeData();
                   }
             else if(data>=50&&data<60)
                   
                  { 
                        s=5;
                        flag1= revalue(-1002-data-s);
                        falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                        sysParam .sysParam_30.ConcentParam_50.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                        sysParam .sysParam_30.ConcentParam_50.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                        falsh_writeData();
                    }
              else if(data>=40&&data<50)
                        
                     {
                        s=5*sin(0.15*(data-30));
                        flag1= revalue(-1002-data-s); 
                        falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                        sysParam .sysParam_30.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                        sysParam .sysParam_30.ConcentParam_40.Value = (int)Flag2;
                        falsh_writeData();
                      }
              else if(data>=28&&data<40)
                     
                       {
                          s=5*sin(0.15*(data-30));
                          flag1= revalue(-1002-data-s); 
                          falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                          sysParam .sysParam_30.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                          sysParam .sysParam_30.ConcentParam_30.Value = (int)Flag2;
                          falsh_writeData();
                        }
               else if(data>=18&&data<28)
                     
                      {
                          s=5*sin(0.24*(data-17));
                          flag1= revalue(-1002-data+s);
                          falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                          sysParam .sysParam_30.ConcentParam_20.concentration = (int)(flag1*2.5);
                          sysParam .sysParam_30.ConcentParam_20.Value =(int)Flag2 ;
                          falsh_writeData();
                        }
                else if(data>8&&data<18)
                    {
                       s=5*sin(0.155*(data)); 
                       flag1= revalue(-1002-data-s);
                       falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                       sysParam .sysParam_30.ConcentParam_10.concentration =(int)(flag1*2.5);
                       sysParam .sysParam_30.ConcentParam_10.Value =(int) Flag2 ;
                       falsh_writeData();
                    }
                else
                {
                    s=5*sin(0.155*(data));
                    flag1= revalue(-1002-data-s);
                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                    sysParam .sysParam_30.ConcentParam_0.concentration =(int) (flag1*2.5);
                    sysParam .sysParam_30.ConcentParam_0.Value = (int)Flag2;
                    falsh_writeData();
                }
           }
                             else if(19<Temperature&&Temperature<21)
                               {
                                      if(data>=60)
                                            
                                            {
                                               s=5;
                                               flag1= revalue(-1002-data-s);
                                               falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                               sysParam .sysParam_20.ConcentParam_60.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                               sysParam .sysParam_20.ConcentParam_60.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                               falsh_writeData();
                                             }
                                       else if(data>=50&&data<60)
                                             
                                            { 
                                                  s=5;
                                                  flag1= revalue(-1002-data-s);
                                                  falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                  sysParam .sysParam_20.ConcentParam_50.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                  sysParam .sysParam_20.ConcentParam_50.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                  falsh_writeData();
                                              }
                                        else if(data>=40&&data<50)
                                                  
                                               {
                                                  s=5*sin(0.15*(data-30));
                                                  flag1= revalue(-1002-data-s); 
                                                  falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                  sysParam .sysParam_20.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                  sysParam .sysParam_20.ConcentParam_40.Value = (int)Flag2;
                                                  falsh_writeData();
                                                }
                                        else if(data>=28&&data<40)
                                               
                                                 {
                                                    s=5*sin(0.15*(data-30));
                                                    flag1= revalue(-1002-data-s); 
                                                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                    sysParam .sysParam_20.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                    sysParam .sysParam_20.ConcentParam_30.Value = (int)Flag2;
                                                    falsh_writeData();
                                                  }
                                         else if(data>=18&&data<28)
                                               
                                                {
                                                    s=5*sin(0.24*(data-17));
                                                    flag1= revalue(-1002-data+s);
                                                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                    sysParam .sysParam_20.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                    sysParam .sysParam_20.ConcentParam_20.Value =(int)Flag2 ;
                                                    falsh_writeData();
                                                                                          
                                                    
                                                    
                                                  }
                                          else if(data>8&&data<18)
                                              {
                                                 s=5*sin(0.155*(data)); 
                                                 flag1= revalue(-1002-data-s);
                                                 falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                 sysParam .sysParam_20.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                 sysParam .sysParam_20.ConcentParam_10.Value =(int) Flag2 ;
                                                 falsh_writeData();
                                              }
                                          else
                                          {
                                              s=5*sin(0.155*(data));
                                              flag1= revalue(-1002-data-s);
                                              falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                              sysParam .sysParam_20.ConcentParam_0.concentration =(int) (flag1*2.5);
                                              sysParam .sysParam_20.ConcentParam_0.Value = (int)Flag2;
                                              falsh_writeData();
                                          }
                               }
                                            else if(9<Temperature&&Temperature<11)
                                             {
                                                          if(data>=60)
                                                        
                                                        {
                                                           s=5;
                                                           flag1= revalue(-1002-data-s);
                                                           falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                           sysParam .sysParam_10.ConcentParam_60.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                           sysParam .sysParam_10.ConcentParam_60.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                           falsh_writeData();
                                                         }
                                                   else if(data>=50&&data<60)
                                                         
                                                        { 
                                                              s=5;
                                                              flag1= revalue(-1002-data-s);
                                                              falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                              sysParam .sysParam_10.ConcentParam_50.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                              sysParam .sysParam_10.ConcentParam_50.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                              falsh_writeData();
                                                          }
                                                    else if(data>=40&&data<50)
                                                              
                                                           {
                                                              s=5*sin(0.15*(data-30));
                                                              flag1= revalue(-1002-data-s); 
                                                              falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                              sysParam .sysParam_10.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                              sysParam .sysParam_10.ConcentParam_40.Value = (int)Flag2;
                                                              falsh_writeData();
                                                            }
                                                    else if(data>=28&&data<40)
                                                           
                                                             {
                                                                s=5*sin(0.15*(data-30));
                                                                flag1= revalue(-1002-data-s); 
                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                sysParam .sysParam_10.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                sysParam .sysParam_10.ConcentParam_30.Value = (int)Flag2;
                                                                falsh_writeData();
                                                              }
                                                     else if(data>=18&&data<28)
                                                           
                                                            {
                                                                s=5*sin(0.24*(data-17));
                                                                flag1= revalue(-1002-data+s);
                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                sysParam .sysParam_10.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                sysParam .sysParam_10.ConcentParam_20.Value =(int)Flag2 ;
                                                                falsh_writeData();
                                                              }
                                                      else if(data>8&&data<18)
                                                          {
                                                             s=5*sin(0.155*(data)); 
                                                             flag1= revalue(-1002-data-s);
                                                             falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                             sysParam .sysParam_10.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                             sysParam .sysParam_10.ConcentParam_10.Value =(int) Flag2 ;
                                                             falsh_writeData();
                                                          }
                                                      else
                                                      {
                                                          s=5*sin(0.155*(data));
                                                          flag1= revalue(-1002-data-s);
                                                          falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                          sysParam .sysParam_10.ConcentParam_0.concentration =(int) (flag1*2.5);
                                                          sysParam .sysParam_10.ConcentParam_0.Value = (int)Flag2;
                                                          falsh_writeData();
                                                      }
                                             }
                                                            else if(-1<Temperature&&Temperature<1)
                                                             {
                                                                       if(data>=60)
                                                                            
                                                                            {
                                                                               s=5;
                                                                               flag1= revalue(-1002-data-s);
                                                                               falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                               sysParam .sysParam_0.ConcentParam_60.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                               sysParam .sysParam_0.ConcentParam_60.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                               falsh_writeData();
                                                                             }
                                                                       else if(data>=50&&data<60)
                                                                             
                                                                            { 
                                                                                  s=5;
                                                                                  flag1= revalue(-1002-data-s);
                                                                                  falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                  sysParam .sysParam_0.ConcentParam_50.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                  sysParam .sysParam_0.ConcentParam_50.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                  falsh_writeData();
                                                                              }
                                                                        else if(data>=40&&data<50)
                                                                                  
                                                                               {
                                                                                  s=5*sin(0.15*(data-30));
                                                                                  flag1= revalue(-1002-data-s); 
                                                                                  falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                  sysParam .sysParam_0.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                                                  sysParam .sysParam_0.ConcentParam_40.Value = (int)Flag2;
                                                                                  falsh_writeData();
                                                                                }
                                                                        else if(data>=28&&data<40)
                                                                               
                                                                                 {
                                                                                    s=5*sin(0.15*(data-30));
                                                                                    flag1= revalue(-1002-data-s); 
                                                                                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                    sysParam .sysParam_0.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                                    sysParam .sysParam_0.ConcentParam_30.Value = (int)Flag2;
                                                                                    falsh_writeData();
                                                                                  }
                                                                         else if(data>=18&&data<28)
                                                                               
                                                                                {
                                                                                    s=5*sin(0.24*(data-17));
                                                                                    flag1= revalue(-1002-data+s);
                                                                                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                    sysParam .sysParam_0.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                                    sysParam .sysParam_0.ConcentParam_20.Value =(int)Flag2 ;
                                                                                    falsh_writeData();
                                                                                  }
                                                                          else if(data>8&&data<18)
                                                                              {
                                                                                 s=5*sin(0.155*(data)); 
                                                                                 flag1= revalue(-1002-data-s);
                                                                                 falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                 sysParam .sysParam_0.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                                                 sysParam .sysParam_0.ConcentParam_10.Value =(int) Flag2 ;
                                                                                 falsh_writeData();
                                                                              }
                                                                          else
                                                                          {
                                                                              s=5*sin(0.155*(data));
                                                                              flag1= revalue(-1002-data-s);
                                                                              falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                              sysParam .sysParam_0.ConcentParam_0.concentration =(int) (flag1*2.5);
                                                                              sysParam .sysParam_0.ConcentParam_0.Value = (int)Flag2;
                                                                              falsh_writeData();
                                                                          }
                                                             }
                                                                               else if(-11<Temperature&&Temperature<-9)
                                                                                 {
                                                                                                   if(data>=60)
                                                                                                        
                                                                                                        {
                                                                                                           s=5;
                                                                                                           flag1= revalue(-1002-data-s);
                                                                                                           falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                           sysParam .sysParam_l_10.ConcentParam_60.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                           sysParam .sysParam_l_10.ConcentParam_60.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                           falsh_writeData();
                                                                                                         }
                                                                                                   else if(data>=50&&data<60)
                                                                                                         
                                                                                                        { 
                                                                                                              s=5;
                                                                                                              flag1= revalue(-1002-data-s);
                                                                                                              falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                              sysParam .sysParam_l_10.ConcentParam_50.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                              sysParam .sysParam_l_10.ConcentParam_50.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                              falsh_writeData();
                                                                                                          }
                                                                                                    else if(data>=40&&data<50)
                                                                                                              
                                                                                                           {
                                                                                                              s=5*sin(0.15*(data-30));
                                                                                                              flag1= revalue(-1002-data-s); 
                                                                                                              falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                              sysParam .sysParam_l_10.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                                                                              sysParam .sysParam_l_10.ConcentParam_40.Value = (int)Flag2;
                                                                                                              falsh_writeData();
                                                                                                            }
                                                                                                    else if(data>=28&&data<40)
                                                                                                           
                                                                                                             {
                                                                                                                s=5*sin(0.15*(data-30));
                                                                                                                flag1= revalue(-1002-data-s); 
                                                                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                sysParam .sysParam_l_10.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                                                                sysParam .sysParam_l_10.ConcentParam_30.Value = (int)Flag2;
                                                                                                                falsh_writeData();
                                                                                                              }
                                                                                                     else if(data>=18&&data<28)
                                                                                                           
                                                                                                            {
                                                                                                                s=5*sin(0.24*(data-17));
                                                                                                                flag1= revalue(-1002-data+s);
                                                                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                sysParam .sysParam_l_10.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                                                                sysParam .sysParam_l_10.ConcentParam_20.Value =(int)Flag2 ;
                                                                                                                falsh_writeData();
                                                                                                              }
                                                                                                      else if(data>8&&data<18)
                                                                                                          {
                                                                                                             s=5*sin(0.155*(data)); 
                                                                                                             flag1= revalue(-1002-data-s);
                                                                                                             falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                             sysParam .sysParam_l_10.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                                                                             sysParam .sysParam_l_10.ConcentParam_10.Value =(int) Flag2 ;
                                                                                                             falsh_writeData();
                                                                                                          }
                                                                                                      else
                                                                                                      {
                                                                                                          s=5*sin(0.155*(data));
                                                                                                          flag1= revalue(-1002-data-s);
                                                                                                          falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                          sysParam .sysParam_l_10.ConcentParam_0.concentration =(int) (flag1*2.5);
                                                                                                          sysParam .sysParam_l_10.ConcentParam_0.Value = (int)Flag2;
                                                                                                          falsh_writeData();
                                                                                                      }
                                                                                 }
                                                                                               else if(-21<Temperature&&Temperature<-19)
                                                                                                 {
                                                                                                         if(data>=60)
                                                                                                              
                                                                                                              {
                                                                                                                 s=5;
                                                                                                                 flag1= revalue(-1002-data-s);
                                                                                                                 falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                 sysParam .sysParam_l_20.ConcentParam_60.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                                 sysParam .sysParam_l_20.ConcentParam_60.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                                 falsh_writeData();
                                                                                                               }
                                                                                                         else if(data>=50&&data<60)
                                                                                                               
                                                                                                              { 
                                                                                                                    s=5;
                                                                                                                    flag1= revalue(-1002-data-s);
                                                                                                                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_50.concentration =(int) (flag1*2.5) ;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_50.Value =(int) Flag2;//����Ҫ�궨��Ƶ��ֵ��ʵ��Ƶ��ֵ����
                                                                                                                    falsh_writeData();
                                                                                                                }
                                                                                                          else if(data>=40&&data<50)
                                                                                                                    
                                                                                                                 {
                                                                                                                    s=5*sin(0.15*(data-30));
                                                                                                                    flag1= revalue(-1002-data-s); 
                                                                                                                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_40.Value = (int)Flag2;
                                                                                                                    falsh_writeData();
                                                                                                                  }
                                                                                                          else if(data>=28&&data<40)
                                                                                                                 
                                                                                                                   {
                                                                                                                      s=5*sin(0.15*(data-30));
                                                                                                                      flag1= revalue(-1002-data-s); 
                                                                                                                      falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_30.Value = (int)Flag2;
                                                                                                                      falsh_writeData();
                                                                                                                    }
                                                                                                           else if(data>=18&&data<28)
                                                                                                                 
                                                                                                                  {
                                                                                                                      s=5*sin(0.24*(data-17));
                                                                                                                      flag1= revalue(-1002-data+s);
                                                                                                                      falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_20.Value =(int)Flag2 ;
                                                                                                                      falsh_writeData();
                                                                                                                    }
                                                                                                            else if(data>8&&data<18)
                                                                                                                {
                                                                                                                   s=5*sin(0.155*(data)); 
                                                                                                                   flag1= revalue(-1002-data-s);
                                                                                                                   falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                   sysParam .sysParam_l_20.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                                                                                   sysParam .sysParam_l_20.ConcentParam_10.Value =(int) Flag2 ;
                                                                                                                   falsh_writeData();
                                                                                                                }
                                                                                                            else
                                                                                                            {
                                                                                                                s=5*sin(0.155*(data));
                                                                                                                flag1= revalue(-1002-data-s);
                                                                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                                                                sysParam .sysParam_l_20.ConcentParam_0.concentration =(int) (flag1*2.5);
                                                                                                                sysParam .sysParam_l_20.ConcentParam_0.Value = (int)Flag2;
                                                                                                                falsh_writeData();
                                                                                                            }
                                                                                                 }
      }
     
       else if(n==254)  //У׼��������  10¶��
      {
         if(Temperature>31||(21<Temperature&&Temperature<29)||(11<Temperature&&Temperature<19)||(1<Temperature&&Temperature<9)||(-9<Temperature&&Temperature<-1)||(-19<Temperature&&Temperature<-11)||Temperature<-21)//�жϵ�ǰ�¶��Ƿ���Ա궨������������궨�����򷵻�
      {
        Send1Char(0x33); 
      Send1Char(0x44);
       return 0;
      }
          if(31>Temperature&&Temperature>29)
          {  
      
           if(data>5&&data<15) 
              {
                    s=0;
                    flag1= 2059-31*data;
                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                    sysParam .sysParam_30.ConcentParam_h.concentration =(int)(flag1*2.5);
	            sysParam .sysParam_30.ConcentParam_h.Value = (int) Flag2;
                    falsh_writeData();
      
      
                } 
                  else//У׼��������  20¶��
                {
                    s=0;
                    flag1= 2059-31*data;
                    falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                    sysParam .sysParam_30.ConcentParam_h20.concentration =(int)(flag1*2.5);
	            sysParam .sysParam_30.ConcentParam_h20.Value = (int) Flag2;
                    falsh_writeData();
                 }
               }
                     else if(19<Temperature&&Temperature<21)
                         {
                               if(data>5&&data<15) 
                                    {
                                          s=0;
                                          flag1= 2059-31*data;
                                          falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                          sysParam .sysParam_20.ConcentParam_h.concentration =(int)(flag1*2.5);
                                         sysParam .sysParam_20.ConcentParam_h.Value = (int) Flag2;
     /*  high=sysParam .sysParam_20.ConcentParam_h.concentration>>8;
      low=sysParam .sysParam_20.ConcentParam_h.concentration&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x0a); 
      Send1Char(0x0a);  //485�������ǵ�Ƶ����Ϣ
     RE;
             high=sysParam .sysParam_20.ConcentParam_h.Value>>8;
      low=sysParam .sysParam_20.ConcentParam_h.Value&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x0a); 
      Send1Char(0x0a);  //485�������ǵ�Ƶ����Ϣ
     RE;                              
           */                               
                                          falsh_writeData();
                            
                            
                                      } 
                                 else//У׼��������  20¶��
                                      {
                                          s=0;
                                          flag1= 2059-31*data;
                                          falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                          sysParam .sysParam_20.ConcentParam_h20.concentration =(int)(flag1*2.5);
                                          sysParam .sysParam_20.ConcentParam_h20.Value = (int) Flag2;
                                          falsh_writeData();
                                       }
                         }
                         else if(9<Temperature&&Temperature<11)
                                {
                                       if(data>5&&data<15) 
                                          {
                                                s=0;
                                                flag1= 2059-31*data;
                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                sysParam .sysParam_10.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                sysParam .sysParam_10.ConcentParam_h.Value = (int) Flag2;
                                                falsh_writeData();
                                  
                                  
                                            } 
                                         else//У׼��������  20¶��
                                            {
                                                s=0;
                                                flag1= 2059-31*data;
                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                sysParam .sysParam_10.ConcentParam_h20.concentration =(int)(flag1*2.5);
                                                sysParam .sysParam_10.ConcentParam_h20.Value = (int) Flag2;
                                                falsh_writeData();
                                             }
                                   }
                                  else if(-1<Temperature&&Temperature<1)
                                         {
                                                 if(data>5&&data<15) 
                                                  {
                                                        s=0;
                                                        flag1= 2059-31*data;
                                                        falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                        sysParam .sysParam_0.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                        sysParam .sysParam_0.ConcentParam_h.Value = (int) Flag2;
                                                        falsh_writeData();
                                          
                                          
                                                    } 
                                                      else//У׼��������  20¶��
                                                    {
                                                        s=0;
                                                        flag1= 2059-31*data;
                                                        falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                        sysParam .sysParam_0.ConcentParam_h20.concentration =(int)(flag1*2.5);
                                                        sysParam .sysParam_0.ConcentParam_h20.Value = (int) Flag2;
                                                        falsh_writeData();
                                                     }
                                            }
                                          else if(-11<Temperature&&Temperature<-9)
                                                {
                                                             if(data>5&&data<15) 
                                                          {
                                                                s=0;
                                                                flag1= 2059-31*data;
                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                sysParam .sysParam_l_10.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_10.ConcentParam_h.Value = (int) Flag2;
                                                                falsh_writeData();
                                                  
                                                  
                                                            } 
                                                              else//У׼��������  20¶��
                                                            {
                                                                s=0;
                                                                flag1= 2059-31*data;
                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                sysParam .sysParam_l_10.ConcentParam_h20.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_10.ConcentParam_h20.Value = (int) Flag2;
                                                                falsh_writeData();
                                                             }
                                                  }
                                                  else if(-21<Temperature&&Temperature<-19)
                                                       {
                                                          if(data>5&&data<15) 
                                                          {
                                                                s=0;
                                                                flag1= 2059-31*data;
                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                sysParam .sysParam_l_20.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_20.ConcentParam_h.Value = (int) Flag2;
                                                                falsh_writeData();
                                                  
                                                  
                                                            } 
                                                              else//У׼��������  20¶��
                                                            {
                                                                s=0;
                                                                flag1= 2059-31*data;
                                                                falsh_readData();              //���ȶ���һ����д�룬��ֹ����д��ʧ��
                                                                sysParam .sysParam_l_20.ConcentParam_h20.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_20.ConcentParam_h20.Value = (int) Flag2;
                                                                falsh_writeData();
                                                             }
                                                         }
              }  
      
       else if(n==253)  //У׼�¶�
       {
         if(data>Temperature)
         {
          sysParam .temperature_void+=  ((data-Temperature)+1);
         falsh_writeData();
         }
         else
         {
         sysParam .temperature_void-= ((Temperature-data)-1);
         falsh_writeData();
         }
       
       
       
       }
      else
      {
       
         Send1Char(0x00); 
         Send1Char(0x00); 
         Send1Char(0x00); 
         Send1Char(0x00); 
        
      }
      
       
           return 0;
}
double change_data_ppm(double x)
{

return 0;//�ı�����ʱ�ĺ���
}



double Sensor_Info(double *x)
{
    double arr[6]={0};
     double j=0,dp;
    extern double Dp;
    double s=0;
  
            for(int i=0;i<6;i++)//����ȡ����ֵ��ֵ��������
            {
                j= x[i]/2.5;
                     if(j>=3542)//-40~-80
                          {
                           s=5*sin(1.5717);
                           dp =-( (0.00000005003*j*j*j-0.0004086*j*j+1.115*j-1002)-s);
                          
                          }
                         else if(j>=3442&&j<3542)//-40~-30
                         {
                           
                           s=5*sin(0.0157*(j-200));
                           dp =-( (0.00000005003*j*j*j-0.0004086*j*j+1.115*j-1002)-s);
                           
                         }
                         else if(j>=2850&&j<3442)//-30~-20  3125
                         {
                           
                          s=5*sin(0.005395*(j-530));
                          dp =-( (0.00000005003*j*j*j-0.0004086*j*j+1.115*j-1002)+s);
                          
                         }
                         else if(j>=2059&&j<2850)//-20~0
                         {
                           
                           s=5*sin(0.00397*(j-478));
                           dp =-( (0.00000005003*j*j*j-0.0004086*j*j+1.115*j-1002)-s);
                           
                         }
                         else//0~20
                         {
                           
                          dp =((2059-j)/31);
                              // Dp =9;
                         }
                      arr[i]=dp;          
                 
            }
                 
           if(Temperature>=28)      //�ж�������ݴ����Ƕ�,����¶ȴ��������趨����ֵ֮�䣬��ʹ���������ߵ���ֵ���м������ƽ��ֵ
           {                         //��������Ҫ�ı����Ϊ����ģʽ���ڴ˴��޸����������ʽת�����
                
                Dp=arr[0];
           }
           else if(23<Temperature&&Temperature<28)
           { 
                Dp=(arr[0]+arr[1])/2;      
           }
           else if(18<=Temperature&&Temperature<=23)
           {
                Dp=arr[1];  
           }
           else if(13<Temperature&&Temperature<18)
           {
                 Dp=(arr[1]+arr[2])/2;
           }
           else if(8<=Temperature&&Temperature<=13)
           {
                 Dp=arr[2]; 
           }
           else if(3<Temperature&&Temperature<8)
           {
                  Dp=(arr[2]+arr[3])/2;
           }
           else if(-2<=Temperature&&Temperature<=3)
           {
                  Dp=arr[3];
           }
           else if(-7<Temperature&&Temperature<-2)
           {
                  Dp=(arr[3]+arr[4])/2;
           }
            else if(-12<=Temperature&&Temperature<=-7)
            {
                  Dp=arr[4]; 
            } 
            else if(-17<Temperature&&Temperature<-12)  
            {
                 Dp=(arr[4]+arr[5])/2;
            }
            else if(Temperature<=-17)
            {
                 Dp=arr[5];
            }
                 
                 
                 
                 
                 
      //  Dp= change_data_ppm(Dp);        �����޸��������
                 
                 
                 
                 
                 
                 
       /*�������-80��һֱ��ʾ-80*/
       if(Dp<=-80)
       {
          Dp=-80;
       }
       else if(Dp>=20)
      {
          Dp=20;
       
       }
         
 
   DAC12_0DAT=(int)((Dp+111.25)*21.63);              //����д��Ĵ�����д�뼤��DACת��        
   //   DAC12_0DAT=(int)((Dp+100.0)*34.1);    
    //  _BIS_SR(LPM1_bits + GIE);
  // __low_power_mode_off_on_exit();

 return 0;

}


















