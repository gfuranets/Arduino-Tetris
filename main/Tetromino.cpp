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

// constructor without arguments
Tetromino::Tetromino() : n(0), x(0), y(0) {} // initializer list for constructor

// constructor for different shapes 
Tetromino::Tetromino(char fig) {
    // case O (n = 2)
    if (fig == 'o') {
        n = 2;
        y = 14;
        x = 3;

        bool** g = new bool*[n];
        for (int i = 0; i < n; i++) {
            g[i] = new bool[n];
            for (int j = 0; j < n; j++) {
                g[i][j] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                g[i][j] = 1;
            }
        }

        f = g;
    }

    // case I (n = 4)
    if (fig == 'i') {
        n = 4;
        y = 12;
        x = 2;

        bool** g = new bool*[n];
        for (int i = 0; i < n; i++) {
            g[i] = new bool[n];
            for (int j = 0; j < n; j++) {
                g[i][j] = 0;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (j == 1) g[i][j] = 1;
            }
        }

        f = g;
    }

    // other cases (n = 3)
    else {
        n = 3;
        y = 13;
        x = 3;

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

        bool** g = new bool*[n];
        for (int i = 0; i < n; i++) {
            g[i] = new bool[n];
            for (int j = 0; j < n; j++) {
                // assign one of 5 3x3 shapes to a Tetromino
                g[i][j] = threePiece[pos][i][j];
            }
        }

        f = g;
    }
}

// destructor
Tetromino::~Tetromino() {
    for (int k = 0; k < n; k++) delete [] f[k];
    delete [] f;
}

// check whether a tetromino is connected (has fallen)
// posible situations - 1. touches ground, 2. touched another piece
bool Tetromino::connects(bool** grid) {
    if (n == 4) {
        return connectsI(grid);
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
bool Tetromino::connectsI(bool** grid) {
    // check case if I is horizontal and in first row (f[0][0] == 0)
    for (int posX = 0; posX < n; posX) {
        if (f[0][posX] && f[0][posX + 1]) {
            if (y == 0 || grid[y - 1][0]) return true;
        }
    }

    // check case if I is vertical (only one pixel has posY == 0)
    for (int posX = 0; posX < n; posX++) {
        if (f[0][posX] && f[1][posX]) {
            if (y == 0 || grid[y - 1][x + posX]) return true;
        }
    }

    // check case if I is horizontal and not first row
    for (int posY = 1; posY < n; posY++) {
        if (f[posY][0] && f[posY][1]) {
            for (int posX = 0; posX < n; posX++) {
                if (grid[y + posY - 1][x + posX]) return true;
                else {
                    shift('d');
                }
            }
        }
    }

    return false;
}

void Tetromino::shift(char dir) {
    switch(dir) {
        case 'l':
            for (int posY = 0; posY < n; posY++) {\
                for (int posX = 1; posX < n; posX++) {
                    f[posY][posX - 1] = f[posY][posX];
                }
                f[posY][n - 1] = 0;
            }

            break;

        case 'r':
            for (int posY = 0; posY < n; posY++) {\
                    for (int posX = n - 2; posX >= 0; posX--) {
                        f[posY][posX + 1] = f[posY][posX];
                    }
                    f[posY][0] = 0;
                }

            break;

        default:
            for (int posY = 1; posY < n; posY++) {\
                for (int posX = 0; posX < n; posX++) {
                    f[posY - 1][posX] = f[posY][posX];
                }
                f[n - 1][0] = 0;
            }

    }
}


// move a tetromino on the grid (left, right, down, drop)
// check whether a movement is possible in said direction and perform it if so
void Tetromino::move(bool** grid, char dir) {
    /* if (n == 4) {
        moveI(grid, dir);
        return;
    } */

    switch(dir) {
        case 'l':
            if (x > 0) {
                for (int posY = 0; posY < n; posY++) {
                    if (f[posY][0] && grid[y + posY][x]) return;
                }

                /*
                for (int posY = 0; posY < n; posY++) {
                    for (int posX = 0; posX < n; posX++) {
                        grid[y + posY][x + posX - 1] = grid[y + posY][x + posX];
                        grid[y + posY][x + posX] = 0;
                    }
                }
                */ 
                x--;
            }

            break;

        case 'r':
            if (x < 8 - n) {
                for (int posY = 0; posY < n; posY++) {
                    if (f[posY][n - 1] && grid[y + posY][x + n - 1]) return;
                } 
                /*
                for (int posY = 0; posY < n; posY++) {
                    for (int posX = n - 1; posX >= 0; posX--) {
                        grid[y + posY][x + posX + 1] = grid[y + posY][x + posX];
                        grid[y + posY][x + posX] = 0;
                    }
                }
                */
                x++;
            }

            break;

        case 'd':
            if (y > 0) {
                for (int posX = 0; posX < n; posX++) {
                    if (f[0][posX] && grid[y - 1][x + posX]) return;
                }

                /* 
                for (int posY = 0; posY < n; posY++) {
                    for (int posX = 0; posX < n; posX++) {
                        grid[y + posY - 1][x + posX] = grid[y + posY][x + posX];
                        grid[y + posY][x + posX] = 0;
                    }
                }
                */
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
void Tetromino::moveI(bool** grid, char dir) {
    switch(dir) {
        case 'l':
            

            break;

        case 'r':

        case 'd':

        default:

    }
}

void Tetromino::rotateClockwise() {
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

void Tetromino::rotateCounterClockwise() {
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

void Tetromino::flip() {
    rotateClockwise();
    rotateClockwise();
}

// pass tetromino position to the grid (game logic)
void Tetromino::update(bool** grid) {
    for (int posY = 0; posY < n; posY++) {
        for (int posX = 0; posX < n; posX++) {
            grid[y + posY][x + posX] = f[posY][posX];
        }
    }
}