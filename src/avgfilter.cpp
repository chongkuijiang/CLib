
#include "avgfilter.h"
#include <stdlib.h>
#include <string.h>


AVG_FILTER::AVG_FILTER(uint16_t num)
{
    bufMax = num;
    buf = (uint16_t*)calloc(bufMax, sizeof(uint16_t));
    ptr = 0;
    bufNum = 0;
    
}

uint16_t AVG_FILTER::AVGfilter(uint16_t val)  //滑动平均值
{
    int32_t sum = 0;
    buf[ptr] = val;
    if(++ptr >= bufMax) ptr = 0;
    if(bufNum < bufMax){
        bufNum ++;
    }
    for(int i=0;i<bufNum;i++){
        sum += buf[i];
    }
    return sum / bufNum;
}

//----------------------以下C程序---------------------------------------------
#include "avgfilter_c.h"

void* AVGfilterCreate(uint16_t num)
{
    AVG_FILTER obj = AVG_FILTER(num);
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}

uint16_t AVGfilter(void* obj,uint16_t val)
{
    AVG_FILTER* avg = (AVG_FILTER*)obj;
    return avg->AVGfilter(val);
}

