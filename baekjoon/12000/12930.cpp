#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 30;

struct elem {
    int w1, w2, u;
    elem(int w1, int w2, int u) : w1(w1), w2(w2), u(u) {}
    bool operator<(const elem& rhs) const {
        return w1 > rhs.w1;
    }
};

pair<int, int> adj[mxN][mxN];
int dist[mxN][9 * (mxN - 1) + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    loop(i, n) loop(j, n) {
        char w;
        cin >> w;
        if (w != '.') adj[i][j].first = w - '0';
    }
    loop(i, n) loop(j, n) {
        char w;
        cin >> w;
        if (w != '.') adj[i][j].second = w - '0';
    }

    const int mx = 9 * (n - 1);

    memset(dist, 0x3f, sizeof(dist[0]) * n);
    dist[0][0] = 0;

    priority_queue<elem> pq;
    pq.emplace(0, 0, 0);

    while (!pq.empty()) {
        auto [w1, w2, u] = pq.top();
        pq.pop();
        if (w1 != dist[u][w2]) continue;

        loop(v, n) if (adj[u][v].first) {
            if (w2 + adj[u][v].second > mx ||
                dist[v][w2 + adj[u][v].second] <= w1 + adj[u][v].first)
                continue;

            for (int i = w2 + adj[u][v].second; i <= mx && dist[v][i] > w1 + adj[u][v].first; ++i)
                dist[v][i] = w1 + adj[u][v].first;
            pq.emplace(w1 + adj[u][v].first, w2 + adj[u][v].second, v);
        }
    }

    int ans = -1;
    for (int i = 0; i <= mx; ++i)
        if (dist[1][i] != 0x3f3f3f3f && (ans == -1 || ans > i * dist[1][i]))
            ans = i * dist[1][i];
    cout << ans;
}