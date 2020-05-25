#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAX = 65536;

int mid;
int fenwick[MAX + 1];

void update(int i, int v) {
    for (++i; i <= MAX; i += i & -i)
        fenwick[i] += v;
}
int query(int i) {
    int ret = 0;
    for (++i; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int solve() {
    int l = 0, r = MAX;
    while (l < r) {
        int m = (l + r) / 2;
        query(m) < mid ? (l = m + 1) : (r = m);
    }
    return l;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    queue<int> q;
    int N, K; cin >> N >> K;
    for (int i = 0; i < K; ++i) {
        int x; cin >> x;
        q.emplace(x);
        update(x, 1);
    }

    mid = (K + 1) / 2;
    ll ans = solve();
    for (int i = K; i < N; ++i) {
        int x; cin >> x;
        q.emplace(x);
        update(x, 1);
        update(q.front(), -1); q.pop();
        ans += solve();
    }
    cout << ans;
    return 0;
}