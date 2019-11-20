
#ifndef INERTIA_FILTER_v1_h
#define INERTIA_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h" 

//惯性滤波
class INERTIA_FILTER
{
    public:
        tablt_t inertiaFilter(tablt_t inpout);  //惯性滤波
    private:  
	    tablt_t val_1; 
		tablt_t val_2; 
		tablt_t val_3; 
    
};

#endif

