
#ifndef AVG_FILTER_v1_h
#define AVG_FILTER_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h" 

//滑动平均值,每次都有输入输出，平均值是一个缓冲池。
class AVG_FILTER
{
    public:
        AVG_FILTER(uint16_t num);
        tablt_t AVGfilter(tablt_t val);  //滑动平均值
    private:  
        uint16_t  ptr;
        uint16_t  bufMax;
        uint16_t  bufNum;
        tablt_t* buf;
    
};

#endif

