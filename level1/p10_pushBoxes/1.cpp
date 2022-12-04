
#include <stdio.h>  
#include <conio.h>
#include<stdlib.h> 
#pragma warning(disable:4996);

int map[11][11];

//���Ƶ�ͼ  //��ά����+switch()
int step, score;
void DrawMap()
{
    //������ά����  //0 ��ӡ�ո�  //1 ǽ   //3 Ŀ�ĵ�  //ʲô�ṹ?
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            //if  else  switch
            switch (map[i][j])
            {
            case 0:
                printf("  ");
                break;
            case 1:
                printf("��");
                break;

            case 3:
                printf("��");
                break;
            case 4:
                printf("��");
                break;
            case 5:
                printf("��");  //5��
                break;
            case 7:     //4 + 3  ������Ŀ�ĵ���
                printf("��");
                break;
            case 8:     // 5 + 3  ����Ŀ�ĵص���   ��?
                printf("��");
                break;
            }
        }
        printf("\n");
    }
}


void PlayGame()
{
    int r, c;  //�˵��±�  //
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (map[i][j] == 5 || map[i][j] == 8)  
            {
                r = i;
                c = j;
            }
        }
    }

    char ch; 
    ch = getch();  
    
    switch (ch)
    {
    case 'W':  
    case 'w':
    case 72:
        if (map[r - 1][c] == 0 || map[r - 1][c] == 3)
        {
            map[r - 1][c] += 5;
            map[r][c] -= 5;
        }
        else if (map[r - 1][c] == 4 || map[r - 1][c] == 7)
        {
            if (map[r - 2][c] == 0 || map[r - 2][c] == 3)
            {
                map[r - 2][c] += 4;
                map[r - 1][c] += 1;
                map[r][c] -= 5;
            }
        }
        break;

    case 'S':  
    case 's':
    case 80:
        if (map[r + 1][c] == 0 || map[r + 1][c] == 3)
        {
            map[r + 1][c] += 5;
            map[r][c] -= 5;
        }
        else if (map[r + 1][c] == 4 || map[r + 1][c] == 7)
        {
            if (map[r + 2][c] == 0 || map[r + 2][c] == 3)
            {
                map[r + 2][c] += 4;
                map[r + 1][c] += 1;
                map[r][c] -= 5;
            }
        }
        break;

    case 'A':
    case 'a':
    case 75:
        if (map[r][c - 1] == 0 || map[r][c - 1] == 3)
        {
            map[r][c - 1] += 5;
            map[r][c] -= 5;
        }
        else if (map[r][c - 1] == 4 || map[r][c - 1] == 7)
        {
            if (map[r][c - 2] == 0 || map[r][c - 2] == 3)
            {
                map[r][c - 2] += 4;
                map[r][c - 1] += 1;
                map[r][c] -= 5;
            }
        }
        break;

    case 'D':
    case 'd':
    case 77:
        if (map[r][c + 1] == 0 || map[r][c + 1] == 3)
        {
            map[r][c + 1] += 5;
            map[r][c] -= 5;
        }
        else if (map[r][c + 1] == 4 || map[r][c + 1] == 7)
        {
            if (map[r][c + 2] == 0 || map[r][c + 2] == 3)
            {
                map[r][c + 2] += 4;
                map[r][c + 1] += 1;
                map[r][c] -= 5;
            }
        }
        break;
    }
}

int end()
{
    int count=0;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if (map[i][j] == 4) count++;
        }
    }return count;
}
int main()  
{
    FILE* fp;
    fp = fopen("D:\\125126.txt", "r+");
    //��ֵ��ͼ
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            
            fscanf(fp, "%d", &map[i][j]);
        }
    }
    int step = 1;
    int score = 200;
    do
    {
        system("cls");
        DrawMap();
        step++; 
        score--;
        printf("%d %d",step ,score); 
        PlayGame();
       
    } while (end());
    system("cls");
    DrawMap();
    printf("��Ϸ��ʤ");
    fclose(fp);
    return 0;
}


