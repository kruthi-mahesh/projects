#include<stdio.h>
#include<stdlib.h>
#define size 100

void main()
{
	FILE *fptr;
	fptr = fopen("sample.txt", "w+");
	
	int A[size][size], B[size][size], C[size][size], i, j, k;

//random inputs for the array 
	for(i=0; i<size ; i++)
	{
		for(j=0; j<size ; j++)
		{
			A[i][j] = random()%10;
			B[i][j] = random()%10;
			C[i][j] = 0;
		}
	}

//writing addresses of the statement into the file
	for(i=0; i<size; i++)
	{
		for(j=0; j<size; j++)
		{
			for(k=0; k<size; k++)
			{
//				C[i][j] += A[i][k]*B[k][j];
				fprintf(fptr, "%llx\n", &A[i][k]);
				fprintf(fptr, "%llx\n", &B[k][j]);
				fprintf(fptr, "%llx\n", &C[i][j]);				
			}
		}
	}
}