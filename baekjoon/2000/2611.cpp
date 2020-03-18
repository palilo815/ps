#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

vector<p> adj[1001];
int score[1001], cache[1001];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
    }

    queue<p> q;
    for (auto [w, v] : adj[1]) {
        score[v] = w;
        cache[v] = 1;
        q.emplace(w, v);
    }

    while (!q.empty()) {
        auto [s, u] = q.front(); q.pop();
        if (u == 1 || score[u] > s) continue;

        for (auto [w, v] : adj[u]) {
            int S = s + w;
            if (score[v] < S) {
                score[v] = S;
                cache[v] = u;
                q.emplace(S, v);
            }
        }
    }

    vector<int> path;
    path.emplace_back(1);
    int u = 1;
    do {
        u = cache[u];
        path.emplace_back(u);
    } while (u != 1);

    cout << score[1] << '\n';
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        cout << *it << ' ';
    return 0;
}