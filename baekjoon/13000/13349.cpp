#include <bits/stdc++.h>
using namespace std;

constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
constexpr int INF = 0x3f3f3f3f;

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

    int n, m;
    cin >> n >> m;

    vector grid(n, vector<int>(m));
    for (auto& row : grid)
        for (auto& x : row)
            cin >> x;

    vector need(n, vector<int>(m, INF));

    priority_queue<elem> pq;
    pq.emplace(need[0][0] = 0, 0);

    for (;;) {
        const auto ladder = pq.top().d,
                   x = pq.top().u >> 16, y = pq.top().u & 0xffff;
        pq.pop();

        if (x == n - 1 && y == m - 1) return cout << ladder, 0;

        for (const auto& [dx, dy] : mov) {
            int X = x + dx, Y = y + dy;
            if (X == -1 || X == n || Y == -1 || Y == m) continue;
            if (int L = max(ladder, grid[X][Y] - grid[x][y]); need[X][Y] > L)
                pq.emplace(need[X][Y] = L, X << 16 | Y);
        }
    }
}