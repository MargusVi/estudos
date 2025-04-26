//Marcos, 23/10/2022

#include <stdio.h>

int main(void){
	int miles = 26, yards = 385;
	double kilometers;
	
	kilometers = 1.609 * (miles + yards / 1760.0);
	printf("A marathon is %lf kilometers.\n", kilometers);
	return 0;
}
