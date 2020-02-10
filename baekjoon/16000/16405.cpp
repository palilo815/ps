#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<double, int, int> tup;

const int max_N = 1000;

double pos[max_N][2];
int parent[max_N];
double dist(int u, int v)
{
    double dx = pos[u][0] - pos[v][0], dy = pos[u][1] - pos[v][1];
    return sqrt(dx * dx + dy * dy);
}
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 처음 E개 집은 걸어서 이동 가능
    // 따라서 처음 E개는 미리 union해준다.

    // 주어지는 P개 쌍은 이미 케이블 있다.

    int N, E, P; cin >> N >> E >> P;
    loop(i, N) cin >> pos[i][0] >> pos[i][1];
    loop(i, E) parent[i] = 0;
    for (int i = E; i < N; ++i) parent[i] = i;
    while (P--) {
        int u, v; cin >> u >> v;
        u = find_rt(u - 1), v = find_rt(v - 1);
        parent[u] = parent[v];
    }

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    loop(i, N - 1) for (int j = i + 1; j < N; ++j)
        if (find_rt(i) != find_rt(j))
            pq.push({ dist(i,j),i,j });

    double ans = 0;
    while (!pq.empty()) {
        auto [d, u, v] = pq.top(); pq.pop();
        u = find_rt(u), v = find_rt(v);
        if (u == v) continue;
        ans += d;
        parent[u] = v;
    }
    cout << fixed << setprecision(8) << ans;
    return 0;
}