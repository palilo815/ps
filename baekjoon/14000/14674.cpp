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
    vector<array<int, 3>> a(n);
    for (auto& [x, y, z] : a) {
        cin >> x >> y >> z;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        const auto l = int64_t(lhs[2]) * rhs[1],
                   r = int64_t(rhs[2]) * lhs[1];
        if (l != r) return l > r;
        if (lhs[1] != rhs[1]) return lhs[1] < rhs[1];
        return lhs[0] < rhs[0];
    });
    for (int i = 0; i < k; ++i) {
        cout << a[i][0] << '\n';
    }
}