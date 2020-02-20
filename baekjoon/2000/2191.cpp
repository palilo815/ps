#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-8;
const int max_N = 100;
const int max_M = 100;

double x[max_N + 1], y[max_N + 1];
vector<int> adj[max_N + 1];

bool visited[max_M + 1];
int N_match[max_N + 1];
int M_match[max_M + 1];

double dist(int idx, double X, double Y)
{
    double dx = X - x[idx], dy = Y - y[idx];
    return sqrt(dx * dx + dy * dy);
}
bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    for (int v : adj[u])
        if (!M_match[v] || DFS(M_match[v])) {
            N_match[u] = v;
            M_match[v] = u;
            return true;
        }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, S, V; cin >> N >> M >> S >> V;
    for (int i = 1; i <= N; ++i)
        cin >> x[i] >> y[i];
    for (int v = 1; v <= M; ++v) {
        double X, Y; cin >> X >> Y;
        for (int u = 1; u <= N; ++u)
            if (dist(u, X, Y) / V < S + eps)
                adj[u].emplace_back(v);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (DFS(i)) ++ans;
    }
    cout << N - ans;
    return 0;
}