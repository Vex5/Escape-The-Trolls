#include <conio.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
auto GetRandomNumber(T from, T to) -> decltype(from) {
  T rnd = rand() % to + from;
  return rnd;
}

struct Element {
  pair<int, int> coord;
  int weight;
  Element(int x, int y, int w) {
    weight = w;
    coord.first = x;
    coord.second = y;
  }
};

template <typename T>
void PrintMatrix(vector<vector<T> > matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      cout << matrix[i][j];
    }
    cout << "\n";
  }
}

vector<vector<int> > GetHCMatrix() {
  vector<vector<int> > matrix({{1, 0, 3, 0, 2},
                               {0, 0, 0, 0, 0},
                               {2, 0, 5, 0, 4},
                               {0, 0, 0, 0, 0},
                               {1, 0, 2, 0, 4}});
  return matrix;
}

vector<vector<int> > GetRandomMatrix(int from, int to) {
  int rows(from);
  int cols(to);
  const int lowerBoundRand(2), upperBoundRand(20);
  vector<vector<int> > matrix(rows, vector<int>(cols, 0));
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i % 2 == 0 && j % 2 == 0)
        matrix[i][j] = GetRandomNumber(lowerBoundRand, upperBoundRand);
      else
        matrix[i][j] = 0;
    }
  }
  return matrix;
}

void AddBorders(vector<vector<char> >& matrix) {
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (i == 0) matrix[i][j] = '*';
      if (j == 0) matrix[i][j] = '*';
    }
  }
}

void print(int width, int height) {
  vector<vector<int> > matrix = GetRandomMatrix(height, width);

  vector<vector<char> > finalMaze(matrix.size(),
                                  vector<char>(matrix[0].size(), '*'));
  vector<vector<bool> > visited(matrix.size(),
                                vector<bool>(matrix[0].size(), false));

  const int moves(4);
  int cols[moves] = {2, 0, -2, 0};
  int rows[moves] = {0, 2, 0, -2};

  auto cmp = [](Element left, Element right) {
    return left.weight > right.weight;
  };

  priority_queue<Element, vector<Element>, decltype(cmp)> pq(cmp);

  pq.push(Element(0, 0, 0));
  while (!pq.empty()) {
    // cout << "----------- GENERATING MAZE -----------\n";
    int coordX = pq.top().coord.first;
    int coordY = pq.top().coord.second;
    pq.pop();
    visited[coordX][coordY] = true;
    matrix[coordX][coordY] = 1;
    finalMaze[coordX][coordY] = 'O';
    for (int i = 0; i < moves; i++) {
      int nextRow = coordX + rows[i];
      int nextCol = coordY + cols[i];
      if (nextCol < 0 || nextRow < 0 || nextCol > matrix[0].size() - 1 ||
          nextRow > matrix.size() - 1)
        continue;
      if (!visited[nextRow][nextCol]) {
        Element e(nextRow, nextCol, matrix[nextRow][nextCol]);
        pq.push(e);
      }
    }
    int nextLowCoordX(pq.top().coord.first);
    int nextLowCoordY(pq.top().coord.second);
    if (coordX == nextLowCoordX && (coordY - nextLowCoordY == abs(1))) {
      if (nextLowCoordY > coordY) {
        matrix[nextLowCoordX][nextLowCoordY - 1] = 1;
        finalMaze[nextLowCoordX][nextLowCoordY - 1] = 'O';
      } else {
        matrix[nextLowCoordX][nextLowCoordY + 1] = 1;
        finalMaze[nextLowCoordX][nextLowCoordY + 1] = 'O';
      }
    } else if (coordY == nextLowCoordY && (coordX - nextLowCoordX == abs(1))) {
      if (nextLowCoordX > coordX) {
        matrix[nextLowCoordX - 1][nextLowCoordY] = 1;
        finalMaze[nextLowCoordX - 1][nextLowCoordY] = 'O';
      } else {
        matrix[nextLowCoordX + 1][nextLowCoordY] = 1;
        finalMaze[nextLowCoordX + 1][nextLowCoordY] = 'O';
      }
    } else {
      for (int i = 0; i < moves; i++) {
        int nextRow = coordX + rows[i];
        int nextCol = coordY + cols[i];
        if (nextCol < 0 || nextRow < 0 || nextCol > matrix[0].size() - 1 ||
            nextRow > matrix.size() - 1)
          continue;
        if (visited[nextRow][nextCol]) {
          if (coordX == nextRow) {
            if (nextCol > coordY) {
              matrix[nextRow][nextCol - 1] = 1;
              finalMaze[nextRow][nextCol - 1] = 'O';
            } else {
              matrix[nextRow][nextCol + 1] = 1;
              finalMaze[nextRow][nextCol + 1] = 'O';
            }
            break;
          } else if (coordY == nextCol) {
            if (nextRow > coordX) {
              matrix[nextRow - 1][nextCol] = 1;
              finalMaze[nextRow - 1][nextCol] = 'O';
            } else {
              matrix[nextRow + 1][nextCol] = 1;
              finalMaze[nextRow + 1][nextCol] = 'O';
            }
            break;
          }
        }
      }
    }
  }
  AddBorders(finalMaze);
  PrintMatrix(finalMaze);
}

int main() {
  srand(time(NULL));
  int width, height;
  cout << "Enter width: ";
  cin >> width;
  cout << "Enter height: ";
  cin >> height;
  print(width, height);
  cout << "Exit? (Y) ";
  cin >> height;  
}