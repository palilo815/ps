#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;

vector<int> frnd[max_N + 1];
vector<int> enemy[max_N + 1];
bool visited[max_N + 1];

void BFS(int src) {
    queue<int> q;
    q.emplace(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : frnd[u]) if (!visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
        for (int e : enemy[u]) for (int v : enemy[e]) if (!visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    while (M--) {
        char f; int u, v;
        cin >> f >> u >> v;
        auto& vt = (f == 'F' ? frnd : enemy);
        vt[u].emplace_back(v);
        vt[v].emplace_back(u);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) if (!visited[i]) {
        ++ans;
        BFS(i);
    }
    cout << ans;
    return 0;
}