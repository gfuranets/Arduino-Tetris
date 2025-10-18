#ifndef TETRIS_H
#define TETRIS_H

#include <vector>
using namespace std;

class Tetris {
public:
    vector<vector<bool>> grid;

    Tetris();
    bool full(int row);
    bool empty(int row);
    void checkRows();
    void moveRow(int row);
    void moveAll();
    void update();
};

#endif
