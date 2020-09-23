#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e3;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

int N, M, K, h[mxN + 1][mxN];
bool visited[mxN + 1][mxN];

bool cross(int m) {
    for (int i = 1; i <= N; ++i)
        memset(visited[i], 0, M);

    deque<pair<int, int>> dq;
    loop(j, M) dq.emplace_back(0, j);
    dq.emplace_back(-1, -1);

    for (int cnt = 0;;) {
        auto [r, c] = dq.front();
        dq.pop_front();
        if (r == -1) {
            if (cnt++ == K) return false;
            dq.emplace_back(-1, -1);
            continue;
        }
        if (r == N) break;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && ~C && C ^ M && !visited[R][C]) {
                visited[R][C] = true;
                h[R][C] < m ? dq.emplace_back(R, C) : dq.emplace_front(R, C);
            }
        }
    }
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i)
        loop(j, M) cin >> h[i][j];

    fill(h[0], h[0] + M, INT_MAX);
    fill(visited[0], visited[0] + M, true);

    int lo = 0, hi = 0;
    for (int i = 1; i <= N; ++i)
        hi = max(hi, *max_element(h[i], h[i] + M));

    while (lo ^ hi) {
        int m = (lo + hi + 1) >> 1;
        cross(m) ? (lo = m) : (hi = m - 1);
    }
    cout << lo;
    return 0;
}