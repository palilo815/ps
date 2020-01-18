#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

struct DisjointSet {
    vector<int> parent, rank, size;
    DisjointSet(int n) : parent(n), rank(n, 1), size(n, 1) {
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
        size[v] += size[u];
    }
    int Fr_num(int u) {
        u = Find(u);
        return size[u];
    }
};


int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int t, F;
    cin >> t;
    while (t--) {
        map<string, int> Fnw;
        map<string, int>::iterator it;
        string s1, s2;
        int n1, n2, num = 0;
        cin >> F;
        DisjointSet Dset(2 * F);
        while (F--) {
            cin >> s1 >> s2;
            it = Fnw.find(s1);
            if (it == Fnw.end()) {
                n1 = num++;
                Fnw[s1] = n1;
            }
            else n1 = (*it).second;
            it = Fnw.find(s2);
            if (it == Fnw.end()) {
                n2 = num++;
                Fnw[s2] = n2;
            }
            else n2 = (*it).second;
            Dset.Merge(n1, n2);
            cout << Dset.Fr_num(n1) << '\n';
        }
    }
    return 0;
}