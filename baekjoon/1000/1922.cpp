#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

pair<int, P> arr[100000];
int N, M;

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

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N >> M;
    loop(i, M) {
        int u, v, w; cin >> u >> v >> w;
        arr[i] = { w,{u,v} };
    }
    sort(arr, arr + M);
    DisjointSet sets(N + 1);
    vector<bool> selected(N + 1);
    int ans = 0;

    loop(i, M) {
        int cost = arr[i].first;
        int u = arr[i].second.first, v = arr[i].second.second;
        if (sets.find(u) == sets.find(v)) continue;
        sets.merge(u, v);
        ans += cost;
    }
    cout << ans;
    return 0;
}