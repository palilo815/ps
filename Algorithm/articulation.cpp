/*
    https://codeforces.com/blog/entry/71146
    By "searleser97"
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 100;

vector<int> adj[max_N];
int disc[max_N], low[max_N];
bool ap[max_N];
vector<p> br;

int Time;

int dfsAP(int u, int p) {
    int children = 0;
    low[u] = disc[u] = ++Time;
    for (int v : adj[u]) {
        if (v == p) continue; // we don't want to go back through the same path.
                              // if we go back is because we found another way back
        if (!disc[v]) { // if V has not been discovered before
            children++;
            dfsAP(v, u); // recursive DFS call
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
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    memset(ap, 0, sizeof(ap));
    Time = 0;

    for (int u = 0; u < max_N; ++u) if (!disc[u])
        ap[u] = dfsAP(u, u) > 1; // condition #2
}




void dfsBR(int u, int p) {
    low[u] = disc[u] = ++Time;
    for (int v : adj[u]) {
        if (v == p) continue; // we don't want to go back through the same path.
                              // if we go back is because we found another way back
        if (!disc[v]) { // if V has not been discovered before
            dfsBR(v, u);  // recursive DFS call
            if (disc[u] < low[v]) // condition to find a bridge
                br.push_back({ u, v });
            low[u] = min(low[u], low[v]); // low[v] might be an ancestor of u
        }
        else // if v was already discovered means that we found an ancestor
            low[u] = min(low[u], disc[v]); // finds the ancestor with the least discovery time
    }
}
void BR() {
    memset(disc, 0, sizeof(disc));
    memset(low, 0, sizeof(low));
    memset(ap, 0, sizeof(ap));
    Time = 0;
    for (int u = 0; u < max_N; ++u) if (!disc[u])
        dfsBR(u, -1)
}