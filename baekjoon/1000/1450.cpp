#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, c;
    cin >> n >> c;

    const int nl = n >> 1, nr = n - nl;

    vector<int> l(nl), r(nr);
    for (auto& x : l) cin >> x;
    for (auto& x : r) cin >> x;

    auto get_weights = [&](const vector<int>& a) {
        const int n = a.size();
        vector<int> weights;
        for (int mask = 1; mask != 1 << n; ++mask) {
            int64_t sum = 0;
            for (int i = 0; i < n; ++i)
                if (mask >> i & 1)
                    sum += a[i];
            if (sum <= c) weights.emplace_back(sum);
        }
        return weights;
    };

    auto wl = get_weights(l), wr = get_weights(r);
    sort(wl.begin(), wl.end(), greater<int>());
    sort(wr.begin(), wr.end());

    int ans = wl.size() + wr.size() + 1, i = 0;
    for (const auto& w : wr) {
        while (i < int(wl.size()) && w + wl[i] > c) ++i;
        ans += int(wl.size()) - i;
    }
    cout << ans;
}