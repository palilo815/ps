#include <bits/stdc++.h>
using namespace std;

const int max_N = 100;

vector<int> adj[max_N];
int disc[max_N], low[max_N];
bool ap[max_N];

int Time;

int DFS_AP(int u, int p) {
    int children = 0;
    low[u] = disc[u] = ++Time;
    for (int& v : adj[u]) {
        if (v == p) continue; // we don't want to go back through the same path.
                              // if we go back is because we found another way back
        if (!disc[v]) { // if V has not been discovered before
            children++;
            DFS_AP(v, u); // recursive DFS call
            if (p != -1 && disc[u] <= low[v]) // condition #1
                ap[u] = true;
            low[u] = min(low[u], low[v]); // low[v] might be an ancestor of u
        }
        else // if v was already discovered means that we found an ancestor
            low[u] = min(low[u], disc[v]); // finds the ancestor with the least discovery time
    }
    return children;
}
void AP() {
    Time = 0;
    for (int u = 0; u < max_N; ++u)
        if (!disc[u])
            ap[u] = DFS_AP(u, u) > 1; // condition #2
}
int main()
{
    AP();
    return 0;
}