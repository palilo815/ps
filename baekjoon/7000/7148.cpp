#include <bits/stdc++.h>
using namespace std;

constexpr int mxN = 1e3;
constexpr int mxM = 1e5;

struct edge {
    int u, v;
};

int w[mxM], par[mxN], dist[mxN];
edge e[mxM];

int find(int u) {
    while (par[u] >= 0) u = par[u];
    return u;
}
bool merge(int id) {
    int u = find(e[id].u), v = find(e[id].v);
    if (u == v) return false;

    if (par[u] > par[v]) swap(u, v);
    par[u] += par[v];
    par[v] = u;

    dist[v] = w[id];
    return true;
}
int query(int u, int v) {
    int ret = INT_MAX;
    for (; u != v; u = par[u]) {
        if (dist[u] < dist[v]) swap(u, v);
        ret = dist[u];
    }
    return ret;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
START:
    int n, m;
    cin >> n >> m;
    if (n == 0) return 0;

    for (int i = 0; i < m; ++i) {
        cin >> e[i].u >> e[i].v >> w[i];
        --e[i].u, --e[i].v;
    }

    auto cmp = [&](int a, int b) { return w[a] == w[b] ? a < b : w[a] > w[b]; };
    set<int, decltype(cmp)> st(cmp);

    for (int i = 0; i < m; ++i)
        st.emplace(i);

    int q;
    cin >> q;

    bool updated = true;
    for (int a, b, c; q--;) {
        char op;
        cin >> op;
        if (op == 'S') {
            if (updated) {
                memset(par, -1, sizeof(int) * n);
                memset(dist, -1, sizeof(int) * n);

                int need = n - 1;
                for (const auto id : st)
                    if (merge(id) && --need == 0)
                        break;
                updated = false;
            }
            cin >> a >> b >> c, --a, --b;
            cout << (query(a, b) >= c) << '\n';
        } else {
            cin >> a >> c, --a;
            st.erase(a);
            w[a] = c;
            st.emplace(a);
            updated = true;
        }
    }
    goto START;
}