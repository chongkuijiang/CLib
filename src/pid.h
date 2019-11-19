
#ifndef _V1_PID_C_H_
#define _V1_PID_C_H_

//Constants used in some of the functions below
#define AUTOMATIC	1
#define MANUAL	0

#define DIRECT  0
#define REVERSE  1 

#define POSITIONAL   1
#define INCREMENTAL  0


//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
  
extern int millisCount; //ms计数器   
//----------------------------------------------------------------------------------------------       
void* Pid_create(float* Input, float* Output, float* Setpoint,float Kp, float Ki, float Kd,int isRevrse);	
int Pid_compute(void* pid);
void Pid_setTunings(void* pid,float Kp, float Ki, float Kd); 
void Pid_setSampleTime(void* pid,int NewSampleTime);    
void Pid_SetOutputLimits(void* pid,float Min, float Max);       
void Pid_SetMode(void* pid,int Mode);    
void Pid_SetControllerDirection(void* pid,int inRevrse);  
void Pid_SetAlgorithm(void* pid,int isPositional);
void Pid_SetFilter(void* pid,float filter);    
float Pid_GetKp(void* pid);  
float Pid_GetKi(void* pid);
float Pid_GetKd(void* pid);
int Pid_isAuto(void* pid); 
int Pid_isRevrse(void* pid);    
    
#ifdef __cplusplus
}
#endif

#endif 
