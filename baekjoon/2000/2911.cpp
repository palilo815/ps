#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> a(n);
    for (auto& [p, c] : a) cin >> p >> c;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    int64_t ans = 0;
    int prv = 0;
    for (const auto& [_, c] : a) {
        if (c > prv) ans += c - prv;
        prv = c;
    }
    cout << ans;
}