#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t n, a;
    cin >> n >> a;
    a %= n;

    auto neg = [&]() { return a ? n - a : 0; };
    auto inv = [&]() {
        int64_t m0 = 0, m1 = 1, m = n;
        while (a) {
            auto t = m / a;
            m -= t * a;
            swap(a, m);
            m0 -= t * m1;
            swap(m0, m1);
        }
        return m == 1 ? (m0 < 0 ? m0 + n : m0) : -1;
    };

    cout << neg() << ' ' << inv();
}