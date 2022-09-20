#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
using namespace std;
int main()
{
	int a,b=0;char zimu;scanf("%c",&zimu);system("cls");
	while(1)
	{
		for(int i=1;i<=118;i++)
	{
		for(int j=1;j<=b;j++)
		{
			printf(" ");
		}b++;
		printf("%c",zimu);
		Sleep(10);
		system("cls");
	}
	for(int i=1;i<=118;i++)
	{
		for(int j=1;j<=b;j++)
		{
			printf(" ");
		}b--;
		printf("%c",zimu);
		Sleep(10);
		system("cls");
	}
	}
}
