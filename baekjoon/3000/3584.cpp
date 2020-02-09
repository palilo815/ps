#include <bits/stdc++.h>
using namespace std;

const int max_N = 10000;

int parent[max_N + 1];
bool visited[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        memset(parent, 0, sizeof(int) * (N + 1));
        memset(visited, 0, sizeof(bool) * (N + 1));
        while (--N) {
            int u, v; cin >> u >> v;
            parent[v] = u;
        }
        int u, v; cin >> u >> v;
        // parent[root] = 0 이므로
        // u 부터 root까지 전부 방문체크 한다.
        while (u) {
            visited[u] = true;
            u = parent[u];
        }
        // v에서 위로 올라가다가, u가 방문한 곳을 만나면
        // 그녀석이 LCA임
        while (!visited[v]) v = parent[v];
        cout << v << '\n';
    }
    return 0;
}