#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct list {
	int data;
	struct list* next;
	int num;
}crelist;
void printList(struct list* headNode)
{
	struct list* Pmove = headNode->next;
	while (Pmove)
	{
		printf("%d ", Pmove->data);
		Pmove = Pmove->next;
	}
	printf("\n");

}void searlist(crelist* head, int goal);

crelist* revlist(crelist* head)
{
	crelist* cur = head;
	crelist* pree=NULL;
	crelist* pre = NULL,*temp;
	int remakenum=1;
	while (cur)
	{
		temp = cur->next;
		cur->next = pre;
		pre = cur;
		cur = temp;
	}pree = pre;
	for (pre; pre; pre = pre->next)
	{
		pre->num = remakenum++;
	}
	return pree;
}
int main(int argc, char const* argv[])
{
	int a = 1;
	crelist* head=NULL;
	crelist* last;
	int number;
	do {
		crelist *p = (crelist*)malloc(sizeof(list));
		scanf("%d", &number);
		
			p->data = number;
			p->next = NULL;
			p->num = a++;

		
		last = head;
		if (last != NULL)
		{
			while (last->next)
			{
				last = last->next;
			}
			last->next = p;

		}
		else head = p;

	} while (number!=114);
	head=revlist(head);
	searlist(head, 5);
	return 0;

}
void searlist(crelist* head, int goal)
{
	crelist* p; int found=0;
	for (p = head; p; p = p->next)
	{
		if (p->data == goal)
		{
			printf("%d\n", p->num);
			found = 1;
			break;

		}
	}if (found == 0)printf("-1\n");
	p=p->next;
	for (; p; p = p->next)
	{
		if (p->data == goal)
		{
			printf("%d\n", p->num);
			found = 2;
			break;

		}
	}
	if (found !=2)printf("-1\n");
	
}
