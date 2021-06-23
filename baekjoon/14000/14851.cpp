#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int BLOCK = 3125; // 3125 * 64 == 2e5
    using my_bitset = array<unsigned long long, BLOCK>;

    auto input = []() {
        string s;
        cin >> s;

        vector<my_bitset> bit_vector(64);

        int block_id = 0, bit_id = 0;
        for (const auto& c : s) {
            bit_vector[0][block_id] |= uint64_t(c == '1') << bit_id;
            if (++bit_id == 64)
                bit_id = 0, ++block_id;
        }

        for (int i = 1; i < 64; ++i) {
            for (int b = 0; b < BLOCK - 1; ++b)
                bit_vector[i][b] = (bit_vector[i - 1][b] >> 1) | (bit_vector[i - 1][b + 1] << 63);
            bit_vector[i].back() = bit_vector[i - 1].back() >> 1;
        }
        return bit_vector;
    };

    auto a_vector = input(), b_vector = input();

    int q;
    cin >> q;

    for (int i, j, len; q--;) {
        cin >> i >> j >> len;
        const auto &a = a_vector[i & 63], &b = b_vector[j & 63];
        int ans = 0;
        for (i >>= 6, j >>= 6; len >= 64; len -= 64, ++i, ++j)
            ans += __builtin_popcountll(a[i] ^ b[j]);
        if (len) ans += __builtin_popcountll((a[i] ^ b[j]) & ((1ull << len) - 1ull));
        cout << ans << '\n';
    }
}