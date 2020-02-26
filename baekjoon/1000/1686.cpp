#include <bits/stdc++.h>
using namespace std;
typedef pair<double, double> p;

const double eps = 1e-8;

double dist(const p& a, const p& b) {
    double dx = a.first - b.first, dy = a.second - b.second;
    return sqrt(dx * dx + dy * dy);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    vector<p> hole;
    double v, m; cin >> v >> m;
    double x, y;
    while (cin >> x >> y)
        hole.push_back({ x,y });

    int N = hole.size();
    vector<vector<int>> adj(N);
    for (int i = 0; i < N - 1; ++i)
        for (int j = i + 1; j < N; ++j)
            if (dist(hole[i], hole[j]) / v < 60 * m + eps) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }

    int ans = 0;
    queue<int> q;
    q.push(0); q.push(-1);
    vector<bool> visited(N);
    visited[0] = true;

    while (1) {
        int u = q.front(); q.pop();
        if (u == -1) {
            if (q.empty()) {
                ans = -1; break;
            }
            q.push(-1); ++ans;
            continue;
        }
        if (u == 1) break;
        for (int v : adj[u]) if (!visited[v]) {
            visited[v] = true;
            q.push(v);
        }
    }

    if (ans == -1) cout << "No.";
    else cout << "Yes, visiting " << ans - 1 << " other holes.";
    return 0;
}