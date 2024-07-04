#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <tuple>

#include "hfiles/board.h"
#include "hfiles/minimax.h"
#include "hfiles/movegen.h"
#include "hfiles/opposite_player.h"
#include "hfiles/deep_enough.h"
#include "hfiles/evaluations.h"

using namespace std;

// TODO: Any time this function selects a move we need to print it. This function recurses.

tuple<int, board, int> MINI_MAX_A_B(board state, int depth, string player, int use_thresh, int pass_thresh, int method1, int method2, int expanded){ // Return the optimal move

    // Function Vars
    int VALUE;
    int NEW_VALUE;
    board PATH;
    board BEST_PATH;
    board RESULT_SUCC;
    // ----------------

    // IMPLEMENTATION
    // --------------
    if(DEEP_ENOUGH(state, depth) == true){
        VALUE = EVALUATION(state, player, method1);
        return make_tuple(VALUE, state, expanded);
    }
    // Else, SUCCESSORS = MOVEGEN(position, player);
    int* ptr;
    ptr = MOVEGEN(state, player);
    int idx = 0;
    int possible_moves;
    possible_moves = ptr[idx];
    int read_in_test[82];
    int curr_sqaure = 0;
    board this_board;
    list<board> SUCCESSORS;
    for(int i = 1; i < (possible_moves*9)+1; i++){
        this_board.positions[curr_sqaure] = ptr[i];
        if(i % 9 == 0){
            curr_sqaure = 0;
            SUCCESSORS.push_back(this_board);
            int this_board[9] = {0,0,0,0,0,0,0,0,0};
        }
        else{
            curr_sqaure++;
        }
    }

    // If SUCCESSORS.isempty(), no moves can be made, return structure as above
    if(SUCCESSORS.empty() == true) {
        VALUE = EVALUATION(state, player, method1);
        return make_tuple(VALUE, state, expanded);
    }

    // Else, for SUCC in SUCCESSORS:
    for(const auto& SUCC : SUCCESSORS){
        RESULT_SUCC = get<1>(MINI_MAX_A_B(SUCC, depth + 1, OPPOSITE_PLAYER(player), -pass_thresh, -use_thresh, method1, method2, expanded));
        VALUE = get<0>(MINI_MAX_A_B(SUCC, depth + 1, OPPOSITE_PLAYER(player), -pass_thresh, -use_thresh, method1, method2, expanded));
        expanded += 1;
        NEW_VALUE = -VALUE;
        if (NEW_VALUE > pass_thresh){
            pass_thresh = NEW_VALUE;
            BEST_PATH = RESULT_SUCC;
        }
        if (pass_thresh >= use_thresh) {
            return make_tuple(pass_thresh, BEST_PATH, expanded);
        }
    }

    return make_tuple(pass_thresh, BEST_PATH, expanded);
};
