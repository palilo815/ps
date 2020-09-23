#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e2;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

int N, M, h[mxN + 2][mxN + 2];
vector<pair<int, int>> vt;

queue<pair<int, int>> q;
bool visited[mxN + 2][mxN + 2];

bool solve(int m) {
    memset(visited, 0, sizeof(visited));
    visited[vt[0].first][vt[0].second] = true;
    q.emplace(vt[0]);

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (!visited[R][C] && abs(h[r][c] - h[R][C]) <= m) {
                visited[R][C] = true;
                q.emplace(R, C);
            }
        }
    }

    return all_of(vt.begin(), vt.end(), [&](auto& x) {
        return visited[x.first][x.second];
    });
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M;
    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j)
            cin >> h[i][j];
        h[i][0] = h[i][M + 1] = INT_MAX;
    }
    fill_n(h[0] + 1, M, INT_MAX);
    fill_n(h[N + 1] + 1, M, INT_MAX);

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j) {
            char x;
            cin >> x;
            if (x == '1') vt.emplace_back(i, j);
        }

    int lo = 0, hi = 1e9;
    while (lo ^ hi) {
        int m = (lo + hi) >> 1;
        solve(m) ? (hi = m) : (lo = m + 1);
    }
    cout << lo;
    return 0;
}