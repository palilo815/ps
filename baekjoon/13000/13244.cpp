#include <iostream>
using namespace std;
const int max_N = 1000;

int parent[max_N + 1];
int find_rt(int u)
{
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
bool union_tr(int u, int v)
{
    u = find_rt(u), v = find_rt(v);
    if (u == v) return false;
    parent[u] = v;
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N, M; cin >> N >> M;
        // tree == false 면 입력만 받고 아무 행동 안한다.
        // tree 조건 1 : #_vertex - 1 == #_edge
        bool tree = (N == M + 1);
        if (tree)
            for (int i = 1; i <= N; ++i)
                parent[i] = i;
        while (M--) {
            int u, v; cin >> u >> v;
            // tree 조건 2 : u, v에서 사이클이 생기면 안된다.
            if (tree) tree = (union_tr(u, v));
        }
        if (tree) cout << "tree\n";
        else cout << "graph\n";
    }
    return 0;
}