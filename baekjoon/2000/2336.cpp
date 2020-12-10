#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

struct elem {
    int x, y, z;
};
struct BIT {
    int n;
    vector<int> vt;
    BIT(int n) {
        this->n = n + 1;
        this->vt.resize(n + 1, 0x3f3f3f3f);
    }
    void update(int i, int val) {
        for (; i < n; i += i & -i)
            vt[i] = min(vt[i], val);
    }
    int query(int i) {
        int ret = 0x3f3f3f3f;
        for (; i; i -= i & -i)
            ret = min(ret, vt[i]);
        return ret;
    }
};

elem a[mxN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int i = 1, id; i <= N; ++i) {
        cin >> id;
        a[id - 1].x = i;
    }
    for (int i = 1, id; i <= N; ++i) {
        cin >> id;
        a[id - 1].y = i;
    }
    for (int i = 1, id; i <= N; ++i) {
        cin >> id;
        a[id - 1].z = i;
    }

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.x < b.x;
    });

    BIT bit(N);

    int ans = 0;
    for (int i = 0; i < N; ++i) {
        int mn = bit.query(a[i].y);
        if (mn > a[i].z) ++ans;
        bit.update(a[i].y, a[i].z);
    }
    cout << ans;
}