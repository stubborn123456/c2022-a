#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
int su(int a)
{
	for (int i = 2; i <= a; i++)
	{
		if (a % i == 0)
		{
			return 0;
			break;
		}
		if (i >= sqrt(a)) return (a);
	}
}
int main(int argc, char const* argv[])
{
	int a[100] = { 0 }, sp, n = 1; int add; int  bingo = 0;
	a[0] = 2;
	for (int i = 3; i <= 100; i++)
	{
		sp = su(i);
		if (sp == i)
		{
			a[n++] = i;
		}
	}
	for (int m = 6; m <= 100; m++)
	{
		for (int i = 0; i <= n - 1; i++)
		{
			for (int j = i; j <= n - 1; j++)
			{
				for (int k = j; k <= n - 1; k++)
				{
					add = a[i] + a[j] + a[k];
					if (add == m)
					{
						bingo++;
						goto next;
					}
				}
			}
		}next:;
	}
	if (bingo == 95)printf("哥德巴赫猜想在100范围内正确");
	return 0;
}
