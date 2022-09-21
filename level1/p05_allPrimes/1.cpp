#include<stdio.h>
#include<math.h>
#include<time.h>
int su(int a)
{
	int b,c;
	for(int i=2;i<=a;i++)
	{
		if(a%i==0)
		{
			return 0;
			break;
		}
		if(i>=sqrt(a)) return (a);
	}
}
int main()
{	clock_t start,end;
	start=clock();
	int q;
	for(int t=2;t<=1000;t++)
	{
		q=su(t);
		if(q==t) printf("%d\n",q);
		if(t==2)	printf("2\n");
	}
	end=clock();
	printf("%d",end-start);
	return 0;
}
