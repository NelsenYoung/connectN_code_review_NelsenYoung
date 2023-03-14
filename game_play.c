#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game_play.h"
#include "board.h"
#include "win.h"
#include "input_validation.h"

int get_starting_player_turn(){
	return 0; //0 means player 1, 1 means player 2
}

// Set the player pieces to X and O
char* get_player_pieces(){
	char* player_pieces = (char*)calloc(3, sizeof(char));
	strcpy(player_pieces, "XO");
	return player_pieces;
}

// Creates the board, gets the starting turn and the player pieces
void setup_game(int num_rows, int num_cols, char blank_char, char** *out_board,
								int *out_starting_player_turn, char* *out_player_pieces){
	char** board = create_empty_board(num_rows, num_cols, blank_char);
	int player_turn = get_starting_player_turn();
	char* player_pieces = get_player_pieces();
	*out_board = board;
	*out_starting_player_turn = player_turn;
	*out_player_pieces = player_pieces;
}

// Gets a move from the player, and places the piece
void cur_player_take_turn(char**board, int num_rows, int num_cols, char blank_char, char cur_player_piece ){
	int col;
    int row = 0;
	print_board(board, num_rows, num_cols);
	get_valid_move_from_player(board, num_rows, num_cols, blank_char, &row, &col);
	place_piece(cur_player_piece, board, col, num_rows, blank_char);
}

// Gets a input from user, and will keep asking if the input is invalid
void get_valid_move_from_player(char** board, int num_rows, int num_cols, char blank_char,
								int *out_row, int*out_col){
	int num_args_read;
	do{
		printf("Enter a move in the form col: ");
		num_args_read = scanf("%d", out_col);
	}while(!is_valid_move(num_args_read, board, num_rows, num_cols, blank_char, *out_row, *out_col));
}


// Checks that the move is on the board, and the col is not full
bool is_valid_move(int num_args_read, char** board, int num_rows, int num_cols, char blank_char, int row, int col){
	const int num_args_needed = 1;
	return isValidFormat(num_args_read, num_args_needed);
					(move_is_on_board(num_rows, num_cols, row, col) &&
                    move_is_on_board(num_rows, num_cols, row, col) &&
					board[row][col] == blank_char);
                    
}

// Changes turns based on which player's turn it is
void change_turns(int* cur_player_turn, int number_of_players){
	*cur_player_turn = (*cur_player_turn + 1 ) % number_of_players;
}

// Checks if the game is over, and announces the result based on the currnt player do
void announce_results(char** board, int num_rows, int num_cols, int num_in_a_row, char blank_char, int cur_player_turn){
	if(someone_won(board, num_rows, num_cols, num_in_a_row, blank_char)){
			if(cur_player_turn == 0){
				printf("Player 1 won the game!\n");
			}else{
				printf("Player 2 won the game!\n");
			}
	}else{
		printf("Tie game\n");
	}

}

// Starts the game, and has both player go until the game has ended
void play_game(char** board, int num_rows, int num_cols, char blank_char, int starting_player_turn,
               int num_in_a_row, char* player_pieces){
	int cur_player_turn = starting_player_turn;
	const int num_players = 2;
	while(true){
		cur_player_take_turn(board, num_rows, num_cols, blank_char, player_pieces[cur_player_turn]);
		if(is_game_over(board, num_rows, num_cols, num_in_a_row, blank_char)){
			break;
		}
		change_turns(&cur_player_turn, num_players);
	}
	print_board(board, num_rows, num_cols);
	announce_results(board, num_rows, num_cols, num_in_a_row, blank_char, cur_player_turn);
}

// deletes the board and frees the pieces
void clean_up(char** board, int num_rows, char* player_pieces){
	delete_board(board, num_rows);
	free(player_pieces);
}