#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 10000;

int fruit[max_N + 1];
vector<p> adj[max_N + 1];

int DFS(int u, int p) {
    int ret = 0;
    for (auto& [v, dp] : adj[u]) if (v != p) {
        if (dp == -1) dp = DFS(v, u);
        ret = max(ret, dp);
    }
    return ret + fruit[u];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i) cin >> fruit[i];
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back({ v,-1 });
        adj[v].push_back({ u,-1 });
    }

    int cnt = -1, idx = -1;
    for (int i = 1; i <= N; ++i) {
        int tmp = DFS(i, -1);
        if (tmp > cnt)
            cnt = tmp, idx = i;
    }
    cout << cnt << ' ' << idx;
    return 0;
}