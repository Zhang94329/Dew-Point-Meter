
/*---------------------------------------------------------------- 
 * 文件名：sensor_data.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          数据的处理标定及返回输出
 *     
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/
#include"sensor_data.h"
#include <msp430x16x.h>
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "flash.h"
#include "RS485.h"
#include "adc12.h"
extern double flag1;
extern double Flag2;                  //频率保存标志量
extern float Temperature;
extern uchar high;
extern uchar low;
//*******************************************************************
//	过渡验算函数
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
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_30.ConcentParam_40.Value&&x<sysParam.sysParam_30.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_30.ConcentParam_40.Value, y1 = sysParam.sysParam_30.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_50.Value, y2 = sysParam.sysParam_30.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_30.ConcentParam_30.Value&&x<sysParam.sysParam_30.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_30.ConcentParam_30.Value, y1 = sysParam.sysParam_30.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_40.Value, y2 = sysParam.sysParam_30.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_30.ConcentParam_20.Value&&x<sysParam.sysParam_30.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_30.ConcentParam_20.Value, y1 = sysParam.sysParam_30.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_30.Value, y2 = sysParam.sysParam_30.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_30.ConcentParam_10.Value&&x<sysParam.sysParam_30.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_30.ConcentParam_10.Value, y1 = sysParam.sysParam_30.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_20.Value, y2 = sysParam.sysParam_30.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_30.ConcentParam_0.Value&&x<sysParam.sysParam_30.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_30.ConcentParam_0.Value, y1 = sysParam.sysParam_30.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_10.Value, y2 = sysParam.sysParam_30.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_30.ConcentParam_h.Value&&x<sysParam.sysParam_30.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_30.ConcentParam_h.Value, y1 = sysParam.sysParam_30.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_30.ConcentParam_0.Value, y2 = sysParam.sysParam_30.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_30.ConcentParam_h20.Value&&x<sysParam.sysParam_30.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_30.ConcentParam_h20.Value, y1 = sysParam.sysParam_30.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_30.ConcentParam_h.Value, y2 = sysParam.sysParam_30.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
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
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_20.ConcentParam_40.Value&&x<sysParam.sysParam_20.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_20.ConcentParam_40.Value, y1 = sysParam.sysParam_20.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_50.Value, y2 = sysParam.sysParam_20.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_20.ConcentParam_30.Value&&x<sysParam.sysParam_20.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_20.ConcentParam_30.Value, y1 = sysParam.sysParam_20.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_40.Value, y2 = sysParam.sysParam_20.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_20.ConcentParam_20.Value&&x<sysParam.sysParam_20.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_20.ConcentParam_20.Value, y1 = sysParam.sysParam_20.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_30.Value, y2 = sysParam.sysParam_20.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_20.ConcentParam_10.Value&&x<sysParam.sysParam_20.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_20.ConcentParam_10.Value, y1 = sysParam.sysParam_20.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_20.Value, y2 = sysParam.sysParam_20.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_20.ConcentParam_0.Value&&x<sysParam.sysParam_20.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_20.ConcentParam_0.Value, y1 = sysParam.sysParam_20.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_10.Value, y2 = sysParam.sysParam_20.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_20.ConcentParam_h.Value&&x<sysParam.sysParam_20.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_20.ConcentParam_h.Value, y1 = sysParam.sysParam_20.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_20.ConcentParam_0.Value, y2 = sysParam.sysParam_20.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_20.ConcentParam_h20.Value&&x<sysParam.sysParam_20.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_20.ConcentParam_h20.Value, y1 = sysParam.sysParam_20.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_20.ConcentParam_h.Value, y2 = sysParam.sysParam_20.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
               arr[a]=truevalue;
               /* high=(long)arr[a]>>8;
      low=(long)arr[a]&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x0b); 
      Send1Char(0x0b);  //485发送我们的频率信息
     RE;*/
              }
              else if(a==2)
              {
                if(x>=sysParam.sysParam_10.ConcentParam_50.Value)
             {
             
                                double x1 = sysParam.sysParam_10.ConcentParam_50.Value, y1 = sysParam.sysParam_10.ConcentParam_50.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_60.Value, y2 = sysParam.sysParam_10.ConcentParam_60.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_10.ConcentParam_40.Value&&x<sysParam.sysParam_10.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_10.ConcentParam_40.Value, y1 = sysParam.sysParam_10.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_50.Value, y2 = sysParam.sysParam_10.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_10.ConcentParam_30.Value&&x<sysParam.sysParam_10.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_10.ConcentParam_30.Value, y1 = sysParam.sysParam_10.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_40.Value, y2 = sysParam.sysParam_10.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_10.ConcentParam_20.Value&&x<sysParam.sysParam_10.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_10.ConcentParam_20.Value, y1 = sysParam.sysParam_10.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_30.Value, y2 = sysParam.sysParam_10.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_10.ConcentParam_10.Value&&x<sysParam.sysParam_10.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_10.ConcentParam_10.Value, y1 = sysParam.sysParam_10.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_20.Value, y2 = sysParam.sysParam_10.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_10.ConcentParam_0.Value&&x<sysParam.sysParam_10.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_10.ConcentParam_0.Value, y1 = sysParam.sysParam_10.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_10.Value, y2 = sysParam.sysParam_10.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_10.ConcentParam_h.Value&&x<sysParam.sysParam_10.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_10.ConcentParam_h.Value, y1 = sysParam.sysParam_10.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_10.ConcentParam_0.Value, y2 = sysParam.sysParam_10.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_10.ConcentParam_h20.Value&&x<sysParam.sysParam_10.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_10.ConcentParam_h20.Value, y1 = sysParam.sysParam_10.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_10.ConcentParam_h.Value, y2 = sysParam.sysParam_10.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
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
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_0.ConcentParam_40.Value&&x<sysParam.sysParam_0.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_0.ConcentParam_40.Value, y1 = sysParam.sysParam_0.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_50.Value, y2 = sysParam.sysParam_0.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_0.ConcentParam_30.Value&&x<sysParam.sysParam_0.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_0.ConcentParam_30.Value, y1 = sysParam.sysParam_0.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_40.Value, y2 = sysParam.sysParam_0.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_0.ConcentParam_20.Value&&x<sysParam.sysParam_0.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_0.ConcentParam_20.Value, y1 = sysParam.sysParam_0.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_30.Value, y2 = sysParam.sysParam_0.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_0.ConcentParam_10.Value&&x<sysParam.sysParam_0.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_0.ConcentParam_10.Value, y1 = sysParam.sysParam_0.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_20.Value, y2 = sysParam.sysParam_0.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_0.ConcentParam_0.Value&&x<sysParam.sysParam_0.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_0.ConcentParam_0.Value, y1 = sysParam.sysParam_0.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_10.Value, y2 = sysParam.sysParam_0.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_0.ConcentParam_h.Value&&x<sysParam.sysParam_0.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_0.ConcentParam_h.Value, y1 = sysParam.sysParam_0.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_0.ConcentParam_0.Value, y2 = sysParam.sysParam_0.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_0.ConcentParam_h20.Value&&x<sysParam.sysParam_0.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_0.ConcentParam_h20.Value, y1 = sysParam.sysParam_0.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_0.ConcentParam_h.Value, y2 = sysParam.sysParam_0.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
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
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                   
                   }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_40.Value&&x<sysParam.sysParam_l_10.ConcentParam_50.Value)
                 {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_40.Value, y1 = sysParam.sysParam_l_10.ConcentParam_40.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_50.Value, y2 = sysParam.sysParam_l_10.ConcentParam_50.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                 }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_30.Value&&x<sysParam.sysParam_l_10.ConcentParam_40.Value)
                 {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_30.Value, y1 = sysParam.sysParam_l_10.ConcentParam_30.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_40.Value, y2 = sysParam.sysParam_l_10.ConcentParam_40.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                       
                 }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_20.Value&&x<sysParam.sysParam_l_10.ConcentParam_30.Value)
                 {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_20.Value, y1 = sysParam.sysParam_l_10.ConcentParam_20.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_30.Value, y2 = sysParam.sysParam_l_10.ConcentParam_30.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                 }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_10.Value&&x<sysParam.sysParam_l_10.ConcentParam_20.Value)
                   {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_10.Value, y1 = sysParam.sysParam_l_10.ConcentParam_10.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_20.Value, y2 = sysParam.sysParam_l_10.ConcentParam_20.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                   }
                 else if(x>=sysParam.sysParam_l_10.ConcentParam_0.Value&&x<sysParam.sysParam_l_10.ConcentParam_10.Value)
                     {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_0.Value, y1 = sysParam.sysParam_l_10.ConcentParam_0.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_10.Value, y2 = sysParam.sysParam_l_10.ConcentParam_10.concentration;
                                      
                                      truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                     
                     }
                  else if(x>=sysParam.sysParam_l_10.ConcentParam_h.Value&&x<sysParam.sysParam_l_10.ConcentParam_0.Value)
                     {
                                      double x1 = sysParam.sysParam_l_10.ConcentParam_h.Value, y1 = sysParam.sysParam_l_10.ConcentParam_h.concentration;
                                      double x2 = sysParam.sysParam_l_10.ConcentParam_0.Value, y2 = sysParam.sysParam_l_10.ConcentParam_0.concentration;
                                      
                                      truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
                                      truevalue = (truevalue< 0)?0:truevalue;
                                      
                                      
                     
                     } 
                else if(x>=sysParam.sysParam_l_10.ConcentParam_h20.Value&&x<sysParam.sysParam_l_10.ConcentParam_h.Value)
                     {
                                     
                                       double x1 = sysParam.sysParam_l_10.ConcentParam_h20.Value, y1 = sysParam.sysParam_l_10.ConcentParam_h20.concentration;
                                       double x2 = sysParam.sysParam_l_10.ConcentParam_h.Value, y2 = sysParam.sysParam_l_10.ConcentParam_h.concentration;
                                       
                                      truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
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
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
             
             }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_40.Value&&x<sysParam.sysParam_l_20.ConcentParam_50.Value)
           {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_40.Value, y1 = sysParam.sysParam_l_20.ConcentParam_40.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_50.Value, y2 = sysParam.sysParam_l_20.ConcentParam_50.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_30.Value&&x<sysParam.sysParam_l_20.ConcentParam_40.Value)
           {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_30.Value, y1 = sysParam.sysParam_l_20.ConcentParam_30.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_40.Value, y2 = sysParam.sysParam_l_20.ConcentParam_40.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				 
           }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_20.Value&&x<sysParam.sysParam_l_20.ConcentParam_30.Value)
           {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_20.Value, y1 = sysParam.sysParam_l_20.ConcentParam_20.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_30.Value, y2 = sysParam.sysParam_l_20.ConcentParam_30.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
           }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_10.Value&&x<sysParam.sysParam_l_20.ConcentParam_20.Value)
             {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_10.Value, y1 = sysParam.sysParam_l_20.ConcentParam_10.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_20.Value, y2 = sysParam.sysParam_l_20.ConcentParam_20.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));  //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
             }
           else if(x>=sysParam.sysParam_l_20.ConcentParam_0.Value&&x<sysParam.sysParam_l_20.ConcentParam_10.Value)
               {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_0.Value, y1 = sysParam.sysParam_l_20.ConcentParam_0.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_10.Value, y2 = sysParam.sysParam_l_20.ConcentParam_10.concentration;
				
				truevalue = (((y2 - y1) * (x-x1)/(x2 - x1) + y1));    //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               }
            else if(x>=sysParam.sysParam_l_20.ConcentParam_h.Value&&x<sysParam.sysParam_l_20.ConcentParam_0.Value)
               {
                                double x1 = sysParam.sysParam_l_20.ConcentParam_h.Value, y1 = sysParam.sysParam_l_20.ConcentParam_h.concentration;
				double x2 = sysParam.sysParam_l_20.ConcentParam_0.Value, y2 = sysParam.sysParam_l_20.ConcentParam_0.concentration;
				
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
          else if(x>=sysParam.sysParam_l_20.ConcentParam_h20.Value&&x<sysParam.sysParam_l_20.ConcentParam_h.Value)
               {
                               
				 double x1 = sysParam.sysParam_l_20.ConcentParam_h20.Value, y1 = sysParam.sysParam_l_20.ConcentParam_h20.concentration;
				 double x2 = sysParam.sysParam_l_20.ConcentParam_h.Value, y2 = sysParam.sysParam_l_20.ConcentParam_h.concentration;
                                 
				truevalue = ((y2 - y1) * x/(x2 - x1) + (y1*x2 - y2*x1)/(x2-x1));   //计算所需要的频率值
				truevalue = (truevalue< 0)?0:truevalue;
				
				
               
               } 
               arr[a]=truevalue;
              }
              
         
         }
         
    
 return 0;
  }

/*******************************************************************
			返回值计算
* 名    称： revalue
* 功    能：返回计算值频率
* 入口参数：露点值 
* 出口参数：计算后的频率值
* 说    明: 
********************************************************************/




   double revalue(double x)
   {
            double m=100,n=4000;
            double i,sum;
            double eps=0.001;//1e-6;//eps是精度控制，此处为10^-6，表示无限小
            double  a=0.00000005003,b=-0.0004086,c=1.115,d=x; //a=0.00000005003,b=-0.0004086,c=1.115,d=x;
            double f1,f2;
            f1=a*pow(m,3)+b*pow(m,2)+c*m+d;//pow(x,y)=x^y，幂函数
            f2=a*pow(n,3)+b*pow(n,2)+c*n+d;
            //判断f1*f2<0是主要代码
                if(f1*f2<0)
                    {
                        while(fabs(m-n)>eps)
                        {
                            i=(m+n)/2;
                            sum=a*pow(i,3)+b*pow(i,2)+c*i+d;
                                  if(fabs(sum)<eps)//如果函数f(i)的绝对值|sum|小于无限小
                                    {
                                       // printf("方程的一个近似解为x*=%lf\n",i);
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
                  //如果刚好区间取值为方程解
                  else if(f1*f2==0)
                  {
                      if(f1==0)
                      {// printf("方程的一个解为x*=%lf\n",m);
                      }
                      if(f2==0)
                      {//printf("方程的一个解为x*=%lf\n",n);
                      }
                  }          
                    else
                    {// printf("方程在该区间内无解！\n");
                    }
         
   return i;
   
   }


/*******************************************************************
			校准数据处理函数
               
********************************************************************/
  extern uchar high;
extern uchar low;
  
double get_data_count(double data,int n )
{
   
      double s;
      if(n==255)   //校准负数部分
      {
         if(Temperature>31||(21<Temperature&&Temperature<29)||(11<Temperature&&Temperature<19)||(1<Temperature&&Temperature<9)||(-9<Temperature&&Temperature<-1)||(-19<Temperature&&Temperature<-11)||Temperature<-21)//判断当前温度是否可以标定，若不能满足标定条件则返回
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
                     falsh_readData();              //首先读出一次在写入，防止数据写入失败
                     sysParam .sysParam_30.ConcentParam_60.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                     sysParam .sysParam_30.ConcentParam_60.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                     falsh_writeData();
                   }
             else if(data>=50&&data<60)
                   
                  { 
                        s=5;
                        flag1= revalue(-1002-data-s);
                        falsh_readData();              //首先读出一次在写入，防止数据写入失败
                        sysParam .sysParam_30.ConcentParam_50.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                        sysParam .sysParam_30.ConcentParam_50.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                        falsh_writeData();
                    }
              else if(data>=40&&data<50)
                        
                     {
                        s=5*sin(0.15*(data-30));
                        flag1= revalue(-1002-data-s); 
                        falsh_readData();              //首先读出一次在写入，防止数据写入失败
                        sysParam .sysParam_30.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                        sysParam .sysParam_30.ConcentParam_40.Value = (int)Flag2;
                        falsh_writeData();
                      }
              else if(data>=28&&data<40)
                     
                       {
                          s=5*sin(0.15*(data-30));
                          flag1= revalue(-1002-data-s); 
                          falsh_readData();              //首先读出一次在写入，防止数据写入失败
                          sysParam .sysParam_30.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                          sysParam .sysParam_30.ConcentParam_30.Value = (int)Flag2;
                          falsh_writeData();
                        }
               else if(data>=18&&data<28)
                     
                      {
                          s=5*sin(0.24*(data-17));
                          flag1= revalue(-1002-data+s);
                          falsh_readData();              //首先读出一次在写入，防止数据写入失败
                          sysParam .sysParam_30.ConcentParam_20.concentration = (int)(flag1*2.5);
                          sysParam .sysParam_30.ConcentParam_20.Value =(int)Flag2 ;
                          falsh_writeData();
                        }
                else if(data>8&&data<18)
                    {
                       s=5*sin(0.155*(data)); 
                       flag1= revalue(-1002-data-s);
                       falsh_readData();              //首先读出一次在写入，防止数据写入失败
                       sysParam .sysParam_30.ConcentParam_10.concentration =(int)(flag1*2.5);
                       sysParam .sysParam_30.ConcentParam_10.Value =(int) Flag2 ;
                       falsh_writeData();
                    }
                else
                {
                    s=5*sin(0.155*(data));
                    flag1= revalue(-1002-data-s);
                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                               falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                               sysParam .sysParam_20.ConcentParam_60.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                               sysParam .sysParam_20.ConcentParam_60.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                               falsh_writeData();
                                             }
                                       else if(data>=50&&data<60)
                                             
                                            { 
                                                  s=5;
                                                  flag1= revalue(-1002-data-s);
                                                  falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                  sysParam .sysParam_20.ConcentParam_50.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                  sysParam .sysParam_20.ConcentParam_50.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                  falsh_writeData();
                                              }
                                        else if(data>=40&&data<50)
                                                  
                                               {
                                                  s=5*sin(0.15*(data-30));
                                                  flag1= revalue(-1002-data-s); 
                                                  falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                  sysParam .sysParam_20.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                  sysParam .sysParam_20.ConcentParam_40.Value = (int)Flag2;
                                                  falsh_writeData();
                                                }
                                        else if(data>=28&&data<40)
                                               
                                                 {
                                                    s=5*sin(0.15*(data-30));
                                                    flag1= revalue(-1002-data-s); 
                                                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                    sysParam .sysParam_20.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                    sysParam .sysParam_20.ConcentParam_30.Value = (int)Flag2;
                                                    falsh_writeData();
                                                  }
                                         else if(data>=18&&data<28)
                                               
                                                {
                                                    s=5*sin(0.24*(data-17));
                                                    flag1= revalue(-1002-data+s);
                                                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                    sysParam .sysParam_20.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                    sysParam .sysParam_20.ConcentParam_20.Value =(int)Flag2 ;
                                                    falsh_writeData();
                                                                                          
                                                    
                                                    
                                                  }
                                          else if(data>8&&data<18)
                                              {
                                                 s=5*sin(0.155*(data)); 
                                                 flag1= revalue(-1002-data-s);
                                                 falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                 sysParam .sysParam_20.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                 sysParam .sysParam_20.ConcentParam_10.Value =(int) Flag2 ;
                                                 falsh_writeData();
                                              }
                                          else
                                          {
                                              s=5*sin(0.155*(data));
                                              flag1= revalue(-1002-data-s);
                                              falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                           falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                           sysParam .sysParam_10.ConcentParam_60.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                           sysParam .sysParam_10.ConcentParam_60.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                           falsh_writeData();
                                                         }
                                                   else if(data>=50&&data<60)
                                                         
                                                        { 
                                                              s=5;
                                                              flag1= revalue(-1002-data-s);
                                                              falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                              sysParam .sysParam_10.ConcentParam_50.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                              sysParam .sysParam_10.ConcentParam_50.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                              falsh_writeData();
                                                          }
                                                    else if(data>=40&&data<50)
                                                              
                                                           {
                                                              s=5*sin(0.15*(data-30));
                                                              flag1= revalue(-1002-data-s); 
                                                              falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                              sysParam .sysParam_10.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                              sysParam .sysParam_10.ConcentParam_40.Value = (int)Flag2;
                                                              falsh_writeData();
                                                            }
                                                    else if(data>=28&&data<40)
                                                           
                                                             {
                                                                s=5*sin(0.15*(data-30));
                                                                flag1= revalue(-1002-data-s); 
                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                sysParam .sysParam_10.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                sysParam .sysParam_10.ConcentParam_30.Value = (int)Flag2;
                                                                falsh_writeData();
                                                              }
                                                     else if(data>=18&&data<28)
                                                           
                                                            {
                                                                s=5*sin(0.24*(data-17));
                                                                flag1= revalue(-1002-data+s);
                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                sysParam .sysParam_10.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                sysParam .sysParam_10.ConcentParam_20.Value =(int)Flag2 ;
                                                                falsh_writeData();
                                                              }
                                                      else if(data>8&&data<18)
                                                          {
                                                             s=5*sin(0.155*(data)); 
                                                             flag1= revalue(-1002-data-s);
                                                             falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                             sysParam .sysParam_10.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                             sysParam .sysParam_10.ConcentParam_10.Value =(int) Flag2 ;
                                                             falsh_writeData();
                                                          }
                                                      else
                                                      {
                                                          s=5*sin(0.155*(data));
                                                          flag1= revalue(-1002-data-s);
                                                          falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                                               falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                               sysParam .sysParam_0.ConcentParam_60.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                                               sysParam .sysParam_0.ConcentParam_60.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                                               falsh_writeData();
                                                                             }
                                                                       else if(data>=50&&data<60)
                                                                             
                                                                            { 
                                                                                  s=5;
                                                                                  flag1= revalue(-1002-data-s);
                                                                                  falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                  sysParam .sysParam_0.ConcentParam_50.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                                                  sysParam .sysParam_0.ConcentParam_50.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                                                  falsh_writeData();
                                                                              }
                                                                        else if(data>=40&&data<50)
                                                                                  
                                                                               {
                                                                                  s=5*sin(0.15*(data-30));
                                                                                  flag1= revalue(-1002-data-s); 
                                                                                  falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                  sysParam .sysParam_0.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                                                  sysParam .sysParam_0.ConcentParam_40.Value = (int)Flag2;
                                                                                  falsh_writeData();
                                                                                }
                                                                        else if(data>=28&&data<40)
                                                                               
                                                                                 {
                                                                                    s=5*sin(0.15*(data-30));
                                                                                    flag1= revalue(-1002-data-s); 
                                                                                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                    sysParam .sysParam_0.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                                    sysParam .sysParam_0.ConcentParam_30.Value = (int)Flag2;
                                                                                    falsh_writeData();
                                                                                  }
                                                                         else if(data>=18&&data<28)
                                                                               
                                                                                {
                                                                                    s=5*sin(0.24*(data-17));
                                                                                    flag1= revalue(-1002-data+s);
                                                                                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                    sysParam .sysParam_0.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                                    sysParam .sysParam_0.ConcentParam_20.Value =(int)Flag2 ;
                                                                                    falsh_writeData();
                                                                                  }
                                                                          else if(data>8&&data<18)
                                                                              {
                                                                                 s=5*sin(0.155*(data)); 
                                                                                 flag1= revalue(-1002-data-s);
                                                                                 falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                 sysParam .sysParam_0.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                                                 sysParam .sysParam_0.ConcentParam_10.Value =(int) Flag2 ;
                                                                                 falsh_writeData();
                                                                              }
                                                                          else
                                                                          {
                                                                              s=5*sin(0.155*(data));
                                                                              flag1= revalue(-1002-data-s);
                                                                              falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                                                                           falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                           sysParam .sysParam_l_10.ConcentParam_60.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                                                                           sysParam .sysParam_l_10.ConcentParam_60.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                                                                           falsh_writeData();
                                                                                                         }
                                                                                                   else if(data>=50&&data<60)
                                                                                                         
                                                                                                        { 
                                                                                                              s=5;
                                                                                                              flag1= revalue(-1002-data-s);
                                                                                                              falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                              sysParam .sysParam_l_10.ConcentParam_50.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                                                                              sysParam .sysParam_l_10.ConcentParam_50.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                                                                              falsh_writeData();
                                                                                                          }
                                                                                                    else if(data>=40&&data<50)
                                                                                                              
                                                                                                           {
                                                                                                              s=5*sin(0.15*(data-30));
                                                                                                              flag1= revalue(-1002-data-s); 
                                                                                                              falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                              sysParam .sysParam_l_10.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                                                                              sysParam .sysParam_l_10.ConcentParam_40.Value = (int)Flag2;
                                                                                                              falsh_writeData();
                                                                                                            }
                                                                                                    else if(data>=28&&data<40)
                                                                                                           
                                                                                                             {
                                                                                                                s=5*sin(0.15*(data-30));
                                                                                                                flag1= revalue(-1002-data-s); 
                                                                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                sysParam .sysParam_l_10.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                                                                sysParam .sysParam_l_10.ConcentParam_30.Value = (int)Flag2;
                                                                                                                falsh_writeData();
                                                                                                              }
                                                                                                     else if(data>=18&&data<28)
                                                                                                           
                                                                                                            {
                                                                                                                s=5*sin(0.24*(data-17));
                                                                                                                flag1= revalue(-1002-data+s);
                                                                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                sysParam .sysParam_l_10.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                                                                sysParam .sysParam_l_10.ConcentParam_20.Value =(int)Flag2 ;
                                                                                                                falsh_writeData();
                                                                                                              }
                                                                                                      else if(data>8&&data<18)
                                                                                                          {
                                                                                                             s=5*sin(0.155*(data)); 
                                                                                                             flag1= revalue(-1002-data-s);
                                                                                                             falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                             sysParam .sysParam_l_10.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                                                                             sysParam .sysParam_l_10.ConcentParam_10.Value =(int) Flag2 ;
                                                                                                             falsh_writeData();
                                                                                                          }
                                                                                                      else
                                                                                                      {
                                                                                                          s=5*sin(0.155*(data));
                                                                                                          flag1= revalue(-1002-data-s);
                                                                                                          falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                                                                                 falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                 sysParam .sysParam_l_20.ConcentParam_60.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                                                                                 sysParam .sysParam_l_20.ConcentParam_60.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                                                                                 falsh_writeData();
                                                                                                               }
                                                                                                         else if(data>=50&&data<60)
                                                                                                               
                                                                                                              { 
                                                                                                                    s=5;
                                                                                                                    flag1= revalue(-1002-data-s);
                                                                                                                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_50.concentration =(int) (flag1*2.5) ;//将需要标定的频率值和实际频率值保存
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_50.Value =(int) Flag2;//将需要标定的频率值和实际频率值保存
                                                                                                                    falsh_writeData();
                                                                                                                }
                                                                                                          else if(data>=40&&data<50)
                                                                                                                    
                                                                                                                 {
                                                                                                                    s=5*sin(0.15*(data-30));
                                                                                                                    flag1= revalue(-1002-data-s); 
                                                                                                                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_40.concentration =(int)(flag1*2.5) ;
                                                                                                                    sysParam .sysParam_l_20.ConcentParam_40.Value = (int)Flag2;
                                                                                                                    falsh_writeData();
                                                                                                                  }
                                                                                                          else if(data>=28&&data<40)
                                                                                                                 
                                                                                                                   {
                                                                                                                      s=5*sin(0.15*(data-30));
                                                                                                                      flag1= revalue(-1002-data-s); 
                                                                                                                      falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_30.concentration =(int) (flag1*2.5) ;
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_30.Value = (int)Flag2;
                                                                                                                      falsh_writeData();
                                                                                                                    }
                                                                                                           else if(data>=18&&data<28)
                                                                                                                 
                                                                                                                  {
                                                                                                                      s=5*sin(0.24*(data-17));
                                                                                                                      flag1= revalue(-1002-data+s);
                                                                                                                      falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_20.concentration = (int)(flag1*2.5);
                                                                                                                      sysParam .sysParam_l_20.ConcentParam_20.Value =(int)Flag2 ;
                                                                                                                      falsh_writeData();
                                                                                                                    }
                                                                                                            else if(data>8&&data<18)
                                                                                                                {
                                                                                                                   s=5*sin(0.155*(data)); 
                                                                                                                   flag1= revalue(-1002-data-s);
                                                                                                                   falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                   sysParam .sysParam_l_20.ConcentParam_10.concentration =(int)(flag1*2.5);
                                                                                                                   sysParam .sysParam_l_20.ConcentParam_10.Value =(int) Flag2 ;
                                                                                                                   falsh_writeData();
                                                                                                                }
                                                                                                            else
                                                                                                            {
                                                                                                                s=5*sin(0.155*(data));
                                                                                                                flag1= revalue(-1002-data-s);
                                                                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                                                                sysParam .sysParam_l_20.ConcentParam_0.concentration =(int) (flag1*2.5);
                                                                                                                sysParam .sysParam_l_20.ConcentParam_0.Value = (int)Flag2;
                                                                                                                falsh_writeData();
                                                                                                            }
                                                                                                 }
      }
     
       else if(n==254)  //校准正数部分  10露点
      {
         if(Temperature>31||(21<Temperature&&Temperature<29)||(11<Temperature&&Temperature<19)||(1<Temperature&&Temperature<9)||(-9<Temperature&&Temperature<-1)||(-19<Temperature&&Temperature<-11)||Temperature<-21)//判断当前温度是否可以标定，若不能满足标定条件则返回
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
                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
                    sysParam .sysParam_30.ConcentParam_h.concentration =(int)(flag1*2.5);
	            sysParam .sysParam_30.ConcentParam_h.Value = (int) Flag2;
                    falsh_writeData();
      
      
                } 
                  else//校准正数部分  20露点
                {
                    s=0;
                    flag1= 2059-31*data;
                    falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                          falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                          sysParam .sysParam_20.ConcentParam_h.concentration =(int)(flag1*2.5);
                                         sysParam .sysParam_20.ConcentParam_h.Value = (int) Flag2;
     /*  high=sysParam .sysParam_20.ConcentParam_h.concentration>>8;
      low=sysParam .sysParam_20.ConcentParam_h.concentration&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x0a); 
      Send1Char(0x0a);  //485发送我们的频率信息
     RE;
             high=sysParam .sysParam_20.ConcentParam_h.Value>>8;
      low=sysParam .sysParam_20.ConcentParam_h.Value&0xFF;
     DE;
      Send1Char(high);    
      Send1Char(low);  
      Send1Char(0x0a); 
      Send1Char(0x0a);  //485发送我们的频率信息
     RE;                              
           */                               
                                          falsh_writeData();
                            
                            
                                      } 
                                 else//校准正数部分  20露点
                                      {
                                          s=0;
                                          flag1= 2059-31*data;
                                          falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                sysParam .sysParam_10.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                sysParam .sysParam_10.ConcentParam_h.Value = (int) Flag2;
                                                falsh_writeData();
                                  
                                  
                                            } 
                                         else//校准正数部分  20露点
                                            {
                                                s=0;
                                                flag1= 2059-31*data;
                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                        falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                        sysParam .sysParam_0.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                        sysParam .sysParam_0.ConcentParam_h.Value = (int) Flag2;
                                                        falsh_writeData();
                                          
                                          
                                                    } 
                                                      else//校准正数部分  20露点
                                                    {
                                                        s=0;
                                                        flag1= 2059-31*data;
                                                        falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                sysParam .sysParam_l_10.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_10.ConcentParam_h.Value = (int) Flag2;
                                                                falsh_writeData();
                                                  
                                                  
                                                            } 
                                                              else//校准正数部分  20露点
                                                            {
                                                                s=0;
                                                                flag1= 2059-31*data;
                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
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
                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                sysParam .sysParam_l_20.ConcentParam_h.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_20.ConcentParam_h.Value = (int) Flag2;
                                                                falsh_writeData();
                                                  
                                                  
                                                            } 
                                                              else//校准正数部分  20露点
                                                            {
                                                                s=0;
                                                                flag1= 2059-31*data;
                                                                falsh_readData();              //首先读出一次在写入，防止数据写入失败
                                                                sysParam .sysParam_l_20.ConcentParam_h20.concentration =(int)(flag1*2.5);
                                                                sysParam .sysParam_l_20.ConcentParam_h20.Value = (int) Flag2;
                                                                falsh_writeData();
                                                             }
                                                         }
              }  
      
       else if(n==253)  //校准温度
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

return 0;//改变数据时的函数
}



double Sensor_Info(double *x)
{
    double arr[6]={0};
     double j=0,dp;
    extern double Dp;
    double s=0;
  
            for(int i=0;i<6;i++)//将获取到的值赋值用作运算
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
                 
           if(Temperature>=28)      //判断输出数据处于那段,如果温度处于我们设定点数值之间，则使用两条曲线的数值进行计算输出平均值
           {                         //后续若需要改变输出为其他模式可在此处修改数据输出形式转换输出
                
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
                 
                 
                 
                 
                 
      //  Dp= change_data_ppm(Dp);        后续修改输出函数
                 
                 
                 
                 
                 
                 
       /*输入低于-80后一直显示-80*/
       if(Dp<=-80)
       {
          Dp=-80;
       }
       else if(Dp>=20)
      {
          Dp=20;
       
       }
         
 
   DAC12_0DAT=(int)((Dp+111.25)*21.63);              //数据写入寄存器，写入激活DAC转换        
   //   DAC12_0DAT=(int)((Dp+100.0)*34.1);    
    //  _BIS_SR(LPM1_bits + GIE);
  // __low_power_mode_off_on_exit();

 return 0;

}


















