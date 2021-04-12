#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<pair<int, int>> vt1, vt2;
    for (int a, b; n--;) {
        cin >> a >> b;
        (a <= b ? vt1 : vt2).emplace_back(a, b);
    }

    sort(vt1.begin(), vt1.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });
    sort(vt2.begin(), vt2.end(), [&](auto& a, auto& b) {
        return a.second > b.second;
    });

    int64_t ans = 0, capa = 0;
    for (const auto& [a, b] : vt1) {
        if (capa < a) ans += a - capa, capa = a;
        capa += b - a;
    }
    for (const auto& [a, b] : vt2) {
        if (capa < a) ans += a - capa, capa = a;
        capa += b - a;
    }
    cout << ans;
}