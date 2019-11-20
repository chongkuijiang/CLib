
#include "lookup.h"
#include "lookup_c.h"

LOOKUP::LOOKUP(const tablt_t *Tab,bool isUp,uint16_t step,int16_t min,uint16_t maxIndex)
{
    LOOKUP::Tab = Tab;
    LOOKUP::index = 0;
    LOOKUP::inUptrend = isUp;
    LOOKUP::pace = step;
    LOOKUP::min = min;
    LOOKUP::maxIndex = maxIndex;    
}

float LOOKUP::Lookup_Table(int32_t volt)
{
    if(inUptrend){
        return uptrendTab(volt);
    }
    else{
        return downtrendTab(volt);
    }
}
float LOOKUP::RE_Lookup_Table(int32_t volt)
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
float LOOKUP::uptrendTab(int32_t volt)
{
    float result;
	uint16_t decimal;
	decimal = 0;
	while(1)
    {
		if(volt > Tab[index])
		{
			index++;
			if(volt < Tab[index]){
			   index--;
				decimal = 1;break;
			}
		}
		else if(volt < Tab[index]) 
		{
			index--;
			if(volt > Tab[index]){
				decimal = 1;break;				
			}
		}
		else break;
        if(index > maxIndex){
			index = maxIndex;break;			
		}			
	}
    result = index * pace + min;
	if(decimal == 1){
		result += (float)(volt-Tab[index])*pace / (Tab[index+1]-Tab[index]);
	}
	return result;
}

//----------------------------------------------------------------------------------
// 功能: 查下降趋势表,返回表的下标,常用于NTC测温。
// 参数: tab-每个对像要创建一个变量
// 输入：R-(整数)
// 输出: 输出float值
float LOOKUP::downtrendTab(int32_t R)
{
    float result;
	uint16_t decimal;
	decimal = 0;
	while(1)
    {
		if(R < Tab[index])
		{
			index++;
			if(R > Tab[index]){
			    index--;
			    decimal = 1;break;
			}
		}
		else if(R > Tab[index]) 
		{
			index--;
			if(R < Tab[index]){
				decimal = 1;break;				
			}
		}
		else break;		
		if(index > maxIndex){
			index = maxIndex;break;			
		}	
	}
    result = index * pace + min;
	if(decimal == 1){
		result += (float)(Tab[index]-R)*pace / (Tab[index]-Tab[index+1]);
	}
	return result;
}

// 功能: 反向查上升趋势表,返回数值域。
// 参数: tab-不修改对象中的变量
// 输入：volt-(整数)
// 输出: 输出float值
float LOOKUP::Re_uptrendTab(int32_t volt)
{
    uint16_t i,j;
	float result;
	i = (volt-min)/pace;
	result = Tab[i];
	j = (volt-min)%pace;
	if(j != 0)
		result += (float)j*(Tab[i+1]-Tab[i]) / pace;
	return result;
}

// 功能: 反向查下降趋势表,返回数值域。
// 参数: tab-不修改对象中的变量
// 输入：volt-(整数)
// 输出: 输出float值
float LOOKUP::Re_downtrendTab(int32_t volt)
{
    uint16_t i,j;
	float result;
	i = (volt-min)/pace;
	result = Tab[i];
	j = (volt-min)%pace;
	if(j != 0)
		result -= (float)j*(Tab[i]-Tab[i+1]) / pace;
	return result;
}
//----------------------以下C程序---------------------------------------------
#include <stdlib.h>
#include <string.h>

void* LookupCreate(tablt_t *Tab,int isUp,uint16_t step,int16_t min,uint16_t maxIndex)
{
    LOOKUP obj = LOOKUP(Tab,isUp,step,min,maxIndex);
    void* p = malloc(sizeof(obj));    
    memcpy(p,&obj,sizeof(obj));
    return p;
}

float Lookup_Table(void* look,int32_t vol)
{
    LOOKUP* obj = (LOOKUP*)look;
    return obj->Lookup_Table(vol);
}

float RE_Lookup_Table(void* look,int32_t vol)
{
    LOOKUP* obj = (LOOKUP*)look;
    return obj->RE_Lookup_Table(vol);
}

