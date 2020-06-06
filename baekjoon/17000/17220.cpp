#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

vector<int> adj[26];
int in[26];
bool rt[26], jail[26];

int DFS(int u) {
    jail[u] = true;
    int ret = 1;
    for (int v : adj[u]) if (!jail[v]) ret += DFS(v);
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    fill(rt, rt + 26, true);
    while (M--) {
        char u, v; cin >> u >> v;
        adj[u - 'A'].emplace_back(v - 'A');
        rt[v - 'A'] = false;
    }
    int K; cin >> K;
    while (K--) {
        char x; cin >> x;
        jail[x - 'A'] = true;
    }

    int ans = 0;
    loop(i, N) if (rt[i] && !jail[i])
        ans += DFS(i) - 1;
    cout << ans;
    return 0;
}