//Marcos, November 24, 2022

#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *myFile;
    myFile = fopen("elephant_seal_data.txt", "r"); //Open the file
    
    int array[1000];
    int i, sum, average, totalNum = 0;

    if (myFile == NULL) //Confirm if the file is empty
	{
        printf("Error Reading File\n");
        exit (0);
    }

    for (i = 0; i < 1000; i++) //Read the numbers in the file into an array
	{
        fscanf(myFile, "%d,", &array[i]);
    }

	fclose(myFile);

    for (i = 0; i < 1000; i++) //Sum all the numbers and count how many were summed
	{
        sum += array[i];
        totalNum++;
    }
    
    average = sum / totalNum; //Compute the average
    
    printf("The average is %d.\n", average);

    return 0;
}
