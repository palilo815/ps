#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for (auto i {1}; i <= n * m; ++i) {
        cout << i << " \n"[i % m == 0];
    }
}
