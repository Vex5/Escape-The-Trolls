#include <iostream>
#include <cstdio>
#include <conio.h>
#include <queue>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <utility>
#include <windows.h>
#include "Maze.h"
#include "Troll.h"

using namespace std;

template<typename T>
auto GetRandomNumber(T from, T to) -> decltype(from){
    T rnd = rand() % to + from;
    return rnd;
}

template<typename T>
void PrintMatrix(vector<vector<T>> matrix){
    for(int i = 0; i < matrix.size(); i++){
        for(int j = 0; j < matrix[i].size(); j++){
            cout << matrix[i][j];
        }
    cout << "\n";
    }
}

vector<vector<int>> GetHCMatrix(){
    vector<vector<int>> matrix({
        {1,0,3,0,2},
        {0,0,0,0,0},
        {2,0,5,0,4},
        {0,0,0,0,0},
        {1,0,2,0,4}
    });
    return matrix;

}

vector<vector<int>> GetRandomMatrix(int from, int to){
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

int main()
{
    srand(time(NULL));
    int w, h, numOfTrolls;
    cout <<"Upisite sirinu i duzinu labirinta: ";
    cin >> w >> h;
    cout << "Unesite broj trollova: ";
    cin >> numOfTrolls;
    Maze maze(w, h, numOfTrolls);
    maze.Print();
    maze.PrintPlayerInfo();

    while(1){
        char key = 127;

        key = _getch();

        if (key == 0 || key == -32)
        {
            key = _getch();

            if (key == 72)
            {
                key = 'u';
                maze.UpdatePlayerPosition(maze.GetPlayer().GetXCoord()-1, maze.GetPlayer().GetYCoord());
            }
            else if (key == 75)
            {
                key = 'l';
                maze.UpdatePlayerPosition(maze.GetPlayer().GetXCoord(), maze.GetPlayer().GetYCoord()-1);
            }
            else if (key == 77)
            {
                key = 'r';
                maze.UpdatePlayerPosition(maze.GetPlayer().GetXCoord(), maze.GetPlayer().GetYCoord()+1);
            }
            else if (key == 80)
            {
                key = 'd';
                maze.UpdatePlayerPosition(maze.GetPlayer().GetXCoord()+1, maze.GetPlayer().GetYCoord());
            }
            maze.Print();
        }
   }

    return 0;
}
