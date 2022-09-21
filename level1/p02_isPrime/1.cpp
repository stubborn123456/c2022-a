#include<stdio.h>
#include<math.h>
#include<stdlib.h>
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
		if(i>sqrt(a)) return (a);
	}
}
int main()
{
	int n,q;
	scanf("%d",&n);
		q=su(n);
		if(q==n||n==2) printf("素数");
			else printf("不是素数"); 
	return 0; 
}

