#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h>
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

template <typename K, typename V>
using hash_map = __gnu_pbds::gp_hash_table<K, V, splitmix64_hash>;

template <typename K>
using hash_set = hash_map<K, __gnu_pbds::null_type>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int64_t m1 = 1610612741;
    constexpr int64_t m2 = 1919191969;
    constexpr int64_t p1 = 307;
    constexpr int64_t p2 = 409;
    int c, n;
    cin >> c >> n;
    char buf[2001];
    vector<pair<int, int>> hash_colour(c);
    for (auto& [h1, h2] : hash_colour) {
        cin >> buf;
        for (auto it = buf; *it; ++it) {
            h1 = (h1 * p1 + *it) % m1;
            h2 = (h2 * p2 + *it) % m2;
        }
    }
    hash_set<int64_t> table;
    for (int i = 0; i < n; ++i) {
        cin >> buf;
        int64_t h1 = 0, h2 = 0, pw1 = 1, pw2 = 1;
        for (auto it = buf; *it; ++it) {
            h1 = (h1 * p1 + *it) % m1;
            h2 = (h2 * p2 + *it) % m2;
            pw1 = pw1 * p1 % m1;
            pw2 = pw2 * p2 % m2;
        }
        for (const auto& [c1, c2] : hash_colour) {
            int64_t combined1 = (c1 * pw1 + h1) % m1;
            int64_t combined2 = (c2 * pw2 + h2) % m2;
            table.insert(combined1 << 32 | combined2);
        }
    }
    for (cin >> n; n--;) {
        cin >> buf;
        int64_t h1 = 0, h2 = 0;
        for (auto it = buf; *it; ++it) {
            h1 = (h1 * p1 + *it) % m1;
            h2 = (h2 * p2 + *it) % m2;
        }
        cout << (table.find(h1 << 32 | h2) == table.end() ? "No\n" : "Yes\n");
    }
}