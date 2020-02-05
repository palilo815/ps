#include <iostream>
using namespace std;
const int max_N = 300000;

int parent[max_N + 1];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
void union_tr(int u, int v)
{
    u = find_rt(u), v = find_rt(v);
    parent[u] = v;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        parent[i] = i;
    
    int M = N - 2;
    while (M--) {
        int u, v; cin >> u >> v;
        union_tr(u, v);
    }
    
    int u = find_rt(1);
    int v = 1;
    while (find_rt(v) == u) ++v;
    cout << u << ' ' << v;
    return 0;
}