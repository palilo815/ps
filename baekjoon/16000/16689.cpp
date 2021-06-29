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
    for (auto& [x, y] : a) cin >> x >> y;

    for (int truth = n; ~truth; --truth) {
        int is_true = 0;
        for (const auto& [x, y] : a)
            if (x <= truth && truth <= y)
                ++is_true;
        if (truth == is_true)
            return cout << truth, 0;
    }
    cout << -1;
}