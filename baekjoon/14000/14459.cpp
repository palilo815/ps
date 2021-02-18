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

    vector<int> a(n), pos(n);
    for (auto& x : a) cin >> x, --x;
    for (int i = 0, x; i < n; ++i) {
        cin >> x, --x;
        pos[x] = i;
    }

    vector<int> dp = {INT_MIN}; // sentinel

    vector<int> candi;
    candi.reserve(9);

    for (int i = 0; i < n; ++i) {
        candi.clear();
        for (int j = max(0, a[i] - 4), hi = min(n, a[i] + 5); j != hi; ++j)
            candi.emplace_back(pos[j]);
        sort(candi.rbegin(), candi.rend());

        for (const auto& x : candi)
            if (x > dp.back())
                dp.emplace_back(x);
            else
                *lower_bound(dp.begin(), dp.end(), x) = x;
    }
    cout << dp.size() - 1;
}