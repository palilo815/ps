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
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second == rhs.second ? lhs.first < rhs.first : lhs.second < rhs.second;
    });
    int ans = 0;
    for (auto l = a.begin(), r = l; l != a.end(); l = r) {
        r = find_if_not(next(l), a.end(), [&](const auto& x) {
            return x.second == l->second;
        });
        ans += next(l)->first - l->first + prev(r)->first - prev(prev(r))->first;
        for (auto i = next(l); i != prev(r); ++i) {
            ans += min(next(i)->first - i->first, i->first - prev(i)->first);
        }
    }
    cout << ans;
}