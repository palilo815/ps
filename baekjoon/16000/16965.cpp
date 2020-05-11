#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;

int sz;
int x[max_N], y[max_N];

int BFS(int src, int dst) {
    vector<bool> visited(sz);
    visited[src] = true;

    queue<int> q;
    q.emplace(src);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        if (u == dst) return 1;

        loop(v, sz) if (!visited[v]) {
            if (x[v] < x[u] && x[u] < y[v] || x[v] < y[u] && y[u] < y[v]) {
                visited[v] = true;
                q.emplace(v);
            }
        }
    }
    return 0;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) {
        int q; cin >> q;
        if (q == 1) {
            cin >> x[sz] >> y[sz];
            ++sz;
        }
        else {
            int u, v; cin >> u >> v;
            cout << BFS(u - 1, v - 1) << '\n';
        }
    }
    return 0;
}