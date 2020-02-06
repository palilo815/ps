#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;
const int max_N = 200000;
const int max_M = 200000;

int parent[max_N];
tup road[max_M];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    while (1) {
        // 왜 #_vertex가 M이냐.. N이 국룰이다.
        int N, M; cin >> N >> M;
        if (N == 0) break;
        loop(i, N) parent[i] = i;
        
        // total : 기존에 있던 모든 길의 비용
        int total = 0;
        loop(i, M) {
            int u, v, w; cin >> u >> v >> w;
            road[i] = { w,u,v };
            total += w;
        }
        sort(road, road + M);

        // total에서, MST에 해당되는 edge의 비용을 빼준다.
        loop(i, M) {
            int u = get<1>(road[i]), v = get<2>(road[i]);
            u = find_rt(u), v = find_rt(v);
            if (u == v) continue;
            parent[u] = v;
            total -= get<0>(road[i]);
        }
        cout << total << '\n';
    }
    return 0;
}