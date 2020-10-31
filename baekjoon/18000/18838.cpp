#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
    int len;
    ll cnt;
};

const int mxN = 1e5;
const ll INF = 1e18;

int N, a[mxN];
node bit[mxN + 1], lis[mxN];

node merge(node& lhs, node& rhs) {
    if (lhs.len != rhs.len) return lhs.len > rhs.len ? lhs : rhs;
    return {lhs.len, lhs.cnt + rhs.cnt > INF ? INF : lhs.cnt + rhs.cnt};
}
void update(int i, node& n) {
    ++n.len;
    if (!n.cnt) n.cnt = 1;

    for (; i <= N; i += i & -i)
        bit[i] = merge(bit[i], n);
}
node query(int i) {
    node ret = {0, 0};
    for (; i; i -= i & -i)
        ret = merge(ret, bit[i]);
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    ll K;
    cin >> N >> K;
    for (int i = 0; i < N; ++i)
        cin >> a[i];

    for (int i = N - 1; ~i; --i)
        update(N - a[i] + 1, lis[i] = query(N - a[i]));

    auto total = query(N);

    if (total.cnt < K) return cout << -1, 0;
    --K;

    vector<vector<int>> vt(total.len + 1);
    for (int i = 0; i < N; ++i)
        vt[lis[i].len].emplace_back(i);

    int prv_num = -1;
    for (int i = total.len; i; --i) {
        while (a[vt[i].back()] < prv_num) vt[i].pop_back();
        while (lis[vt[i].back()].cnt <= K) {
            K -= lis[vt[i].back()].cnt;
            vt[i].pop_back();
        }
        cout << (prv_num = a[vt[i].back()]) << ' ';
    }
}