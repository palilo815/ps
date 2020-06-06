#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 50;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

int row, col;
char board[M][M];
bool visited[M][M];

bool cycle(int r, int c, int pr, int pc) {
    visited[r][c] = true;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || (pr == R && pc == C) || board[r][c] != board[R][C]) continue;
        if (visited[R][C] || cycle(R, C, r, c)) return true;
    }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];

    int flag = 0;
    loop(i, row) loop(j, col) if (!visited[i][j])
        if (cycle(i, j, -1, -1)) {
            flag = 1; break;
        }
    cout << (flag ? "Yes" : "No");
    return 0;
}