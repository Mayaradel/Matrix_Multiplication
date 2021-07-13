// C Program to multiply two matrix using pthreads without
// use of global variables
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>

int matA[50][50];
int matB[50][50];
int matC[50][50];
int row1, row2, col1, col2 ;
int step_i = 0;


void ReadFile()
{
    FILE *fp = fopen("input.txt","r");
    char temp[50];
    char *token;

    // first matrix
    fgets(temp,50,fp);
    token = strtok(temp," ");
    row1 = atoi(token);
    token = strtok(NULL," ");
    col1 = atoi(token);

    for(int i=0; i<row1; i++)
    {
        fgets(temp,50,fp);
        token = strtok(temp," ");

        for(int j=0; j<col1; j++)
        {
            matA[i][j] =atoi(token);
            token = strtok(NULL," ");
        }

    }
    printf("\n");
    printf("row1 = %d\ncol1 = %d\n",row1,col1);
    printf("\n");
    printMatrix(row1,col1,matA);
    printf("\n");

    //second matrix

    fgets(temp,50,fp);
    token = strtok(temp," ");
    row2 = atoi(token);
    token = strtok(NULL," ");
    col2 = atoi(token);
    for(int i=0; i<row2; i++)
    {
        fgets(temp,50,fp);
        token = strtok(temp," ");
        for(int j=0; j<col2; j++)
        {
            matB[i][j] =atoi(token);
            token = strtok(NULL," ");
        }
    }
    printf("row2 = %d\ncol2 = %d\n",row2,col2);
    printf("\n");
    printMatrix(row2,col2,matB);
    printf("\n");
    fclose(fp);
}

void* multi(void* arg)
{

	// Each thread computes 1/4th of matrix multiplication
	for (int i = step_i; i < step_i+1; i++)
		for (int j = 0; j < col2; j++)
			for (int k = 0; k < row2; k++)
				matC[i][j] += matA[i][k] * matB[k][j];
    step_i++;
}

//print the matrix
void printMatrix(int r,int c,int matrix[50][50])
{
    for(int i=0; i<r; i++)
    {
        for(int j=0; j<c; j++)
        {
            printf("\t %d",matrix[i][j]);
        }
        printf("\n");
    }
}

//Driver code
int main()
{
    ReadFile();

    int i,j,k;
    int resultant_size = row1*col2;

    // declaring number of threads as the number of the result rows
    pthread_t threads[row1];

    printf("Resultant Matrix = \n");

    // Creating number of threads, each evaluating its own part
    for (int i = 0; i < row1; i++)
    {
        int* p;
        pthread_create(&threads[i], NULL, multi, (void*)(p));
    }

    // join the threads
    //print the resultant matrix
    for (int i = 0; i < row1; i++)
        pthread_join(threads[i], NULL);

    printMatrix(row1,col2,matC);

    return 0;
}

