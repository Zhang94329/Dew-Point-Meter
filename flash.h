//#include "BoardConfig.h"
#define uchar unsigned char
#define uint unsigned int
#define   int16_t  unsigned short 
#define   int32_t  unsigned int

#define SegmentA 0x1080
#define SegmentB 0x1000
void FlashInit();
void WaitForEnable();
void FlashErase(unsigned int Addr)  ;
void FlashWriteChar(unsigned int addr,char Data);
void FlashWriteWord(unsigned int addr,unsigned int Data);
char FlashReadChar(unsigned int Addr);
unsigned int FlashReadWord(unsigned int Addr);
void STMFLASH_Write(int32_t ReadAddr1,int32_t ReadAddr2,int16_t *pBuffer,int16_t NumToRead);
void  falsh_writeData();
void STMFLASH_Read(int32_t ReadAddr,int16_t *pBuffer,int16_t NumToRead);
void falsh_readData();
//***********************************************************************
//              系统参数
//***********************************************************************
#define SYS_PARAM_VALID      0x56                        //读出的参数标记为该值，表示参数有效 
//#define TEMPTER_FLAG     0x0c                               //温度修改系数
typedef struct 
{
	int16_t concentration;     //计算得出的频率值
	int16_t Value;          //实际的频率值
}Count_Param_t;
typedef struct{
  
	Count_Param_t ConcentParam_60;     /* (干气)-60度参数 */
	Count_Param_t ConcentParam_50;     /* -50度参数 */
	Count_Param_t ConcentParam_40;     /* -40度参数 */
	Count_Param_t ConcentParam_30;     /*-30度参数 */
	Count_Param_t ConcentParam_20;
        Count_Param_t ConcentParam_10; 
        Count_Param_t ConcentParam_0;
        Count_Param_t ConcentParam_h;
        Count_Param_t ConcentParam_h20;
       //short  temperature:8;
        
}Sys_Param_t;

typedef struct{
  
	//Sys_Param_t sysParam_50;      /*温度50 */
	//Sys_Param_t sysParam_40;      /* 温度40 */
	Sys_Param_t sysParam_30;      /* 温度30 */
	Sys_Param_t sysParam_20;      /* 温度20*/
	Sys_Param_t sysParam_10;
        Sys_Param_t sysParam_0; 
        Sys_Param_t sysParam_l_10;      /*零下 温度10*/
        Sys_Param_t sysParam_l_20;
       //  Sys_Param_t sysParam_l_30;
       // Sys_Param_t sysParam_l_40;
        int16_t  fa:8;	
        short temperature_void;
       
}Sys_Param_p;

extern Sys_Param_p sysParam;


