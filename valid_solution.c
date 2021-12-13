//Valid Solution function
//Code by: Noah Blount (n_blount@u.pacific.edu)

#include<stdio.h>
#include "headers.h"


int valid_solution(int rows, int columns, struct sud_num **board_array)
{
	int valid = 1;
	int add_val;
	int diff;
	for(int i = 0; i < rows; i++) //Checking each row
	{
		add_val = 0;
		diff = 0;
		for(int j = 0; j < columns; j++)
		{
			add_val += (board_array[i][j]).val;
		}
		for(int k = 1; k < columns; k++)
		{
			if((board_array[i][k]).val == (board_array[i][(k - 1)]).val)
			{
				diff = 1;
			}
		}
		if(add_val != 45 || diff)
		{
			valid = 0;
		}
	}
	for(int i = 0; i < columns; i++) //Checking each column
	{
		add_val = 0;
		diff = 0;
		for(int j = 0; j < rows; j++)
		{
			add_val += (board_array[j][i]).val;
		}
		for(int k = 1; k < rows; k++)
		{
			if((board_array[k][i]).val == (board_array[(k - 1)][i]).val)
			{
				diff = 1;
			}
		}
		if(add_val != 45 || diff)
		{
			valid = 0;
		}
	}
	for(int i = 0; i < rows; i += 3)//Checking each square
	{
		for(int j = 0; j < columns; j += 3)
		{
			add_val = 0;
			diff = 0;
			
			for(int k = 0; k < (rows/3); k++)
			{
				for(int l = 0; l < (columns/3); l++)
				{
					add_val += (board_array[(k+i)][(l+j)]).val;
				}
				for(int m = 1; m < (columns/3); m++)
				{
					if((board_array[(k+i)][(m+j)]).val == (board_array[(k+i)][((m+j) - 1)]).val)
					{
						diff = 1;
					}
				}
			}
			if(add_val != 45 || diff)
			{
				valid = 0;
			}
		}
	}
	return valid;
}
