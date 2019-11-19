
#include <stdint.h>

#include "lookup_c.h"
#include "mid_lookup_c.h"
#include "pid.h"
#include "avgfilter_c.h"
int a,b;
float c;

typedef union
{
    int32_t u;
    float   f;
}Tab_t;

Tab_t* tab;

int32_t utab[]={7895,6978,245788,9854555};
float ftab[]={78.154,658.25,9875,55.25};

int main()
{
    tab = (Tab_t*)utab;
    a = tab[0].u;
}