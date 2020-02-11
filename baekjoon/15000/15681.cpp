#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

vector<int> adj[max_N + 1];
int cnt[max_N + 1];

int DFS(int u, int p)
{
    int ret = 1;
    for (int v : adj[u])
        if (v != p) ret += DFS(v, u);
    return cnt[u] = ret;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, root, Q; cin >> N >> root >> Q;
    while (--N) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    DFS(root, -1);

    while (Q--) {
        int q; cin >> q;
        cout << cnt[q] << '\n';
    }
    return 0;
}