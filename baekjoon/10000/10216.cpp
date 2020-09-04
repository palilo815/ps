#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mxN = 3e3;

int x[mxN], y[mxN], r[mxN], par[mxN];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
void solve() {
    int N; cin >> N;
    loop(i, N) cin >> x[i] >> y[i] >> r[i];

    memset(par, -1, sizeof(int) * N);

    loop(i, N) {
        int u = _find(i);
        loop(j, i) {
            int v = _find(j);
            if (u == v) continue;

            int dx = x[i] - x[j], dy = y[i] - y[j], sr = r[i] + r[j];
            if (dx * dx + dy * dy <= sr * sr)
                par[v] = u;
        }
    }
    cout << count(par, par + N, -1) << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}