#include <bits/stdc++.h>
using namespace std;

const int M = 1000;

int parent[M];

int _find(int u) {
    if (parent[u] < 0) return u;
    return parent[u] = _find(parent[u]);
}
void _union(int u, int v) {
    u = _find(u), v = _find(v);
    if (u ^ v) {
        if (parent[u] < parent[v]) swap(u, v);
        parent[v] += parent[u];
        parent[u] = v;
    }
}