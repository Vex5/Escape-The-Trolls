#pragma once
#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <windows.h>
#include "Troll.h"
#include "Player.h"

using namespace std;

class Maze : public Troll{

    int _height, _width;

    struct Element{
        pair<int, int> coord;
        int weight;
        Element(int x, int y, int w){
            weight = w;
            coord.first = x;
            coord.second = y;
        }
    };

    vector<vector<char>> _GeneratedMaze;
    vector<Troll> _trolls;
    Player _player;

    void AddTrolls();
    void AddPlayer();
    void AddBorders(vector<vector<char>> &matrix);
    void Generate();
    void PrintMatrix(vector<vector<char>> matrix);
    vector<vector<int>> GetRandomMatrix(int from, int to);

    public:
        Maze(int width, int height, int numOfTrolls) : _height(height), _width(width), _trolls(numOfTrolls) {Generate();}
        vector<vector<char>> Get2DVectorFormat(){ return _GeneratedMaze; }
        void Print();
        void Print(vector<vector<char>> maze);

        void PrintPlayerInfo();
        void UpdatePlayerPosition(int newX, int newY);
        void MovePlayer(int newX, int newY);

        Player GetPlayer(){ return _player; };

        template<typename T>
        friend auto GetRandomNumber(T from, T to) -> decltype(from);
};
