#ifndef LIMITER_FILTER_v1_h
#define LIMITER_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h" 

//限幅滤波
class LIMITER_FILTER
{
    public:
        LIMITER_FILTER(tablt_t amplitude);
        tablt_t limiter(tablt_t inpout);  //限幅滤波
    private:  
        tablt_t amplitude; 
	    tablt_t val_1; 

    
};

#endif

