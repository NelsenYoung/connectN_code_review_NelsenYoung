#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "board.h"


// Dynamically allocates a 2d array of chars
char** create_empty_board(int num_rows, int num_cols, char blank_char){
	char** board = (char**)calloc(num_rows, sizeof(char*));
	for(int i = 0; i < num_rows; ++i){
		board[i] = (char*)calloc(num_cols, sizeof(char));
		for(int j = 0; j < num_cols; ++j){
			board[i][j] = blank_char;
		}
	}
	return board;
}

// Prints the board
void print_board(char** board, int num_rows, int num_cols){
	//print the column headers
	printf("  ");
	for(int i = 0; i < num_rows; ++i){
		printf("%d ", i);
	}
	printf("\n");

	//print the boards contents
	for(int i = 0; i < num_rows; ++i){
		printf("%d ", i);
		for(int j = 0; j < num_cols; ++j){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

// Deletes the board
void delete_board(char** board, int num_rows){
	for(int i = 0 ; i < num_rows; ++i){
		free(board[i]);
	}
	free(board);
}

// Checks how far the pieces needes to drop, then places the piece at that location
void place_piece(char piece, char** board, int col, int numRows, char blankChar){
    for(int i = 0; i < numRows; ++i){
        if(board[numRows - (i + 1)][col] == blankChar){
            board[numRows - (i + 1)][col] = piece;
            i = numRows;
        }
    }
}

// Checks if the move is with the bounds of the board
bool move_is_on_board(int num_rows, int num_cols, int row, int col){
	return is_between(row, 0, num_rows - 1) &&
	       is_between(col, 0, num_cols - 1);
}

// Checks if a given value is inbetween the bounds
bool is_between(int value, int min_val, int max_val){
	return value >= min_val && value <= max_val;
}

// Checks if the are the desired number of pieces in a row, given row or col
bool all_same(char* values, int len, int num_needed){
    char start_char = values[0];
    int num_in_a_row = 1;
	for(int i = 1; i < len; ++i){
        if(num_in_a_row >= num_needed){
            return true;

        }else if(values[i] != start_char){
            start_char = values[i];
            num_in_a_row = 1;
		}
        num_in_a_row += 1;
	}
	return false;
}

// Gets column on the board given a certain col
char* get_column(char** board, int num_rows, int col){
	char* the_column = (char*)calloc(num_rows, sizeof(char));
	for(int i = 0; i < num_rows; ++i){
		the_column[i] = board[i][col];
	}
	return the_column;
}