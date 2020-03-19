#include<bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 1000;

vector<int> rev[max_N + 1];
int t[max_N + 1];
int total[max_N + 1];

int DFS(int v) {
    int cost = 0;
    for (int u : rev[v]) {
        if (total[u] == -1) DFS(u);
        cost = max(cost, total[u]);
    }
    return total[v] = t[v] + cost;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        memset(total, -1, sizeof(int) * (N + 1));
        LOOP(i, N) rev[i].clear();
        LOOP(i, N) cin >> t[i];
        while (M--) {
            int u, v; cin >> u >> v;
            rev[v].emplace_back(u);
        }

        int dst; cin >> dst;
        cout << DFS(dst) << '\n';
    }
    return 0;
}