#include <bits/stdc++.h>
using namespace std;

constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
constexpr int64_t INF = 0x3f3f3f3f3f3f3f3f;

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
    int h, w, n;
    int64_t a, b, c;
    cin >> h >> w >> a >> b >> c >> n;
    ++h, ++w;

    vector<pair<int, int>> player(n);
    for (auto& [x, y] : player)
        cin >> x >> y;

    auto dist = [&]() {
        vector<vector<int>> dist(h, vector<int>(w, -1));
        queue<int> q;
        for (const auto& [x, y] : player) {
            dist[x][y] = 0;
            q.emplace(x << 16 | y);
        }

        while (!q.empty()) {
            auto x = q.front();
            auto y = x & 0xffff;
            x >>= 16;
            q.pop();

            for (const auto& [dx, dy] : mov) {
                auto X = x + dx, Y = y + dy;
                if (~X && X != h && ~Y && Y != w && dist[X][Y] == -1) {
                    dist[X][Y] = dist[x][y] + 1;
                    q.emplace(X << 16 | Y);
                }
            }
        }
        return dist;
    }();

    vector<vector<array<int64_t, 5>>> cost(h, vector<array<int64_t, 5>>(w, {INF, INF, INF, INF, INF}));

    priority_queue<elem> pq;
    pq.emplace(cost[player[0].first][player[0].second][4] = 0,
               4 << 24 | player[0].first << 12 | player[0].second);

    while (!pq.empty()) {
        auto [d, dir] = pq.top();
        auto y = dir & 0xfff;
        dir >>= 12;
        auto x = dir & 0xfff;
        dir >>= 12;
        pq.pop();

        if (cost[x][y][dir] != d) continue;

        if (dir == 4) {
            for (int i = 0; i < 4; ++i)
                if (cost[x][y][i] > cost[x][y][4] + b)
                    pq.emplace(cost[x][y][i] = cost[x][y][4] + b, i << 24 | x << 12 | y);
            for (const auto& [dx, dy] : mov) {
                auto X = x + dx, Y = y + dy;
                if (~X && X != h && ~Y && Y != w && cost[X][Y][4] > cost[x][y][4] + c)
                    pq.emplace(cost[X][Y][4] = cost[x][y][4] + c, 4 << 24 | X << 12 | Y);
            }
        } else {
            if (cost[x][y][4] > cost[x][y][dir] + c * dist[x][y])
                pq.emplace(cost[x][y][4] = cost[x][y][dir] + c * dist[x][y], 4 << 24 | x << 12 | y);
            auto X = x + mov[dir].first, Y = y + mov[dir].second;
            if (~X && X != h && ~Y && Y != w && cost[X][Y][dir] > cost[x][y][dir] + a)
                pq.emplace(cost[X][Y][dir] = cost[x][y][dir] + a, dir << 24 | X << 12 | Y);
        }
    }
    cout << cost[player[n - 1].first][player[n - 1].second][4];
}