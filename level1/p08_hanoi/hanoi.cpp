#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void hanoi(int n, char A, char B, char C)
{
	if (n == 1)
	{
		printf("%c -> %c\n", A, C);
	}
	else {
		hanoi(n - 1, A, C, B);
		printf("%c -> %c\n", A, C);
		hanoi(n - 1, B, A, C);
	}
}
int main(int argc, char const* argv[])
{
	hanoi(64, 'A', 'B', 'C');
}
