#include "traffic.h"
#include <bits/stdc++.h>

namespace std {
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

int LocateCentre(int n, int p[], int s[], int d[]) {
    using namespace std;
    vector<int> counter(n + 1);
    for (int i = 0; i + 1 < n; ++i) {
        ++counter[s[i] + 1];
        ++counter[d[i] + 1];
    }
    partial_sum(counter.begin(), counter.end(), counter.begin());
    const auto start(counter);
    vector<int> elist((n - 1) << 1);
    for (int i = 0; i + 1 < n; ++i) {
        elist[counter[s[i]]++] = d[i];
        elist[counter[d[i]]++] = s[i];
    }
    y_combinator([&](auto self, int u, int par) -> void {
        for (int i = start[u]; i < start[u + 1]; ++i) {
            const auto& v = elist[i];
            if (v == par) continue;
            self(v, u);
            p[u] += p[v];
        }
    })(0, -1);
    const auto total = p[0];
    pair ans(INT_MAX, INT_MAX);
    y_combinator([&](auto self, int u, int par) -> void {
        pair res(total - p[u], u);
        for (int i = start[u]; i < start[u + 1]; ++i) {
            const auto& v = elist[i];
            if (v == par) continue;
            res.first = max(res.first, p[v]);
            self(v, u);
        }
        ans = min(ans, res);
    })(0, -1);
    return ans.second;
}
