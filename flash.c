/*---------------------------------------------------------------- 
 * �ļ����� Flash.c
 * 
 * �ļ�����������   
 *          MSP430F16x,MSP430F14Xϵ�е�Ƭ��Flash�����
 *      ˵����  
 *          �ó������Flash������ģ���ͨ�ó���⣬���ñ��������
 *          ���Flash�Ĳ�����д���ֻ��ֽڣ�������û��ʵ�ֿ�д�빦
 *          �ܡ����ڳ��������ɲ������еĶΣ� ����ʹ��ʱһ��Ҫע
 *          �⣬��Ҫ�Ѽ������еĳ��������ʹ��ʱע�⣬Flash������
 *          ÿ��д��󣬲����ڲ���֮ǰ�ٴ�д�����ݣ� �����������
 *          �𺦡�
 *     
 * 
 * �޸ı�ʶ��   
 * �޸�������   
**----------------------------------------------------------------*/

#include <msp430x16x.h>
#include "flash.h"
#include "Config.h"                     //����������ͷ�ļ�����Ҫ����IO�˿���Ϣ
#include "math.h"
#include "stdio.h"
#include "string.h"
#include "RS485.h"
unsigned char FlashSR;
/*=======================�궨��==========================*/
#define DINT    FlashSR=__get_SR_register();_DINT() // ���жϣ�������״̬�Ĵ���
#define EINT    if(FlashSR & GIE)           _EINT() //���ݱ���Ľ���ж� ���ж�
/*=======================================================*/
Sys_Param_p sysParam = {
        .fa=SYS_PARAM_VALID ,
        .temperature_void= 13,
       
         .sysParam_30 = {
        //.tempter=30,
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* �������� */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50�Ȳ��� */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40�Ȳ��� */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30�Ȳ��� */
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
		.concentration =2300 ,    /*10�Ȳ��� */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20�Ȳ��� */
		.Value = 1900,
	},
         },
         .sysParam_20 = {
           
       // .tempter=20,
        
       .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* �������� */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50�Ȳ��� */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40�Ȳ��� */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30�Ȳ��� */
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
		.concentration =2300 ,    /*10�Ȳ��� */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20�Ȳ��� */
		.Value = 1900,
	},
         },
         .sysParam_10 = {
        
          // .tempter=10,
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* �������� */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50�Ȳ��� */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40�Ȳ��� */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30�Ȳ��� */
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
		.concentration =2300 ,    /*10�Ȳ��� */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20�Ȳ��� */
		.Value = 1900,
	},
         },
         .sysParam_0 = {
        
          // .tempter=0,
           
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* �������� */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50�Ȳ��� */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40�Ȳ��� */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30�Ȳ��� */
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
		.concentration =2300 ,    /*10�Ȳ��� */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20�Ȳ��� */
		.Value = 1900,
	},
         },
         .sysParam_l_10 = {
        
          // .tempter=-10,
           
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* �������� */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50�Ȳ��� */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40�Ȳ��� */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30�Ȳ��� */
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
		.concentration =2300 ,    /*10�Ȳ��� */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20�Ȳ��� */
		.Value = 1900,
	},
         },
        .sysParam_l_20 = {
        
          // .tempter=-20,
          
        .ConcentParam_60 = {
		.concentration =6720,   
		.Value =6720,           /* �������� */
	},  
	.ConcentParam_50 = {
		.concentration =5147,   
		.Value =5147,
	},                              /* -50�Ȳ��� */
	.ConcentParam_40 = {
		.concentration = 4500,   
		.Value = 4500,
	},                              /* -40�Ȳ��� */
	.ConcentParam_30 = {
		.concentration = 3397,   
		.Value =3397,
	},                               /*-30�Ȳ��� */
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
		.concentration =2300 ,    /*10�Ȳ��� */
		.Value = 2300,
	}, 
         .ConcentParam_h20 = {
		.concentration =1900 ,    /*20�Ȳ��� */
		.Value = 1900,
	},
        },
        };

/************************************************************
* �������ƣ�FlashInit
* ��    �ܣ�Flash��ؼĴ�������Դ��ʼ��
* ��    ������
* �� �� ֵ����
* ˵    ����ʹ�ó����֮ǰӦ�ȵ��ô˺�����
*************************************************************/
void FlashInit()
{
    FCTL2 = FWKEY + FSSEL_2 + FN1;          // Ĭ�� SMCLK/3 =333KHz 
}

/****************************************************************************
* ��    �ƣ�WaitForEnable
* ��    �ܣ�Flashæ�ȴ�
* ��ڲ������� 
* ���ڲ�������
* ˵    ��: ��Flashæ��ȴ���ֱ��Flash�������(����)�ŷ��ء�
****************************************************************************/
void WaitForEnable()
{
    while((FCTL3 & BUSY) == BUSY);      //Busy
}

/****************************************************************************
* ��    �ƣ�FlashErase
* ��    �ܣ�����Flash��һ�����ݶ�
* ��ڲ�����Addr:���������ݶε��׵�ַ 
* ���ڲ�������
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
* ��    �ƣ�FlashWriteChar
* ��    �ܣ���Flash��д��һ���ֽ�(Char�ͱ���)
* ��ڲ�����Addr:������ݵĵ�ַ
            Data:��д�������
* ���ڲ�������
* ˵    ������ַֻ����ż������������������Զ�ǰ��һλ
* ��    ����FlashWriteChar(0x1000,123);������123д��0x1000��Ԫ
            FlashWriteChar(0x1002,a);�����ͱ���aд��0x1002��Ԫ 
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
* ��    �ƣ�FlashWriteChar
* ��    �ܣ���Flash��д��һ����(�޷������ͱ���)
* ��ڲ�����Addr:������ݵĵ�ַ
            Data:��д�������
* ���ڲ�������
* ��    ����FlashWriteChar(0x1000,123);������123д��0x1000��Ԫ
            FlashWriteChar(0x1002,a);�����ͱ���aд��0x1002��Ԫ 
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
* ��    �ƣ�FlashReadChar
* ��    �ܣ���Flash�ж�ȡһ���ֽ�
* ��ڲ�����Addr:������ݵĵ�ַ
* ���ڲ��������ص�����
****************************************************************************/
char FlashReadChar(unsigned int Addr)
{ 
    char Data;
    char *FlashPtr = (char *) Addr; 
    Data = *FlashPtr;
    return(Data);
}

/****************************************************************************
* ��    �ƣ�FlashReadWord
* ��    �ܣ���Flash�ж�ȡһ����
* ��ڲ�����Addr:������ݵĵ�ַ
* ���ڲ��������ص����ݣ��޷������ͣ�
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
* ��    �ƣ�STMFLASH_Write
* ��    �ܣ���Flash��д������
* ��ڲ�����ReadAddr:������ݵĵ�ַ��pBuffer�������飬NumToReadд�����
* ���ڲ��������ص����ݣ��޷������ͣ�
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
* ��    �ƣ�falsh_writeData
* ��    �ܣ���Flash��д������
* ��ڲ�����
* ���ڲ��������ص����ݣ��޷������ͣ�
****************************************************************************/
void  falsh_writeData()
{
     STMFLASH_Write(SegmentB,SegmentA,(int16_t*)&sysParam,sizeof(Sys_Param_p)/2);

   

    
}
/****************************************************************************
* ��    �ƣ� STMFLASH_Read
* ��    �ܣ���Flash�ж��������ݾ�
* ��ڲ�����ReadAddr:������ݵĵ�ַ��pBuffer�������飬NumToReadд�����
* ���ڲ��������ص����ݣ��޷������ͣ�
****************************************************************************/
void STMFLASH_Read(int32_t ReadAddr,int16_t *pBuffer,int16_t NumToRead)   //��ȡ����
{
  
  
  
  
  
   int i=0;
  //float temp;
   for(i=0;i<NumToRead;i++)
   {
       pBuffer[i] = FlashReadWord((int16_t ) ReadAddr);
       ReadAddr+=2;
       

     //Send1Char( pBuffer[i]); 
     // Send1Char(0x03);  //485�������ǵ�¶����Ϣ
    
   }


}
/****************************************************************************
* ��    �ƣ� falsh_readData
* ��    �ܣ���Flash�ж��������ݾ�
* ��ڲ�����
* ���ڲ��������ص����ݣ��޷������ͣ�
****************************************************************************/
void falsh_readData()
{
       
	Sys_Param_p sp;
	
       STMFLASH_Read(SegmentB,(int16_t *)&sp,sizeof(Sys_Param_p)/2);
	if( sp.fa == SYS_PARAM_VALID  )    //������Ч
	{
		 memcpy(&sysParam, &sp, sizeof(Sys_Param_p));
                  
	
	}
	else   //������Ч,�����е�д���ȥ
	{
		 falsh_writeData();
	}
  /*
  */
  
	
}

