#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct elem {
    int h, r, c;
    elem(int h, int r, int c) : h(h), r(r), c(c) {}
    bool operator<(const elem& rhs) const {
        return h > rhs.h;
    }
};

const int mxN = 3e2;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

int h[mxN][mxN];
bool visited[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int M, N;
    cin >> M >> N;
    loop(i, N) loop(j, M) cin >> h[i][j];

    priority_queue<elem> pq;
    for (int i = 1; i < M - 1; ++i) {
        pq.emplace(h[0][i], 0, i);
        pq.emplace(h[N - 1][i], N - 1, i);
        visited[0][i] = visited[N - 1][i] = true;
    }
    for (int i = 1; i < N - 1; ++i) {
        pq.emplace(h[i][0], i, 0);
        pq.emplace(h[i][M - 1], i, M - 1);
        visited[i][0] = visited[i][M - 1] = true;
    }
    visited[0][0] = visited[0][M - 1] = visited[N - 1][0] = visited[N - 1][M - 1] = true;

    int ans = 0;
    while (!pq.empty()) {
        auto [water, r, c] = pq.top();
        pq.pop();

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == N || C == -1 || C == M || visited[R][C]) continue;
            visited[R][C] = true;

            if (water > h[R][C]) {
                ans += water - h[R][C];
                pq.emplace(water, R, C);
            } else
                pq.emplace(h[R][C], R, C);
        }
    }
    cout << ans;
    return 0;
}