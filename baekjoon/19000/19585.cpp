#include <bits/stdc++.h>
using namespace std;

struct hash_t {
    uint64_t x;
    hash_t() = default;
    hash_t(uint64_t x) : x(x) {}
#define OP(O, A, B)                         \
    hash_t operator O(hash_t o) {           \
        uint64_t r = x;                     \
        asm(A "addq %%rdx, %0\n adcq $0,%0" \
            : "+a"(r)                       \
            : B);                           \
        return r;                           \
    }
    OP(+, , "d"(o.x))
    OP(*, "mul %1\n", "r"(o.x)
        : "rdx")
    hash_t operator-(const hash_t& o) { return *this + ~o.x; }
    uint64_t get() const { return x + !~x; }
    bool operator==(const hash_t& o) const { return get() == o.get(); }
    bool operator<(const hash_t& o) const { return get() < o.get(); }
};

static const hash_t C = 1e11 + 3;

#include <bits/extc++.h>
struct splitmix64_hash {
    // http://xorshift.di.unimi.it/splitmix64.c
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(hash_t x) const {
        static const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.get() + FIXED_RANDOM);
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
    int c, n;
    cin >> c >> n;
    char buf[2001];
    vector<hash_t> hash_colour(c);
    for (auto& h : hash_colour) {
        cin >> buf;
        for (auto it = buf; *it; ++it) {
            h = h * C + *it;
        }
    }
    hash_set<hash_t> table;
    for (hash_t h, pw; n--;) {
        cin >> buf;
        h = 0, pw = 1;
        for (auto it = buf; *it; ++it) {
            h = h * C + *it;
            pw = pw * C;
        }
        for (auto hc : hash_colour) {
            table.insert(hc * pw + h);
        }
    }
    cin >> n;
    for (hash_t h; n--;) {
        cin >> buf;
        h = 0;
        for (auto it = buf; *it; ++it) {
            h = h * C + *it;
        }
        cout << (table.find(h) == table.end() ? "No\n" : "Yes\n");
    }
}