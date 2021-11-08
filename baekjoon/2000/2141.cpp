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
        return lhs.first < rhs.first;
    });
    auto need = (accumulate(a.begin(), a.end(), int64_t(0), [&](const auto& sum, const auto& x) {
        return sum + x.second;
    }) + 1) / 2;
    for (const auto& [x, y] : a) {
        need -= y;
        if (need <= 0) return cout << x, 0;
    }
    assert(false);
}