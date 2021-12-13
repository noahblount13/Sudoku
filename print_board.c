//Print board function
//Code by: Noah Blount (n_blount@u.pacific.edu)

#include<stdio.h>
#include "headers.h"

void print_board(int rows, int columns, int quit, struct sud_num **board_array)
{
	printf("     1 2 3   4 5 6   7 8 9\n");
	for (int i = 0; i < rows; i++)
	{
		if (i%3 == 0)
		{
		printf("   |-----------------------|\n");
		}
		printf("%i  ", i+1);
		for (int j = 0; j < columns; j++)
		{
			if (j%3 == 0)
			{
				printf("| ");
			}
			if(quit == 0 && (board_array[i][j]).bool_visible == 0)
			{
				red();
				printf("# ");
				reset();
			}
			else if(quit == 0)
			{
				green();
				printf("%i ", (board_array[i][j]).val);
				reset();
			}
			else
			{
				green();
				printf("%i ", (board_array[i][j]).sol_val);
				reset();
			}
			
		}
		printf("|\n");

	}
	printf("   |-----------------------|\n");
}

