#include<graphics.h>
#include<Windows.h>
#include <math.h>
#include<time.h>
#include<easyx.h>
#include<stdio.h>
IMAGE hei, bai, pan;
#define defence 2//���ز���
#define V 10//�����÷ֺ����ӱ���
long double A = -99999999;//������Сֵ
long double B = -A;//��С�����ֵ
#define MIN 5
#define MAX 20
#define dep 3
int num = 0;//����
int first=1;//˭����1���		2����
struct point
{
	int who;//�õ��״̬  0�� 1���� -1���
	long double value;//�õ�Ŀǰ�÷�
	long double prevalue;//��һ�����ڸõ�ĵ÷�
};
typedef struct Step
{
	int x;
	int y;
}step;
step step1[120];//��ҵ�ÿһ��
step step2[120];//���Ե�ÿһ��
step ste[3][120];
void board();//�滭����
void initialize(struct point p[25][25]);//��ʼ�����̣������̹���
void begin(point p[25][25]);//����
int robot(struct point p[25][25]);//��������
void ass(struct point p[25][25]);//����һ��ĵ÷�
double wholeass(struct point p[25][25]);//��������Ŀǰ�ĵ÷�
double deduction(struct point p[25][25], int sex, int depth, long double a, long double b,int robot_time);//��Ҫ�ļ��㺯��������Сֵ����֦
int end(struct point p[25][25]);//����
void over(int a);
void execute(point p[25][25], int x, int y);
void regret(point p[25][25],int num);
int prevent(point p[25][25],int x,int y);//����
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
int end(struct point p[25][25])//�õ�ʤ��
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
					e = 1;//ƽ��
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
					if (p[i][j].who == 1)	e = 2;//���lose
					else if (p[i][j].who == -1)	e=3;//���win

				}
			}
			
		}
	}
	return e;//��eΪ0��û����
}
void board()
{
	char i=1, j=1;
	initgraph(1000, 850);//��ʼ����ͼ����
	setbkcolor(BLACK);//����Ϊ��
	cleardevice();//�õ�ǰ����ɫ�����һ����ͼ
	putimage(50, 50, &pan);
	settextcolor(WHITE);
	settextstyle(20, 0, _T("����"));
	/*for (; i <= 15; i++)
	{
		char a[20];
		sprintf_s(a, "%d", i);
		outtextxy(20, i*50, (LPCTSTR)(a));
	}*/
	outtextxy(20,  (i++) * 50-5,_T("1")); outtextxy(20,  (i++) * 50-5, _T("2")); outtextxy(20, (i++) * 50-5, _T("3")); outtextxy(20,  (i++) * 50-5, _T("4")); outtextxy(20, (i++) * 50-5, _T("5")); outtextxy(20, (i++) * 50-5, _T("6")); outtextxy(20,(i++) * 50-5, _T("7")); outtextxy(20, (i++) * 50-5, _T("8")); outtextxy(20,(i++) * 50-5, _T("9")); outtextxy(20,(i++) * 50-5, _T("10")); outtextxy(20,(i++) * 50-5, _T("11")); outtextxy(20,(i++) * 50-5, _T("12")); outtextxy(20,(i++) * 50-5, _T("13")); outtextxy(20, (i++) * 50-5, _T("14")); outtextxy(20,(i++) * 50-5, _T("15")); outtextxy(20, (i++) * 50 - 5, _T("16"));
	outtextxy(-5 + (j++) * 50, 820, _T("1")); outtextxy(-5 + (j++) * 50, 820, _T("2")); outtextxy(-5 + (j++) * 50, 820, _T("3")); outtextxy(-5 + (j++) * 50, 820, _T("4")); outtextxy(-5 + (j++) * 50, 820, _T("5")); outtextxy(-5 + (j++) * 50, 820, _T("6")); outtextxy(-5 + (j++) * 50, 820, _T("7")); outtextxy(-5 + (j++) * 50, 820, _T("8")); outtextxy(-5 + (j++) * 50, 820, _T("9")); outtextxy(-5 + (j++) * 50, 820, _T("10")); outtextxy(-5 + (j++) * 50, 820, _T("11")); outtextxy(-5 + (j++) * 50, 820, _T("12")); outtextxy(-5 + (j++) * 50, 820, _T("13")); outtextxy(-5 + (j++) * 50, 820, _T("14")); outtextxy(-5 + (j++) * 50, 820, _T("15")); outtextxy(-5 + (j++) * 50, 820, _T("16"));
	settextstyle(40, 0, _T("����"));
	outtextxy(820, 200, _T("�� ��"));
	outtextxy(820, 500,_T("�� ��"));
	outtextxy(820, 400, _T("�� ��"));
	outtextxy(820, 300, _T("�� ��"));
}
void execute(struct point p[25][25], int x, int y)//�������
{
	setfillcolor(WHITE);
	fillcircle((x + 1 - MIN) * 50, (y + 1 - MIN) * 50, 20);
	p[x][y].who = 1;
	ste[2][num].x = x;
	ste[2][num].y = y;
}
//����
void regret(point p[25][25],int num)
{
	board();
	setrop2(R2_COPYPEN);  //���û�����ɫ
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
int prevent(point p[25][25], int x,int y)//���� ���յ�˭�������һ���������
{
	int count=0;
	int det = 0;//��firstתΪ��Ӧ��ҵ��Ե�-1��1  first1 ���			first2 ����
	if (first == 1)	det = -1;
	if (first == 2)	det = 1;
	if (p[x - 1][y].who == det && p[x - 2][y].who == det && p[x + 1][y].who != -det && p[x - 3][y].who != -det)	count++;//�ϻ���
	if (p[x + 1][y].who == det && p[x + 2][y].who == det && p[x - 1][y].who != -det && p[x +3][y].who != -det)	count++;//�»���
	if (p[x][y - 1].who == det && p[x ][y- 2].who == det && p[x ][y+ 1].who != -det && p[x ][y-3].who != -det)	count++;//�����
	if (p[x][y + 1].who == det && p[x][y + 2].who == det && p[x][y - 1].who != -det && p[x][y + 3].who != -det)	count++;//�һ���
	if (p[x + 1][y - 1].who == det && p[x + 2][y - 2].who == det && p[x - 1][y + 1].who != -det && p[x + 3][y - 3].who != -det)	count++;//���»���
	if (p[x - 1][y - 1].who == det && p[x - 2][y - 2].who == det && p[x + 1][y + 1].who != -det && p[x - 3][y - 3].who != -det)	count++;//���ϻ���
	if (p[x - 1][y + 1].who == det && p[x - 2][y + 2].who == det && p[x + 1][y - 1].who != -det && p[x - 3][y + 3].who != -det)	count++;//���ϻ���
	if (p[x + 1][y + 1].who == det && p[x + 2][y + 2].who == det && p[x - 1][y - 1].who != -det && p[x + 3][y + 3].who != -det)	count++;//���»���
	if (count == 2)
	{
		if (first == 1)	return 2;//�����
		if (first == 2) return 3;//������
	}

	
}
void begin(point p[25][25])//���֣�Ĭ��������֣�
{
	MOUSEMSG m;//mouse
	int x, y, i, j,count=0;//ij�ֱ�Ϊ�����ĺ�������
	board();
	setlinecolor(WHITE);

	while (1)
	{
		m = GetMouseMsg();//��ȡ���λ��
		x = m.x % 50;
		y = m.y % 50;
		setrop2(R2_COPYPEN);
		if (m.uMsg == WM_LBUTTONDOWN)//�������
		{
			if (m.x <= 900 && m.y<550 && m.x>820 && m.y > 500)//�˳�
			{
				closegraph();//�رջ�ͼ����
				exit(0);//ǿ���˳�
			}
			if (m.x <= 900 && m.y < 450 && m.x>820 && m.y > 400)//regret
			{
				num--;
				regret(p,num);
				continue;
			}
			if (m.x > 820 && m.x <= 900 && m.y > 300 && m.y < 350)//�ؿ�
			{
				initialize(p);
				begin(p);
			}
			if (m.x > 820 && m.x <= 900 && m.y > 200 && m.y < 250&&count==0)//����
			{
				first = 2;
				robot(p);
				count = 1;
			}
			if (x >= 25)	m.x = m.x - x + 50;
			else m.x = m.x - x;
			if (y >= 25)	m.y = m.y - y + 50;
			else m.y = m.y - y;//�����λ�ö������̵ĵ���
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
					over(2);//��������
				}
				if (end(p) != 0)//�ж��Ƿ����
				{
					Sleep(1000);
					over(end(p));//��������
				}
				robot(p);
				if (end(p) != 0)//�ж��Ƿ����
				{
					Sleep(1000);
					over(end(p));//��������
				}
				num++;
			/*char num[50];
			sprintf_s(num, " % d", step);
			settextcolor(WHITE);
			settextstyle(40, 0, _T("����"));
			outtextxy(800, 400, num[50]);*/
			}
		}
		
	}
}
//��������
void over(int a)
{
	point pp[25][25];       //  5--19	
	initialize(pp);      //��ʼ��
	initgraph(400, 400);
	cleardevice();     //ʹ�õ�ǰ����ɫ��ջ�ͼ�豸
	settextstyle(50, 24, _T("����"));
	settextcolor(RED);    //������ɫ
	if (a == 1)
	{
		outtextxy(100, 50, _T("ƽ��") );
	}
	else if (a == 2)
	{
		outtextxy(100, 50, _T("���Ի�ʤ"));
	}
	else if (a == 3)
	{
		outtextxy(100, 50, _T("��Ӯ����"));
	}
	settextcolor(WHITE);
	outtextxy(50, 200, _T("������Ϸ����") );
	outtextxy(80, 300, _T(" ������Ϸ"));

	while (true)
	{
		MOUSEMSG n;//�����Ϣ
		n = GetMouseMsg();
		switch (n.uMsg) {
		case WM_LBUTTONDOWN:
			if (n.x <= 350 && n.x >= 50 && n.y <= 250 && n.y >= 200)
				begin(pp);   //������Ϸ����
			if (n.x <= 300 && n.x >= 80 && n.y <= 350 && n.y >= 300)
			{
				closegraph(); // �رջ�ͼ����
				exit(0);    //ǿ���˳�
			}
		}
	}
}
//�ܾ�������
double wholeass(struct point p[25][25])
{
	int i, j;
	ass(p);
	long double wholevalue = 0;
	for (i = MIN; i < MAX; i++)
	{
		for (j = MIN; j < MAX; j++)
		{
			wholevalue += p[i][j].value;//�ܵ÷�
		}
	}return wholevalue;
}
//ĳ���ֵ����
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
				for (x = 0, n = j; p[i][j].who != -p[i][n + 1].who && n + 1 < 20 && x < 4; x++, n++)//��
				{ }
				if (x < 4)
				{
					v1 = 0;//����סΪ0
				}
				else
				{
					for (k = 0, n = j; p[i][j].who == p[i][n + 1].who && k < 4; k++, n++)
					{
						v1 *= V;
					}
				}
				for (x = 0, n = j; p[i][j].who != -p[i][n - 1].who && n - 1 > 5 && x < 4; x++, n--)//��
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
				}for (x = 0, n = i; p[i][j].who != -p[n-1][j].who && n - 1 > 5 && x < 4; x++, n--)//��
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
				}for (x = 0, n = i; p[i][j].who != -p[n+1][j].who && n +1<20 && x < 4; x++, n++)//��
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
				}for (x = 0, m=i,n=j; p[i][j].who != -p[m-1][n - 1].who && n - 1 > 5 &&m-1>5&& x < 4; x++, m--,n--)//����
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
				}for (x = 0,m=i, n = j; p[i][j].who != -p[m+1][n - 1].who && n - 1 > 5&&m+1<20 && x < 4; x++,m++, n--)//����
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
				}for (x = 0,m=i, n = j; p[i][j].who != -p[m-1][n + 1].who && n +1<20 &&m-1>5&& x < 4; x++, m--,n++)//����
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
				}for (x = 0,m=i, n = j; p[i][j].who != -p[m+1][n + 1].who && n +1<20&&m+1<20 && x < 4; x++, n++,m++)//����
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
				p[i][j].value = v1 + v2 + v3 + v4 + v5 + v6 + v7 + v8 + 0.1 * (15 - abs(i - 12) - abs(j - 12));//��������ķ��������������Ʒ�
				if (p[i][j].who == -1)
				{
					p[i][j].value = -p[i][j].value * defence;//
				}
			}
		}
	}
}
//�ݹ�
double deduction(struct point p[25][25], int sex, int depth, long double a, long double b)
{
	int m, n, i, j, t = 0, br = 0;
	long double va = 0;
	if (depth == 0 || end(p) != 0)//�ﵽԤ����Ȼ���ֽ���
	{
		return wholeass(p);
	}
	else if (sex % 2 == 1)//��һغ�
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1)//b��֦
			{
				break;
			}
			for (n = MIN; n < MAX; n++)
			{
				if (p[m][n].who == 0)//�õ�û��
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
									t++;//��ȥƫƧ��
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
						p[m][n].who = -1;//��������
						if (first == 2 && prevent(p, m, n) == 3)	va = A;
						else va = deduction(p, sex + 1, depth - 1, a, b);
						p[m][n].who = 0;//����
					}
					if (va < b)
					{
						b = va;//���Ҫ������С�ĵ÷�
					}
					if (b < a)
					{
						br = 1;
						break;//b��֦
					}
				}
			}
		}
		return b;//���ص÷�
	}
	else if (sex % 2 == 0)//���Իغ�
	{
		for (m = MIN; m < MAX; m++)
		{
			if (br == 1)
			{
				break;//a��֦
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
									t++;//��ȥƫƧ��
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
						a = va;//����Ҫ�����÷�
					}
					if (b < a)
					{
						br = 1;
						break;//a��֦
					}
				}
			}
		}
		return a;//���ط���
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
							t++;//��ȥƫƧ��
						}

					}
				}
				if (t != 0)//��ƫƧ
				{
					p[i][j].who = 1;
					if (end(p) == 1)
					{
						execute(p, i, j);//���һ����
						return 0;
					}
					p[i][j].prevalue = deduction(p, 1, 3, A, B);
					p[i][j].who = 0;//����
					if (p[i][j].prevalue > v)
					{
						v = p[i][j].prevalue;//�����ֵ
						x = i; y = j;//��ȡ��Ӧ����
					}
				}
			}
		}
	}
	execute(p, x, y);//����
	return 0;
}

int main()
{
	loadimage(&pan, _T("res/pan.png"), 750, 750);
	point p[25][25];//���̴�С15*15 �߽�Ϊ5
	initialize(p);
	begin(p);
	return 0;
}