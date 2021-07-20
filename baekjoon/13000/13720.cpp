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
    if (n & 1) {
        for (int i = 1; i <= n * n; ++i) {
            cout << i << " \n"[i % n == 0];
        }
    } else {
        if (n == 2) {
            cout << -1;
        } else {
            vector<int> a(n);
            for (int i = 0; i < n - 1; ++i) {
                a[i] = 20000 * (i + 1);
            }
            a.back() = a[n / 2] * n - accumulate(a.begin(), a.end(), 0);
            for (const auto& x : a) {
                cout << x << ' ';
            }
            cout << '\n';
            for (int i = 2; i < n / 2; ++i) {
                for (const auto& x : a) {
                    cout << x - i << ' ';
                }
                cout << '\n';
            }
            for (const auto& x : a) {
                cout << x - n / 2 - 1 << ' ';
            }
            cout << '\n';
            for (int i = 1; i <= n / 2; ++i) {
                for (const auto& x : a) {
                    cout << x + i << ' ';
                }
                cout << '\n';
            }
        }
    }
}