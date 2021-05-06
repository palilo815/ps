#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
public:
    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }

private:
    vector<int> par;
};

struct _query {
    int x1, y1, x2, y2;
};

constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> cnt(n, vector<int>(m));
    vector<_query> query(q);
    for (auto& [x1, y1, x2, y2] : query) {
        cin >> x1 >> y1 >> x2 >> y2, --x1, --y1, --x2, --y2;
        if (x1 == x2)
            for (int y = y1; y <= y2; ++y)
                ++cnt[x1][y];
        else
            for (int x = x1; x <= x2; ++x)
                ++cnt[x][y1];
    }

    disjoint_set dsu(n * m);
    int components = 0;
    auto check = [&](int x, int y) {
        ++components;
        for (const auto& [dx, dy] : mov) {
            int X = x + dx, Y = y + dy;
            if (~X && X != n && ~Y && Y != m && !cnt[X][Y] && dsu.merge(x * m + y, X * m + Y))
                --components;
        }
    };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!cnt[i][j]) check(i, j);

    vector<int> ans(q);
    for (int i = q; i--;) {
        ans[i] = components;
        const auto& [x1, y1, x2, y2] = query[i];
        if (x1 == x2) {
            for (int y = y1; y <= y2; ++y)
                if (--cnt[x1][y] == 0)
                    check(x1, y);
        } else {
            for (int x = x1; x <= x2; ++x)
                if (--cnt[x][y1] == 0)
                    check(x, y1);
        }
    }

    for (const auto& x : ans)
        cout << x << '\n';
}