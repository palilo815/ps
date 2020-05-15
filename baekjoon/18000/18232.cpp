#include <bits/stdc++.h>
using namespace std;

const int max_N = 300001;

vector<int> tele[max_N];
bool visited[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M, S, E; cin >> N >> M >> S >> E;
    while (M--) {
        int u, v; cin >> u >> v;
        tele[u].emplace_back(v);
        tele[v].emplace_back(u);
    }

    visited[S] = true;

    queue<int> q;
    q.emplace(S);
    q.emplace(-1);

    int ans = 0;
    while (1) {
        int u = q.front(); q.pop();
        if (u == -1) {
            ++ans; q.emplace(-1);
            continue;
        }
        if (u == E) break;

        if (u - 1 > 0 && !visited[u - 1]) {
            visited[u - 1] = true;
            q.emplace(u - 1);
        }
        if (u + 1 <= N && !visited[u + 1]) {
            visited[u + 1] = true;
            q.emplace(u + 1);
        }
        for (int v : tele[u]) if (!visited[v]) {
            visited[v] = true;
            q.emplace(v);
        }
    }
    cout << ans;
    return 0;
}