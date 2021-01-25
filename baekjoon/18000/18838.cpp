#include <bits/stdc++.h>
using namespace std;

constexpr int mxN = 1e5;
constexpr int64_t INF = 1e18;

struct node {
    int len;
    int64_t cnt;
    void merge(const node& rhs) {
        if (rhs.len > len)
            len = rhs.len, cnt = rhs.cnt;
        else if (rhs.len == len)
            cnt = min(cnt + rhs.cnt, INF);
    }
};

int a[mxN];
node lis[mxN];

struct BIT {
    vector<node> vt;
    BIT(int n) : vt(n + 1) {}
    void update(int i, node& val) {
        ++val.len;
        if (!val.cnt) val.cnt = 1;

        for (; i; i -= i & -i)
            vt[i].merge(val);
    }
    node query(int i) {
        node ret = {0, 0};
        for (++i; i < vt.size(); i += i & -i)
            ret.merge(vt[i]);
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t k;
    cin >> n >> k;
    --k;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    BIT bit(n);
    for (int i = n; i--;)
        bit.update(a[i], lis[i] = bit.query(a[i]));

    auto total = bit.query(0);
    if (total.cnt <= k) return cout << -1, 0;

    vector<vector<int>> vt(total.len + 1);
    for (int i = 0; i < n; ++i)
        vt[lis[i].len].emplace_back(i);

    int prv_num = -1;
    for (int i = total.len; i; --i) {
        while (a[vt[i].back()] < prv_num) vt[i].pop_back();
        while (lis[vt[i].back()].cnt <= k) {
            k -= lis[vt[i].back()].cnt;
            vt[i].pop_back();
        }
        cout << (prv_num = a[vt[i].back()]) << ' ';
    }
}