
#include "limiterfilter.h"
#include <stdlib.h>

LIMITER_FILTER::LIMITER_FILTER(tablt_t amplitude)
{
    LIMITER_FILTER::amplitude = amplitude;
    LIMITER_FILTER::val_1 = 0;
}

tablt_t LIMITER_FILTER::limiter(tablt_t inpout)  //限幅滤波
{
    tablt_t temp;
    if(val_1 == 0) val_1 = inpout;
    if(abs(inpout - val_1) <= amplitude) 
		temp = inpout;
	else
	    temp = val_1;
	val_1 = inpout;
	return temp;
}

//----------------------以下C程序---------------------------------------------

#include "limiterfilter_c.h"
#include <string.h>

void* LimiterCreate(tablt_t amplitude)
{
    LIMITER_FILTER obj = LIMITER_FILTER(amplitude);
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}

tablt_t limiter(void* obj,tablt_t inpout)
{
    LIMITER_FILTER* avg = (LIMITER_FILTER*)obj;
    return avg->limiter(inpout);
}

