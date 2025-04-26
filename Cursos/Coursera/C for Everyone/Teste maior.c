#include<stdio.h>

int main()
{
	int array[40] = {27, 31, 35, 3, 6, 10, 39, 16, 20, 24, 26, 29, 33, 1, 4, 8, 37, 14, 18, 22, 38, 30, 34, 2, 5, 9, 12, 15, 19, 23, 28, 32, 36, 40, 7, 11, 13, 17, 21, 25};
	
	int i, maior = array[0];
	printf("Maior = %d\n", maior);
	for(i = 0; i < 40; i++)
	{
		if(maior < array[i + 1])
		{
			maior = array[i + 1];
			printf("Maior = %d\n", maior);
		}
	}
	
	return 0;
}
