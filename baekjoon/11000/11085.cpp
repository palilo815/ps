#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 1000;
const int max_M = 50000;

int parent[max_N];
tup edge[max_M];

int find_rt(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, src, dst;
    cin >> N >> M >> src >> dst;
    loop(i, N) parent[i] = i;
    loop(i, M) {
        int u, v, w; cin >> u >> v >> w;
        edge[i] = { w,u,v };
    }
    sort(edge, edge + M, greater<tup>());
    loop(i, M) {
        auto [w, u, v] = edge[i];
        u = find_rt(u), v = find_rt(v);
        if (u == v) continue;

        parent[u] = v;
        if (find_rt(src) == find_rt(dst)) {
            cout << w;
            break;
        }
    }
    return 0;
}