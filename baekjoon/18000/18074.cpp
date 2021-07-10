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
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    const int mx = *max_element(a.begin() + 1, a.end());
    partial_sum(a.begin(), a.end(), a.begin());
    vector ans(a.back() + 1, -1);
    fill(ans.begin(), ans.begin() + mx, 0);
    auto solve = [&](int sz) {
        int cnt = 0;
        for (auto it = a.begin() + 1; it != a.end(); ++cnt) {
            it = upper_bound(it, a.end(), *prev(it) + sz);
        }
        ans[sz] = cnt;
    };
    int q;
    cin >> q;
    for (int x; q--;) {
        cin >> x;
        if (ans[x] == -1) {
            solve(x);
        }
        if (ans[x]) {
            cout << ans[x] << '\n';
        } else {
            cout << "Impossible\n";
        }
    }
}