#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;

vector<int> rev[max_N + 1];
int ans[max_N + 1];

void DFS(int v) {
    ans[v] = 1;
    for (int u : rev[v]) {
        if (!ans[u]) DFS(u);
        ans[v] = max(ans[v], ans[u] + 1);
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        rev[v].emplace_back(u);
    }

    for (int i = 1; i <= N; ++i) if (!ans[i])
        DFS(i);
    for (int i = 1; i <= N; ++i)
        cout << ans[i] << ' ';
    return 0;
}