#include <bits/stdc++.h>

template <typename T>
class BinaryIndexedTree {
    static constexpr size_t n = 3e5 + 1;
    std::array<T, n + 1> tree {};

public:
    BinaryIndexedTree() = default;

    auto update(size_t i, T val) {
        assert(i <= n);
        for (++i; i <= n; i += i & -i) {
            tree[i] += val;
        }
    }
    [[nodiscard]] auto sum(size_t i) const {
        assert(i <= n);
        T ret = 0;
        for (; i; i &= i - 1) {
            ret += tree[i];
        }
        return ret;
    }
    [[nodiscard]] auto sum(size_t l, size_t r) const {
        assert(l <= r && r <= n);
        return sum(r) - sum(l);
    }
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, q;
    string colour;
    cin >> n >> q >> colour;
    BinaryIndexedTree<int> c, z;
    {
        const auto cnt_c = count(colour.begin(), colour.end(), 'C');
        c.update(0, cnt_c), z.update(0, n - cnt_c);
    }
    vector<int> score(n);
    int64_t ans = 0;
    for (int i, d; q--;) {
        cin >> i >> d, --i;
        if (colour[i] == 'C') {
            ans += z.sum(score[i], score[i] + d);
            c.update(score[i], -1);
            score[i] += d;
            c.update(score[i], 1);
        } else {
            ans -= c.sum(score[i] + 1, score[i] + d + 1);
            z.update(score[i], -1);
            score[i] += d;
            z.update(score[i], 1);
        }
        cout << ans << '\n';
    }
}
