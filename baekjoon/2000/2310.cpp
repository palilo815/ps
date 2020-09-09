#include <bits/stdc++.h>
using namespace std;

const int mxN = 1001;

vector<int> adj[mxN];
int room[mxN], dist[mxN];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);
TOP:
    int N; cin >> N;
    if (!N) return 0;

    for (int i = 1; i <= N; ++i)
        adj[i].clear();

    for (int i = 1, x; i <= N; ++i) {
        char c; cin >> c >> x;
        room[i] = (c == 'L' ? x : -x);

        for (;;) {
            cin >> x;
            if (!x) break;
            adj[i].emplace_back(x);
        }
    }

    memset(dist + 1, -1, sizeof(int) * N);
    dist[1] = 0;

    queue<int> q;
    q.emplace(1);
    bool flag = false;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == N) {flag = true; break;}

        for (int& v : adj[u]) {
            int m = dist[u];
            if (room[v])
                m = (room[v] > 0 ? max(m, room[v]) : m + room[v]);
            if (dist[v] < m) {
                dist[v] = m;
                q.emplace(v);
            }
        }
    }
    cout << (flag ? "Yes\n" : "No\n");
    goto TOP;
}