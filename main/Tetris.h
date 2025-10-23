#ifndef TETRIS_H
#define TETRIS_H

class Tetris {
public:
    bool** grid;

    Tetris();
    bool full(int row);
    bool empty(int row);
    void checkRows();
    void moveRow(int row);
    void moveAll();
    void update();
};

#endif
