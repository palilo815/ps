#include <bits/stdc++.h>
using namespace std;

const int max_N = 100001;

vector<int> adj[max_N];

int _time;
int in[max_N];
int out[max_N];
int f1[max_N];
int f2[max_N];

void DFS(int u) {
    in[u] = ++_time;
    for (int v : adj[u]) DFS(v);
    out[u] = _time;
}
void update(int f[], int i, int w) {
    while (i <= _time) {
        f[i] += w;
        i += i & -i;
    }
}
int read(int f[], int i) {
    int ret = 0;
    while (i) {
        ret += f[i];
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

    int turn = 1;
    while (M--) {
        int q; cin >> q;
        if (q == 1) {
            int i, w; cin >> i >> w;
            if (turn) {
                update(f1, in[i], w);
                update(f1, out[i] + 1, -w);
            }
            else
                update(f2, in[i], w);
        }
        else if (q == 2) {
            int i; cin >> i;
            cout << read(f1, in[i]) + read(f2, out[i]) - read(f2, in[i] - 1) << '\n';
        }
        else turn ^= 1;
    }
    return 0;
}