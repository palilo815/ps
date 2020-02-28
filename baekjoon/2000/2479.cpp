#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;

int num[max_N + 1];
vector<int> adj[max_N + 1];
bool visited[max_N + 1];
int parent[max_N + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K; cin >> N >> K;
    string b;
    for (int i = 1; i <= N; ++i) {
        cin >> b;
        loop(j, K) num[i] += (b[K - 1 - j] - '0') << j;
    }

    for (int i = 1; i < N; ++i) for (int j = i + 1; j <= N; ++j)
        if (__builtin_popcount(num[i] ^ num[j]) == 1) {
            adj[i].push_back(j);
            adj[j].push_back(i);
        }

    int src, dst; cin >> src >> dst;
    visited[src] = true;

    queue<int> q;
    q.push(src);
    
    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) break;
        for (int v : adj[u]) if (!visited[v]) {
            visited[v] = true;
            parent[v] = u;
            q.push(v);
        }
    }

    if (!parent[dst]) { cout << -1; return 0; }

    vector<int> ans;
    while (dst) {
        ans.push_back(dst);
        dst = parent[dst];
    }
    for (auto it = ans.rbegin(); it != ans.rend(); ++it)
        cout << *it << ' ';
    return 0;
}