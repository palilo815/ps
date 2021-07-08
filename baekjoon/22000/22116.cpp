#include <bits/stdc++.h>
using namespace std;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    constexpr int INF = 0x3f3f3f3f;
    int n;
    cin >> n;
    vector grid(n, vector<int>(n));
    for (auto& vt : grid) {
        for (auto& x : vt) {
            cin >> x;
        }
    }
    vector dist(n, vector(n, INF));
    priority_queue<elem> pq;
    pq.emplace(dist[0][0] = 0, 0);
    while (!pq.empty()) {
        const auto d = pq.top().d;
        const auto x = pq.top().u >> 16, y = pq.top().u & 0xffff;
        pq.pop();
        if (d != dist[x][y]) {
            continue;
        }
        for (const auto& [dx, dy] : mov) {
            const auto x2 = x + dx, y2 = y + dy;
            if (x2 == -1 || x2 == n || y2 == -1 || y2 == n) {
                continue;
            }
            if (auto d2 = max(d, abs(grid[x][y] - grid[x2][y2])); dist[x2][y2] > d2) {
                pq.emplace(dist[x2][y2] = d2, x2 << 16 | y2);
            }
        }
    }
    cout << dist.back().back();
}