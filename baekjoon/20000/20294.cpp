#include <bits/stdc++.h>
using namespace std;

struct point3D {
    int x, y, z;
    point3D(int x, int y, int z) : x(x), y(y), z(z) {}
};

struct bipartite_matching {
    bipartite_matching(int _n, int _m) : n(_n), m(_m),
                                         adj(n), match(n, -1), rev(m, -1), visited(n) {}

    void add_edge(int u, int v) { adj[u].emplace_back(v); }
    int maximum_matching() {
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;

            for (int i = 0; i < n; ++i)
                if (match[i] == -1 && dfs(i))
                    update = true;
        }
        return n - count(match.begin(), match.end(), -1);
    }

private:
    const int n, m;
    vector<vector<int>> adj;
    vector<int> match, rev;
    vector<bool> visited;

    bool dfs(int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<point3D> odd, even;
    for (int i = 0, x, y, z; i < n; ++i) {
        cin >> x >> y >> z;
        (abs(x) + abs(y) + abs(z) & 1 ? odd : even).emplace_back(x, y, z);
    }

    n = odd.size();
    int m = even.size();

    vector<bool> chk_odd(n), chk_even(m);
    bipartite_matching solver(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (abs(odd[i].x - even[j].x) + abs(odd[i].y - even[j].y) + abs(odd[i].z - even[j].z) == 1) {
                solver.add_edge(i, j);
                chk_odd[i] = chk_even[j] = true;
            }

    cout << solver.maximum_matching() + count(chk_odd.begin(), chk_odd.end(), false) + count(chk_even.begin(), chk_even.end(), false);
}