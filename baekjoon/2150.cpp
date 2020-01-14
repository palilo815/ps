#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int V;
stack<int> stk; // stack by finish time
bool visited[10001];
vector<int> adj[10001], rev[10001];
vector<vector<int>> ANS;

// Kosaraju's Algorithm
// 1. 정방향 그래프로 DFS 탐색.
//    여기서 빨리 끝난 vertex 순서대로 stack에 집어넣음
// 2. stack에서 순서대로 꺼내며 역방향 그래프로 DFS탐색
void DFS1(int start)
{
    visited[start] = true;
    loop(i, adj[start].size()) {
        int To = adj[start][i];
        if (!visited[To])
            DFS1(To);
    }
    stk.push(start);
}

void DFS2(int start, vector<int>& vt)
{
    visited[start] = true;
    vt.push_back(start);
    loop(i, rev[start].size()) {
        int To = rev[start][i];
        if (!visited[To])
            DFS2(To, vt);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int E;
    cin >> V >> E;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 1; i <= V; ++i)
        if (!visited[i])
            DFS1(i);
    memset(visited, 0, sizeof(visited));

    while (!stk.empty()) {
        int Start = stk.top(); stk.pop();
        if (visited[Start]) continue;
        vector<int> tmp;
        DFS2(Start, tmp);
        sort(tmp.begin(), tmp.end());
        ANS.push_back(tmp);
    }
    sort(ANS.begin(), ANS.end());
    cout << ANS.size() << '\n';
    loop(i, ANS.size()) {
        loop(j, ANS[i].size())
            cout << ANS[i][j] << ' ';
        cout << "-1\n";
    }
    return 0;
}