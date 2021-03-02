#include <bits/stdc++.h>
using namespace std;

struct query {
    int r1, c1, r2, c2, id;
};

struct elem {
    int64_t d;
    int u;
    elem(int64_t d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;
    constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<int>> mat(n, vector<int>(m));
    for (int j = 0; j < m; ++j)
        for (int i = 0; i < n; ++i)
            cin >> mat[i][j];

    vector<query> q(k);
    {
        int i = -1;
        for (auto& [r1, c1, r2, c2, id] : q) {
            cin >> r1 >> c1 >> r2 >> c2;
            --r1, --c1, --r2, --c2;
            if (c1 > c2) swap(r1, r2), swap(c1, c2);
            id = ++i;
        }
    }

    vector<vector<int64_t>> dist(n, vector<int64_t>(m));
    auto dijk = [&](int l, int mid, int r, int src) {
        for (int i = 0; i < n; ++i)
            fill(dist[i].begin() + l, dist[i].begin() + r, INF);

        priority_queue<elem> pq;
        pq.emplace(dist[src][mid] = 0, src << 16 | mid);

        while (!pq.empty()) {
            auto [d, x] = pq.top();
            auto y = x & 0xffff;
            x >>= 16;
            pq.pop();

            if (d != dist[x][y]) continue;

            for (const auto& [dx, dy] : mov) {
                const auto X = x + dx, Y = y + dy;
                if (~X && X != n && ~Y && Y != m && dist[X][Y] > d + mat[X][Y])
                    pq.emplace(dist[X][Y] = d + mat[X][Y], X << 16 | Y);
            }
        }
    };

    vector<int64_t> ans(k, INF);
    function<void(int, int, int, int)> solve = [&](int l, int r, int ql, int qr) {
        if (l == r || ql == qr) return;

        int mid = (l + r) >> 1;
        for (int i = 0; i < n; ++i) {
            dijk(l, mid, r, i);
            for (int j = ql; j < qr; ++j) {
                const auto& [r1, c1, r2, c2, id] = q[j];
                ans[id] = min(ans[id], dist[r1][c1] + dist[r2][c2] + mat[i][mid]);
            }
        }

        const auto p1 = partition(q.begin() + ql, q.begin() + qr, [&](auto& q) {
            return q.c2 < mid;
        });
        const auto p2 = partition(p1, q.begin() + qr, [&](auto& q) {
            return mid < q.c1;
        });
        solve(l, mid, ql, p1 - q.begin()), solve(mid, r, p1 - q.begin(), p2 - q.begin());
    };
    solve(0, m, 0, k);

    for (const auto& x : ans) cout << x << '\n';
}