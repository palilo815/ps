#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int M = 50;
const int _ = 1 << 6;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

char board[M][M];
bool visited[M][M][1 << 5];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int col, row; cin >> col >> row;
    int K = 0;
    queue<int> q;
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 'X')
            board[i][j] = K++;
        else if (board[i][j] == 'S')
            q.emplace(i * _ + j);
    }

    q.emplace(-1);

    int ans = 0;
    while (1) {
        int k = q.front(); q.pop();
        if (k == -1) {
            ++ans;
            q.emplace(-1);
            continue;
        }
        int c = k % _; k /= _;
        int r = k % _; k /= _;
        if (board[r][c] < K) k |= (1 << board[r][c]);
        if (board[r][c] == 'E') {
            if (k == (1 << K) - 1) break;
            else continue;
        }

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (board[R][C] == '#' || visited[R][C][k]) continue;
            visited[R][C][k] = true;
            q.emplace(k * _ * _ + R * _ + C);
        }
    }
    cout << ans;
    return 0;
}