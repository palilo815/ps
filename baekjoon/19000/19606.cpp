#include <bits/stdc++.h>
using namespace std;

constexpr int mxN = 1e3;
constexpr int mask = (1 << 10) - 1;

int mat[mxN][mxN];
bool visited[mxN][mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mat[i][j];

    vector<int> ord(n * m);
    for (int i = 0; i < n; ++i)
        move(mat[i], mat[i] + m, ord.begin() + i * m);

    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            mat[i][j] = lower_bound(ord.begin(), ord.end(), mat[i][j]) - ord.begin();

    vector<vector<int>> adj(ord.size());
    for (int i = 0; i < int(ord.size()); ++i)
        for (int x = 1; x * x <= ord[i]; ++x)
            if (ord[i] % x == 0)
                adj[i].emplace_back(x);

    queue<int> q;
    q.emplace(0);
    visited[0][0] = true;

    while (!q.empty()) {
        int r = q.front() >> 10, c = q.front() & mask;
        q.pop();

        for (auto x : adj[mat[r][c]]) {
            auto y = ord[mat[r][c]] / x;
            if (x == n && y == m || x == m && y == n) return cout << "yes", 0;
            --x, --y;
            if (x < n && y < m && !visited[x][y]) {
                visited[x][y] = true;
                q.emplace(x << 10 | y);
            }
            if (y < n && x < m && !visited[y][x]) {
                visited[y][x] = true;
                q.emplace(y << 10 | x);
            }
        }
    }
    cout << "no";
}