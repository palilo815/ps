#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t k;
    cin >> n >> k;
    vector<int> jump(n), a(n);
    for (auto& x : a) cin >> x, --x;
    for (auto& x : jump) cin >> x, --x;
    for (vector<int> tmp(n); k; k >>= 1) {
        if (k & 1) {
            for (int i = 0; i < n; ++i) {
                tmp[jump[i]] = a[i];
            }
            a.swap(tmp);
        }
        for (int i = 0; i < n; ++i) {
            tmp[i] = jump[jump[i]];
        }
        jump.swap(tmp);
    }
    for (const auto& x : a) {
        cout << x + 1 << ' ';
    }
}