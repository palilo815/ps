#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int64_t x;
    int n;
    cin >> x >> n;
    for (int64_t a, b; n--;) {
        cin >> a >> b;
        x -= a * b;
    }
    cout << (x ? "No" : "Yes");
}
