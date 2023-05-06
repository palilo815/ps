#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    array<int64_t, 100'000> a;
    for (auto _ = n; _--;) {
        int m;
        cin >> m;
        for (auto i = 0; i < m; ++i) {
            cin >> a[i];
        }
        int64_t maj = 0;
        int cnt = 0;
        for (auto i = 0; i < m; ++i) {
            if (cnt == 0) {
                maj = a[i], cnt = 1;
            } else if (maj == a[i]) {
                ++cnt;
            } else {
                --cnt;
            }
        }
        if (count(a.begin(), a.begin() + m, maj) > m / 2) {
            cout << maj << '\n';
        } else {
            cout << "SYJKGW\n";
        }
    }
}
