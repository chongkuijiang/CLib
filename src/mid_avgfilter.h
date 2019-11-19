
#ifndef MID_AVG_FILTER_v1_h
#define MID_AVG_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include <stdint.h>

//中值平均值
class MID_AVG_FILTER
{
    public:
        MID_AVG_FILTER(uint16_t* output,uint16_t bufnum,uint16_t lostnum);
        void MIDfilter(uint16_t val);  //中值平均值
    private:  
        uint16_t  ptr;
        uint16_t  bufMax;
        uint16_t  lostNum;
        uint16_t* buf;
        uint16_t* Output;
    
};

#endif

