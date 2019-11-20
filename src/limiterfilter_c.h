

#ifndef _V1_LIMITER_FILTER_C_H_
#define _V1_LIMITER_FILTER_C_H_

#include "tabtype.h" 



//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
    


//----------------------------------------------------------------------------------------------  
void* LimiterCreate(tablt_t amplitude);
tablt_t limiter(void* obj,tablt_t inpout);
    
#ifdef __cplusplus
}
#endif

#endif 

