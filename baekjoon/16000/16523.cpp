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

    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (auto& [d, c] : a) {
        cin >> d >> c;
        c <<= 2;
    }

    vector dp(n + 1, INF);
    dp[0] = 0;

    for (int i = 0; i < n; ++i) {
        int dsum = 0;
        for (int j = i + 1; j <= n && j <= i + 6 && dsum < 120; ++j) {
            dsum += a[j - 1].first;
            int csum = 0;
            for (int k = 0; k < j - i; ++k) {
                if (k == 0)
                    csum += a[i + k].second;
                else if (k == 1)
                    csum += a[i + k].second >> 1;
                else
                    csum += a[i + k].second >> 2;
            }
            chmin(dp[j], dp[i] + csum);
        }
    }

    cout << (dp.back() >> 2) << '.';
    cout << setw(2) << setfill('0') << ((dp.back() & 3) * 25);
}