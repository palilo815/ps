#include <bits/stdc++.h>
using namespace std;

struct BIT {
    vector<int> ord, xorT, cntT;
    int n, sz;

    BIT(vector<int>& q) {
        ord.reserve(count_if(q.begin(), q.end(), [&](auto& x) { return x >= 0; }));

        for (const auto& x : q)
            if (x >= 0)
                ord.emplace_back(x);

        sort(ord.begin(), ord.end(), greater<int>());
        ord.erase(unique(ord.begin(), ord.end()), ord.end());

        n = ord.size();
        sz = 1 << 32 - __builtin_clz(n - 1);

        xorT.resize(sz + 1);
        cntT.resize(sz + 1);
    }
    void update(int val) {
        int i = lower_bound(ord.begin(), ord.end(), val, greater<int>()) - ord.begin();
        for (int j = i + 1; j <= sz; j += j & -j)
            xorT[j] ^= val;
        for (int j = i + 1; j <= sz; j += j & -j)
            ++cntT[j];
    }
    int query(int i) {
        int ret = 0;
        for (; i; i &= i - 1)
            ret += cntT[i];
        return ret;
    }
    int query(int l, int r) {
        return query(r) - query(l);
    }
    int access(int i) {
        return i & 1 ? query(i + 1) - query(i) : cntT[i + 1];
    }
    int kth(int k) {
        int s = 0, ret = 0;
        for (int len = sz >> 1; len; len >>= 1)
            if (k >= cntT[s | len]) {
                s |= len;
                k -= cntT[s], ret ^= xorT[s];
            }
        if (k && s < n && min(k, access(s)) & 1)
            ret ^= ord[s];
        return ret;
    }
};

void solve() {
    int n;
    cin >> n;

    vector<int> q(n);
    char op[7];
    for (auto& x : q) {
        cin >> op >> x;
        if (op[0] == 'p') x = ~x;
    }

    BIT bit(q);
    for (const auto& x : q) {
        if (x >= 0)
            bit.update(x);
        else
            cout << bit.kth(~x) << '\n';
    }
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}