#include <bits/stdc++.h>
using namespace std;

struct elem {
    int d, r, c;
    elem(int d, int r, int c) : d(d), r(r), c(c) {}
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
    constexpr int INF = 0x3f3f3f3f;
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) {
        cin >> x;
    }
    vector fall(n, vector<int>(m));
    for (int j = 0; j < m; ++j) {
        int land = n - 1;
        for (int i = n - 1; i--;) {
            if (grid[i][j] == 'X') {
                fall[i][j] = land;
            } else {
                land = i;
            }
        }
    }
    priority_queue<elem> pq;
    vector dist(n, vector(m, INF));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'C') {
                pq.emplace(0, i, j);
                dist[i][j] = 0;
            }
        }
    }
    assert(pq.size() == 1);
    while (!pq.empty()) {
        const auto [d, r, c] = pq.top();
        pq.pop();
        if (grid[r][c] == 'E') return cout << d, 0;
        if (d != dist[r][c]) continue;
        if (grid[r][c] == 'X') {
            // 떨어짐
            int r2 = fall[r][c];
            if (grid[r2][c] != 'D' && dist[r2][c] > d + 10) {
                pq.emplace(dist[r2][c] = d + 10, r2, c);
            }
        } else {
            // 좌우
            if (c && grid[r][c - 1] != 'D' && dist[r][c - 1] > d + 1) {
                pq.emplace(dist[r][c - 1] = d + 1, r, c - 1);
            }
            if (c + 1 != m && grid[r][c + 1] != 'D' && dist[r][c + 1] > d + 1) {
                pq.emplace(dist[r][c + 1] = d + 1, r, c + 1);
            }
            // 사다리
            if (r && grid[r][c] == 'L' && grid[r - 1][c] != 'D' && dist[r - 1][c] > d + 5) {
                pq.emplace(dist[r - 1][c] = d + 5, r - 1, c);
            }
            if (r + 1 != n && grid[r + 1][c] == 'L' && dist[r + 1][c] > d + 5) {
                pq.emplace(dist[r + 1][c] = d + 5, r + 1, c);
            }
        }
    }
    cout << "dodo sad";
}