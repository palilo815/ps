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
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    int ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        ans += abs(a[i].first - a[i + 1].first) + abs(a[i].second - a[i + 1].second);
    }
    cout << ans;
}