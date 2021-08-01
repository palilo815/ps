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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    const int s = accumulate(a.begin(), a.end(), 0);
    vector<int> dp(s + 1, -1), prv(s + 1);
    dp[0] = 0;
    for (const auto& x : a) {
        dp.swap(prv);
        memcpy(dp.data(), prv.data(), sizeof(int) * dp.size());
        for (int i = 0; i <= s; ++i) {
            if (prv[i] == -1) {
                continue;
            }
            chmax(dp[i + x], prv[i] + x);
            chmax(dp[abs(i - x)], prv[i] + x);
        }
    }
    cout << (dp[0] > 0 ? dp[0] / 2 : -1);
}