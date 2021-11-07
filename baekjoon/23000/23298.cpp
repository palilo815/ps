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

struct hash_interval {
    vector<hash_t> h, pw;
    hash_interval(string& str) : h(str.size() + 1), pw(h) {
        pw[0] = 1;
        for (int i = 0; i < int(str.size()); ++i) {
            h[i + 1] = h[i] * C + str[i];
            pw[i + 1] = pw[i] * C;
        }
    }
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<string> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    string s;
    cin >> s;
    a.erase(remove_if(a.begin(), a.end(), [&](const auto& x) {
        return x.size() > s.size() - 2;
    }),
        a.end());
    n = a.size();
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.size() < rhs.size();
    });
    vector<hash_t> hash_val(n);
    transform(a.begin(), a.end(), hash_val.begin(), hash_str);
    hash_set<int64_t> table;
    for (const auto& x : hash_val) {
        table.insert(x.get());
    }
    hash_interval hay(s);
    vector<int> l, r;
    for (int i = 0; i < n; ++i) {
        if (hay.get_hash(0, a[i].size()) == hash_val[i]) {
            l.emplace_back(a[i].size());
        }
        if (hay.get_hash(s.size() - a[i].size(), s.size()) == hash_val[i]) {
            r.emplace_back(s.size() - a[i].size());
        }
    }
    int64_t ans = 0;
    for (const auto& lptr : l) {
        for (const auto& rptr : r) {
            if (lptr >= rptr) break;
            ans += table.find(hay.get_hash(lptr, rptr).get()) != table.end();
        }
    }
    cout << ans;
}