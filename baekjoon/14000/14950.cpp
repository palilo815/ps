#include <bits/stdc++.h>
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 10000;

int parent[max_N + 1];

int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, t; cin >> N >> M >> t;
    for (int i = 1; i <= N; ++i)
        parent[i] = i;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        pq.push({ w,u,v });
    }

    int cnt = 0, cost = 0;
    while (cnt < N - 1) {
        auto [w, u, v] = pq.top(); pq.pop();
        u = find_rt(u), v = find_rt(v);
        if (u == v) continue;
        parent[u] = v;
        cost += w + t * cnt;
        ++cnt;
    }
    cout << cost;
    return 0;
}