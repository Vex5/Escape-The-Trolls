#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <windows.h>
#include "Troll.h"

Troll::Troll(){
    _coords = make_pair(-1, -1);
}

Troll::Troll(int startX, int startY){
    _coords = make_pair(startX, startY);
}

void Troll::SetCoordsEqualTo(int coordX, int coordY){
    _coords = make_pair(coordX, coordY);
}

void Troll::SetCoordsEqualToPair(pair<int, int> newCoords){
    _coords = newCoords;
}
