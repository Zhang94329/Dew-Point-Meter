
/*---------------------------------------------------------------- 
 * 文件名： sensor_data.h
 * 
 * 文件功能描述：   
 *          MSP430F16x,MSP430F14X系列单片机Flash程序库
 *      说明：  
 *          数据处理，以及标定使用的函数
 * 
 * 修改标识：   
 * 修改描述：   
**----------------------------------------------------------------*/





double  earlier(double x,double *arr);
double revalue(double x);
double get_data_count(double data,int n );
double Sensor_Info(double *x);
//double change_data_ppm(double x);