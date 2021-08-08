#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) cin >> x;
    sort(a.begin(), a.end());
    rotate(a.begin(), a.begin() + n - k, a.end());
    if (n != k && a.back() > k) return cout << -1, 0;
    for (int i = 0; i < k; ++i) {
        if (a[i] <= i) {
            return cout << -1, 0;
        }
    }
    reverse(a.begin(), a.end());
    for (const auto& x : a) {
        cout << x << ' ';
    }
}