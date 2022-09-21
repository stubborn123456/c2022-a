#include <iostream>
#include <stdio.h>
#include <stdlib.h>
int hs(int a)
{
    int o,p,q,he;
    o=a/100;
    p=a/10%10;
    q=a%10;
    he=o*o*o+p*p*p+q*q*q;
    if(he==a)
        {
            return(a);
        }else return 0;
}
int main() {
	int h; 
    for(int i=100;i<=999;i++)
        {
        	h=hs(i);
        if(h==i)    printf("%d\n",i);
        }
    return 0;
}

