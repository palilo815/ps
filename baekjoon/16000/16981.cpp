#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> a(n);
    for (auto& [val, sz] : a) cin >> sz >> val;

    vector<int> c(m);
    for (auto& x : c) cin >> x;

    sort(a.rbegin(), a.rend());
    sort(c.rbegin(), c.rend());

    int i = 0;
    for (const auto& [_, sz] : a)
        if (i != m && c[i] >= sz)
            ++i;
    cout << i;
}