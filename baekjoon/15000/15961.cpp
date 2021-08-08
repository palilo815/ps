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
    int n, d, k, c;
    cin >> n >> d >> k >> c;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    int cur = 0;
    vector<int> cnt(d + 1);
    for (int i = 0; i < k; ++i) {
        if (++cnt[a[i]] == 1) {
            ++cur;
        }
    }
    int ans = cur + !cnt[c];
    for (int i = 0; i < n - 1; ++i) {
        if (++cnt[a[i + k < n ? i + k : i + k - n]] == 1) ++cur;
        if (--cnt[a[i]] == 0) --cur;
        chmax(ans, cur + !cnt[c]);
    }
    cout << ans << '\n';
}