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

void solve() {
    string a, b;
    cin >> a >> b;
    const int n = a.size() / 2 + 1;
    auto hash_tree = [&](const string& s) {
        vector<vector<int>> adj(n);
        vector<int> par(n), rev_dfn;
        vector<hash_t> dp(n);
        rev_dfn.reserve(n);
        int cur = 0, id = 0;
        for (const auto& c : s) {
            if (c == '0') {
                ++id;
                adj[cur].emplace_back(id);
                par[id] = cur, dp[id] = dp[cur] + 1;
                cur = id;
            } else {
                rev_dfn.emplace_back(cur);
                cur = par[cur];
            }
        }
        rev_dfn.emplace_back(0);
        for (const auto& u : rev_dfn) {
            sort(adj[u].begin(), adj[u].end(), [&](const auto& lhs, const auto& rhs) {
                return dp[lhs] < dp[rhs];
            });
            for (const auto& v : adj[u]) {
                dp[u] = dp[u] * C + dp[v];
            }
        }
        return dp[0];
    };
    cout << (hash_tree(a) == hash_tree(b)) << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}