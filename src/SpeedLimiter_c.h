
#ifndef _V1_SPEEDLIMITER_FILTER_C_H_
#define _V1_SPEEDLIMITER_FILTER_C_H_

#include "tabtype.h" 



//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
    


//----------------------------------------------------------------------------------------------  
void* SpeedFilterCreate(tablt_t amplitude);
tablt_t speedLimiter(void* obj,tablt_t input);
    
#ifdef __cplusplus
}
#endif

#endif 

