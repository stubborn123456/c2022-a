#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
typedef struct Good
{
	int num;
	char *name;
}good;
typedef struct Node
{
	good goods;
	struct Node* next, * pre;
}node;

node* head, * tail;
void newnode()
{
	node* pretail = tail;
	if (tail == NULL)
	{
		head = tail = (node*)malloc(sizeof(node));
	}
	else
	{
		tail->next = (node*)malloc(sizeof(node));
		tail = tail->next;
	}
	if (pretail != NULL)
	{
		pretail->next = tail;
	}
	tail->next = NULL;
	tail->pre = pretail;
}

int main()
{

	int option=0,len=0,numgood;
	char namegood[20];
	FILE* fp=fopen("D:\\1.txt", "r");
	while (fscanf(fp,"%s%d",namegood,&numgood) != EOF)//先给字符串赋值避免出错 
	{
		newnode();
		len = strlen(namegood);
		tail->goods.name = (char*)malloc(sizeof(char) * (len+1));
		strcpy(tail->goods.name, namegood);
		tail->goods.num = numgood;
		
	}fclose(fp);
	while (1)
	{
		scanf("%d", &option);
		if (option == 1)
		{
			for (node* p = head; p != NULL; p = p->next)
			{
				printf("%s %d\n",  p->goods.name,p->goods.num);
			}
		}
		else if (option == 2)
		{
			int isfound = 0;
			scanf("%s%d",namegood,&numgood);
			for (node* p = head; p != NULL; p = p->next)
			{
				if (strcmp((*p).goods.name,namegood)==0)
				{
					p->goods.num += numgood;
					isfound=1;
					break;
				}
			}
			if (!isfound)
			{
				newnode();
				len = strlen(namegood) + 1;
				tail->goods.name = (char*)malloc(sizeof(char*) * len);
				strcpy(tail->goods.name, namegood);
				tail->goods.num = numgood;
			}

		}
		else if (option == 3)
		{
			int isfound = 0;
			scanf("%s%d", namegood,&numgood);
			for (node* p = head; p != NULL; p = p->next)
			{
				if (strcmp((*p).goods.name,namegood)==0)
				{
					isfound = 1;
					if (p->goods.num < numgood)
					{
						printf("库存不足，少了%d件%s物品", numgood - p->goods.num,(*p).goods.name);
						break;
					}
					if (p->goods.num == numgood)
					{
						if(p->pre!=NULL)
						{
							p->pre->next=p->next;
						}
						if(p->next!=NULL)
						{
							p->next->pre=p->pre;
						}
						if(p==head)
						{
							head=p->next;
						}
						if(p==tail)
						{
							tail=p->pre;
						}
					}
					p->goods.num -= numgood;
				}
			}
		}
		else break;
	}fp=fopen("D:\\1.txt","w");
		for(node*p=head;p!=NULL;p=p->next)
		{
			fprintf(fp,"%s %d\n",p->goods.name,p->goods.num);
		}
		fclose(fp);
	return 0;

}


