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
    int b, n;
    cin >> b >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    vector dp(n + 1, DBL_MAX);
    dp[0] = 0;
    while (b--) {
        for (int r = n; r; --r) {
            int sum = 0;
            double avg = 0, diff = 0;
            for (int l = r; l--;) {
                double new_avg = double(sum + a[l]) / (r - l);
                diff += pow(a[l] - new_avg, 2) + 2 * sum * (avg - new_avg) + (pow(new_avg, 2) - pow(avg, 2)) * (r - l - 1);
                if (dp[l] != DBL_MAX) chmin(dp[r], dp[l] + diff);
                sum += a[l], avg = new_avg;
            }
        }
    }
    cout << fixed << setprecision(9)
         << dp.back();
}