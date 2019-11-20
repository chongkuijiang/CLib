
#ifndef _V1_MID_AVD_FILTER_C_H_
#define _V1_MID_AVD_FILTER_C_H_

#include "tabtype.h"



//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
    


//----------------------------------------------------------------------------------------------  
void* MidfilterCreate(tablt_t* output,uint16_t bufnum,uint16_t lostnum);    
void Midfilter(void* obj,tablt_t val);  //中值平均值


    
#ifdef __cplusplus
}
#endif

#endif 
