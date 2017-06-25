#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <windows.h>
#include "Player.h"

using namespace std;

Player::Player(){
    _coords = make_pair(-1, -1);
}

Player::Player(int startX, int startY){
    _coords = make_pair(startX, startY);
}

void Player::SetCoordsEqualTo(int coordX, int coordY){
    _coords = make_pair(coordX, coordY);
}

void Player::SetCoordsEqualToPair(pair<int, int> newCoords){
    _coords = newCoords;
}

void Player::PrintInfo(){
    cout << "Health: " << _healthPoints << endl;
    cout << "Attack: " << _attackDamage << endl;
    cout << "X: " << _coords.second << " Y: " << _coords.first << endl;
}
