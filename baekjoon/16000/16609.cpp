#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    int64_t x = 1, y = 1;
    for (int i = 0; i < n; ++i) {
        if (a[i] > i + 1) return cout << "impossible", 0;
        if (x * (i + 1) > y * a[i])
            x = a[i], y = i + 1;
    }
    cout << fixed << setprecision(9) << double(x) / y;
}