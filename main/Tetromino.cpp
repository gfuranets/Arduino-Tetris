// define a Block class which make up a single Tetromino piece
// each Tetromino contains a central block which gives access to all the other blocks in a piece

// 2 piece - o

// 3 piece - t, j, l, z, s
bool threePiece[5][3][3] = {{{0, 1, 0}, 
                             {0, 1, 1}, 
                             {0, 1, 0}},
                            
                            {{0, 0, 1},
                             {0, 0, 1},
                             {0, 1, 1}},
                            
                            {{0, 1, 0},
                             {0, 1, 0},
                             {0, 1, 1}},

                            {{0, 1, 0},
                             {1, 1, 0},
                             {1, 0, 0}},
                            
                            {{0, 1, 0},
                             {0, 1, 1},
                             {0, 0, 1}}};

// 4 piece - i

#include "Tetromino.h"
#include <vector>
using namespace std;

class Tetromino {
public:
    int n, x, y;
    vector<vector<bool>> f;

    Tetromino() {}

    Tetromino(int size) {
        n = size;
        y = 16 - size;
        x = 4 - size / 2;

        switch(n) {
            case 2:
                for (int k = 0; k < n; k++) f[k][k] = 1;
                break;
            default:
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (j == 1) f[i][j] = 1;
                    }
                }

        }
    }

    Tetromino(char fig) {
        n = 3;
        y = 13;
        x = 2;

        int pos;
        switch(fig) {
            case 'j':
                pos = 1;
                break;
            case 'l':
                pos = 2;
                break;
            case 'z':
                pos = 3;
                break;
            case 's':
                pos = 4;
                break;
            default:
                pos = 0;
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // assign one of 5 3x3 shapes to a Tetromino
                f[i][j] = threePiece[pos][i][j];
            }
        }
    }

    // destructor
    ~Tetromino() {
        for (int k = 0; k < n; k++) f[k][k] = 0;
    }

    // check whether a tetromino is connected (has fallen)
    // posible situations - 1. touches ground, 2. touched another piece
    bool connects(vector<vector<bool>> grid) {
        if (n == 4) {
            connectsI(grid);
            return;
        }

        for (int posX = 0; posX < n; posX++) {
            if (y == 0 && grid[y][x + posX]) return true;

            for (int posY = 0; posY < n; posY++) {
                if (f[posY][x + posX] && grid[y + posY - 1][posX]) return true;
                if (f[posY][posX] && !f[posY - 1][posX] 
                    && grid[y + posY - 1][x + posX]) return true;
            }
        }
        return false;
    }

    // specific connects() case for I shape
    bool connectsI(vector<vector<bool>> grid) {
        for (int posX = 0; posX < n; posX++) {
            if (y == 0) {
                if (f[0][0]) return true;
                else {
                    for (int posY = 1; posY < n; posY++) {
                        f[posY - 1][posX] = f[posY][posX];
                    }
                    f[n - 1][posX] = 0;
                }
            }

            for (int posY = 0; posY < n; posY++) {
                if (f[posY][x + posX] && grid[y + posY - 1][posX]) return true;
                if (f[posY][posX] && !f[posY - 1][posX] 
                    && grid[y + posY - 1][x + posX]) return true;
            }
        }
        return false;
    }


    // move a tetromino on the grid (left, right, down, drop)
    // check whether a movement is possible in said direction and perform it if so
    void move(vector<vector<bool>> &grid, char dir) {
        if (n == 4) {
            moveI(grid, dir);
            return;
        }

        switch(dir) {
            case 'l':
                if (x > 0) {
                    for (int posY = 0; posY < n; posY++) {
                        if (f[posY][0] && grid[y + posY][x]) return;
                    }

                    for (int posY = 0; posY < n; posY++) {
                        for (int posX = 0; posX < n; posX++) {
                            grid[y + posY][x + posX - 1] = grid[y + posY][x + posX];
                            grid[y + posY][x + posX] = 0;
                        }
                    }
                    x--;
                }

                break;

            case 'r':
                if (x < 8 - n) {
                    for (int posY = 0; posY < n; posY++) {
                        if (f[posY][n - 1] && grid[y + posY][x + n - 1]) return;
                    } 

                    for (int posY = 0; posY < n; posY++) {
                        for (int posX = n - 1; posX >= 0; posX--) {
                            grid[y + posY][x + posX + 1] = grid[y + posY][x + posX];
                            grid[y + posY][x + posX] = 0;
                        }
                    }
                    x++;
                }

                break;

            case 'd':
                if (y > 0) {
                    for (int posX = 0; posX < n; posX++) {
                        if (f[0][posX] && grid[y - 1][x + posX]) return;
                    }

                    for (int posY = 0; posY < n; posY++) {
                        for (int posX = 0; posX < n; posX++) {
                            grid[y + posY - 1][x + posX] = grid[y + posY][x + posX];
                            grid[y + posY][x + posX] = 0;
                        }
                    }
                    y--;
                }

                break;

            default:
                while(!connects(grid)) {
                    move(grid, 'd');
                }
        }
    }
    
    // specific move() case for I shape
    bool moveI(vector<vector<bool>> grid, char dir) {
        switch(dir) {

        }
    }

    void rotateClockwise() {
        int t;
        for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - i - 1; j++) {
                t = f[i][j];
                f[i][j] = f[j][n - i - 1];
                f[j][n - i - 1] = f[n - i - 1][n - j - 1];
                f[n - i - 1][n - j - 1] = f[j][n - i - 1];
                f[j][n - i - 1] = t;
            }
        }
    }

    void rotateCounterClockwise() {
        int t;
        for (int i = 0; i < n / 2; i++) {
            for (int j = i; j < n - i - 1; j++) {
                t = f[i][j];
                f[i][j] = f[j][n - i - 1];
                f[j][n - i - 1] = f[n - i - 1][n - j - 1];
                f[n - i - 1][n - j - 1] = f[j][n - i - 1];
                f[j][n - i - 1] = t;
            }
        }
    }

    void flip() {
        rotateClockwise();
        rotateClockwise();
    }
};
