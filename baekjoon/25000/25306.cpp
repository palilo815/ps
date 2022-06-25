#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int64_t l, r;
    cin >> l >> r;
    auto xorsum = [](long long n) {
        const auto mod {n % 4};
        if (mod == 0) return n;
        if (mod == 1) return 1LL;
        if (mod == 2) return n + 1;
        return 0LL;
    };
    cout << (xorsum(l - 1) ^ xorsum(r));
}
