#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    cin >> k;
    const auto total = accumulate(a.begin(), a.end(), 0);
    double ans = 0;
    for (const auto& x : a) {
        if (x < k) continue;
        double res = 1;
        for (int i = 0; i < k; ++i) {
            res *= double(x - i) / (total - i);
        }
        ans += res;
    }
    cout << fixed << setprecision(12)
         << ans;
}