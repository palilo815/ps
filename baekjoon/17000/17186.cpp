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

    constexpr int NEG = 0xc0c0c0c0;

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> a(n), b(m);
    for (auto& x : a) cin >> x;
    for (auto& x : b) cin >> x;

    if (any_of(a.begin(), a.end(), [&](auto& x) { return x < k; }))
        return cout << "Impossible", 0;

    vector dp(accumulate(b.begin(), b.end(), 1), NEG);
    dp[0] = 0;

    // dp[i] = b값 합이 i일 때 가능한 최대 박스 크기
    int sum = 0;
    for (const auto& x : b) {
        for (int i = sum, add = min(x, n); ~i; --i)
            if (dp[i] != NEG)
                chmax(dp[i + x], dp[i] + add);
        sum += x;
    }

    int asum = accumulate(a.begin(), a.end(), 0);
    for (int i = asum; i < int(dp.size()); ++i)
        if (dp[i] >= n * k)
            return cout << i - asum, 0;
    cout << "Impossible";
}