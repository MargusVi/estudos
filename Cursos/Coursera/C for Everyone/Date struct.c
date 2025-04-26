//Marcos, January 9th, 2023

#include<stdio.h>
#include<stdlib.h>

typedef enum month{Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec}Month; //Enum with all months

typedef struct date //Struct with the month and date
{
	Month m;
	int d;
}Date;

void switchmonth(Date d) //Function to printf the month
{
	switch(d.m)
	{
		case 0: printf("January, "); break;
		case 1: printf("February, "); break;
		case 2: printf("March, "); break;
		case 3: printf("April, "); break;
		case 4: printf("May, "); break;
		case 5: printf("June, "); break;
		case 6: printf("July, "); break;
		case 7: printf("August, "); break;
		case 8: printf("September, "); break;
		case 9: printf("October, "); break;
		case 10: printf("November, "); break;
		case 11: printf("December, "); break;
	}
}

int nextday(Date d) //Function to print the next date, and change the month if necessary
{
	if(d.m == 1 && d.d == 28) //If the date is february 28, then next day is march 1
	{
		d.d = 1;
		d.m++;
		printdate(d);
		printf("\n");
	}
	//If the date is a month with 31 days and the day is 31, then next day is 1 from next month
	else if(d.m == 0 && d.d == 31 || d.m == 2 && d.d == 31 || d.m == 4 && d.d == 31 || d.m == 6 && d.d == 31 || d.m == 7 && d.d == 31 || d.m == 9 && d.d == 31)
	{
		d.d = 1;
		d.m++;
		printdate(d);
		printf("\n");
	}
	//If the date is a month with 30 days and the day is 31, then next day is 1 from next month
	else if(d.m == 3 && d.d == 30 || d.m == 5 && d.d == 30 || d.m == 8 && d.d == 30 || d.m == 10 && d.d == 30)
	{
		d.d = 1;
		d.m++;
		printdate(d);
		printf("\n");
	}
	//If the date is december 31, then next day is january 1
	else if(d.m == 11 && d.d == 31)
	{
		d.d = 1;
		d.m = 1;
		printdate(d);
		printf("\n");
	}
	else
	{
		d.d++;
		printdate(d);
		printf("\n");
	}
}

int printdate(Date d) //Function to print the date
{
	switchmonth(d);
	printf("%d\n", d.d);
}

int main()
{
	Date d;
	
	d.m = 1;
	d.d = 28;
	
	printdate(d);
	nextday(d);
	
	d.m = 2;
	d.d = 14;
	
	printdate(d);
	nextday(d);
	
	d.m = 9;
	d.d = 31;
	
	printdate(d);
	nextday(d);
	
	d.m = 11;
	d.d = 31;
	
	printdate(d);
	nextday(d);
	
	return 0;
}
