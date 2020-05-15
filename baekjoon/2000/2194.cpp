#include <bits/stdc++.h>
#define rep(i,s,e) for(int i=s;i<e;++i)
using namespace std;

const int M = 500;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool wall[M][M];
bool visited[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, A, B, K;
    cin >> row >> col >> A >> B >> K;
    row -= A - 1, col -= B - 1;
    while (K--) {
        int r, c; cin >> r >> c;
        rep(i, max(0, r - A), r) rep(j, max(0, c - B), c)
            wall[i][j] = true;
    }

    int sr, sc, dr, dc;
    cin >> sr >> sc >> dr >> dc;
    --sr, --sc, --dr, --dc;
    visited[sr][sc] = true;

    queue<pair<int, int>> q;
    q.emplace(sr, sc);
    q.emplace(-1, -1);

    int ans = 0;
    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans;
            q.emplace(-1, -1);
            continue;
        }
        if (r == dr && c == dc) break;

        rep(i, 0, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || wall[R][C] || visited[R][C]) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }
    cout << ans;
    return 0;
}