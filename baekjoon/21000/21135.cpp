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

    int n, c;
    cin >> n >> c;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    vector<int> psum(n + 1);
    partial_sum(a.begin(), a.end(), psum.begin() + 1);

    chmin(c, psum.back());

    vector<char> dp(c + 1);
    dp[0] = 1;

    int ans = c;
    for (int i = n; i--;) {
        for (int w = c; w >= a[i]; --w)
            dp[w] |= dp[w - a[i]];
        for (int w = max(0, c - psum[i] - a[i] + 1); w + psum[i] < ans; ++w)
            if (dp[w]) {
                ans = w + psum[i];
                break;
            }
    }
    cout << ans;
}