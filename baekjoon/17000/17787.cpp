#include <bits/stdc++.h>
using namespace std;

const int mxN = 3e5;

int a[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int k;
    cin >> k;

    vector<int> ans, vt;
    for (int i = 1, n; i <= k; ++i) {
        cin >> n;
        for (int j = 0; j < n; ++j)
            cin >> a[j];

        vt.clear();
        bool ok = false;
        for (int j = 0, alice = INT_MAX; j < n; ++j) {
            if (a[j] > alice) {
                ok = true;
                break;
            }
            for (; !vt.empty() && vt.back() > a[j]; vt.pop_back())
                alice = min(alice, vt.back());
            vt.emplace_back(a[j]);
        }
        if (ok) ans.emplace_back(i);
    }

    cout << ans.size() << '\n';
    for (auto& x : ans) cout << x << '\n';
}