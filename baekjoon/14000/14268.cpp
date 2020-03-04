#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

vector<int> adj[max_N + 1];

int _time;
int in[max_N + 1];
int out[max_N + 1];
int fenwick[max_N + 1];

void DFS(int u) {
    in[u] = ++_time;
    for (int v : adj[u]) DFS(v);
    out[u] = _time;
}
void update(int idx, int val) {
    while (idx <= _time) {
        fenwick[idx] += val;
        idx += (idx & -idx);
    }
}
int read(int idx) {
    int ret = 0;
    while (idx) {
        ret += fenwick[idx];
        idx -= (idx & -idx);
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    int boss; cin >> boss;
    for (int i = 2; i <= N; ++i) {
        cin >> boss;
        adj[boss].emplace_back(i);
    }

    DFS(1);

    while (Q--) {
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