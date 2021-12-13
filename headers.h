//Main Header file
//Code by: Noah Blount (n_blount@u.pacific.edu)

#ifndef HEADERS
#define HEADERS

//Creating a struct for sudoku numbers
struct sud_num
{
int bool_visible;
int val;
int sol_val;
int bool_given;
};

void print_board(int rows, int columns, int quit, struct sud_num **board_array);
int valid_solution(int rows, int columns, struct sud_num **board_array);

//I know this is extra but my eyes hurt looking at all the white text so I added this to make it easier for me
void red(); //Sets text to red

void green(); //Sets text to green

void reset(); //Resets text to default color

#endif
