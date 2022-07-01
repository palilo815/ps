#include <bits/stdc++.h>

template <class T, class F>
class BinaryIndexedTree {
    const size_t n;
    const T e;
    const F f;
    std::vector<T> tree;

public:
    BinaryIndexedTree(size_t n, T e, F f) : n(n), e(e), f(f), tree(n + 1, e) {}

    auto update(size_t i, T val) {
        assert(i <= n);
        for (++i; i <= n; i += i & -i) {
            tree[i] = f(tree[i], val);
        }
    }
    [[nodiscard]] auto prefix(size_t i) const {
        assert(i <= n);
        auto ret = e;
        for (; i; i &= i - 1) {
            ret = f(ret, tree[i]);
        }
        return ret;
    }
};

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<tuple<int, int, int64_t>> a(n);
    for (auto& [b, f, d] : a) {
        cin >> b >> f >> d;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return get<0>(lhs) != get<0>(rhs) ? get<0>(lhs) < get<0>(rhs) : get<1>(lhs) > get<1>(rhs);
    });
    {
        auto it = a.begin();
        for (auto jt = it; jt != a.end(); ++it) {
            for (*it = *jt++; jt != a.end() && get<0>(*it) == get<0>(*jt) && get<1>(*it) == get<1>(*jt); ++jt) {
                get<2>(*it) += get<2>(*jt);
            }
        }
        a.erase(it, a.end());
    }
    vector<int> comp(n);
    transform(a.begin(), a.end(), comp.begin(), [&](const auto& x) {
        return get<1>(x);
    });
    sort(comp.begin(), comp.end());
    comp.erase(unique(comp.begin(), comp.end()), comp.end());
    for (auto& [_, f, __] : a) {
        f = lower_bound(comp.begin(), comp.end(), f) - comp.begin();
    }
    BinaryIndexedTree bit(comp.size(), 0LL, [](const auto& l, const auto& r) { return max(l, r); });
    for (const auto& [_, f, d] : a) {
        bit.update(f, bit.prefix(f) + d);
    }
    cout << bit.prefix(comp.size());
}
