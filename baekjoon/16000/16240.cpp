#include <bits/stdc++.h>
using namespace std;

struct disjoint_set {
    vector<int> par;
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
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    constexpr int mx_val = 1000;

    unordered_map<string, int> mp;
    int hash_val = mx_val;

    auto input = [&]() {
        vector<int> ret(n);
        string s;
        for (auto& x : ret) {
            cin >> s;
            if (isdigit(s[0])) x = stoi(s);
            else {
                if (!mp[s]) mp[s] = hash_val++;
                x = mp[s];
            }
        }
        return ret;
    };

    auto a = input();
    auto b = input();

    disjoint_set dsu(hash_val);

    for (int i = 0; i < n; ++i)
        dsu.merge(a[i], b[i]);

    vector<bool> check(hash_val);
    for (int i = 1; i < mx_val; ++i) {
        auto root = dsu.find(i);
        if (check[root]) return cout << "NE", 0;
        check[root] = true;
    }
    cout << "DA";
}