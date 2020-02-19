#include <bits/stdc++.h>
using namespace std;

const int max_N = 100;
const int max_M = 5000;

int N, M;
bool visited[max_N + 1];
vector<int> adj[max_N + 1];
int person[max_N + 1];  // person[i] : i번 사람이 소유한 노트북 번호
int laptop[max_M + 1];  // laptop[i] : i번 노트북의 주인

bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    // v : u가 자기꺼라고 주장한 노트북 번호
    for (int v : adj[u])
        // v의 주인이 없거나, v의 주인이 또다른 노트북을 가질 수 있는 경우
        if (!laptop[v] || DFS(laptop[v])) {
            person[u] = v;
            laptop[v] = u;
            return true;
        }
    return false;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (DFS(i)) ++ans;
    }
    cout << ans;
    return 0;
}