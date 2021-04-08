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

    vector<int> a(n), b(n);
    for (auto& x : a) cin >> x;

    int m;
    cin >> m;

    vector<pair<int, int>> swp(m);
    for (auto& [x, y] : swp) cin >> x >> y;

    // applied [0, mid)
    auto valid = [&](int mid) {
        b.assign(a.begin(), a.end());
        for (int i = 0; i < mid; ++i)
            swap(b[swp[i].first], b[swp[i].second]);

        int need = 0;
        for (int i = 0; i < n; ++i)
            for (; i != b[i]; ++need)
                swap(b[i], b[b[i]]);
        return need <= mid;
    };

    int lo = 0, hi = m;
    while (lo != hi) {
        int mid = (lo + hi) >> 1;
        valid(mid) ? hi = mid : lo = mid + 1;
    }

    b.assign(a.begin(), a.end());
    for (int i = 0; i < lo; ++i)
        swap(b[swp[i].first], b[swp[i].second]);

    vector<pair<int, int>> ans;
    ans.reserve(lo);

    for (int i = 0; i < n; ++i)
        while (i != b[i]) {
            ans.emplace_back(b[i], b[b[i]]);
            swap(b[i], b[b[i]]);
        }
    while (int(ans.size()) < lo) ans.emplace_back(0, 0);

    vector<int> idx(n);
    for (int i = 0; i < n; ++i)
        idx[a[i]] = i;

    for (int i = 0; i < lo; ++i) {
        swap(idx[a[swp[i].first]], idx[a[swp[i].second]]);
        swap(a[swp[i].first], a[swp[i].second]);
        const pair p = {idx[ans[i].first], idx[ans[i].second]};

        swap(a[idx[ans[i].first]], a[idx[ans[i].second]]);
        swap(idx[ans[i].first], idx[ans[i].second]);
        ans[i] = p;
    }

    cout << lo << '\n';
    for (const auto& [x, y] : ans)
        cout << x << ' ' << y << '\n';
}