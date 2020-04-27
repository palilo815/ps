#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 1000;

bool visited[max_N];
int adj[max_N][max_N];
int happy[max_N];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> adj[i][j];
    int src, dst; cin >> src >> dst;

    fill(happy, happy + N, INT_MIN);
    while (src--) {
        int idx, val; cin >> idx >> val;
        happy[idx - 1] = val;
    }

    vector<p> hotel(dst);
    loop(i, dst) cin >> hotel[i].first >> hotel[i].second;

    while (1) {
        int u = -1;
        loop(i, N) if (!visited[i] && (u == -1 || happy[i] > happy[u]))
            u = i;
        if (u == -1) break;

        visited[u] = true;
        loop(v, N) if (!visited[v] && adj[u][v])
            happy[v] = max(happy[v], happy[u] - adj[u][v]);
    }

    int ans = INT_MIN;
    for (auto [idx, val] : hotel)
        ans = max(ans, happy[idx - 1] + val);
    cout << ans;
    return 0;
}