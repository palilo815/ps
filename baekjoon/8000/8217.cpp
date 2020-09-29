#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
using ll = long long;

const int mx = 3e5;

vector<int> state[mx];
int N, M, req[mx];
int l[mx], r[mx], w[mx];
int lo[mx], hi[mx];

ll fenwick[mx + 1];

void update(int i, int v) {
    for (; i <= M; i += i & -i)
        fenwick[i] += v;
}
ll read(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M;
    for (int i = 1, owner; i <= M; ++i) {
        cin >> owner;
        state[owner - 1].emplace_back(i);
    }
    loop(i, N) cin >> req[i];

    int Q;
    cin >> Q;
    loop(i, Q) cin >> l[i] >> r[i] >> w[i];
    loop(i, Q) r[i]++;

    fill(hi, hi + N, Q);

    for (;;) {
        vector<vector<int>> vt(Q);
        bool done = true;

        loop(i, N) if (lo[i] != hi[i]) {
            int m = (lo[i] + hi[i]) >> 1;
            vt[m].emplace_back(i);
            done = false;
        }
        if (done) break;

        memset(fenwick + 1, 0, sizeof(ll) * M);
        loop(m, Q) {
            if (l[m] < r[m])
                update(l[m], w[m]), update(r[m], -w[m]);
            else
                update(1, w[m]), update(r[m], -w[m]), update(l[m], w[m]);

            for (int& i : vt[m]) {
                ll total = 0;
                for (int& x : state[i]) {
                    total += read(x);
                    if (total >= req[i]) break;
                }
                total < req[i] ? (lo[i] = m + 1) : (hi[i] = m);
            }
        }
    }
    loop(i, N) {
        if (lo[i] == Q) cout << "NIE\n";
        else
            cout << lo[i] + 1 << '\n';
    }
    return 0;
}