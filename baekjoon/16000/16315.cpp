#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, d;
    cin >> n >> d;

    struct frog {
        int l, w, h;
    };

    vector<frog> a(n);
    for (auto& [l, w, h] : a)
        cin >> l >> w >> h;

    sort(a.begin(), a.end(), [&](auto& lhs, auto& rhs) {
        return lhs.w > rhs.w;
    });

    constexpr int mxW = 1e8;
    vector<int> dp(mxW + 1);

    int ans = 0;
    for (const auto& [l, w, h] : a) {
        ans += (l + dp[w] > d);
        for (int i = 1, ed = min(w, mxW + 1 - w); i < ed; ++i)
            chmax(dp[i], h + dp[w + i]);
    }
    cout << ans;
}