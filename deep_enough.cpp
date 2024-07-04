#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <cmath>

#include "hfiles/board.h"
#include "hfiles/deep_enough.h"

bool DEEP_ENOUGH(board state, int depth){

    if(depth == 1){ // Have 2 ply been generated?
        return true;
    }
    if(state.positions[4] != 0){
        if(state.positions[3] + state.positions[4] + state.positions[5] == -3){
            return true;
        }
        if(state.positions[1] + state.positions[4] + state.positions[7] == -3){
            return true;
        }
        if(state.positions[0] + state.positions[4] + state.positions[8] == -3){
            return true;
        }
        if(state.positions[2] + state.positions[4] + state.positions[6] == -3){
            return true;
        }
    }
    if(state.positions[0] != 0){
        if(state.positions[0] + state.positions[1] + state.positions[2] == -3){
            return true;
        }
        if(state.positions[0] + state.positions[3] + state.positions[6] == -3){
            return true;
        }
    }
    if(state.positions[8] != 0){
        if(state.positions[8] + state.positions[5] + state.positions[2] == -3){
            return true;
        }
        if(state.positions[8] + state.positions[7] + state.positions[6] == -3){
            return true;
        }
    }

    if(state.positions[4] != 0){
        if(state.positions[3] + state.positions[4] + state.positions[5] == int(abs(3))){
            return true;
        }
        if(state.positions[1] + state.positions[4] + state.positions[7] == int(abs(3))){
            return true;
        }
        if(state.positions[0] + state.positions[4] + state.positions[8] == int(abs(3))){
            return true;
        }
        if(state.positions[2] + state.positions[4] + state.positions[6] == int(abs(3))){
            return true;
        }
    }
    if(state.positions[0] != 0){
        if(state.positions[0] + state.positions[1] + state.positions[2] == int(abs(3))){
            return true;
        }
        if(state.positions[0] + state.positions[3] + state.positions[6] == int(abs(3))){
            return true;
        }
    }
    if(state.positions[8] != 0){
        if(state.positions[8] + state.positions[5] + state.positions[2] == int(abs(3))){
            return true;
        }
        if(state.positions[8] + state.positions[7] + state.positions[6] == int(abs(3))){
            return true;
        }
    }

    int i = 0;
    while(i < 9){
        if(state.positions[i] == 0){
            return false;
        }
        i++;
    }

    return true; // 
}
