#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool adj[100][100], rev[100][100];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    while (E-- > 0) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u][v] = true;
        rev[v][u] = true;
    }

    // 플로이드-와샬
    // adj[i][j] : i는 j보다 확실히 무겁다
    // rev[i][j] : i는 j보다 확실히 가볍다
    loop(i, V) adj[i][i] = true, rev[i][i] = true;
    loop(k, V) loop(i, V) loop(j, V)
        adj[i][j] = adj[i][j] || (adj[i][k] && adj[k][j]);
    loop(k, V) loop(i, V) loop(j, V)
        rev[i][j] = rev[i][j] || (rev[i][k] && rev[k][j]);

    loop(i, V) {
        int ans = 0;
        // 만약 j가 i보다 확실히 가볍거나 무거우면 ans증가
        loop(j, V)
            if (adj[i][j] || rev[i][j]) ans++;
        // ans : 확실히 무게를 비교할 수 있는 개수
        // 따라서 비교할 수 없는 개수는 V-ans
        cout << V - ans << '\n';
    }
    return 0;
}