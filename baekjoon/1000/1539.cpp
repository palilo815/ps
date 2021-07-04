#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, x;
    cin >> n >> x;

    map<int, int> mp;
    mp[x] = 1;

    for (int i = 1; i < n; ++i) {
        cin >> x;
        auto it = mp.lower_bound(x);
        int c = max(it == mp.begin() ? 0 : prev(it)->second, it == mp.end() ? 0 : it->second);
        mp.emplace_hint(it, x, c + 1);
    }

    cout << accumulate(mp.begin(), mp.end(), 0ll, [&](const auto& sum, const auto& elem) {
        return sum + elem.second;
    });
}