/*---------------------------------------------------------------- 
 * 文件名： Flash.c
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          该程序完成Flash控制器模块的通用程序库，调用本程序可以
 *          完成Flash的擦除，写入字或字节，本程序没有实现块写入功
 *          能。由于程序可以完成擦除所有的段， 所以使用时一定要注
 *          意，不要把即将运行的程序擦除。使用时注意，Flash的内容
 *          每次写入后，不能在擦除之前再次写入数据， 否则会有数据
 *          损害。
 *     
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "flash.h"
#include "Config.h"                     //开发板配置头文件，主要配置IO端口信息
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "RS485.h"
unsigned char FlashSR;
/*=======================宏定义==========================*/
#define DINT    FlashSR=__get_SR_register();_DINT() // 关中断，并保存状态寄存器
#define EINT    if(FlashSR & GIE)           _EINT() //根据保存的结果判断 开中断
/*=======================================================*/
Sys_Param_p sysParam = {
        .fa=SYS_PARAM_VALID ,
        .temperature_void= 13,
       
         .sysParam_30 = {
        //.tempter=30,
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* 干气参数 */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50度参数 */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40度参数 */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30度参数 */
	.ConcentParam_20 = {
		.concentration = 3000,  
		.Value = 3000,
	},
        .ConcentParam_10 = {
		.concentration = 2700,   
		.Value = 2700,
	},
        .ConcentParam_0 = {
		.concentration = 2500,   
		.Value = 2500,
	}, 
        .ConcentParam_h = {
		.concentration =2300 ,    /*10度参数 */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20度参数 */
		.Value = 1900,
	},
         },
         .sysParam_20 = {
           
       // .tempter=20,
        
       .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* 干气参数 */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50度参数 */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40度参数 */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30度参数 */
	.ConcentParam_20 = {
		.concentration = 3000,  
		.Value = 3000,
	},
        .ConcentParam_10 = {
		.concentration = 2700,   
		.Value = 2700,
	},
        .ConcentParam_0 = {
		.concentration = 2500,   
		.Value = 2500,
	}, 
        .ConcentParam_h = {
		.concentration =2300 ,    /*10度参数 */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20度参数 */
		.Value = 1900,
	},
         },
         .sysParam_10 = {
        
          // .tempter=10,
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* 干气参数 */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50度参数 */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40度参数 */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30度参数 */
	.ConcentParam_20 = {
		.concentration = 3000,  
		.Value = 3000,
	},
        .ConcentParam_10 = {
		.concentration = 2700,   
		.Value = 2700,
	},
        .ConcentParam_0 = {
		.concentration = 2500,   
		.Value = 2500,
	}, 
        .ConcentParam_h = {
		.concentration =2300 ,    /*10度参数 */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20度参数 */
		.Value = 1900,
	},
         },
         .sysParam_0 = {
        
          // .tempter=0,
           
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* 干气参数 */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50度参数 */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40度参数 */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30度参数 */
	.ConcentParam_20 = {
		.concentration = 3000,  
		.Value = 3000,
	},
        .ConcentParam_10 = {
		.concentration = 2700,   
		.Value = 2700,
	},
        .ConcentParam_0 = {
		.concentration = 2500,   
		.Value = 2500,
	}, 
        .ConcentParam_h = {
		.concentration =2300 ,    /*10度参数 */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20度参数 */
		.Value = 1900,
	},
         },
         .sysParam_l_10 = {
        
          // .tempter=-10,
           
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* 干气参数 */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50度参数 */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40度参数 */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30度参数 */
	.ConcentParam_20 = {
		.concentration = 3000,  
		.Value = 3000,
	},
        .ConcentParam_10 = {
		.concentration = 2700,   
		.Value = 2700,
	},
        .ConcentParam_0 = {
		.concentration = 2500,   
		.Value = 2500,
	}, 
        .ConcentParam_h = {
		.concentration =2300 ,    /*10度参数 */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20度参数 */
		.Value = 1900,
	},
         },
        .sysParam_l_20 = {
        
          // .tempter=-20,
          
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* 干气参数 */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50度参数 */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40度参数 */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30度参数 */
	.ConcentParam_20 = {
		.concentration = 3000,  
		.Value = 3000,
	},
        .ConcentParam_10 = {
		.concentration = 2700,   
		.Value = 2700,
	},
        .ConcentParam_0 = {
		.concentration = 2500,   
		.Value = 2500,
	}, 
        .ConcentParam_h = {
		.concentration =2300 ,    /*10度参数 */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20度参数 */
		.Value = 1900,
	},
        },
        };

/************************************************************
* 函数名称：FlashInit
* 功    能：Flash相关寄存器等资源初始化
* 参    数：无
* 返 回 值：无
* 说    明：使用程序库之前应先调用此函数。
*************************************************************/
void FlashInit()
{
    FCTL2 = FWKEY + FSSEL_2 + FN1;          // 默认 SMCLK/3 =333KHz 
}

/****************************************************************************
* 名    称：WaitForEnable
* 功    能：Flash忙等待
* 入口参数：无 
* 出口参数：无
* 说    明: 若Flash忙则等待，直到Flash操作完成(空闲)才返回。
****************************************************************************/
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}

/****************************************************************************
* 名    称：FlashErase
* 功    能：擦除Flash的一个数据段
* 入口参数：Addr:被擦除数据段的首地址 
* 出口参数：无
****************************************************************************/
void FlashErase(unsigned int Addr)  
{ 
    char *FlashPtr;
    FlashPtr = (char *)Addr;
    FCTL1 = FWKEY + ERASE;                      // Set Erase bit
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = 0;                              // Dummy write to erase Flash segment B
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Lock
    FCTL3 = FWKEY + LOCK;                       // Set Lock bit  
}

/****************************************************************************
* 名    称：FlashWriteChar
* 功    能：向Flash中写入一个字节(Char型变量)
* 入口参数：Addr:存放数据的地址
            Data:待写入的数据
* 出口参数：无
* 说    明：地址只能是偶数，如果是奇数，会自动前移一位
* 范    例：FlashWriteChar(0x1000,123);将常数123写入0x1000单元
            FlashWriteChar(0x1002,a);将整型变量a写入0x1002单元 
****************************************************************************/
void FlashWriteChar(unsigned int addr,char Data)
{
    char *FlashPtr = (char *)addr;              // Segment A pointer
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
}  

/****************************************************************************
* 名    称：FlashWriteChar
* 功    能：向Flash中写入一个字(无符号整型变量)
* 入口参数：Addr:存放数据的地址
            Data:待写入的数据
* 出口参数：无
* 范    例：FlashWriteChar(0x1000,123);将常数123写入0x1000单元
            FlashWriteChar(0x1002,a);将整型变量a写入0x1002单元 
****************************************************************************/
void FlashWriteWord(unsigned int addr,unsigned int Data)
{
    unsigned int *FlashPtr = (unsigned int *)addr;
    FCTL1 = FWKEY + WRT;                        // Set WRT bit for write operation
    FCTL3 = FWKEY;                              // Clear Lock bit
    DINT;
    *FlashPtr = Data;                           // Save Data
    WaitForEnable();                            //Busy
    EINT;
    FCTL1 = FWKEY;                              // Clear WRT bit
    FCTL3 = FWKEY + LOCK;                       // Set LOCK bit
   
}  

/****************************************************************************
* 名    称：FlashReadChar
* 功    能：从Flash中读取一个字节
* 入口参数：Addr:存放数据的地址
* 出口参数：读回的数据
****************************************************************************/
char FlashReadChar(unsigned int Addr)
{ 
    char Data;
    char *FlashPtr = (char *) Addr; 
    Data = *FlashPtr;
    return(Data);
}

/****************************************************************************
* 名    称：FlashReadWord
* 功    能：从Flash中读取一个字
* 入口参数：Addr:存放数据的地址
* 出口参数：读回的数据（无符号整型）
****************************************************************************/
unsigned int FlashReadWord(unsigned int Addr)
{ 
    unsigned int Data;
    unsigned int *FlashPtr = (unsigned int *)Addr; 
    Data = *FlashPtr;
    //Send1Char(Data);
    return(Data);
     
}
/****************************************************************************
* 名    称：STMFLASH_Write
* 功    能：向Flash中写入数据
* 入口参数：ReadAddr:存放数据的地址，pBuffer数据数组，NumToRead写入个数
* 出口参数：读回的数据（无符号整型）
****************************************************************************/
void STMFLASH_Write(int32_t ReadAddr1,int32_t ReadAddr2,int16_t *pBuffer,int16_t NumToRead)
{
  FlashErase(ReadAddr1);
  FlashErase(ReadAddr2);
  int i=0;
  //Sys_Param_t *sp = (Sys_Param_t *) SegmentA;    
  for(i=0;i<NumToRead;i++)
  {
    if(i<64)
    {
 FlashWriteWord(ReadAddr1,pBuffer[i]);
    ReadAddr1+=2;
    }
    else
    {
     FlashWriteWord(ReadAddr2,pBuffer[i]);
    ReadAddr2+=2;
    } 
  }

}
/****************************************************************************
* 名    称：falsh_writeData
* 功    能：向Flash中写入数据
* 入口参数：
* 出口参数：读回的数据（无符号整型）
****************************************************************************/
void  falsh_writeData()
{
     STMFLASH_Write(SegmentB,SegmentA,(int16_t*)&sysParam,sizeof(Sys_Param_p)/2);

   

    
}
/****************************************************************************
* 名    称： STMFLASH_Read
* 功    能：向Flash中读出数数据据
* 入口参数：ReadAddr:存放数据的地址，pBuffer数据数组，NumToRead写入个数
* 出口参数：读回的数据（无符号整型）
****************************************************************************/
void STMFLASH_Read(int32_t ReadAddr,int16_t *pBuffer,int16_t NumToRead)   //读取参数
{
  
  
  
  
  
   int i=0;
  //float temp;
   for(i=0;i<NumToRead;i++)
   {
       pBuffer[i] = FlashReadWord((int16_t ) ReadAddr);
       ReadAddr+=2;
       

     //Send1Char( pBuffer[i]); 
     // Send1Char(0x03);  //485发送我们的露点信息
    
   }


}
/****************************************************************************
* 名    称： falsh_readData
* 功    能：向Flash中读出数数据据
* 入口参数：
* 出口参数：读回的数据（无符号整型）
****************************************************************************/
void falsh_readData()
{
       
	Sys_Param_p sp;
	
       STMFLASH_Read(SegmentB,(int16_t *)&sp,sizeof(Sys_Param_p)/2);
	if( sp.fa == SYS_PARAM_VALID  )    //参数有效
	{
		 memcpy(&sysParam, &sp, sizeof(Sys_Param_p));
                  
	
	}
	else   //参数无效,将现有的写入进去
	{
		 falsh_writeData();
	}
  /*
  */
  
	
}

