#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e4 + 1;

int par[mxN], dist[mxN];

void pull(int u) {
    if (u == par[u]) return;

    pull(par[u]);
    dist[u] += dist[par[u]];
    par[u] = par[par[u]];
}
void solve() {
    int N;
    cin >> N;

    iota(par + 1, par + N + 1, 1);
    memset(dist + 1, 0, sizeof(int) * N);

    char op;
    for (int u, v;;) {
        cin >> op;
        if (op == 'O') break;
        if (op == 'E') {
            cin >> u;
            pull(u);
            cout << dist[u] << '\n';
        } else {
            cin >> u >> v;
            par[u] = v;
            dist[u] = abs(u - v) % 1000;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}