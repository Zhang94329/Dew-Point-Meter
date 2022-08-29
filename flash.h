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
//              ϵͳ����
//***********************************************************************
#define SYS_PARAM_VALID      0x56                        //�����Ĳ������Ϊ��ֵ����ʾ������Ч 
//#define TEMPTER_FLAG     0x0c                               //�¶��޸�ϵ��
typedef struct 
{
	int16_t concentration;     //����ó���Ƶ��ֵ
	int16_t Value;          //ʵ�ʵ�Ƶ��ֵ
}Count_Param_t;
typedef struct{
  
	Count_Param_t ConcentParam_60;     /* (����)-60�Ȳ��� */
	Count_Param_t ConcentParam_50;     /* -50�Ȳ��� */
	Count_Param_t ConcentParam_40;     /* -40�Ȳ��� */
	Count_Param_t ConcentParam_30;     /*-30�Ȳ��� */
	Count_Param_t ConcentParam_20;
        Count_Param_t ConcentParam_10; 
        Count_Param_t ConcentParam_0;
        Count_Param_t ConcentParam_h;
        Count_Param_t ConcentParam_h20;
       //short  temperature:8;
        
}Sys_Param_t;

typedef struct{
  
	//Sys_Param_t sysParam_50;      /*�¶�50 */
	//Sys_Param_t sysParam_40;      /* �¶�40 */
	Sys_Param_t sysParam_30;      /* �¶�30 */
	Sys_Param_t sysParam_20;      /* �¶�20*/
	Sys_Param_t sysParam_10;
        Sys_Param_t sysParam_0; 
        Sys_Param_t sysParam_l_10;      /*���� �¶�10*/
        Sys_Param_t sysParam_l_20;
       //  Sys_Param_t sysParam_l_30;
       // Sys_Param_t sysParam_l_40;
        int16_t  fa:8;	
        short temperature_void;
       
}Sys_Param_p;

extern Sys_Param_p sysParam;


