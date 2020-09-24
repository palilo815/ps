#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e2;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

int N, M, h[mxN][mxN], t1[mxN][mxN], t2[mxN][mxN];
queue<pair<int, int>> q;

void bfs(int t[][mxN]) {
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ N && ~C && C ^ M && t[R][C] > t[r][c] + 1) {
                t[R][C] = t[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int V, x, y;
    cin >> N >> M >> V >> x >> y;
    loop(i, N) loop(j, M) cin >> h[i][j];
    --x, --y;

    vector<tuple<int, int, int>> vt(V);
    for (auto& [x, y, w] : vt) cin >> x >> y >> w;
    for (auto& [x, y, w] : vt) --x, --y;

    memset(t1, 0x3f, sizeof(t1));
    for (auto& [x, y, w] : vt)
        t1[x][y] = -1;
    t1[x][y] = 0;
    q.emplace(x, y);
    bfs(t1);

    memset(t2, 0x3f, sizeof(t2));
    for (auto& [x, y, w] : vt) {
        t2[x][y] = w;
        q.emplace(x, y);
    }
    bfs(t2);

    for (auto& [x, y, w] : vt)
        t2[x][y] = -1;

    int mxh = 0, mnt = INT_MAX;
    loop(i, N) loop(j, M) if (t1[i][j] < t2[i][j]) {
        if (h[i][j] > mxh)
            mxh = h[i][j], mnt = t1[i][j];
        else if (h[i][j] == mxh && t1[i][j] < mnt)
            mnt = t1[i][j];
    }
    cout << mxh << ' ' << mnt;
    return 0;
}