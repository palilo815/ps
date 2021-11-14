#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr size_t MX_N = 1e3;
constexpr int INF = 0x3f3f3f3f;

array<int, MX_N * 100 + 1> dp, prv;

void solve() {
    int n;
    cin >> n;
    const size_t sz = sizeof(int) * (n * 100 + 1);
    memset(dp.begin(), 0x3f, sz);
    dp[0] = 0;
    int sum = 0;
    for (int a, b; n--; sum += a) {
        cin >> a >> b;
        dp.swap(prv);
        memset(dp.begin(), 0x3f, sz);
        for (int i = 0; i <= sum; ++i) {
            if (prv[i] != INF) {
                chmin(dp[i + a], prv[i]);
                chmin(dp[i], prv[i] + b);
            }
        }
    }
    int ans = INF;
    for (int i = 0; i <= sum; ++i) {
        chmin(ans, max(i, dp[i]));
    }
    cout << ans << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}