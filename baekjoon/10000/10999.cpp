#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int M = 1000001;

int N;
ll fen1[M], fen2[M];

void update(ll fenwick[], int i, ll v) {
    for (; i <= N; i += i & -i)
        fenwick[i] += v;
}
ll read(ll fenwick[], int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void Q1(int l, int r, ll v) {
    update(fen1, l, v), update(fen1, r + 1, -v);
    update(fen2, l, v * (l - 1)), update(fen2, r + 1, -v * r);
}
ll Q2(int l, int r) {
    return read(fen1, r) * r - read(fen2, r) -
           read(fen1, l - 1) * (l - 1) + read(fen2, l - 1);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int Q, QQ; cin >> N >> Q >> QQ;
    Q += QQ;
    for (int i = 1; i <= N; ++i) {
        ll x; cin >> x;
        Q1(i, i, x);
    }

    for (int i = 0, q, l, r; i < Q; ++i) {
        cin >> q >> l >> r;
        if (q == 1) {
            ll v; cin >> v;
            Q1(l, r, v);
        }
        else  cout << Q2(l, r) << '\n';
    }
    return 0;
}