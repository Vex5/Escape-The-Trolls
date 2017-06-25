#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <windows.h>

using namespace std;

class Troll{

    pair<int,int> _coords;
    int _healthPoints = 1;
    int _attackDamage = 1;

    void SetCoordsEqualTo(int coordX, int coordY);
    void SetCoordsEqualToPair(pair<int, int> coords);

    public:
        Troll();
        Troll(int startX, int startY) ;
        int GetXCoord(){ return _coords.first; }
        int GetYCoord(){ return _coords.second; }
        pair<int, int> GetCoordsPair(){ return _coords; }
        void SetXCoord(int coordX){ SetCoordsEqualTo(coordX, _coords.second); }
        void SetYCoord(int coordY){ SetCoordsEqualTo(_coords.first, coordY); }
        void SetCoordsPair(pair<int, int> coords){ SetCoordsEqualToPair(coords); }
        void SetCoords(int coordX, int coordY){ SetCoordsEqualTo(coordX, coordY); }
};
