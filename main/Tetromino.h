#ifndef TETROMINO_H
#define TETROMINO_H

extern bool threePiece[5][3][3];

class Tetromino {
public:
    int n, x, y;
    bool** f;

    Tetromino();
    Tetromino(int size);
    Tetromino(char fig);

    bool connects(bool** grid);
    bool connectsI(bool** grid);

    void move(bool** grid, char dir);
    bool moveI(bool** grid, char dir);

    void shift(char dir);

    void rotateClockwise();
    void rotateCounterClockwise();
    void flip();

    void update(bool** grid);
};

#endif