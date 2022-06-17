#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    constexpr int64_t MOD {1'000'000'007};
    int64_t n;
    cin >> n;
    const auto sum {(n + 1) * n / 2};
    int64_t score {}, fac {1};
    for (; n; --n) {
        score += (sum + n) * n;
        fac *= n;
        score %= MOD, fac %= MOD;
    }
    cout << score << ' ' << fac * fac % MOD;
}
