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
    constexpr int INF = 0x3f3f3f3f;
    int n, k;
    cin >> n >> k;
    vector dp(k + 1, INF);
    dp[0] = 0;
    for (int x; n--;) {
        cin >> x;
        for (int i = k; i >= x; --i) {
            chmin(dp[i], dp[i - x] + 1);
        }
    }
    cout << (dp.back() == INF ? -1 : dp.back());
}