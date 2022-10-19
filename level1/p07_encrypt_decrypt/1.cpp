#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define n 10
#pragma warning(disable:4996);

int main()
{
	FILE* xie = fopen("2.txt", "r+");
	FILE* jie = fopen("3.txt", "w+");
	char ch;
	while((ch=fgetc(xie))!=EOF)
	{
		ch-=n;
		fputc(ch,jie);
	 } 
	 fclose(xie); fclose(jie);
	 return 0;
}
int main1()
{
	FILE* yuan = fopen("0.txt", "r+");
	FILE* xie = fopen("2.txt", "w+");
	char ch;
	while ((ch = fgetc(yuan)) != EOF)
	{
		ch += n;
		fputc(ch, xie);
	}

	fclose(yuan);
	fclose(xie); 
	return 0;
}
