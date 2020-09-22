#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 1e5;
const int mxM = 5e4;

int N, M;
vector<int> obs[mxM], adj[mxN];
int in[mxN];
char colour[mxN];

bool cycle(int u) {
    colour[u] = 'g';
    for (int& v : adj[u])
        if (colour[v] == 'g' || colour[v] == 'w' && cycle(v))
            return true;
    colour[u] = 'b';
    return false;
}
bool valid(int m) {
    loop(i, N) adj[i].clear();
    loop(i, m) loop(j, obs[i].size() - 1) {
        adj[obs[i][j]].emplace_back(obs[i][j + 1]);
    }

    memset(colour, 'w', N);
    loop(i, N) if (colour[i] == 'w' && cycle(i)) return false;
    return true;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N >> M;
    for (int i = 0, sz; i < M; ++i) {
        cin >> sz;
        obs[i].resize(sz);
        for (int& x : obs[i]) cin >> x;
        for (int& x : obs[i]) --x;
    }

    int lo = 0, hi = M - 1;
    while (lo ^ hi) {
        int m = (lo + hi + 1) >> 1;
        valid(m) ? (lo = m) : (hi = m - 1);
    }

    memset(colour, 0, N);
    loop(i, N) adj[i].clear();
    loop(i, lo) loop(j, obs[i].size() - 1) {
        adj[obs[i][j]].emplace_back(obs[i][j + 1]);
        ++in[obs[i][j + 1]];
        colour[obs[i][j]] = colour[obs[i][j + 1]] = 1;
    }

    vector<int> v1, v2;
    loop(i, N) if (!colour[i])
        v1.emplace_back(i);

    priority_queue<int, vector<int>, greater<int>> pq;
    loop(i, N) if (colour[i] && !in[i])
        pq.emplace(i);

    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        v2.emplace_back(u);
        for (int& v : adj[u])
            if (--in[v] == 0)
                pq.emplace(v);
    }

    v1.emplace_back(INT_MAX), v2.emplace_back(INT_MAX);
    for (int i = 0, j = 0; i + j < N;)
        cout << (v1[i] < v2[j] ? v1[i++] : v2[j++]) + 1 << ' ';
    return 0;
}