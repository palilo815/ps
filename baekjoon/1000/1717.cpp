#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n, 1) {
        loop(i, n) parent[i] = i;
    }
    int Find(int u) {
        if (u == parent[u]) return u;
        return parent[u] = Find(parent[u]);
    }
    void Merge(int u, int v) {
        u = Find(u), v = Find(v);
        if (u == v) return;
        if (rank[u] > rank[v]) swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v]) ++rank[v];
    }
};


int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m; cin >> n >> m;
    DisjointSet Dset(n + 1);
    while (m--) {
        int op, u, v;
        cin >> op >> u >> v;
        if (op) {
            if (Dset.Find(u) == Dset.Find(v)) cout << "YES\n";
            else cout << "NO\n";
        }
        else
            Dset.Merge(u, v);
    }
    return 0;
}