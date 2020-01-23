#include <algorithm>
#include <iostream>
using namespace std;

char board_W[8][8];

int Recolor(char **arr, int a, int b) {
    int count_W = 0, count_B = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (arr[a + i][b + j] == board_W[i][j])
                count_B++;
            else
                count_W++;
        }
    }
    return min(count_W, count_B);
}

int main() {
    cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if ((i % 2 == 0 && j % 2 == 0) || (i % 2 == 1 && j % 2 == 1))
                board_W[i][j] = 'W';
            else
                board_W[i][j] = 'B';
        }
    }

    int row, col;
    cin >> row >> col;
    char **arr = new char *[row];
    for (int i = 0; i < row; i++)
        arr[i] = new char[col];

    for (int i = 0; i < row; i++)
        for (int j = 0; j < col; j++)
            cin >> arr[i][j];

    int minimum = 64;
    for (int i = 0; i <= row - 8; i++)
        for (int j = 0; j <= col - 8; j++)
            minimum = min(minimum, Recolor(arr, i, j));
    cout << minimum;
    return 0;
}