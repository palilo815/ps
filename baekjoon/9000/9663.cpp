#include <iostream>
using namespace std;

int N, board[15][15], ans;

void check(int r, int c, int val) {
    for (int i = r + 1; i < N; ++i) board[i][c] += val;
    for (int i = r + 1, j = c - 1; i < N && j >= 0; ++i, --j) board[i][j] += val;
    for (int i = r + 1, j = c + 1; i < N && j < N; ++i, ++j) board[i][j] += val;
}
void placing(int row) {
    if (row == N) {
        ++ans;
        return;
    }
    for (int i = 0; i < N; ++i) if (!board[row][i]) {
        check(row, i, 1);
        placing(row + 1);
        check(row, i, -1);
    }
}
int main() {
    cin >> N;
    placing(0);
    cout << ans;
    return 0;
}