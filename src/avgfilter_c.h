
#ifndef _V1_AVD_FILTER_C_H_
#define _V1_AVD_FILTER_C_H_

#include "tabtype.h" 



//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
    


//----------------------------------------------------------------------------------------------  
void* AVGfilterCreate(uint16_t num);    
tablt_t AVGfilter(void* obj,tablt_t val);  //滑动平均值


    
#ifdef __cplusplus
}
#endif

#endif 
