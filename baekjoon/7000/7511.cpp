#include <iostream>
using namespace std;
const int max_N = 1000000;

int parent[max_N];
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

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N, M; cin >> N >> M;

        for (int i = 0; i < N; ++i)
            parent[i] = i;

        while (M--) {
            int u, v; cin >> u >> v;
            union_tr(u, v);
        }

        cout << "Scenario " << t << ":\n";
        cin >> M;
        while (M--) {
            int u, v; cin >> u >> v;
            cout << (find_rt(u) == find_rt(v)) << '\n';
        }
        cout << '\n';
    }
    return 0;
}