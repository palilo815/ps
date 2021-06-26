#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<int> relative_sum(k);

    auto cmp = [&](const vector<int>& a, const vector<int>& b) {
        for (int i = 0; i < k; ++i)
            if (a[i] != b[i])
                return a[i] < b[i];
        return false;
    };
    map<vector<int>, int, decltype(cmp)> mp(cmp);
    mp[relative_sum] = -1;

    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j)
            if (a[i] >> j & 1)
                ++relative_sum[j];

        auto mn = *min_element(relative_sum.begin(), relative_sum.end());
        for (auto& x : relative_sum)
            x -= mn;

        if (auto it = mp.find(relative_sum); it == mp.end())
            mp[relative_sum] = i;
        else
            chmax(ans, i - it->second);
    }
    cout << ans;
}