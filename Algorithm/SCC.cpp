#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;

vector<int> adj[max_N], rev[max_N];
bool visited[max_N];
stack<int> stk;

void DFS(int u)
{
    visited[u] = true;
    for (int v : adj[u])
        if (!visited[v]) DFS(v);
    stk.push(u);
}
void SCC(int u, vector<int>& vt)
{
    visited[u] = true;
    vt.push_back(u);
    for (int v : rev[u])
        if (!visited[v]) SCC(v, vt);
}
int main()
{
    // ** Kosaraju's algorithm ** //

    int N;

    memset(visited, 0, sizeof(visited));
    loop(i, N) if (!visited[i])
        DFS(i);

    memset(visited, 0, sizeof(visited));
    while (!stk.empty()) {
        if (!visited[stk.top()]) {
            vector<int> vt;
            SCC(stk.top(), vt);
            for (int i : vt)
                cout << i << ' ';
            cout << '\n';
        }
        stk.pop();
    }

    return 0;
}