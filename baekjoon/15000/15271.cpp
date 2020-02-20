#include <bits/stdc++.h>
using namespace std;

const int max_N = 200;

// boy -> girl 관계도
vector<int> adj[max_N / 2 + 1];

bool visited[max_N / 2 + 1];
int girl_match[max_N / 2 + 1];
int boy_match[max_N / 2 + 1];

bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    for (int v : adj[u])
        if (!girl_match[v] || DFS(girl_match[v])) {
            boy_match[u] = v;
            girl_match[v] = u;
            return true;
        }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    /*
        여자 : 1,3,5,...,199 -> idx/2+1
        남자 : 2,4,6,...,200 -> idx/2
    */
    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        if (u % 2 == v % 2) continue;
        if (u % 2) swap(u, v);
        adj[u / 2].emplace_back(v / 2 + 1);
    }

    int cnt = 0;
    for (int i = 1; i <= N / 2; ++i) {
        memset(visited, 0, sizeof(visited));
        if (DFS(i)) cnt += 2;
    }
    if (cnt < N) ++cnt;
    cout << cnt;
    return 0;
}