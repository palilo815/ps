#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
using namespace std;

const int max_N = 1002;

int x[max_N], y[max_N];
int dist[max_N][max_N];
bool visited[max_N];

int f(int u, int v) {
    int dx = x[v] - x[u], dy = y[v] - y[u];
    double d = sqrt(dx * dx + dy * dy);
    return (int)ceil(d / 10);
}
int BFS(int N, int fuel) {
    memset(visited + 1, 0, N);

    queue<int> q;
    q.emplace(0);
    q.emplace(-1);

    int ret = -1;
    while (1) {
        int u = q.front(); q.pop();
        if (u == -1) {
            if (q.empty()) return INT_MAX;
            ++ret;
            q.emplace(-1);
            continue;
        }
        if (u == N) return ret;

        LOOP(v, N) if (!visited[v] && dist[u][v] <= fuel) {
            visited[v] = true;
            q.emplace(v);
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, K; cin >> N >> K;
    LOOP(i, N) cin >> x[i] >> y[i];
    ++N;
    x[N] = y[N] = 10000;

    LOOP(i, N) dist[0][i] = f(0, i);
    LOOP(i, N - 1) for (int j = i + 1; j <= N; ++j)
        dist[i][j] = dist[j][i] = f(i, j);

    visited[0] = true;
    int l = 1, r = 1416, ans = 0;
    while (l <= r) {
        int m = (l + r) >> 1;
        int k = BFS(N, m);
        if (k <= K) {
            ans = m;
            r = m - 1;
        }
        else l = m + 1;
    }
    cout << ans;
    return 0;
}