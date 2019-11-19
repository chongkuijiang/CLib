
#ifndef LOOKUP_v1_h
#define LOOKUP_v1_h
#define LIBRARY_VERSION	1.0.0

#include "tabtype.h" 

//查表是在上一次的基础上进行
class LOOKUP
{
    public:
    // 参数: tab-对象指针，Tab-表指针... 
    LOOKUP(tablt_t *Tab,bool isUp,uint16_t step,int16_t min,uint16_t maxIndex);
    float Lookup_Table(int32_t);
    float RE_Lookup_Table(int32_t);
       
    private:  
    float downtrendTab(int32_t);
    float uptrendTab(int32_t);
    float Re_uptrendTab(int32_t);
    float Re_downtrendTab(int32_t);
    
    tablt_t   *Tab; //表格(降趋势表取最大值表,上升趋势表取最小值)	
	uint16_t  index;  //上一次表格素引
	uint16_t  pace; //输出值步距
	int16_t   min;   //输出值最小值(可负值)	
	uint16_t  maxIndex; //表格的最大素引值
    bool inUptrend;    //上升表或下降表只能是其中之一
         
};

#endif
