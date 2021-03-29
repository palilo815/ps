#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, l, k;
    cin >> n >> m >> l >> k;

    vector<pair<int, int>> a(k);
    for (auto& [x, y] : a) cin >> x >> y;

    vector<int> ord(k << 1);
    memmove(ord.data(), a.data(), sizeof(a[0]) * a.size());
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    int ans = 0;
    for (const auto& x : ord)
        for (const auto& y : ord)
            ans = max(ans, int(count_if(a.begin(), a.end(), [&](auto& pos) { return x <= pos.first && pos.first <= x + l && y <= pos.second && pos.second <= y + l; })));
    cout << k - ans;
}