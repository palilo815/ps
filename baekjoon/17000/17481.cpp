#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;
const int max_M = 1000;

string member[max_M];

vector<int> adj[max_N + 1];

bool visited[max_M + 1];
int N_match[max_N + 1];
int M_match[max_M + 1];

bool DFS(int u)
{
    if (visited[u]) return false;
    visited[u] = true;
    for(int v : adj[u])
        if (!M_match[v] || DFS(M_match[v])) {
            N_match[u] = v;
            M_match[v] = u;
            return true;
        }
    return false;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    for (int i = 0; i < M; ++i)
        cin >> member[i];
    sort(member, member + M);

    for (int i = 1; i <= N; ++i) {
        int cnt; cin >> cnt;
        string s;
        while (cnt--) {
            cin >> s;
            int idx = lower_bound(member, member + M, s) - member + 1;
            adj[i].emplace_back(idx);
        }
    }

    int ans = 0;
    for (int i = 1; i <= N; ++i) {
        memset(visited, 0, sizeof(visited));
        if (DFS(i)) ++ans;
    }
    if (ans == N) cout << "YES";
    else cout << "NO\n" << ans;
    return 0;
}