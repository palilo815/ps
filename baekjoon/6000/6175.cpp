#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int MAX = 102;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

char board[MAX][MAX];
int path[2][MAX][MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, T, sr, sc, dr, dc;
    cin >> row >> col >> T;
    LOOP(i, row) LOOP(j, col) cin >> board[i][j];
    cin >> sr >> sc >> dr >> dc;

    path[0][sr][sc] = 1;
    LOOP(t, T) {
        int v = t & 1;
        int u = 1 - v;
        memset(path[v], 0, sizeof(int) * MAX * MAX);

        LOOP(r, row) LOOP(c, col)
            for (int i = 0; i < 4; ++i) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (board[R][C] != '*')
                    path[v][R][C] += path[u][r][c];
            }
    }
    cout << path[T & 1][dr][dc];
    return 0;
}