#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    vector<int> a(n), pos(n), rank(n);
    iota(a.begin(), a.end(), 0);
    iota(pos.begin(), pos.end(), 0);
    iota(rank.begin(), rank.end(), 0);
    for (int i; k--;) {
        cin >> i, --i;
        const auto x = pos[i];
        const auto y = x ? x - 1 : n - 1;
        if (rank[a[x]] - 1 == rank[a[y]]) {
            --rank[a[x]], ++rank[a[y]];
        }
        swap(a[x], a[y]);
        pos[a[x]] = x, pos[a[y]] = y;
    }
    for (int i = 0; i < min(6, n); ++i) {
        cout << find(rank.begin(), rank.end(), i) - rank.begin() + 1 << ' ';
    }
}
