#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "win.h"
#include "board.h"

// Checks if someone has won or if it is a tie game
bool is_game_over(char** board, int num_rows, int num_cols, int num_in_a_row, char blank_char){
	return someone_won(board, num_rows, num_cols, num_in_a_row, blank_char) || tie(board, num_rows, num_cols, num_in_a_row, blank_char);
}

//Checks if someone won veritcally, horizontally, or diagonally
bool someone_won(char** board, int num_rows, int num_cols, int num_in_a_row, char blank_char){
	return someone_won_vertically(board, num_rows, num_in_a_row, blank_char) ||
	someone_won_horizontally(board, num_rows, num_cols, num_in_a_row, blank_char) ||
	someone_won_diagonally(board, num_rows, num_cols, num_in_a_row, blank_char);
}

// Check each row to see if there are the desired number of peices in a row
bool someone_won_horizontally(char** board, int num_rows, int num_cols, int num_in_a_row, char blank_char){
	for(int i = 0; i < num_rows; ++i){
		if(board[i][0] != blank_char && all_same(board[i], num_cols, num_in_a_row)){
			printf("Won horizontally\n");
            return true;
		}
	}
	return false;
}

// Gets each column and checks if there are the desired number of pieces in a row
bool someone_won_vertically(char** board, int num_rows, int num_in_a_row, char blank_char){
	for(int i = 0; i < num_rows; ++i){
		char* col = get_column(board, num_rows, i);
		if(col[0] != blank_char && all_same(col, num_rows, num_in_a_row)){
			free(col);
            printf("Won vertically\n");
			return true;
		}
		free(col);
	}
	return false;
}

// Checks if someone won on the left or right diagonal
bool someone_won_diagonally(char** board, int num_rows, int num_cols, int num_in_a_row, char blank_char){
	return someone_won_left_diagonally(board, num_rows, num_cols, blank_char) ||
	 	   someone_won_right_diagonally(board, num_rows, num_cols);
}

// Checks if the pieces on the left diagonal is the same as the top left piece
bool is_left_diagonal_same(char** board, int num_rows, char blank_char){
    for(int i = 0; i < num_rows; ++i){
            if(board[i][i] != board[0][0] || board[i][i] == blank_char){
                return false;
            }
        }   
    return true;
}

// Checks each col to see if a left diagonal starts on any columns
bool someone_won_left_diagonally(char** board, int num_rows, int num_cols, char blank_char){
    for(int j = 0; j < (num_cols); ++j){
        if(is_left_diagonal_same(board, num_rows, blank_char)){
            printf("won left diagonally\n");
            return true;
        }
    }
    return false;
}

// Checks if the pieces on the right diagonal is the same as the top right piece
bool is_right_diagonal_same(char** board, int num_rows, int num_cols){
    for(int i = 0; i < num_rows; ++i){
        if(board[i][num_cols - i - 1] != board[0][num_cols - 1]){
            return false;
        }
    }
    return true;
}

// Checks each col to see if a right diagonal starts on any columns
bool someone_won_right_diagonally(char** board, int num_rows, int num_cols){
    for(int j = 0; j < (num_cols); ++j){
        if(is_right_diagonal_same(board, num_rows, num_cols)){
            printf("won right diagonally\n");
            return true;
        }
    }
    return false;
}

// Checks if someone won, or all of the spaces on the board are taken
bool tie(char** board, int num_rows, int num_cols, int num_in_a_row, char blank_char){
	if(someone_won(board, num_rows, num_cols, num_in_a_row, blank_char)){
		return false;
	}
	for(int i = 0; i < num_rows; ++i){ //for each row
		for(int j = 0; j < num_cols; ++j) //for each column/ for each piece in the row
			if(board[i][j] == blank_char){
				return false;
			}
	}
	return true;
}