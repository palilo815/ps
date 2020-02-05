#include <bits/stdc++.h>
using namespace std;
const int max_N = 500;

int parent[max_N + 1];
int find_rt(int u)
{
    if (u == parent[u] || parent[u] == -1) return parent[u];
    return parent[u] = find_rt(parent[u]);
}
void union_tr(int u, int v)
{
    u = find_rt(u), v = find_rt(v);
    if (v == -1) swap(u, v);

    // 만약 u랑 v랑 같은 트리인데 서로 연결이 된다면
    // 사이클이 생겨서 더이상 트리가 아니다.
    // 트리가 아닌 트리는(?) root를 -1로 만든다.
    if (u == v) parent[u] = parent[v] = -1;
    else parent[v] = u;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, t = 0;
    while (1) {
        cin >> N >> M;
        if (N == 0) break;
        
        for (int i = 1; i <= N; ++i)
            parent[i] = i;

        while (M--) {
            int u, v; cin >> u >> v;
            union_tr(u, v);
        }

        set<int> root;
        for (int i = 1; i <= N; ++i)
            root.insert(find_rt(i));

        int ans = root.size();
        if (root.find(-1) != root.end()) --ans;

        cout << "Case " << ++t << ": ";
        switch (ans) {
        case 0: cout << "No trees.\n";
            break;
        case 1: cout << "There is one tree.\n";
            break;
        default: cout << "A forest of " << ans << " trees.\n";
        }
    }
    return 0;
}