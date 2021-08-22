#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> a(n * k);
    for (int i = 0; i < n; ++i) {
        for (int j = 0, x; j < k; ++j) {
            cin >> x;
            a[i * k + j] = {i, x};
        }
    }
    for (auto it = a.begin(); a.size() != 1;) {
        auto nxt = it + it->second - 1;
        a.erase(it);
        while (nxt >= a.end()) nxt -= a.size();
        it = nxt;
    }
    cout << a[0].first + 1 << ' ' << a[0].second;
}