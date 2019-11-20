
#include "inertiaFilter.h"


tablt_t INERTIA_FILTER::inertiaFilter(tablt_t input)  //惯性滤波
{
    tablt_t temp;
    if((val_2 ==0)&&(val_1 == 0)){
        val_2 = val_1 = input;
    }
	val_3 = val_2;
	val_2 = val_1;
	val_1 = input;
	temp = val_2*0.25 + val_1*0.35 + input*0.40;	
	return  temp;
}

//----------------------以下C程序---------------------------------------------

#include "inertiafilter_c.h"
#include <stdlib.h>
#include <string.h>

void* inertiaFilterCreate()
{
    INERTIA_FILTER obj = INERTIA_FILTER();
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}

tablt_t inertiaFilter(void* obj,tablt_t input)
{
    INERTIA_FILTER* avg = (INERTIA_FILTER*)obj;
    return avg->inertiaFilter(input);
}

