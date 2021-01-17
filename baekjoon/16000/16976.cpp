#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

struct disjoint_set {
    vector<int> par, when;
    disjoint_set(int n) {
        par.resize(n, -1);
        when.resize(n, 0x3f3f3f3f);
    }
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    void merge(int u, int v, int w) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u, when[v] = w;
    }
};

vector<int> player[mxN];
int visited[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, q;
    cin >> n >> m >> q;

    for (int i = 0, game; i < n; ++i) {
        cin >> game;
        player[game - 1].emplace_back(i);
    }

    disjoint_set dsu(n);

    for (int i = 1, u, v; i <= q; ++i) {
        cin >> u >> v;
        dsu.merge(u - 1, v - 1, i);
    }

    memset(visited, -1, sizeof(int) * n);

    for (int i = 0, ans, root; i < m; ++i) {
        ans = 0, root = dsu.find(player[i][0]);
        priority_queue<elem> pq;

        for (int& x : player[i]) {
            if (dsu.find(x) != root) {
                ans = -1;
                break;
            }
            pq.emplace(dsu.when[x], x);
            visited[x] = i;
        }

        if (ans == -1) {
            cout << "-1\n";
            continue;
        }

        while (pq.size() != 1) {
            int u = pq.top().u;
            ans = pq.top().d;
            pq.pop();

            if (visited[dsu.par[u]] != i) {
                visited[dsu.par[u]] = i;
                pq.emplace(dsu.when[dsu.par[u]], dsu.par[u]);
            }
        }
        cout << ans << '\n';
    }
}