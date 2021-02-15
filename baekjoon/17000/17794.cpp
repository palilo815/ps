#include <bits/stdc++.h>
using namespace std;

struct slot {
    int w, m, pos;
};

struct coin {
    int w, m;
};

struct BIT {
    static constexpr int n = 1e5;
    int tr[n + 1];

    BIT() { memset(tr, 0x3f, sizeof(tr)); }
    void update(int i, int val) {
        for (++i; i <= n; i += i & -i)
            tr[i] = min(tr[i], val);
    }
    int query(int r) const {
        int ret = INT_MAX;
        for (; r; r -= r & -r)
            ret = min(ret, tr[r]);
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int s;
    cin >> s;

    vector<slot> slots(s + 1);
    for (int i = 0; i < s; ++i)
        cin >> slots[i].w >> slots[i].m, slots[i].pos = i + 1;

    int c;
    cin >> c;

    vector<coin> coins(c);
    for (auto& [w, m] : coins)
        cin >> w >> m;

    sort(slots.begin(), slots.end(), [&](auto& a, auto& b) {
        return a.w > b.w;
    });
    sort(coins.begin(), coins.end(), [&](auto& a, auto& b) {
        return a.w > b.w;
    });

    BIT bit;
    int64_t ans = 0;
    int j = 0;
    for (const auto& [w, m] : coins) {
        for (; slots[j].w >= w; ++j)
            bit.update(slots[j].m - 1, slots[j].pos);
        ans += bit.query(m);
    }
    cout << ans;
}