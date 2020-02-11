#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 100;

vector<int> adj[max_N], rev[max_N];
int price[max_N];
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
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) cin >> price[i];
    loop(i, N) loop(j, N) {
        char x; cin >> x;
        if (x == '1') {
            adj[i].push_back(j);
            rev[j].push_back(i);
        }
    }

    loop(i, N) if (!visited[i])
        DFS(i);
    memset(visited, 0, N);
    int ans = 0;
    while (!stk.empty()) {
        if (!visited[stk.top()]) {
            // vt에는 SCC vtx의 index가 담긴다.
            vector<int> vt;
            SCC(stk.top(), vt);
            int cost = INT_MAX;
            for (int i : vt)
                cost = min(cost, price[i]);
            ans += cost;
        }
        stk.pop();
    }
    cout << ans;
    return 0;
}