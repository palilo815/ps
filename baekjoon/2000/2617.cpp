#include<bits/stdc++.h>
using namespace std;
#define LOOP(i,n) for(int i=1;i<=n;++i)

int adj[100][100], rev[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E; cin >> V >> E;
    LOOP(i, V) LOOP(j, V)
        adj[i][j] = rev[i][j] = INT32_MAX / 2;
    while (E--) {
        int u, v; cin >> u >> v;
        adj[u][v] = rev[v][u] = 1;
    }

    LOOP(k, V) LOOP(i, V) LOOP(j, V)
        adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);
    LOOP(k, V) LOOP(i, V) LOOP(j, V)
        rev[i][j] = min(rev[i][j], rev[i][k] + rev[k][j]);

    int ans = 0, order;
    LOOP(i, V) {
        bool possible = true;

        // adj그래프 기준, 자기보다 무거운 개수 센다.
        // 만약 무거운 애가 V/2 보다 많다면, 중간이 될 수 없다.
        order = 0;
        LOOP(j, V)
            if (adj[i][j] > 0 && adj[i][j] < INT32_MAX / 2)
                ++order;
        if (order > V / 2) possible = false;

        // rev그래프 기준으로도 체크
        if (possible) {
            order = 0;
            LOOP(j, V)
                if (rev[i][j] > 0 && rev[i][j] < INT32_MAX / 2)
                    ++order;
            if (order > V / 2) possible = false;
        }
        if (!possible) ++ans;
    }
    cout << ans;
    return 0;
}