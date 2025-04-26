//Marcos, 23/10/2022

#include <stdio.h>

int main(void){
	int miles, yards;
	double kilometers;
	
	printf("Enter miles: ");
	scanf("%d", &miles);
	printf("Enter yards: ");
	scanf("%d", &yards);
	kilometers = 1.609 * (miles + yards / 1760.0);
	printf("%d miles and %d yards is %lf kilometers.\n", miles, yards, kilometers);
	return 0;
}
