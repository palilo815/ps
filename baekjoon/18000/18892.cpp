#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

struct node {
    int len, cnt;
};

const int mxN = 500;
const int sgN = 512;
const int INF = 1e9;

int N, K, a[mxN];
node segT[sgN << 1], lis[mxN];

node merge(node& lhs, node& rhs) {
    if (lhs.len != rhs.len) return lhs.len > rhs.len ? lhs : rhs;
    return {lhs.len, lhs.cnt + rhs.cnt > INF ? INF : lhs.cnt + rhs.cnt};
}
void update(int i, node& n) {
    ++n.len;
    if (!n.cnt) n.cnt = 1;

    i += sgN - 1;
    segT[i] = merge(segT[i], n);

    while (i >>= 1)
        segT[i] = merge(segT[left], segT[right]);
}
node query(int l, int r = sgN + N) {
    node ret = {0, 0};
    for (l += sgN; l != r; l >>= 1, r >>= 1) {
        if (l & 1) ret = merge(ret, segT[l++]);
        if (r & 1) ret = merge(ret, segT[--r]);
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    for (int i = N - 1; ~i; --i)
        update(a[i], lis[i] = query(a[i]));

    auto total = query(0);

    if (total.cnt < K) return cout << -1, 0;
    --K;

    vector<stack<pair<int, int>>> vt(total.len + 1);
    for (int i = 0; i < N; ++i)
        vt[lis[i].len].emplace(a[i], lis[i].cnt);

    int prv_num = -1;
    for (int i = total.len; i; --i) {
        while (vt[i].top().first < prv_num) vt[i].pop();
        while (vt[i].top().second <= K) {
            K -= vt[i].top().second;
            vt[i].pop();
        }
        cout << (prv_num = vt[i].top().first) << ' ';
    }
}