#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    auto ord = a;
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    for (auto& x : a)
        x = lower_bound(ord.begin(), ord.end(), x) - ord.begin();

    auto& pos = ord;
    pos.resize(n);

    vector<int> lt(n);
    fill(pos.begin(), pos.end(), -1);
    for (int i = 0; i < n; ++i) {
        lt[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    vector<int> rt(n);
    fill(pos.begin(), pos.end(), n);
    for (int i = n; i--;) {
        rt[i] = pos[a[i]];
        pos[a[i]] = i;
    }

    function<bool(int, int)> solve = [&](int l, int r) {
        if (r - l <= 1) return true;
        for (int i = l, j = r - 1; l <= j; ++i, --j) {
            if (lt[i] < l && r <= rt[i])
                return solve(l, i) && solve(i + 1, r);
            if (lt[j] < l && r <= rt[j])
                return solve(l, j) && solve(j + 1, r);
        }
        return false;
    };

    if (solve(0, n)) cout << "non-";
    cout << "boring\n";
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}