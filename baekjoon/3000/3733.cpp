#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, s;
    while (cin >> n >> s) {
        cout << s / (n + 1) << '\n';
    }
}
