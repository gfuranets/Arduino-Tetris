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

class Tetromino {
public:
    int n, x, y;
    bool** f = nullptr;

    Tetromino() {}

    Tetromino(int size) {
        n = size;
        y = 16 - size;
        x = 4 - size / 2;
        
        bool** g = new bool*[n];
        for (int i = 0; i < n; i++) {
            g[i] = new bool[n];
        }

        switch(n) {
            case 2:
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        g[i][j] = 1;
                    }
                }
                break;
            default:
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        if (j == 1) g[i][j] = 1;
                    }
                }

        }

        f = g;
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
        
        bool** g = new bool*[n];
        for (int i = 0; i < n; i++) {
            g[i] = new bool[n];
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                // assign one of 5 3x3 shapes to a Tetromino
                g[i][j] = threePiece[pos][i][j];
            }
        }

        f = g;
    }

    // delete tetromino shape array to prevent memory overload
    ~Tetromino() {
        for (int k = 0; k < n; k++) delete [] f[k];
        delete [] f;
    }

    // check whether a tetromino is connected (has fallen)
    // posible situations - 1. touches ground, 2. touched another piece
    bool connects(bool grid[16][8]) {
        for (int posX = 0; posX < n; posX++) {
            if (!grid[y][x + posX]) return true;

            for (int posY = 0; posY < n; posY++) {
                if (posY == 0) {
                    if (f[posY][posX] && grid[y + posY - 1][x + posX]) return true;

                    if (f[posY][posX] && !f[posY - 1][posX] 
                        && grid[y + posY - 1][x + posX]) return true;
                }
            }
        }
        return false;
    }

    // specific connects() case for I shape
    bool connects(bool grid[16][8], char arg) {

    }

    // move a tetromino on the grid (left, right, down, drop)
    // check whether a movement is possible in said direction and perform it if so
    void move(bool (&grid)[16][8], char dir) {
        switch(dir) {
            case 'l':

            case 'r':

            case 'd':

            default:
        }
    }
    
    // specific move() case for I shape
    bool move(bool grid[16][8], char dir, char arg) {
        
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
