
#ifndef AVG_FILTER_v1_h
#define AVG_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include <stdint.h>

//滑动平均值
class AVG_FILTER
{
    public:
        AVG_FILTER(uint16_t num);
        uint16_t AVGfilter(uint16_t val);  //滑动平均值
    private:  
        uint16_t  ptr;
        uint16_t  bufMax;
        uint16_t  bufNum;
        uint16_t* buf;
    
};

#endif

