#include <iostream>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <windows.h>
#include <stdexcept>
#include "Maze.h"
#include "Troll.h"

using namespace std;

void Maze::PrintMatrix(vector<vector<char>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j];
        }
    cout << "\n";
    }
}

vector<vector<int>> Maze::GetRandomMatrix(int from, int to){
    int rows(from);
    int cols(to);
    const int lowerBoundRand(2), upperBoundRand(20);
    vector<vector<int>> matrix(rows, vector<int>(cols,0));
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            if(i%2==0 && j%2==0) matrix[i][j] = GetRandomNumber(lowerBoundRand, upperBoundRand);
            else matrix[i][j] = 0;
        }
    }
    return matrix;
}

void Maze::Generate(){

    vector<vector<int>> matrix=GetRandomMatrix(_height, _width);

    vector<vector<char>> finalMaze(matrix.size(), vector<char>(matrix[0].size(), '*'));
    vector<vector<bool>> visited(matrix.size(), vector<bool>(matrix[0].size(), false));

    const int moves(4);
    int cols[moves]={2, 0, -2, 0};
    int rows[moves]={0, 2, 0, -2};

    auto cmp = [](Element left, Element right) { return left.weight > right.weight;};

    priority_queue<Element, vector<Element>, decltype(cmp)> pq(cmp);

    pq.push(Element(0,0,0));
    while(!pq.empty()){
        //cout << "----------- GENERATING MAZE -----------\n";
        int coordX = pq.top().coord.first;
        int coordY = pq.top().coord.second;
        pq.pop();
        visited[coordX][coordY] = true;
        matrix[coordX][coordY] = 1;
        finalMaze[coordX][coordY] = 'O';
        for(int i = 0; i < moves; i++){
            int nextRow = coordX+rows[i];
            int nextCol = coordY+cols[i];
            if(nextCol < 0 || nextRow < 0 || nextCol > matrix[0].size()-1 || nextRow > matrix.size()-1) continue;
            if(!visited[nextRow][nextCol]){
                Element e(nextRow, nextCol, matrix[nextRow][nextCol]);
                pq.push(e);
            }
        }
        int nextLowCoordX(pq.top().coord.first);
        int nextLowCoordY(pq.top().coord.second);
        if(coordX == nextLowCoordX && (coordY - nextLowCoordY == abs(1))){
            if(nextLowCoordY > coordY){ matrix[nextLowCoordX][nextLowCoordY-1] = 1; finalMaze[nextLowCoordX][nextLowCoordY-1] = 'O'; }
            else{ matrix[nextLowCoordX][nextLowCoordY+1] = 1; finalMaze[nextLowCoordX][nextLowCoordY+1] = 'O'; }
        }
        else if(coordY == nextLowCoordY && (coordX - nextLowCoordX == abs(1))){
            if(nextLowCoordX > coordX){ matrix[nextLowCoordX-1][nextLowCoordY] = 1; finalMaze[nextLowCoordX-1][nextLowCoordY] = 'O';}
            else{ matrix[nextLowCoordX+1][nextLowCoordY] = 1; finalMaze[nextLowCoordX+1][nextLowCoordY] = 'O';}
        }
        else{
            for(int i = 0; i < moves; i++){
                int nextRow = coordX+rows[i];
                int nextCol = coordY+cols[i];
                if(nextCol < 0 || nextRow < 0 || nextCol > matrix[0].size()-1 || nextRow > matrix.size()-1) continue;
                if(visited[nextRow][nextCol]){
                    if(coordX == nextRow){
                        if(nextCol > coordY){ matrix[nextRow][nextCol-1] = 1; finalMaze[nextRow][nextCol-1] = 'O';}
                        else{ matrix[nextRow][nextCol+1]=1; finalMaze[nextRow][nextCol+1] = 'O';}
                        break;
                    }
                    else if(coordY == nextCol){
                        if(nextRow > coordX){ matrix[nextRow-1][nextCol] = 1;  finalMaze[nextRow-1][nextCol] = 'O';}
                        else{ matrix[nextRow+1][nextCol]=1;  finalMaze[nextRow+1][nextCol] = 'O';}
                        break;
                    }
                }
            }
        }

        //PrintMatrix(finalMaze);
        //Sleep(500);
       // system("CLS");

    }
    AddBorders(finalMaze);
    _GeneratedMaze = finalMaze;
    AddPlayer();
    AddTrolls();
}

void Maze::AddBorders(vector<vector<char>> &matrix){

    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            if(i == 0) matrix[i][j] = '*';
            if(j == 0) matrix[i][j] = '*';
        }
    }

}

void Maze::AddPlayer(){

    for(int i = 0; i < _GeneratedMaze.size(); i++){
        for(int j = 0; j < _GeneratedMaze[0].size(); j++){
            if(_GeneratedMaze[i][j] == 'O'){
                _GeneratedMaze[i][j] = 'P';
                _player.SetCoords(i, j);
                return;
            }
        }
    }

}

void Maze::AddTrolls(){

    int coordX = GetRandomNumber(0, _height-1);
    int coordY = GetRandomNumber(0, _width-1);
    int i=0;
    while(i!=_trolls.size()){
        if(_GeneratedMaze[coordX][coordY] == 'O'){
            _GeneratedMaze[coordX][coordY] = 'T';
            _trolls[i] = Troll(coordX, coordY);
            i++;
        }
        else{
            coordX = GetRandomNumber(0, _height-1);
            coordY = GetRandomNumber(0, _width-1);
        }
    }
}

void Maze::Print(){

    system("ClS");
    for(int i = 0; i < _height; i++){
        for(int j = 0; j < _width; j++){
            cout << _GeneratedMaze[i][j];
        }
    cout << "\n";
    }

}

void Maze::PrintPlayerInfo(){
    _player.PrintInfo();
}

void Maze::UpdatePlayerPosition(int newX, int newY){

    if(_GeneratedMaze[newX][newY] == 'O') MovePlayer(newX, newY);
    else if(_GeneratedMaze[newX][newY] == 'T') {} //nesto

}

void Maze::MovePlayer(int newX, int newY){

    _GeneratedMaze[_player.GetXCoord()][_player.GetYCoord()] = 'O';
    _player.SetCoords(newX, newY);
    _GeneratedMaze[newX][newY] = 'P';

}
