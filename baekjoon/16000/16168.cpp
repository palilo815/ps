#include <cstdio>

const int max_V = 3001;

int cnt[max_V];
int parent[max_V];

int find_rt(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find_rt(parent[u]);
}
int main() {
    int V, E; scanf("%d %d", &V, &E);
    for (int i = 1; i <= V; ++i) parent[i] = i;
    while (E--) {
        int u, v; scanf("%d %d", &u, &v);
        ++cnt[u], ++cnt[v];
        u = find_rt(u), v = find_rt(v);
        parent[u] = v;
    }

    int odd = 0, rt = find_rt(1);
    for (int i = 1; i <= V; ++i) {
        if (cnt[i] & 1) ++odd;
        if (find_rt(i) != rt) { odd = -1; break; }
    }

    printf("%s", (odd == 0 || odd == 2) ? "YES" : "NO");
    return 0;
}