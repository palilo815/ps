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
    vector<int> a(m);
    for (auto& x : a) {
        cin >> x, --x;
    }
    vector cost(n, vector<int>(n));
    for (auto& vt : cost) {
        for (auto& x : vt) {
            cin >> x;
        }
    }
    int ans = 0;
    for (int i = 1; i < m; ++i) {
        ans += cost[a[i - 1]][a[i]];
    }
    cout << ans;
}