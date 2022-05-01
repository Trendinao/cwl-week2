#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matrix(char **p_matrix, int p_row, int p_column);

int main(){
	//input matrix's row and column
	int i = 0, j = 0;
	int row = 0, column = 0;
	printf("enter the matrix row and column\n");
	scanf("%d %d", &row, &column);
	
	//assign the memory for matrix and set the mat