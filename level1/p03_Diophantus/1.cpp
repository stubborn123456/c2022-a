#include<stdio.h>
#include<cstdlib>
int main()
{
	float lf1,lf2,a,b;
	lf1=2*lf2;//方程为lf1-lf2=lf1*(1/6+1/12+1/7)+5+4
	//即是lf1*3/28=9;
	for(lf1=0;;lf1++)
	{
		a=3.0/28*lf1;
		if(a==9)
		{
			printf("儿子死时丢番图的年龄为：%d\n",(int)(lf1-4));
			break;
		}
	 } system("pause");return 0;
 } 
