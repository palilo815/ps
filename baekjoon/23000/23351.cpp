#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k, a, b;
    cin >> n >> k >> a >> b;
    n /= a;
    int x = k, x_cnt = n;
    for (int day = 0;;) {
        if (!x) return cout << day, 0;
        day += x;
        const auto remain = x % n;
        x = x / n * b;
        remain < x_cnt ? (x_cnt -= remain) : (x += b, x_cnt += n - remain);
    }
}
