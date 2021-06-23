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

    vector<int> dont(m);
    for (auto& x : dont) {
        int u, v;
        cin >> u >> v, --u, --v;
        x = 1 << u | 1 << v;
    }

    int ans = 0;
    for (int mask = 1 << n; mask--;)
        ans += none_of(dont.begin(), dont.end(), [&](auto& x) { return (mask & x) == x; });
    cout << ans;
}