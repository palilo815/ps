#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    string s;
    cin >> n >> s;

    auto valid = [&](int len) {
        constexpr int64_t p = 31, m0 = 1e9 + 7, m1 = 1e9 + 9;

        int64_t h0 = s[0], h1 = s[0], b0 = 1, b1 = 1;
        for (int i = 1; i < len; ++i) {
            h0 = (h0 * p + s[i]) % m0;
            h1 = (h1 * p + s[i]) % m1;

            b0 = b0 * p % m0;
            b1 = b1 * p % m1;
        }

        unordered_set<int64_t> st = {h0 << 32 | h1};
        for (int i = len; i < n; ++i) {
            h0 -= s[i - len] * b0 % m0;
            if (h0 < 0) h0 += m0;
            h0 = (h0 * p + s[i]) % m0;

            h1 -= s[i - len] * b1 % m1;
            if (h1 < 0) h1 += m1;
            h1 = (h1 * p + s[i]) % m1;
            if (!st.emplace(h0 << 32 | h1).second)
                return true;
        }
        return false;
    };

    int lo = 0, hi = n - 1;
    while (lo != hi) {
        const int mid = lo + hi + 1 >> 1;
        valid(mid) ? lo = mid : hi = mid - 1;
    }
    cout << lo;
}