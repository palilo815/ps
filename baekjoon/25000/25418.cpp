#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    unsigned a, k;
    cin >> a >> k;
    auto diff = bit_width(k) - bit_width(a);
    auto b = k >> diff;
    if (a > b) {
        --diff;
        b = k >> diff;
    }
    cout << b - a + diff + popcount(k ^ b << diff);
}
