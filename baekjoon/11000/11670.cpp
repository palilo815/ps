#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;

const int max_N = 2500;

vector<int> adj[max_N];
int a[max_N], b[max_N];
ll c[max_N * 3], res[max_N];

bool visited[max_N];
int match[max_N * 3];

bool dfs(int u) {
    if (visited[u]) return false;
    visited[u] = true;
    for (int& v : adj[u])
        if (match[v] == -1 || dfs(match[v])) {
            match[v] = u;
            res[u] = c[v];
            return true;
        }
    return false;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) cin >> a[i] >> b[i];
    loop(i, N) {
        c[3 * i] = a[i] + b[i];
        c[3 * i + 1] = a[i] - b[i];
        c[3 * i + 2] = (ll)a[i] * b[i];
    }

    sort(c, c + 3 * N);
    int M = unique(c, c + 3 * N) - c;
    loop(u, N) {
        adj[u].emplace_back(lower_bound(c, c + M, a[u] + b[u]) - c);
        adj[u].emplace_back(lower_bound(c, c + M, a[u] - b[u]) - c);
        adj[u].emplace_back(lower_bound(c, c + M, (ll)a[u] * b[u]) - c);

        sort(adj[u].begin(), adj[u].end());
        adj[u].erase(unique(adj[u].begin(), adj[u].end()), adj[u].end());
    }

    memset(match, -1, sizeof(match));
    int ans = 0;
    loop(u, N) {
        memset(visited, 0, sizeof(visited));
        if (!dfs(u)) {cout << "impossible"; return 0;}
    }

    loop(i, N) {
        cout << a[i] << ' '
             << (a[i] + b[i] == res[i] ? '+' : a[i] - b[i] == res[i] ? '-' : '*') << ' '
             << b[i] << " = " << res[i] << '\n';
    }
    return 0;
}