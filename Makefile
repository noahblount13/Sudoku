#Makefile
#Code by Dr. Pallipuram for use by: Noah Blount (n_blount@u.pacific.edu)

# The variable CC specifies which compiler will be used.
# (because different unix systems may use different compilers)
CC=gcc

# The variable CFLAGS specifies compiler options
#   -c :    Only compile (don't link)
#   -Wall:  Enable all warnings about lazy / dangerous C programming 
#  You can add additional options on this same line..
#  WARNING: NEVER REMOVE THE -c FLAG, it is essential to proper operation
CFLAGS=-c -std=c99 -Wall -Wextra

# All of the .h header files to use as dependencies
HEADERS=headers.h

# All of the object files to produce as intermediary work
OBJECTS=source.o print_board.o valid_solution.o red.o green.o reset.o

# The final program to build
EXECUTABLE=sudoku

# --------------------------------------------

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -rf *.o $(EXECUTABLE)
