#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;
const int white = 0; // not visited
const int grey = -1; // visiting
const int black = 1; // visited

int colour[max_N + 1];
vector<int> adj[max_N + 1];
stack<int> stk;

// cycle 발견하면 return false
bool DFS(int u)
{
    colour[u] = grey;
    for (int v : adj[u]) {
        if (colour[v] == grey) return false;
        if (colour[v] == white && DFS(v) == false) return false;
    }
    colour[u] = black;
    stk.push(u);
    return true;
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int m, u, v;
        cin >> m >> u;
        while (--m) {
            cin >> v;
            adj[u].push_back(v);
            u = v;
        }
    }

    bool cycle = false;
    for (int i = 1; i <= N; ++i)
        if (colour[i] == white)
            if (DFS(i) == false) {
                cycle = true;
                break;
            }

    if (cycle) cout << 0;
    else while (!stk.empty()) {
        cout << stk.top() << '\n';
        stk.pop();
    }
    return 0;
}