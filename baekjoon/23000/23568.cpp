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
    int n;
    cin >> n;
    hash_map<int, int> nxt;
    for (int u, v; n--;) {
        char op;
        cin >> u >> op >> v;
        nxt[u] = u + (op == 'R' ? v : -v);
    }
    cin >> n;
    for (;;) {
        auto v = nxt.find(n);
        if (v == nxt.end()) break;
        n = v->second;
    }
    cout << n;
}