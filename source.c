//Main Source file
//Code by: Noah Blount (n_blount@u.pacific.edu)
//ASCII Art courtesy of https://www.asciiart.eu/


//Including header files
#include<stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "headers.h"


int main()
{

//Declaring parameter variables [!!!---THESE MUST COME FIRST---!!!]
int board_rows = 9;
int board_columns = 9;
int allowed_input_size = 5;
//--------------------------------------------------------------------------

//Declaring mutable variables to be used later in the program
int asterisk = 0;
int row_count = 0;
int col_count = 0;
int unsolved = 0;
int quit = 0;
int win = 0;
int loss = 0;
int temp_col = 0;
int temp_row = 0;
int temp_val = 0;
char tempFileChar;
//--------------------------------------------------------------------------

//Declaring arrays & creating array of sudoku values
char file_name[50];
char user_input[allowed_input_size];
struct sud_num **values = malloc(board_rows * sizeof(struct sud_num *));
for(int i = 0; i < board_rows; i++)
{
	values[i] = malloc(board_columns * sizeof(struct sud_num));
}
//---------------------------------------------------------------------------


//Inputting game file
printf("SUDOKU GAME\n\nRules: Fill the 9x9 square such that each row, column,\nor block contains all of the numbers 1-9\n\nEnter game filename to load: ");
scanf("%s", file_name);

//Loading game file
FILE *ptr_sud_file;
ptr_sud_file =fopen(file_name,"r");


while (!ptr_sud_file) //Verifying the file exists
{
	printf("Error loading file.\nPlease try again.\nEnter game filename to load: ");
	scanf("%s", file_name);
	ptr_sud_file =fopen(file_name,"r");
}

//Loading file into array
printf("Loading game file %s", file_name);
while (!feof(ptr_sud_file))
{
	tempFileChar = (char)fgetc(ptr_sud_file);
	if(tempFileChar == '*') //Checking if next value should be displayed or not
	{
		asterisk = 1;
	}
	if(isdigit(tempFileChar))//Loading values from file into array
	{
		if (asterisk) //Displaying value on board
		{
			values[row_count][col_count].val=atoi(&tempFileChar);
			values[row_count][col_count].sol_val=atoi(&tempFileChar);
			values[row_count][col_count].bool_visible = 1;
			values[row_count][col_count].bool_given = 1;
			asterisk = 0;
			
		}
		else//Hiding value on board
		{
		values[row_count][col_count].sol_val=atoi(&tempFileChar); 
		values[row_count][col_count].val=0;
		values[row_count][col_count].bool_visible = 0;
		values[row_count][col_count].bool_given = 0;
		unsolved += 1;
		}
		if (col_count == 8)
		{ //Incrementing array index values
			col_count = 0;
			row_count += 1;
		}
		else
		{
			col_count += 1;
		}
	}

}
fclose(ptr_sud_file); //Closing file to prevent memory leaks

//First print of game state
printf("\nGame file %s sucsessfuly loaded\n", file_name);

do
{
	printf("\nCurrent puzzle has %i unsolved items\n\n\n", unsolved);
	print_board(board_rows, board_columns, quit, values);
	printf("\nEnter row #, column #, and desired value to solve a square, or -1 to exit program: ");
	scanf(" %s", user_input);
	for(int i = 0; i < allowed_input_size; i++)
	{
		if(user_input[i] == '-')
		{
			quit = 1;
			break;
		}//Program will exit when user inputs negative number, such as -1
		if(isdigit(user_input[i]) && temp_col != 0)
		{
			temp_val = user_input[i] - '0';
		}
		else if(isdigit(user_input[i]) && temp_row != 0)
		{
			temp_col = user_input[i] - '0';
		}
		else if(isdigit(user_input[i]))
		{
			temp_row = user_input[i] - '0';
		}
	}
	if(quit == 0)
	{
		temp_row -= 1;
		temp_col -= 1;
		if(temp_row == -1)//Input non numerical
		{
			printf("\nNo values entered.");
		}
		else if(temp_row >= 9 || temp_col >=9)//Row or column out of bounds
		{
			printf("\nInvalid row or column");
		}
		else if(values[temp_row][temp_col].bool_given == 1)//Attempt to change given value
		{
			printf("\nCannot change initial condition values");
		}
		else
		{
			values[temp_row][temp_col].val = temp_val;
			if(values[temp_row][temp_col].bool_visible == 0)
			{
				values[temp_row][temp_col].bool_visible = 1;
				unsolved -= 1;
			}
		}
		temp_row = 0;
		temp_col = 0;
		temp_val = 0;
		if(unsolved == 0 && valid_solution(board_rows, board_columns, values))//Exiting game if user wins
		{
			win = 1;
		}
		else if(unsolved == 0)
		{
			loss = 1;
		}
	}
}while(quit == 0 && win == 0 && loss == 0);

//Displaying different text depending on EOP condition
if (quit == 1)
{
	printf("\nExiting game immediately by user command\nIntended solution for this puzzle:\n\n");
	print_board(board_rows, board_columns, quit, values); //Displaying solution after user exit
}
if (loss == 1)
{
	printf("\nGame finished\nSorry, user solution is invalid\nIntended solution for this puzzle:\n\n");
	print_board(board_rows, board_columns, quit, values); //Displaying solution after loss
}
if(win == 1)
{
	printf("\n\n\n                                   .''.\n       .''.      .        *''*    :_\\/_:     .\n      :_\\/_:   _\\(/_  .:.*_\\/_*   : /\\ :  .'.:.'.\n  .''.: /\\ :    /)\\   ':'* /\\ *  : '..'.  -=:o:=-\n :_\\/_:'.:::.  | ' *''*    * '.\'/.'_\\(/_ '.':'.'\n : /\\ : :::::  =  *_\\/_*     -= o =- /)\\     '  *\n  '..'  ':::' === * /\\ *     .'/.\'.  ' ._____\n      *        |   *..*         :       |.   |' .---'|\n        *      |     _           .--'|  ||   | _|    |\n        *      |  .-'|       __  |   |  |    ||      |\n     .-----.   |  |' |  ||  |  | |   |  |    ||      |\n ___'       ' /'\\ |  '-."".    '-'   '-.'    '`      |____\njgs~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n  &                    ~-~-~-~-~-~-~-~-~-~   /|\n ejm97    )      ~-~-~-~-~-~-~-~  /|~       /_|\n        _-H-__  -~-~-~-~-~-~     /_|\\    -~======-~\n~-\\XXXXXXXXXX/~     ~-~-~-~     /__|_\\ ~-~-~-~\n~-~-~-~-~-~    ~-~~-~-~-~-~    ========  ~-~-~-~\n      ~-~~-~-~-~-~-~-~-~-~-~-~-~ ~-~~-~-~-~-~\n                        ~-~~-~-~-~-~\n\nCongratulations, you found the solution!\nOne solution for this puzzle:\n\n");
	print_board(board_rows, board_columns, win, values); //Displaying solution after user solution, along with a little celabratory ASCII art courtesy of https://www.asciiart.eu/
}


//Clearing the array of board values to prevent memory leaks
for(int i = 0; i < board_rows; i++)
{
	free(values[i]);
}
free(values);

//EOP
return 0;
}



