#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "hfiles/board.h"
#include "hfiles/movegen.h"
using namespace std;

int* MOVEGEN(board state, string player){

    static int possible_moves[10]; // DETERMINE WHOSE TURN, NUM OF POSSIBLE MOVES
    int player_id = 0;
    if(player == "MAX") {
        player_id = 1;
    }
    else {
        player_id = -1;
    }
    int i = 0;

    for (int idx = 0; idx < 9; idx++){ // GENERATE IDX'S OF OPEN SQAURES
        if(state.positions[idx] == 0){
            possible_moves[i + 1] = idx;
            i++;
        }
    }
    possible_moves[0] = i; // STORE MOVE COUNT AND POSSIBLE MOVE IDX'S HERE

    static int possible_boards[82]; // GENERATE EACH POSSIBLE BOARD STATE PER POSSIBLE MOVE
    int possible_move_num = possible_moves[0];
    possible_boards[0] = possible_move_num;
    i = 1;
    int array_idx = 1;
    int this_board[9];
    int this_move;
    while(i <= possible_move_num){

        for(int inner_idx = 0; inner_idx < 9; inner_idx++){ // DUPLICATE POSITION
            this_board[inner_idx] = state.positions[inner_idx];
        }
        this_move = possible_moves[i];
        this_board[this_move] = player_id; // PLAY POSSIBLE MOVE ON DUPLICATE BOARD

        // ADD DUPLICATE BOARD WITH MOVE TO possible_boards[]
        for(int idx = 0; idx < 9; idx++){
            possible_boards[array_idx] = this_board[idx];
            array_idx++;
        }

        i++; // WE HAVE PROCESSED ONE MOVE, NEXT
    }

    int* possible_moves_ptr = possible_boards;
    return possible_moves_ptr; 
    // Returns a POINTER. possible_moves[0] is the total num of possible moves.
    // Everything after is sqaures the player can play in.
}
