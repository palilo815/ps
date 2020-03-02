#include <bits/stdc++.h>
using namespace std;

const int max_N = 100000;

vector<int> adj[max_N + 1];
bool visited[max_N + 1];
int ans[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    int M = N;
    while (--M) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < N; ++i) cin >> ans[i];

    if (ans[0] != 1) { cout << 0; return 0; }

    queue<int> q;
    q.push(1);
    int i = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        visited[u] = true;
        vector<int> child;
        for (int v : adj[u]) if (!visited[v])
            child.push_back(v);
        sort(child.begin(), child.end());
        int cnt = child.size();
        while (cnt--) {
            if (binary_search(child.begin(), child.end(), ans[i]))
                q.push(ans[i]);
            else { cout << 0; return 0; }
            ++i;
        }
    }
    cout << (i == N ? 1 : 0);
    return 0;
}