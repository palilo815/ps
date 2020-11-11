#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

struct elem {
    int d, r, c;
    elem(int d, int r, int c) : d(d), r(r), c(c) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 1e3;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

int mat[mxN][mxN], dist[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;
    loop(i, N) loop(j, M) cin >> mat[i][j];

    if (mat[0][0] == -1 || mat[N - 1][M - 1] == -1) return cout << -1, 0;

    memset(dist, 0x3f, sizeof(dist));

    priority_queue<elem> pq;
    pq.emplace(dist[0][0] = mat[0][0], 0, 0);

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (dist[r][c] != d) continue;
        if (r == N - 1 && c == M - 1) return cout << d, 0;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R != N && ~C && C != M && ~mat[R][C] && d + mat[R][C] < dist[R][C])
                pq.emplace(dist[R][C] = d + mat[R][C], R, C);
        }
    }
    cout << -1;
}