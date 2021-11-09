#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
public:
    vector<int> par;
    disjoint_set(size_t n) : par(n, -1) {}

    int find(size_t u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    void unite(const size_t win, const size_t lose) {
        const auto u = find(win), v = find(lose);
        if (u == v) {
            par[win] = par[u];
            par[lose] = win;
            return;
        }
        par[u] += par[v];
        par[v] = u;
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
    vector<string> a(n);
    string s;
    for (auto& x : a) {
        cin >> s >> s >> x;
    }
    sort(a.begin(), a.end());
    disjoint_set dsu(n);
    for (int u, v; m--;) {
        cin >> s >> s >> s;
        u = lower_bound(a.begin(), a.end(), s.substr(0, s.find(','))) - a.begin();
        cin >> s >> s;
        v = lower_bound(a.begin(), a.end(), s.substr(0, s.find(','))) - a.begin();
        if (s.back() == '2') swap(u, v);
        dsu.unite(u, v);
    }
    cout << count_if(dsu.par.begin(), dsu.par.end(), [&](const auto& x) {
        return x < 0;
    }) << '\n';
    for (int i = 0; i < n; ++i) {
        if (dsu.par[i] < 0) {
            cout << "Kingdom of " << a[i] << '\n';
        }
    }
}