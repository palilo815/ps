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
    vector<int> dp;
    for (int i = 0, x; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> x;
            if (x) {
                const auto it = lower_bound(dp.begin(), dp.end(), j, greater());
                if (it == dp.end()) {
                    dp.emplace_back(j);
                } else {
                    *it = j;
                }
            }
        }
    }
    cout << dp.size();
}