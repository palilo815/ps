#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 1000;
const unsigned mod = (1 << 31) - 1;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int N;
char board[M][M];
bool visited[M][M];
unsigned DP[M + 1][M + 1];

int BFS(int r, int c) {
    visited[r][c] = true;
    queue<pair<int, int>> q;
    q.emplace(r, c);
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == N - 1 && c == N - 1) return 1;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N || board[R][C] == '#' || visited[R][C]) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    loop(i, N) loop(j, N) cin >> board[i][j];

    DP[0][0] = 1;
    loop(i, N) loop(j, N) if (board[i][j] == '.')
        DP[i][j + 1] = (DP[i][j + 1] + DP[i][j]) % mod,
        DP[i + 1][j] = (DP[i + 1][j] + DP[i][j]) % mod;

    if (DP[N - 1][N - 1])
        cout << DP[N - 1][N - 1];
    else
        cout << (BFS(0, 0) ? "THE GAME IS A LIE" : "INCONCEIVABLE");
    return 0;
}