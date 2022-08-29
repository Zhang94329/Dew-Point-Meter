/*---------------------------------------------------------------- 
 * 文件名： 485.h
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          485通讯
 *     
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息


/*
#define DRE_out   P5DIR |= BIT2 //连接485芯片的DE，RE端口的IO设置为输出状态
#define DE        P5OUT |=BIT2 //设置485芯片处于发送状态
#define RE        P5OUT &= ~BIT2 //设置485芯片处于接收状态
*/
void Set_UART1(void);
void PutString0(char *ptr);
void Send1Char(uchar sendchar);

