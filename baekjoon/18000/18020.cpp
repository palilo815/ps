#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    cout << []() -> int {
        int64_t n, m, a;
        cin >> n >> m >> a;

        if (a % n == 0 || a % m == 0) return 1;

        int64_t b = n * m - a;
        for (int64_t i = 1; i < n; ++i)
            if ((a % i == 0 && a / i <= m) || (b % i == 0 && b / i <= m))
                return 2;
        for (int64_t i = 1; i < m; ++i)
            if ((a % i == 0 && a / i <= n) || (b % i == 0 && b / i <= n))
                return 2;

        return 3;
    }();
}