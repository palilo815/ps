#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<bitset<2000>> a(n);
    for (auto& x : a) cin >> x;

    int q;
    cin >> q;

    for (int u, v; q--;) {
        cin >> u >> v, --u, --v;
        cout << (a[u] & a[v]).count() << '\n';
    }
}