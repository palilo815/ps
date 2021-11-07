#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct min_heap_elem {
    int key, x, y;

    min_heap_elem() = default;
    min_heap_elem(const int& key, const int& x, const int& y) : key(key), x(x), y(y) {}

    bool operator<(const min_heap_elem& rhs) const {
        return key > rhs.key;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    constexpr array<pair<int, int>, 4> mov {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    int n;
    cin >> n;
    vector grid(n, vector<int>(n));
    for (auto& row : grid) {
        for (auto& x : row) {
            cin >> x;
        }
    }
    vector<pair<int, int>> a(1);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == -1) {
                a[0] = {i, j};
                grid[i][j] = 0;
            } else if (grid[i][j] == 0) {
                a.emplace_back(i, j);
            }
        }
    }
    priority_queue<min_heap_elem> pq;
    vector dist(n, vector<int>(n));
    const auto dijk = [&](const int s) {
        for_each(dist.begin(), dist.end(), [&](auto& x) {
            fill(x.begin(), x.end(), INF);
        });
        pq.emplace(dist[a[s].first][a[s].second] = 0, a[s].first, a[s].second);
        while (!pq.empty()) {
            const auto [d, x, y] = pq.top();
            pq.pop();
            if (d != dist[x][y]) continue;
            for (const auto& [dx, dy] : mov) {
                const auto x2 = x + dx, y2 = y + dy;
                if (~x2 && x2 != n && ~y2 && y2 != n && dist[x2][y2] > d + grid[x2][y2]) {
                    pq.emplace(dist[x2][y2] = d + grid[x2][y2], x2, y2);
                }
            }
        }
        vector<int> cost(a.size());
        transform(a.begin(), a.end(), cost.begin(), [&](const auto& x) {
            return dist[x.first][x.second];
        });
        return cost;
    };
    vector<vector<int>> cost(a.size());
    for (int i = 0; i < int(a.size()); ++i) {
        cost[i] = dijk(i);
    }
    vector<int> ord(a.size() + 1);
    iota(ord.begin() + 1, ord.end() - 1, 1);
    int64_t ans = LLONG_MAX;
    do {
        int64_t res = 0;
        for (int i = 0; i < int(cost.size()); ++i) {
            res += cost[ord[i]][ord[i + 1]];
        }
        chmin(ans, res);
    } while (next_permutation(ord.begin() + 1, ord.end() - 1));
    cout << ans;
}