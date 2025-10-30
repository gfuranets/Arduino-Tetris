// define a Tetris game class

#include "Tetris.h"

// class constructor fills the game grid with 0 (empty grid)
Tetris::Tetris() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 8; j++) {
            grid[i][j] = 0;
        }
    }
}

// check whether a row is full, used in move()
bool Tetris::full(int row) {
    int num = 0;
    for (int k = 0; k < 8; k++) {
        if (grid[row][k]) num++;
    }
    return num == 8 ? true : false;
}

// check whether a row is empty (for row moving)
bool Tetris::empty(int row) {
    int num = 0;
    for (int k = 0; k < 8; k++) {
        if (grid[row][k]) num++;
    }
    return num == 0 ? true : false;
}

// loop through all rows and delete it (fill with 0) if it is full
void Tetris::checkRows() {
    for (int row = 0; row < 16; row++) {
        if (full(row)) {
            // delete a row
            for (int k = 0; k < 8; k++) grid[row][k] = 0;
        }
    }
}

// move a row down if there are
void Tetris::moveRow(int row) {
    if (row == 0 || !empty(row - 1)) return;
    else {
        // replace grid[row - 1] elements with grid[row] elements
        for (int k = 0; k < 8; k++) {
            grid[row - 1][k] = grid[row][k];
            grid[row][k] = 0;
        }
        // recursively call the moveRow() from the next 
        moveRow(row - 1);
    }
}

// loop through each row (0 <= row <= 15) and call moveRow() (updates the grid from the bottom)
void Tetris::moveAll() {
    for (int row = 0; row < 16; row++) moveRow(row);
}

// combine all functions for grid changing
void Tetris::update() {
    checkRows();
    moveAll();
}
