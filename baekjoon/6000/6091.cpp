#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1024;

bool v[max_N];
int adj[max_N][max_N];
int dist[max_N];
int parent[max_N];

vector<int> ans[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) {
        if (i > j) adj[i][j] = adj[j][i];
        else if (i < j) cin >> adj[i][j];
    }
    
    v[0] = true;
    loop(i, N) dist[i] = adj[0][i];
    int cnt = N - 1;

    while (cnt--) {
        int k = 0;
        loop(i, N) if (!v[i] && (!k || dist[i] < dist[k]))
            k = i;

        v[k] = true;
        ans[k].emplace_back(parent[k]);
        ans[parent[k]].emplace_back(k);

        loop(i, N) if (!v[i] && adj[k][i] < dist[i])
            dist[i] = adj[k][i], parent[i] = k;
    }

    loop(i, N) {
        cout << ans[i].size();
        sort(ans[i].begin(), ans[i].end());
        for (int x : ans[i]) cout << ' ' << x + 1;
        cout << '\n';
    }
    return 0;
}