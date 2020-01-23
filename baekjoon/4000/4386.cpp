#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<double,int>

struct DisjointSet {
    vector<int> parent, rank;
    DisjointSet(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    int find(int u) {
        if (u == parent[u])
            return u;
        return parent[u] = find(parent[u]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v)
            return;
        if (rank[u] > rank[v])
            swap(u, v);
        parent[u] = v;
        if (rank[u] == rank[v])
            ++rank[v];
    }
};


double star[100][2];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // Kruskal Algorithm
    int V; cin >> V;
    loop(i, V) cin >> star[i][0] >> star[i][1];

    vector<P> edges;
    loop(i, V - 1) for (int j = i + 1;j < V;++j) {
        double dy = star[i][0] - star[j][0], dx = star[i][1] - star[j][1];
        edges.push_back({ dy * dy + dx * dx, 128 * i + j });
    }
    sort(edges.begin(), edges.end());
    DisjointSet sets(V);

    double ans = 0;
    int len = edges.size();
    loop(i, len) {
        double dist = edges[i].first;
        int u = edges[i].second / 128, v = edges[i].second % 128;

        if (sets.find(u) == sets.find(v)) continue;
        sets.merge(u, v);
        ans += sqrt(dist);
    }
    cout << fixed << setprecision(8) << ans;
    return 0;
}