
#ifndef _V1_INERTIA_FILTER_C_H_
#define _V1_INERTIA_FILTER_C_H_

#include "tabtype.h" 



//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
    


//----------------------------------------------------------------------------------------------  
void* inertiaFilterCreate();
tablt_t inertiaFilter(void* obj,tablt_t input);
    
#ifdef __cplusplus
}
#endif

#endif 

