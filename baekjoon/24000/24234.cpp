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

static const hash_t C = 1e11 + 19;

struct hash_interval {
    vector<hash_t> h, pw;
    hash_interval(string& str) : h(str.size() + 1), pw(h) {
        pw[0] = 1;
        for (int i = 0; i < int(str.size()); ++i) {
            h[i + 1] = h[i] * C + str[i];
            pw[i + 1] = pw[i] * C;
        }
    }
    // hash [st, ed)
    hash_t get_hash(int st, int ed) {
        return h[ed] - h[st] * pw[ed - st];
    }
};

vector<hash_t> hash_substrs(string& str, int length) {
    if (int(str.size()) < length) return {};
    hash_t h = 0, pw = 1;
    for (int i = 0; i < length; ++i) {
        h = h * C + str[i];
        pw = pw * C;
    }
    vector<hash_t> ret;
    ret.reserve(int(str.size()) - length + 1);
    ret.emplace_back(h);
    for (int i = length; i < int(str.size()); ++i) {
        h = h * C + str[i] - pw * str[i - length];
        ret.emplace_back(h);
    }
    return ret;
}

hash_t hash_str(const string& s) {
    hash_t h = 0;
    for (const auto& c : s) {
        h = h * C + c;
    }
    return h;
}

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
    int n, q;
    cin >> n >> q;
    vector<vector<int>> a(n);
    for (auto& vt : a) {
        size_t m;
        cin >> m;
        vt.resize(m);
        for (auto& x : vt) {
            cin >> x;
        }
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.size() > rhs.size();
    });
    hash_map<uint64_t, uint64_t> mp;
    array<uint64_t, 10001> res {};
    for (const auto& vt : a) {
        hash_t h = 0, h2 = 0;
        for (int j = 0; j < int(vt.size()); ++j, h = h2) {
            h2 = h * C + vt[j];
            if (j) res[vt[j - 1]] += mp[h.get()] - mp[h2.get()];
        }
        h = 0;
        for (int i = 0; i < int(vt.size()); ++i) {
            h = h * C + vt[i];
            ++mp[h.get()];
        }
    }
    for (int x; q--;) {
        cin >> x;
        cout << res[x] << '\n';
    }
}
