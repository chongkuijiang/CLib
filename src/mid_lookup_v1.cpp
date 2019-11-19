
#include "mid_lookup.h"
#include "mid_lookup_c.h"

MID_LOOKUP::MID_LOOKUP(tablt_t *Tab,bool isUp,uint16_t step,int16_t min,uint16_t maxIndex)
{
    MID_LOOKUP::Tab = Tab;
    MID_LOOKUP::inUptrend = isUp;
    MID_LOOKUP::pace = step;
    MID_LOOKUP::tabmin = min;
    MID_LOOKUP::maxIndex = maxIndex;    
}

float MID_LOOKUP::Lookup_Table(int32_t volt)
{
    if(inUptrend){
        return uptrendTab(volt);
    }
    else{
        return downtrendTab(volt);
    }
}
float MID_LOOKUP::RE_Lookup_Table(int32_t volt)
{
    if(inUptrend){
        return Re_uptrendTab(volt);
    }
    else{
        return Re_downtrendTab(volt);
    }
}

// 功能: 查上升趋势表,返回表的下标,常用于热电耦测温。
// 参数: tab-每个对像要创建一个变量
// 输入：volt-(整数)
// 输出: 输出float值
float MID_LOOKUP::uptrendTab(int32_t volt)
{
    float result;
	int16_t  max = maxIndex, min=0;
	int16_t  fkey=maxIndex/2, okey=0;
    
	if 	(volt<=Tab[0])   result = tabmin;		
    else if (volt>=Tab[maxIndex])   result = (float)(maxIndex*pace) + tabmin;		
    else 
    {
        while(1) 
        {
            if 	(volt > Tab[fkey]) { min = fkey; }
            else if (volt < Tab[fkey]) { max = fkey; }
            else {
                result = (float)(fkey*pace) + tabmin;
                break;
            }

            okey = fkey;
            fkey = ((max-min)>>1) + min;
            
            if (okey==fkey) {
                result  = (volt - Tab[fkey]);
                result /= (Tab[fkey+1] - Tab[fkey]);
                result *= pace;
                result += ((float)(fkey*pace) + tabmin);	
                break;
            }			
        }		
    }
	return result;
}

//----------------------------------------------------------------------------------
// 功能: 查下降趋势表,返回表的下标,常用于NTC测温。
// 参数: tab-每个对像要创建一个变量
// 输入：R-(整数)
// 输出: 输出float值
float MID_LOOKUP::downtrendTab(int32_t R)  //采用中值查表法
{
    float result;
    int16_t  max = maxIndex, min=0;
	int16_t  fkey=maxIndex/2, okey=0;
          
    if(R >= Tab[0]) result = tabmin;
    else if(R <= Tab[maxIndex]) result =  (float)(maxIndex*pace) + tabmin;	
    else 
    {	
        while(1) 
        {
            if (R > (float)Tab[fkey]) { max = fkey; }
            else if(R < (float)Tab[fkey]) { min = fkey; }
            else {
                result = (float)(fkey*pace) + tabmin;
                break;
            }

            okey = fkey;
            fkey = ((max-min)>>1) + min;
            
            if (okey==fkey) {			
                result  = ((float)Tab[fkey] - R);
                result /= ((float)Tab[fkey] - Tab[fkey+1]);
                result *= pace;
                result += ((float)(fkey*pace) + tabmin);	
                break;
            }			
        }
    }	
	return result;
}

// 功能: 反向查上升趋势表,返回数值域。
// 参数: tab-不修改对象中的变量
// 输入：volt-(整数)
// 输出: 输出float值
float MID_LOOKUP::Re_uptrendTab(int32_t volt)
{
    uint16_t i,j;
	float result;
	i = (volt-tabmin)/pace;
	result = Tab[i];
	j = (volt-tabmin)%pace;
	if(j != 0)
		result += (float)j*(Tab[i+1]-Tab[i]) / pace;
	return result;
}

// 功能: 反向查下降趋势表,返回数值域。
// 参数: tab-不修改对象中的变量
// 输入：volt-(整数)
// 输出: 输出float值
float MID_LOOKUP::Re_downtrendTab(int32_t volt)
{
    uint16_t i,j;
	float result;
	i = (volt-tabmin)/pace;
	result = Tab[i];
	j = (volt-tabmin)%pace;
	if(j != 0)
		result -= (float)j*(Tab[i]-Tab[i+1]) / pace;
	return result;
}
//----------------------以下C程序---------------------------------------------
#include <stdlib.h>
#include <string.h>

void* midLookupCreate(tablt_t *Tab,int isUp,uint16_t step,int16_t min,uint16_t maxIndex)
{
    MID_LOOKUP obj = MID_LOOKUP(Tab,isUp,step,min,maxIndex);
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}

float midLookup_Table(void* look,int32_t vol)
{
    MID_LOOKUP* obj = (MID_LOOKUP*)look;
    return obj->Lookup_Table(vol);
}

float midRE_Lookup_Table(void* look,int32_t vol)
{
    MID_LOOKUP* obj = (MID_LOOKUP*)look;
    return obj->RE_Lookup_Table(vol);
}

