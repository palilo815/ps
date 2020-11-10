#include <bits/stdc++.h>
using namespace std;

const int mxK = 1e3;

int x[mxK], y[mxK], s[mxK];
bool con[mxK];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M, K;
    cin >> N >> M >> K;

    for (int i = 0; i < K; ++i)
        cin >> x[i] >> y[i] >> s[i];

    queue<int> q;
    for (int i = 0; i < K; ++i)
        if (x[i] - s[i] <= 0 || y[i] + s[i] >= M) {
            con[i] = true;
            q.emplace(i);
        }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v = 0; v < K; ++v)
            if (!con[v]) {
                int dx = x[u] - x[v], dy = y[u] - y[v], dz = s[u] + s[v];
                if (dx * dx + dy * dy <= dz * dz) {
                    con[v] = true;
                    q.emplace(v);
                }
            }
    }

    for (int i = 0; i < K; ++i)
        if (con[i] && (x[i] + s[i] >= N || y[i] - s[i] <= 0))
            return cout << 'N', 0;
    cout << 'S';
}