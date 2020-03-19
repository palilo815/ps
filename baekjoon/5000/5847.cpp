#include <bits/stdc++.h>
using namespace std;

const int max_N = 10000;

vector<int> rev[max_N + 1];
int T[max_N + 1];
int total[max_N + 1];

int DFS(int v) {
    total[v] = T[v];
    for (int u : rev[v]) {
        if (!total[u]) DFS(u);
        total[v] = max(total[v], total[u] + T[v]);
    }
    return total[v];
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> T[i];
    while (M--) {
        int v, u; cin >> v >> u;
        rev[v].emplace_back(u);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) if (!total[i])
        ans = max(ans, DFS(i));
    cout << ans;
    return 0;
}