#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

vector<int> adj[max_N];
int _time;
int in[max_N];
int out[max_N];
int fenwick[max_N];

void DFS(int u) {
    in[u] = ++_time;
    for (int v : adj[u]) DFS(v);
    out[u] = _time;
}
void update(int i, int w) {
    while (i <= _time) {
        fenwick[i] += w;
        i += i & -i;
    }
}
int read(int i) {
    int ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    int u; cin >> u;
    for (int v = 2; v <= N; ++v) {
        cin >> u;
        adj[u].emplace_back(v);
    }

    DFS(1);

    while (M--) {
        int q; cin >> q;
        if (q == 1) {
            int i, w; cin >> i >> w;
            update(in[i], w);
            update(out[i] + 1, -w);
        }
        else {
            int i; cin >> i;
            cout << read(in[i]) << '\n';
        }
    }
    return 0;
}