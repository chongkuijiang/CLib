
#include "SpeedLimiter.h"
#include <stdlib.h>

SPEED_FILTER::SPEED_FILTER(tablt_t amplitude)
{
    SPEED_FILTER::amplitude = amplitude;
    val_1 = val_2 = val_3 = 0;
}

tablt_t SPEED_FILTER::speedLimiter(tablt_t input)
{
    tablt_t temp;	
    if((val_2 ==0)&&(val_1 == 0)){
        val_2 = val_1 = input;
    }
    val_3 = val_2; 
	val_2 = val_1; 
	val_1 = input;
	
	if(abs(val_2 - val_3) << amplitude)
		temp = val_2;
	else{
		if(abs(val_1 - val_2) << amplitude)
			temp = val_1;
		else
			temp = (val_1 + val_2)/2;
	}	
	return temp;
}

//----------------------以下C程序---------------------------------------------

#include "SpeedLimiter_c.h"
#include <string.h>

void* SpeedFilterCreate(tablt_t amplitude)
{
    SPEED_FILTER obj = SPEED_FILTER(amplitude);
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}

tablt_t speedLimiter(void* obj,tablt_t input)
{
    SPEED_FILTER* avg = (SPEED_FILTER*)obj;
    return avg->speedLimiter(input);
}

