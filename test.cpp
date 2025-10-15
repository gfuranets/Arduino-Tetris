// test.cpp file for testing in-game features

#include <iostream>
#include <cstdlib>
using namespace std;

// rotating an nxn matrix in a counter-clockwise direction
void rotateCounterClockwise(int** m, int n) {
    // n = 2k => 0 <= i < n / 2
    // n = 2k + 1 => 0 <= i < n / 2
    // single algorithm for any n value

    int t;
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            t = m[i][j];
            m[i][j] = m[j][n - i - 1];
            m[j][n - i - 1] = m[n - i - 1][n - j - 1];
            m[n - i - 1][n - j - 1] = m[j][n - i - 1];
            m[j][n - i - 1] = t;
        }
    }
}

void rotateClockwise(int** m, int n) {
    int t;
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            t = m[i][j];
            m[i][j] = m[n - j - 1][i];
            m[n - j - 1][i] = m[n - i - 1][n - j - 1];
            m[n - i - 1][n - j - 1] = m[j][n - i - 1];
            m[j][n - i - 1] = t;
        }
    }
}

int main() {
    srand(67);
    int n = 5;
    int** m = new int*[n];
    for (int i = 0; i < n; i++) {
        m[i] = new int[n];
        for (int j = 0; j < n; j++) {
            m[i][j] = rand() % 10;
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    rotateClockwise(m, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << m[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";

    return 0;
}