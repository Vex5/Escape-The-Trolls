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

class Player{

    pair<int,int> _coords;

    int _healthPoints = 5;
    int _attackDamage = 1;

    void SetCoordsEqualTo(int coordX, int coordY);
    void SetCoordsEqualToPair(pair<int, int> coords);

    public:
        Player();
        Player(int startX, int startY) ;
        void PrintInfo();
        int GetXCoord(){ return _coords.first; }
        int GetYCoord(){ return _coords.second; }
        pair<int, int> GetCoords(){ return _coords; }
        void SetXCoord(int coordX){ SetCoordsEqualTo(coordX, _coords.second); }
        void SetYCoord(int coordY){ SetCoordsEqualTo(_coords.first, coordY); }
        void SetCoordsPair(pair<int, int> coords){ SetCoordsEqualToPair(coords); }
        void SetCoords(int coordX, int coordY){ SetCoordsEqualTo(coordX, coordY); }
};
