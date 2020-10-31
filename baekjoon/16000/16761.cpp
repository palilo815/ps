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
bool ok[mxN + 1];

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

    int longest = query(N).len;
    --K;

    vector<vector<int>> vt(longest + 1);
    for (int i = 0; i < N; ++i)
        vt[lis[i].len].emplace_back(i);

    int prv_num = -1, prv_idx = -1;
    for (int i = longest; i; --i)
        for (int& x : vt[i]) {
            if (x < prv_idx || a[x] < prv_num) continue;
            if (lis[x].cnt > K) {
                ok[prv_num = a[x]] = true;
                prv_idx = x;
                break;
            }
            K -= lis[x].cnt;
        }

    cout << count(ok + 1, ok + N + 1, false) << '\n';
    for (int i = 1; i <= N; ++i)
        if (!ok[i])
            cout << i << '\n';
}