#ifndef TETROMINO_H
#define TETROMINO_H

#include <vector>
using namespace std;

extern bool threePiece[5][3][3];

class Tetromino {
public:
    int n, x, y;
    vector<vector<bool>> f;

    Tetromino();
    Tetromino(int size);
    Tetromino(char fig);

    bool connects(vector<vector<bool>> grid);
    bool connectsI(vector<vector<bool>> grid);

    void move(vector<vector<bool>> &grid, char dir);
    bool moveI(vector<vector<bool>> &grid, char dir);

    void rotateClockwise();
    void rotateCounterClockwise();
    void flip();
};

#endif