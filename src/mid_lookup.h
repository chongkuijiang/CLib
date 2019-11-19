
#ifndef MID_LOOKUP_v1_h
#define MID_LOOKUP_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h"

//查表每次都从最中间查找
class MID_LOOKUP
{ 
    public:
    // 参数: tab-对象指针，Tab-表指针... 
    MID_LOOKUP(tablt_t *Tab,bool isUp,uint16_t step,int16_t min,uint16_t maxIndex);
    float Lookup_Table(int32_t);
    float RE_Lookup_Table(int32_t);
       
    private:  
    float downtrendTab(int32_t);
    float uptrendTab(int32_t);
    float Re_uptrendTab(int32_t);
    float Re_downtrendTab(int32_t);
    
    tablt_t   *Tab; //表格(降趋势表取最大值表,上升趋势表取最小值)	
	uint16_t  pace; //输出值步距
	int16_t   tabmin;   //输出值最小值(可负值)	
	uint16_t  maxIndex; //表格的最大素引值
    bool inUptrend;    //上升表或下降表只能是其中之一
         
};

#endif
