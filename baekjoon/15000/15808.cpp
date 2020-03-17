#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

bool visited[max_N];
int adj[max_N][max_N];
int happy[max_N];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> adj[i][j];
    fill(happy, happy + N, INT_MIN);

    int src, dst; cin >> src >> dst;
    while (src--) {
        int idx, val; cin >> idx >> val;
        happy[idx - 1] = val;
    }

    vector<p> vt(dst);
    loop(i, dst) cin >> vt[i].first >> vt[i].second;

    while (1) {
        int u = -1;
        loop(i, N) if (!visited[i])
            if (u == -1 || (happy[i] > happy[u]))
                u = i;
        if (u == -1) break;

        visited[u] = true;
        loop(v, N) if (!visited[v] && adj[u][v])
            happy[v] = max(happy[v], happy[u] - adj[u][v]);
    }

    int ans = INT_MIN;
    for (auto [idx, val] : vt)
        ans = max(ans, happy[idx - 1] + val);
    cout << ans;
    return 0;
}