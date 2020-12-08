#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;

int par[mxN], weight[mxN];

void pull(const int u) {
    if (u == par[u]) return;

    pull(par[u]);
    weight[u] += weight[par[u]];
    par[u] = par[par[u]];
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (int N, M;;) {
        cin >> N >> M;
        if (!N) break;

        iota(par + 1, par + N + 1, 1);
        memset(weight + 1, 0, sizeof(int) * N);

        char op;
        for (int a, b, w; M--;) {
            cin >> op >> a >> b;
            pull(a), pull(b);

            if (op == '!') {
                cin >> w;
                if (par[a] != par[b]) {
                    weight[par[b]] = w + weight[a] - weight[b];
                    par[par[b]] = par[a];
                }
            } else if (par[a] == par[b]) {
                cout << weight[b] - weight[a] << '\n';
            } else
                cout << "UNKNOWN\n";
        }
    }
}