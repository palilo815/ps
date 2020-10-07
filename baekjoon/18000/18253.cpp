#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using ll = long long;
struct query {
    int r1, c1, r2, c2, idx;
};
struct elem {
    ll d;
    int r, c;
    elem(ll d, int r, int c) : d(d), r(r), c(c) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int N = 5, M = 1e5;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

int row, col, mat[N][M];
ll dist[N][M], ans[M];
query q[M];

priority_queue<elem> pq;

void dijk(int s, int m, int e, int src) {
    loop(i, row) memset(dist[i] + s, 0x3f, sizeof(ll) * (e - s));
    pq.emplace(dist[src][m] = 0, src, m);

    while (!pq.empty()) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (d != dist[r][c]) continue;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R != row && C != s - 1 && C != e && dist[R][C] > d + mat[R][C])
                pq.emplace(dist[R][C] = d + mat[R][C], R, C);
        }
    }
}
void solve(int s, int e, int qs, int qe) {
    if (s == e || qs == qe) return;
    int m = (s + e) >> 1;
    loop(r, row) {
        dijk(s, m, e, r);
        for (int i = qs; i < qe; ++i) {
            auto& [r1, c1, r2, c2, idx] = q[i];
            ans[idx] = min(ans[idx], dist[r1][c1] + dist[r2][c2] + mat[r][m]);
        }
    }

    int it1 = qs, it2 = qs;
    for (int i = qs; i < qe; ++i) {
        if (q[i].c2 < m) {
            query tmp = q[i];
            q[it2++] = q[it1];
            q[it1++] = tmp;
        } else if (m < q[i].c1)
            q[it2++] = q[i];
    }
    solve(s, m, qs, it1), solve(m, e, it1, it2);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    int Q;
    cin >> Q;

    loop(i, Q) {
        auto& [r1, c1, r2, c2, idx] = q[i];
        cin >> r1 >> c1 >> r2 >> c2;
        --r1, --c1, --r2, --c2;
        if (c1 > c2)
            swap(r1, r2), swap(c1, c2);
        idx = i;
    }

    memset(ans, 0x3f, sizeof(ll) * Q);

    solve(0, col, 0, Q);

    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}