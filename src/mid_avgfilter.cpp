
#include "mid_avgfilter.h"
#include <stdlib.h>
#include <string.h>

MID_AVG_FILTER::MID_AVG_FILTER(tablt_t* output,uint16_t bufnum,uint16_t lostnum)
{
    Output = output;
    bufMax = bufnum;
    if(lostnum < 4) lostNum = lostnum;
    else  lostNum = 3;
    buf = (tablt_t*)calloc(bufMax, sizeof(tablt_t));
    ptr = 0;
}

void MID_AVG_FILTER::MIDfilter(tablt_t val)  //中值平均值
{
    uint16_t i, j;
    tablt_t temp;
    uint32_t sum=0;
    
    if(ptr < bufMax){
        buf[ptr++] = val;
    }
    else {
        for(i=0;i<bufMax-1; i++)
        {
            for(j=i+1;j<bufMax;j++)
            {
                if(buf[i]>buf[j])
                {
                    temp=buf[i];
                    buf[i]=buf[j];
                    buf[j]=temp;
                }
            }
        }
        sum = 0;
        for(i=lostNum;i<bufMax-lostNum;i++)sum+=buf[i];
        temp=sum/(bufMax-2*lostNum);  
        *Output = temp;
        ptr = 0;
    }
}

//----------------------以下C程序---------------------------------------------
#include "mid_avgfilter_c.h"

void* MidfilterCreate(tablt_t* output,uint16_t bufnum,uint16_t lostnum)
{
    MID_AVG_FILTER obj = MID_AVG_FILTER(output,bufnum,lostnum);
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}    

void Midfilter(void* obj,tablt_t val)
{
    MID_AVG_FILTER* avg = (MID_AVG_FILTER*)obj;
    avg->MIDfilter(val);
}



