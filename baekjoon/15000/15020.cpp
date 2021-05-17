#include <bits/stdc++.h>
using namespace std;

constexpr array<pair<int, int>, 8> mov =
    {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    for (auto& row : h)
        for (auto& x : row)
            cin >> x;

    int sr, sc;
    cin >> sr >> sc, --sr, --sc;

    struct elem {
        int d, r, c;
        elem(int d, int r, int c) : d(d), r(r), c(c) {}
        bool operator<(const elem& rhs) const {
            return d > rhs.d;
        }
    };

    priority_queue<elem> pq;
    pq.emplace(h[sr][sc], sr, sc);

    vector<vector<bool>> visited(n, vector<bool>(m));
    visited[sr][sc] = true;

    int64_t ans = -h[sr][sc];
    while (!pq.empty()) {
        auto [height, r, c] = pq.top();
        pq.pop();

        for (const auto& [dr, dc] : mov) {
            int nr = r + dr, nc = c + dc;
            if (nr == -1 || nr == n || nc == -1 || nc == m || visited[nr][nc] || h[nr][nc] >= 0)
                continue;

            visited[nr][nc] = true;
            int nh = max(height, h[nr][nc]);
            ans += -nh;
            pq.emplace(nh, nr, nc);
        }
    }
    cout << ans;
}