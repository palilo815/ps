#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    BIT(int _n) : n(_n), tree(_n + 1) {}
    void add(int i) {
        for (++i; i <= n; i += i & -i)
            ++tree[i];
    }
    T query(int i) {
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l);
    }

private:
    const int n;
    vector<T> tree;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int64_t> a(n + 1);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];

    int p;
    cin >> p;

    for (int i = 1; i <= n; ++i)
        a[i] = a[i - 1] + a[i] - p;

    auto ord = a;
    sort(ord.begin(), ord.end(), greater<int64_t>());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    for (auto& x : a) x = lower_bound(ord.begin(), ord.end(), x, greater<int64_t>()) - ord.begin();

    BIT<int> bit(ord.size());

    int64_t ans = 0;
    for (int i = n + 1; i--;) {
        ans += bit.query(a[i] + 1);
        bit.add(a[i]);
    }
    cout << ans;
}