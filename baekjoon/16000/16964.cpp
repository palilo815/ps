#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 100001;

int N, idx = 1;
vector<int> adj[max_N];
int path[max_N];
int order[max_N];

bool cmp(const int a, const int b) {
    return order[a] < order[b];
}
int valid() {
    if (idx == N + 1) return 1;
    int u = path[idx++];
    LOOP(i, adj[u].size() - 1) {
        int v = path[idx];
        if (v != adj[u][i] || !valid()) return 0;
    }
    return 1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> N;
    adj[1].emplace_back(0);
    LOOP(i, N - 1) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    LOOP(i, N) {
        cin >> path[i];
        order[path[i]] = i;
    }
    LOOP(i, N) sort(adj[i].begin(), adj[i].end(), cmp);
    cout << (order[1] == 1 ? valid() : 0);
    return 0;
}