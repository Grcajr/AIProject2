#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "hfiles/opposite_player.h"
using namespace std;

string OPPOSITE_PLAYER(string this_player){
    string new_player;
    if (this_player == "MAX") {
        new_player = "MIN";
        }
    else if (this_player == "MIN") {
        new_player = "MAX";
        }
    else {
        cout << "OPPOSITE() experienced an error...";
        new_player = this_player;
    }
    return new_player;
}
