//Marcos, 23/10/2022

#include <stdio.h>

int main(void){
	float a, b, c, sum;
	printf("Input three floats: ");
	scanf("%f%f%f", &a, &b, &c);
	printf("a = %f, b = %f, c = %f\n", a, b, c);
	sum = a + b + c;
	printf("sum = %f\n\n", sum);
	return 0;
}
