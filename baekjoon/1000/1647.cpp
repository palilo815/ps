#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;
const int max_N = 100000;
const int max_M = 1000000;
int parent[max_N + 1];
tup edge[max_M];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for(int i=1; i<=N; ++i)
        parent[i] = i;
    loop(i, M) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = { w,u,v };
    }
    sort(edge, edge + M);

    // N-2개의 edge를 연결하면 두 개로 분할된 트리를 얻는다.
    int E = N - 2, ans = 0, idx = 0;
    while (E) {
        int w = get<0>(edge[idx]), u = get<1>(edge[idx]), v = get<2>(edge[idx]);
        ++idx;
        u = find_rt(u), v = find_rt(v);
        if (u == v) continue;
        parent[u] = v;
        --E, ans += w;
    }
    cout << ans;
    return 0;
}