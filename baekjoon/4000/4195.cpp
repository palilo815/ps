#include <bits/stdc++.h>
using namespace std;

const int mx = 1e5;

int par[mx << 1 | 1];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
void solve() {
    unordered_map<string, int> mp;
    int cnt = 0;

    int N; cin >> N;
    memset(par + 1, -1, sizeof(int) * N * 2);
    for (string a, b; N--;) {
        cin >> a >> b;
        int u = mp[a], v = mp[b];

        if (!u) u = mp[a] = ++cnt;
        if (!v) v = mp[b] = ++cnt;

        u = _find(u), v = _find(v);
        if (u ^ v) {
            if (u < v) swap(u, v);
            par[v] += par[u];
            par[u] = v;
        }
        cout << -par[v] << '\n';
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}