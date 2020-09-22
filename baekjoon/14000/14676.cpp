#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

vector<int> adj[mxN];
int cnt[mxN], req[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, K;
    cin >> N >> M >> K;
    for (int u, v; M--;) {
        cin >> u >> v;
        --u, --v;
        adj[u].emplace_back(v);
        ++req[v];
    }

    for (int op, u; K--;) {
        cin >> op >> u;
        --u;
        if (op == 1) {
            if (req[u]) {
                cout << "Lier!";
                return 0;
            }
            if (++cnt[u] == 1)
                for (int& v : adj[u])
                    --req[v];
        } else {
            if (!cnt[u]) {
                cout << "Lier!";
                return 0;
            }
            if (--cnt[u] == 0)
                for (int& v : adj[u])
                    ++req[v];
        }
    }
    cout << "King-God-Emperor";
    return 0;
}