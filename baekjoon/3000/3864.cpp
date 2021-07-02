#include <bits/extc++.h>
#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

struct splitmix64_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

template <typename K, typename V, typename Hash = splitmix64_hash>
using hash_map = __gnu_pbds::gp_hash_table<K, V, Hash>;

template <typename K, typename Hash = splitmix64_hash>
using hash_set = hash_map<K, __gnu_pbds::null_type, Hash>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr uint64_t p = 131, m0 = 1e9 + 7, m1 = 1e9 + 9;

    hash_map<uint64_t, int> table;
    hash_map<uint64_t, pair<int, int>> table_pair;

TOP:;
    int n;
    string s;
    cin >> n;
    if (n == 0) return 0;
    cin >> s;

    if (n == 1) {
        cout << s.size() << ' ' << 0 << '\n';
        goto TOP;
    }

    auto parametric = [&](auto lo, auto hi) -> int {
        auto f = [&](auto mid) -> bool {
            uint64_t h0 = s[0], h1 = s[0], b0 = 1, b1 = 1;
            for (int i = 1; i < mid; ++i) {
                h0 = (h0 * p + s[i]) % m0;
                h1 = (h1 * p + s[i]) % m1;

                b0 = b0 * p % m0;
                b1 = b1 * p % m1;
            }

            table.clear();
            table[h0 << 32 | h1] = 1;

            for (int i = mid; i < int(s.size()); ++i) {
                h0 -= s[i - mid] * b0 % m0;
                h1 -= s[i - mid] * b1 % m1;
                if (h0 >= m0) h0 += m0;
                if (h1 >= m1) h1 += m1;
                h0 = (h0 * p + s[i]) % m0;
                h1 = (h1 * p + s[i]) % m1;

                if (++table[h0 << 32 | h1] == n)
                    return true;
            }
            return false;
        };

        // last true
        while (lo != hi) {
            auto mid = lo + (hi - lo + 1) / 2;
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    };

    const auto len = parametric(0, int(s.size()) - 1);

    if (len) {
        uint64_t h0 = s[0], h1 = s[0], b0 = 1, b1 = 1;
        for (int i = 1; i < len; ++i) {
            h0 = (h0 * p + s[i]) % m0;
            h1 = (h1 * p + s[i]) % m1;

            b0 = b0 * p % m0;
            b1 = b1 * p % m1;
        }

        table_pair.clear();
        table_pair[h0 << 32 | h1] = {1, 0};

        for (int i = len; i < int(s.size()); ++i) {
            h0 -= s[i - len] * b0 % m0;
            h1 -= s[i - len] * b1 % m1;
            if (h0 >= m0) h0 += m0;
            if (h1 >= m1) h1 += m1;
            h0 = (h0 * p + s[i]) % m0;
            h1 = (h1 * p + s[i]) % m1;

            ++table_pair[h0 << 32 | h1].first;
            table_pair[h0 << 32 | h1].second = i - len + 1;
        }

        int last_pos = -1;
        for (const auto& [cnt, val] : table_pair)
            if (val.first >= n)
                chmax(last_pos, val.second);
        cout << len << ' ' << last_pos << '\n';
    } else {
        cout << "none\n";
    }
    goto TOP;
}