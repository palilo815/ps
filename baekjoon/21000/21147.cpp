#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    int64_t ans = 0;
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 1; j < n; ++j) {
            int cnt = 0;
            for (int k = 0; k < n; ++k)
                if (k != i && k != j && a[k] > a[i] && a[k] > a[j] && a[i] + a[j] > a[k])
                    ++cnt;
            ans += (1ll << cnt) - 1;
        }
    cout << ans;
}