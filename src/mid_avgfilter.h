
#ifndef MID_AVG_FILTER_v1_h
#define MID_AVG_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h" 

//中值平均值,去掉最大值和最小值，再求平均值。
class MID_AVG_FILTER
{
    public:
        MID_AVG_FILTER(tablt_t* output,uint16_t bufnum,uint16_t lostnum);
        void MIDfilter(tablt_t val);  //中值平均值
    private:  
        uint16_t  ptr;
        uint16_t  bufMax;
        uint16_t  lostNum;
        tablt_t* buf;
        tablt_t* Output;
    
};

#endif

