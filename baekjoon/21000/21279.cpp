#include <bits/stdc++.h>
using namespace std;

template <typename T, typename U>
struct BIT {
    BIT(int _n) : n(1 << __lg(_n - 1) + 1), tree(n + 1) {}
    void update(int i, pair<T, U> val) {
        assert(0 <= i and i < n);
        for (++i; i <= n; i += i & -i) {
            tree[i].first += val.first;
            tree[i].second += val.second;
            // tree[i] += val;
        }
    }
    T query(int i) {
        assert(0 <= i and i <= n);
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i].first;
        return ret;
    }
    U kth(U k) {
        if (k >= tree[n].second) return n;
        U l = 0;
        for (int len = n >> 1; len; len >>= 1)
            if (k >= tree[l | len].second)
                k -= tree[l |= len].second;
        return l;
    }

private:
    const int n;
    vector<pair<T, U>> tree;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, c;
    cin >> n >> c;

    vector<int> x(n), y(n), v(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i] >> y[i] >> v[i];

    auto ord = x;
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());
    for (auto& i : x)
        i = lower_bound(ord.begin(), ord.end(), i) - ord.begin();

    BIT<int64_t, int> bit(ord.size());

    ord.resize(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](auto& a, auto& b) {
        return y[a] < y[b];
    });

    int64_t ans = 0;
    for (int i = 0, j = 0; i < n; i = j) {
        for (; j < n && y[ord[i]] == y[ord[j]]; ++j)
            bit.update(x[ord[j]], {v[ord[j]], 1});
        ans = max(ans, bit.query(bit.kth(c)));
    }
    cout << ans;
}