#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e6;

int N;
ll a[mxN + 1], fenwick[mxN + 1];

ll read(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void update(int i, ll v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int M, K; cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i)
        cin >> a[i];

    for (int i = 1; i <= N; ++i)
        update(i, a[i]);

    for (M += K; M; --M) {
        char op;
        ll u, v;
        cin >> op >> u >> v;

        if (op == '1') {
            ll diff = v - a[u];
            a[u] = v;
            update(u, diff);
        }
        else cout << read(v) - read(u - 1) << '\n';
    }
    return 0;
}