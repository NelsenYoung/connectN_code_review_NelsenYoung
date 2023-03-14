#include "game_play.h"
#include <stdio.h>

/*
This program will run connect n by taking in the number of columns,
number of rows, and the number of pieces in a row needed to win
*/

int main(int argc, char** argv){
    if(argc != 4){
        //exit(0);
    }
    int num_rows;
    sscanf(argv[1], "%d", &num_rows);

    int num_cols;
    sscanf(argv[2], "%d", &num_cols);

    int num_in_a_row;
    sscanf(argv[3], "%d", &num_in_a_row);

	char blank_char = '*';
	char** board;
	char* player_pieces;
	int player_turn;
	setup_game(num_rows, num_cols, blank_char, &board, & player_turn, &player_pieces);
	play_game(board, num_rows, num_cols, blank_char, player_turn, num_in_a_row, player_pieces);
	clean_up(board, num_rows, player_pieces);
	return 0;
}