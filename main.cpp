#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>
#include <chrono>

#include "hfiles/board.h"
#include "hfiles/minimax.h"
#include "hfiles/deep_enough.h"
#include "hfiles/opposite_player.h"
#include "hfiles/evaluations.h"

using namespace std;

int main(){
    int EVAL_MAX = 120000; // THESE DEPEND ON THE EVAL FUNCTION
    int EVAL_MIN = -120000; 
    int method1 = 0;
    int method2 = 0;
    string input = "0";
    int temp = 0;
    int expanded = 0;
    string player = "MAX";

    cout << "Select Evaluation Method for Xs (1-4): ";
    cin >> input;
    while((input != "1") && (input != "2") && (input != "3") && (input != "4")) {
        cout << "Invalid Input. Please enter a number 1 through 4 for Xs: ";
        cin >> input;
    }
    method1 = stoi(input);
    cout << "Select Evaluation Method for Os (1-4): ";
    cin >> input;
    while((input != "1") && (input != "2") && (input != "3") && (input != "4")) {
        cout << "Invalid Input. Please enter a number 1 through 4 for Os: ";
        cin >> input;
    }
    method2 = stoi(input);
    cout << "You have selected evaluation function " << method1 << " for Xs.\n";
    cout << "You have selected evaluation function " << method2 << " for Os\n";

    auto start = chrono::high_resolution_clock::now(); // Start clock
    
    board position; // BLANK BOARD STATE FOR NEW GAME
    for(int i = 0; i < 9; i++){
        position.positions[i] = 0;
    }
    
    int moves_left = 9;
    bool game_over = DEEP_ENOUGH(position, 0);
    while(game_over == false){
        position = get<1>(MINI_MAX_A_B(position, 0, player, EVAL_MAX, EVAL_MIN, method1, method2, expanded));
        expanded = expanded + (moves_left*(moves_left-1));
        cout << "\n";
        display_board(position);

        player = OPPOSITE_PLAYER(player);
        temp = method1;
        method1 = method2;
        method2 = temp;

        game_over = DEEP_ENOUGH(position, 0);
    }
    auto end = chrono::high_resolution_clock::now();
    double execution_time = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    cout << "Execution Time: " << execution_time / (1 * 10^6) << " milliseconds.\n";
    cout << "Expanded Nodes: " << expanded << "\n\n";

    return 0;
}
