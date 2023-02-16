#include<graphics.h>
#include<Windows.h>
#include <math.h>
#include<time.h>
#include<easyx.h>
#include<stdio.h>
IMAGE hei, bai, pan;
#define defence 2//防守参数
#define V 10//基础得分和连子倍率
long double A = -99999999;//最大的最小值
long double B = -A;//最小的最大值
#define MIN 5
#define MAX 20
#define dep 3
int num = 0;//步数
int first=1;//谁先手1玩家		2电脑
struct point
{
	int who;//该点的状态  0空 1电脑 -1玩家
	long double value;//该点目前得分
	long double prevalue;//下一步下在该点的得分
};
typedef struct Step
{
	int x;
	int y;
}step;
step step1[120];//玩家的每一步
step step2[120];//电脑的每一步
step ste[3][120];
void board();//绘画棋盘
void initialize(struct point p[25][25]);//初始化棋盘，将棋盘归零
void begin(point p[25][25]);//开局
int robot(struct point p[25][25]);//电脑下棋
void ass(struct point p[25][25]);//评估一点的得分
double wholeass(struct point p[25][25]);//评估整盘目前的得分
double deduction(struct point p[25][25], int sex, int depth, long double a, long double b,int robot_time);//主要的计算函数，极大极小值，剪枝
int end(struct point p[25][25]);//结束
void over(int a);
void execute(point p[25][25], int x, int y);
void regret(point p[25][25],int num);
int prevent(point p[25][25],int x,int y);//禁手
void initialize(struct point p[25][25])
{
	num = 0;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 25; j++)
		{
			p[i][j].who = 0;
			p[i][j].value = 0;
			p[i][j].prevalue = 0;
		}
	}
}
int end(struct point p[25][25])//得到胜负
{
	int x, y, xiex, xiey,k=0,e=0;
	for (int i = MIN; i <MAX; i++)
	{
		for (int j = MIN; j < MAX; j++)
		{	if (p[i][j].who == 0)
			{
				k++;
				if (k == 0)
				{
					e = 1;//平局
				}
			}
			if (p[i][j].who)
			{
				for (x = -2; p[i][j + x].who == p[i][j].who && x < 4; x++)
				{
				}
				for (y = -2; p[i + y][j].who == p[i][j].who && y < 4; y++)
				{
				}
				for (xiex = -2; p[i + xiex][j + xiex].who == p[i][j].who && xiex < 4; xiex++)
				{
				}
				for (xiey = -2; p[i - xiey][j + xiey].who == p[i][j].who && xiey < 4; xiey++)
				{
				}
				if (x == 3 || y == 3 || xiex == 3 || xiey == 3)
				{
					if (p[i][j].who == 1)	e = 2;//玩家lose
					else if (p[i][j].who == -1)	e=3;//玩家win

				}
			}
			
		}
	}
	return e;//若e为0则没结束
}
void board()
{
	char i=1, j=1;
	initgraph(1000, 850);//初始化绘图窗口
	setbkcolor(BLACK);//背景为黑
	cleardevice();//用当前背景色清空上一个绘图
	putimage(50, 50, &pan);
	settextcolor(WHITE);
	settextstyle(20, 0, _T("宋体"));
	/*for (; i <= 15; i++)
	{
		char a[20];
		sprintf_s(a, "%d", i);
		outtextxy(20, i*50, (LPCTSTR)(a));
	}*/
	outtextxy(20,  (i++) * 50-5,_T("1")); outtextxy(20,  (i++) * 50-5, _T("2")); outtextxy(20, (i++) * 50-5, _T("3")); outtextxy(20,  (i++) * 50-5, _T("4")); outtextxy(20, (i++) * 50-5, _T("5")); outtextxy(20, (i++) * 50-5, _T("6")); outtextxy(20,(i++) * 50-5, _T("7")); outtextxy(20, (i++) * 50-5, _T("8")); outtextxy(20,(i++) * 50-5, _T("9")); outtextxy(20,(i++) * 50-5, _T("10")); outtextxy(20,(i++) * 50-5, _T("11")); outtextxy(20,(i++) * 50-5, _T("12")); outtextxy(20,(i++) * 50-5, _T("13")); outtextxy(20, (i++) * 50-5, _T("14")); outtextxy(20,(i++) * 50-5, _T("15")); outtextxy(20, (i++) * 50 - 5, _T("16"));
	outtextxy(-5 + (j++) * 50, 820, _T("1")); outtextxy(-5 + (j++) * 50, 820, _T("2")); outtextxy(-5 + (j++) * 50, 820, _T("3")); outtextxy(-5 + (j++) * 50, 820, _T("4")); outtextxy(-5 + (j++) * 50, 820, _T("5")); outtextxy(-5 + (j++) * 50, 820, _T("6")); outtextxy(-5 + (j++) * 50, 820, _T("7")); outtextxy(-5 + (j++) * 50, 820, _T("8")); outtextxy(-5 + (j++) * 50, 820, _T("9")); outtextxy(-5 + (j++) * 50, 820, _T("10")); outtextxy(-5 + (j++) * 50, 820, _T("11")); outtextxy(-5 + (j++) * 50, 820, _T("12")); outtextxy(-5 + (j++) * 50, 820, _T("13")); outtextxy(-5 + (j++) * 50, 820, _T("14")); outtextxy(-5 + (j++) * 50, 820, _T("15")); outtextxy(-5 + (j++) * 50, 820, _T("16"));
	settextstyle(40, 0, _T("楷体"));
	outtextxy(820, 200, _T("后 手"));
	outtextxy(820, 500,_T("退 出"));
	outtextxy(820, 400, _T("悔 棋"));
	outtextxy(820, 300, _T("重 开"));
}
void execute(struct point p[25][25], int x, int y)//玩家下棋
{
	setfillcolor(WHITE);
	fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);
	p[x][y].who = 1;
	ste[2][num].x = x;
	ste[2][num].y = y;
}
//悔棋
void regret(point p[25][25],int num)
{
	board();
	setrop2(R2_COPYPEN);  //设置绘制颜色
	setcolor(WHITE);
	p[ste[1][num].x][ste[1][num].y].who = 0;
	p[ste[2][num].x][ste[2][num].y].who = 0;
	for (int i = MIN; i < MAX; i++)
	{
		for (int j = MIN; j < MAX; j++)
		{
			if (p[i][j].who == 1)
			{
				setfillcolor(WHITE);
				fillcircle((i + 1 - MIN) * 50, (j + 1 - MIN) * 50, 20);
			}
			if (p[i][j].who == -1)
			{
				setfillcolor(BLACK);
				fillcircle((i + 1 - MIN) * 50, (j + 1 - MIN) * 50, 20);
			}
		}
	}
}
int prevent(point p[25][25], int x,int y)//禁手 需收到谁先手最后一步棋的坐标
{
	int count=0;
	int det = 0;//将first转为对应玩家电脑的-1和1  first1 玩家			first2 电脑
	if (first == 1)	det = -1;
	if (first == 2)	det = 1;
	if (p[x - 1][y].who == det && p[x - 2][y].who == det && p[x + 1][y].who != -det && p[x - 3][y].who != -det)	count++;//上活三
	if (p[x + 1][y].who == det && p[x + 2][y].who == det && p[x - 1][y].who != -det && p[x +3][y].who != -det)	count++;//下活三
	if (p[x][y - 1].who == det && p[x ][y- 2].who == det && p[x ][y+ 1].who != -det && p[x ][y-3].who != -det)	count++;//左活三
	if (p[x][y + 1].who == det && p[x][y + 2].who == det && p[x][y - 1].who != -det && p[x][y + 3].who != -det)	count++;//右活三
	if (p[x + 1][y - 1].who == det && p[x + 2][y - 2].who == det && p[x - 1][y + 1].who != -det && p[x + 3][y - 3].who != -det)	count++;//左下活三
	if (p[x - 1][y - 1].who == det && p[x - 2][y - 2].who == det && p[x + 1][y + 1].who != -det && p[x - 3][y - 3].who != -det)	count++;//左上活三
	if (p[x - 1][y + 1].who == det && p[x - 2][y + 2].who == det && p[x + 1][y - 1].who != -det && p[x - 3][y + 3].who != -det)	count++;//右上活三
	if (p[x + 1][y + 1].who == det && p[x + 2][y + 2].who == det && p[x - 1][y - 1].who != -det && p[x + 3][y + 3].who != -det)	count++;//右下活三
	if (count == 2)
	{
		if (first == 1)	return 2;//玩家输
		if (first == 2) return 3;//电脑输
	}

	
}
void begin(point p[25][25])//开局（默认玩家先手）
{
	MOUSEMSG m;//mouse
	int x, y, i, j,count=0;//ij分别为处理后的横纵坐标
	board();
	setlinecolor(WHITE);

	while (1)
	{
		m = GetMouseMsg();//获取鼠标位置
		x = m.x % 50;
		y = m.y % 50;
		setrop2(R2_COPYPEN);
		if (m.uMsg == WM_LBUTTONDOWN)//按下左键
		{
			if (m.x <= 900 && m.y<550 && m.x>820 && m.y > 500)//退出
			{
				closegraph();//关闭绘图窗口
				exit(0);//强制退出
			}
			if (m.x <= 900 && m.y < 450 && m.x>820 && m.y > 400)//regret
			{
				num--;
				regret(p,num);
				continue;
			}
			if (m.x > 820 && m.x <= 900 && m.y > 300 && m.y < 350)//重开
			{
				initialize(p);
				begin(p);
			}
			if (m.x > 820 && m.x <= 900 && m.y > 200 && m.y < 250&&count==0)//后手
			{
				first = 2;
				robot(p);
				count = 1;
			}
			if (x >= 25)	m.x = m.x - x + 50;
			else m.x = m.x - x;
			if (y >= 25)	m.y = m.y - y + 50;
			else m.y = m.y - y;//讲点击位置定在棋盘的点上
			i = m.x / 50 - 1 + MIN;
			j = m.y / 50 - 1 + MIN;
			if (i < 21 && j < 21)
			{
				if (p[i][j].who)	continue;
				if (m.x <= 800 && m.y <= 800 && m.x >= 50 && m.y >= 50)
				{
					setfillcolor(BLACK);
					fillcircle(m.x, m.y, 20);
					p[i][j].who = -1;
					ste[1][num].x = i;
					ste[1][num].y = j;

				}
				if (first==1&&prevent(p, i, j) == 2)
				{
					Sleep(1000);
					over(2);//结束动画
				}
				if (end(p) != 0)//判断是否结束
				{
					Sleep(1000);
					over(end(p));//结束动画
				}
				robot(p);
				if (end(p) != 0)//判断是否结束
				{
					Sleep(1000);
					over(end(p));//结束动画
				}
				num++;
			/*char num[50];
			sprintf_s(num, " % d", step);
			settextcolor(WHITE);
			settextstyle(40, 0, _T("宋体"));
			outtextxy(800, 400, num[50]);*/
			}
		}
		
	}
}
//结束画面
void over(int a)
{
	point pp[25][25];       //  5--19	
	initialize(pp);      //初始化
	initgraph(400, 400);
	cleardevice();     //使用当前背景色清空绘图设备
	settextstyle(50, 24, _T("宋体"));
	settextcolor(RED);    //字体颜色
	if (a == 1)
	{
		outtextxy(100, 50, _T("平局") );
	}
	else if (a == 2)
	{
		outtextxy(100, 50, _T("电脑获胜"));
	}
	else if (a == 3)
	{
		outtextxy(100, 50, _T("我赢啦！"));
	}
	settextcolor(WHITE);
	outtextxy(50, 200, _T("返回游戏界面") );
	outtextxy(80, 300, _T(" 结束游戏"));

	while (true)
	{
		MOUSEMSG n;//鼠标信息
		n = GetMouseMsg();
		switch (n.uMsg) {
		case WM_LBUTTONDOWN:
			if (n.x <= 350 && n.x >= 50 && n.y <= 250 && n.y >= 200)
				begin(pp);   //返回游戏界面
			if (n.x <= 300 && n.x >= 80 && n.y <= 350 && n.y >= 300)
			{
				closegraph(); // 关闭绘图窗口
				exit(0);    //强制退出
			}
		}
	}
}
//总局面评估
double wholeass(struct point p[25][25])
{
	int i, j;
	ass(p);
	long double wholevalue = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			wholevalue += p[i][j].value;//总得分
		}
	}return wholevalue;
}
//某点价值评估
void ass(point p[25][25])
{
	int i, j, k, m, n, x;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].who == 0)
			{
				p[i][j].value = 0;
			}
			else
			{
				long double v1 = V, v2 = V, v3 = V, v4 = V, v5 = V, v6 = V, v7 = V, v8 = V;
				for (x = 0, n = j; p[i][j].who != -p[i][n + 1].who && n + 1 < 20 && x < 4; x++, n++)//右
				{ }
				if (x < 4)
				{
					v1 = 0;//被挡住为0
				}
				else
				{
					for (k = 0, n = j; p[i][j].who == p[i][n + 1].who && k < 4; k++, n++)
					{
						v1 *= V;
					}
				}
				for (x = 0, n = j; p[i][j].who != -p[i][n - 1].who && n - 1 > 5 && x < 4; x++, n--)//左
				{ }
				if (x < 4)
				{
					v2 = 0;
				}
				else
				{
					for (k = 0, n = j; p[i][j].who == p[i][n - 1].who && k < 4; k++, n--)
					{
						v2 *= V;
					}
				}for (x = 0, n = i; p[i][j].who != -p[n-1][j].who && n - 1 > 5 && x < 4; x++, n--)//上
				{
				}
				if (x < 4)
				{
					v3= 0;
				}
				else
				{
					for (k = 0, n = i; p[i][j].who == p[n-1][j].who && k < 4; k++, n--)
					{
						v3 *= V;
					}
				}for (x = 0, n = i; p[i][j].who != -p[n+1][j].who && n +1<20 && x < 4; x++, n++)//下
				{
				}
				if (x < 4)
				{
					v4 = 0;
				}
				else
				{
					for (k = 0, n = i; p[i][j].who == p[n+1][j].who && k < 4; k++, n++)
					{
						v4 *= V;
					}
				}for (x = 0, m=i,n=j; p[i][j].who != -p[m-1][n - 1].who && n - 1 > 5 &&m-1>5&& x < 4; x++, m--,n--)//左上
				{
				}
				if (x < 4)
				{
					v5 = 0;
				}
				else
				{
					for (k = 0, m=i,n = j; p[i][j].who == p[m-1][n - 1].who && k < 4; k++,m--, n--)
					{
						v5 *= V;
					}
				}for (x = 0,m=i, n = j; p[i][j].who != -p[m+1][n - 1].who && n - 1 > 5&&m+1<20 && x < 4; x++,m++, n--)//左下
				{
				}
				if (x < 4)
				{
					v6 = 0;
				}
				else
				{
					for (k = 0,m=i, n = j; p[i][j].who == p[m+1][n - 1].who && k < 4; k++,m++, n--)
					{
						v6 *= V;
					}
				}for (x = 0,m=i, n = j; p[i][j].who != -p[m-1][n + 1].who && n +1<20 &&m-1>5&& x < 4; x++, m--,n++)//右上
				{
				}
				if (x < 4)
				{
					v7 = 0;
				}
				else
				{
					for (k = 0,m=i, n = j; p[i][j].who == p[m-1][n + 1].who && k < 4; k++, m--,n++)
					{
						v7 *= V;
					}
				}for (x = 0,m=i, n = j; p[i][j].who != -p[m+1][n + 1].who && n +1<20&&m+1<20 && x < 4; x++, n++,m++)//右下
				{
				}
				if (x < 4)
				{
					v8 = 0;
				}
				else
				{
					for (k = 0,m=i, n = j; p[i][j].who == p[m+1][n + 1].who && k < 4; k++, m++,n++)
					{
						v8 *= V;
					}
				}
				p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));//各个方向的分数加上中心优势分
				if (p[i][j].who == -1)
				{
					p[i][j].value = -p[i][j].value * defence;//
				}
			}
		}
	}
}
//递归
double deduction(struct point p[25][25], int sex, int depth, long double a, long double b)
{
	int m, n, i, j, t = 0, br = 0;
	long double va = 0;
	if (depth == 0 || end(p) != 0)//达到预定深度或棋局结束
	{
		return wholeass(p);
	}
	else if (sex % 2 == 1)//玩家回合
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1)//b剪枝
			{
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].who == 0)//该点没棋
				{
					if (num < 100)
					{
						t = 0;
						for (i = -1; i <= 1; i++)
						{
							for (j = -1; j <= 1; j++)
							{
								if (p[i + m][j + n] .who!= 0)
								{
									t++;//除去偏僻点
								}

							}
						}
					}
					else t = 1;
					if (t == 0)
					{
						va = B;
					}
					else
					{
						p[m][n].who = -1;//下在这里
						if (first == 2 && prevent(p, m, n) == 3)	va = A;
						else va = deduction(p, sex + 1, depth - 1, a, b);
						p[m][n].who = 0;//撤回
					}
					if (va < b)
					{
						b = va;//玩家要的是最小的得分
					}
					if (b < a)
					{
						br = 1;
						break;//b剪枝
					}
				}
			}
		}
		return b;//返回得分
	}
	else if (sex % 2 == 0)//电脑回合
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1)
			{
				break;//a剪枝
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].who == 0)
				{
					if (num < 100)
					{
						t = 0;
						for (i = -1; i <= 1; i++)
						{
							for (j = -1; j <= 1; j++)
							{
								if (p[i + m][j + n] .who!= 0)
								{
									t++;//除去偏僻点
								}

							}
						}
					}
					else t = 1;
					if (t == 0)
					{
						va = A;
					}
					else
					{
						p[m][n].who = 1;
						va = deduction(p, sex + 1, depth - 1, a, b);
						p[m][n].who = 0;
					}
					if (va > a)
					{
						a = va;//电脑要找最大得分
					}
					if (b < a)
					{
						br = 1;
						break;//a剪枝
					}
				}
			}
		}
		return a;//返回分数
	}
	return 0;
}

int robot(struct point p[25][25])
{
	int i, j, x = 12, y = 12, m, n, t = 0;
	long double v = -9999999999;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			if (p[i][j].who == 0)
			{
				t = 0;
				for (m = -1; m <= 1; m++)
				{
					for (n = -1; n <= 1; n++)
					{
						if (p[i + m][j + n].who != 0)
						{
							t++;//除去偏僻点
						}

					}
				}
				if (t != 0)//不偏僻
				{
					p[i][j].who = 1;
					if (end(p) == 1)
					{
						execute(p, i, j);//最后一步棋
						return 0;
					}
					p[i][j].prevalue = deduction(p, 1, 3, A, B);
					p[i][j].who = 0;//撤回
					if (p[i][j].prevalue > v)
					{
						v = p[i][j].prevalue;//找最大值
						x = i; y = j;//获取相应坐标
					}
				}
			}
		}
	}
	execute(p, x, y);//下棋
	return 0;
}

int main()
{
	loadimage(&pan, _T("res/pan.png"), 750, 750);
	point p[25][25];//棋盘大小15*15 边界为5
	initialize(p);
	begin(p);
	return 0;
}