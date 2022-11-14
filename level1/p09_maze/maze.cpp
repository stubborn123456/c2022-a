#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include<conio.h>
#define maxlength 100
#define hang
#define lie
typedef struct point {
	int x;
	int y;
}point;

int main()
{
	char a[maxlength][maxlength] = {
		"######",
		"#o## !",
		"# ## #",
		"#    #",
		"# ####",
		"# ## #",
		"#    #",
		"######"
	};
	for (int i = 0; i < 8; i++)puts(a[i]);
	point ball, end;
	for (int i = 0; i < maxlength; i++)//找起始点
	{
		for (int j = 0; j < maxlength; j++)
		{
			if (a[i][j] == 'o') {
				ball.x = i; ball.y = j;
			}
			
		}
	}for (int i = 0; i < maxlength; i++)//找终点
	{
		for (int j = 0; j < maxlength; j++)
		{
			if (a[i][j] == '!')
			{
				end.x = i;
				end.y = j;
			}
		}
	}
	char move ;
	while (ball.x != end.x || ball.y != end.y)
	{
		move = _getch();
		if (move == 'w'&&a[ball.x-1][ball.y]!='#')
		{
			a[ball.x][ball.y] = ' '; --ball.x;
			a[ball.x][ball.y] = 'o';
		}
		if (move == 's' && a[ball.x + 1][ball.y] != '#')
		{
			a[ball.x][ball.y] = ' '; ++ball.x;
			a[ball.x][ball.y] = 'o';
		}if (move == 'd' && a[ball.x][ball.y+1] != '#')
		{
			a[ball.x][ball.y] = ' ';
			++ball.y;
			a[ball.x][ball.y] = 'o';
		}if (move == 'a' && a[ball.x][ball.y-1] != '#')
		{
			a[ball.x][ball.y] = ' '; --ball.y;
			a[ball.x][ball.y] = 'o';
		}
		system("cls");
		if (ball.x == end.x && ball.y == end.y)
			printf("成功过关\n");
		for (int i = 0; i < 8; i++)
			puts(a[i]);
	}
	return 0;
}


