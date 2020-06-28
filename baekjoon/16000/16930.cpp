#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int M = 1000;
const int INF = 0x3f3f3f3f;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[M][M];
int dist[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, K; cin >> row >> col >> K;
    loop(i, row) loop(j, col) cin >> mat[i][j];
    int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
    --r1, --c1, --r2, --c2;

    memset(dist, 0x3f, sizeof(dist));
    dist[r1][c1] = 0;

    queue<p> q;
    q.emplace(r1, c1);
    int ans = -1;
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        if (r == r2 && c == c2) { ans = dist[r][c]; break; }

        loop(i, 4) for (int k = 1; k <= K; ++k) {
            int R = r + mov[i][0] * k, C = c + mov[i][1] * k;
            if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C] == '#' || dist[R][C] <= dist[r][c])
                break;
            if (dist[R][C] == INF) {
                dist[R][C] = dist[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }
    cout << ans;
    return 0;
}