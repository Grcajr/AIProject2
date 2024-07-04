#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "hfiles/evaluations.h"
#include "hfiles/board.h"
using namespace std;

const int wins[8][3] = {
  { 0, 1, 2 },
  { 3, 4, 5 },
  { 6, 7, 8 },
  { 0, 3, 6 },
  { 1, 4, 7 },
  { 2, 5, 8 },
  { 0, 4, 8 },
  { 2, 4, 6 }
};

const int HeuristicArr[4][4] = {
  {     0,   -10,  -100, -1000 },
  {    10,     0,     0,     0 },
  {   100,     0,     0,     0 },
  {  1000,     0,     0,     0 }
};
// TODO: Create 4 full evaluation functions to feed the minimax search.

int EVALUATION(board state, string player, int METHOD){ // Implementing the given Evaluation function
    int player_id;
    int opposite_id;
    if(player == "MAX") { // Whose turn is it?
        player_id = 1;
        opposite_id = -1;
    }
    else if(player == "MIN") {
        player_id = -1;
        opposite_id = 1;
    }

    if(METHOD == 1){
        int VALUE = 0;
        int WINNING = 0;
        int LOSING = 0;

        // Check lines the given player could still possibly get a win.
        if(state.positions[0] != opposite_id && state.positions[1] != opposite_id && state.positions[2]  != opposite_id) {WINNING++;} 
        if(state.positions[0] != opposite_id && state.positions[3] != opposite_id && state.positions[6]  != opposite_id) {WINNING++;}
        if((state.positions[3] != opposite_id) && (state.positions[4] != opposite_id) && (state.positions[5]  != opposite_id)) {WINNING++;}
        if((state.positions[6] != opposite_id) && (state.positions[7] != opposite_id) && (state.positions[8]  != opposite_id)) {WINNING++;}
        if((state.positions[1] != opposite_id) && (state.positions[4] != opposite_id) && (state.positions[7]  != opposite_id)) {WINNING++;}
        if((state.positions[2] != opposite_id) && (state.positions[5] != opposite_id) && (state.positions[8]  != opposite_id)) {WINNING++;}
        if((state.positions[0] != opposite_id) && (state.positions[4] != opposite_id) && (state.positions[8]  != opposite_id)) {WINNING++;}
        if((state.positions[2] != opposite_id) && (state.positions[4] != opposite_id) && (state.positions[6]  != opposite_id)) {WINNING++;}
        // Check lines the opposing player could still possibly get a win.
        if(state.positions[0] != player_id && (state.positions[1] != player_id) && (state.positions[2]  != player_id)) {LOSING++;} 
        if((state.positions[0] != player_id) && (state.positions[3] != player_id) && (state.positions[6]  != player_id)) {LOSING++;}
        if((state.positions[3] != player_id) && (state.positions[4] != player_id) && (state.positions[5]  != player_id)) {LOSING++;}
        if((state.positions[6] != player_id) && (state.positions[7] != player_id) && (state.positions[8]  != player_id)) {LOSING++;}
        if((state.positions[1] != player_id) && (state.positions[4] != player_id) && (state.positions[7]  != player_id)) {LOSING++;}
        if((state.positions[2] != player_id) && (state.positions[5] != player_id) && (state.positions[8]  != player_id)) {LOSING++;}
        if((state.positions[0] != player_id) && (state.positions[4] != player_id) && (state.positions[8]  != player_id)) {LOSING++;}
        if((state.positions[2] != player_id) && (state.positions[4] != player_id) && (state.positions[6]  != player_id)) {LOSING++;}

        VALUE = WINNING - LOSING; // Evaluate the state based on possible winning lines.
        return VALUE;
    }

    else if(METHOD == 2){
        int VALUE = 0; 
        int i,j=0;
        for (i = 0; i < 8; i++)  {
            int players = 0;
            int others = 0;
            for (j = 0; j < 3; j++)  {
                int seed = state.positions[wins[i][j]];
                if(player == "MAX" && seed == 1)
                    players++;
                else if(player == "MAX" && seed == -1)
                    others++;
                if(player == "MIN" && seed == -1)
                    players++;
                else if (player == "MIN" && seed == 1)
                    others++;
            }
            VALUE += HeuristicArr[players][others];
        }
        return VALUE;
    }

    else if(METHOD == 3){
        int VALUE = 0;
        if (state.positions[4] == player_id) {
            VALUE += 3;
        }

        int corners[4] = {0,2,6,8}; // Indexes of Corners
        for (int i = 0; i < 4; i++) {
            if(state.positions[corners[i]] == player_id){
                VALUE += 2;
            }
            else if(state.positions[corners[i]] == 0){
                VALUE += 1;
            }
        }
        return VALUE;
    }

    else if(METHOD == 4){
        int VALUE = 0; 
        if(state.positions[4] == player_id) { // Center Control
            VALUE += 5;
        }
        else if(state.positions[4] == opposite_id) {
            VALUE -= 5;
        }
        int corners[4] = {0,2,6,8}; // Corner Control
        for (int i = 0; i < 4; i++) {
            if(state.positions[corners[i]] == player_id){
                VALUE += 3;
            }
            else if(state.positions[corners[i]] == opposite_id){
                VALUE -= 3;
            }
        }
        int mids[4] = {1,3,5,7}; // Remaining Squares
        for (int i = 0; i < 4; i++) {
            if(state.positions[mids[i]] == player_id){
                VALUE += 1;
            }
            else if(state.positions[mids[i]] == opposite_id){
                VALUE -= 1;
            }
        }

        int i,j=0;
        for (i = 0; i < 8; i++)  {
            int players = 0;
            int others = 0;
            for (j = 0; j < 3; j++)  {
                int seed = state.positions[wins[i][j]];
                if(player == "MAX" && seed == 1)
                    players++;
                else if(player == "MAX" && seed == -1)
                    others++;
                if(player == "MIN" && seed == -1)
                    players++;
                else if (player == "MIN" && seed == 1)
                    others++;
            }
            VALUE += HeuristicArr[players][others];
        }

        return VALUE;
    }
    return 0;
}

void display_board(board state) {
    char positions[9];
    string this_boardoard;
    for(int i = 0; i < 9; i++){
        if(state.positions[i] == 1){
            positions[i] = 'X';
        }
        else if(state.positions[i] == -1){
            positions[i] = 'O';
        }
        else{
            positions[i] = '_';
        }
    }
    for(int i = 0; i < 9; i++){
        cout << positions[i];
        if(i == 8){
            cout << "\n\n";
        }
        else if((i+1)%3==0){
            cout << "\n----------\n";
        }
        else {
            cout << " | ";
        }
    }
}
