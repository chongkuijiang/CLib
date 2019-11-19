
#ifndef _V1_LOOKUP_C_H_
#define _V1_LOOKUP_C_H_

#include "tabtype.h" 

//Constants used in some of the functions below
#define   UPTREND      1
#define   DOWNTREND    0


//对外接口函数
#ifdef __cplusplus    
extern "C" {
#endif
    


//----------------------------------------------------------------------------------------------       
void* LookupCreate(tablt_t *Tab,int isUp,uint16_t step,int16_t min,uint16_t maxIndex);
float Lookup_Table(void* look,int32_t vol);
float RE_Lookup_Table(void* look,int32_t vol);


    
#ifdef __cplusplus
}
#endif

#endif 
