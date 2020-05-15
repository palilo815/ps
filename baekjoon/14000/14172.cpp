#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 200;

int x[max_N], y[max_N], p[max_N];
bool visited[max_N];

int dist(int u, int v) {
    int dx = x[u] - x[v];
    int dy = y[u] - y[v];
    return dx * dx + dy * dy;
}
int BFS(int src, int N) {
    memset(visited, 0, N);
    visited[src] = true;

    queue<int> q;
    q.emplace(src);

    int ret = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        ++ret;
        loop(v, N) if (!visited[v]) {
            int d = dist(u, v);
            if (d <= p[u]) {
                visited[v] = true;
                q.emplace(v);
            }
        }
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        cin >> x[i] >> y[i] >> p[i];
        p[i] *= p[i];
    }

    int ans = 0;
    loop(i, N) ans = max(ans, BFS(i, N));
    cout << ans;
    return 0;
}