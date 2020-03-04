#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int max_N = 500000;

int _time;
int in[max_N + 1];
int out[max_N + 1];
vector<int> adj[max_N + 1];

int pay[max_N + 1];
ll fenwick[max_N + 1];

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
ll read(int idx) {
    ll ret = 0;
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
    cin >> pay[1];
    for (int i = 2; i <= N; ++i) {
        int boss;
        cin >> pay[i] >> boss;
        adj[boss].emplace_back(i);
    }

    DFS(1);

    while (Q--) {
        char q; cin >> q;
        if (q == 'p') {
            int idx, val; cin >> idx >> val;
            update(in[idx] + 1, val);
            update(out[idx] + 1, -val);
        }
        else {
            int idx; cin >> idx;
            cout << read(in[idx]) + pay[idx] << '\n';
        }
    }
    return 0;
}