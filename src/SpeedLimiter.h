
#ifndef SPEEDLIMITER_FILTER_v1_h
#define SPEEDLIMITER_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h" 

//限速滤波
class SPEED_FILTER
{
    public:
        SPEED_FILTER(tablt_t amplitude);
        tablt_t speedLimiter(tablt_t input);
    private:  
        tablt_t amplitude; 
		tablt_t val_1; 
		tablt_t val_2;
		tablt_t val_3;	
    
};

#endif

