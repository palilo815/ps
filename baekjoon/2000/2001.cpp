#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

bool visited[101][1 << 14];
int adj[101][101], jewel[101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K; cin >> N >> M >> K;

    // **initialize**
    // jewel은 보석의 종류를 bitmask로 저장한다.
    loop(i, K) {
        int idx; cin >> idx;
        jewel[idx] = 1 << i;
    }
    while (M--) {
        int u, v, w; cin >> u >> v >> w;
        adj[u][v] = adj[v][u] = w;
    }

    // **BFS**
    // q : { idx_island, bitmask_jewel }
    queue<P> q;
    q.push({ 1,0 });
    int ans = 0;
    while (!q.empty()) {
        // u : 현재 위치, jew : 가지고 있는 보석(bitmask), cnt : 보석의 개수
        int u = q.front().first, jew = q.front().second; q.pop();
        int cnt = __builtin_popcount(jew);

        // 출발지로 돌아왔다면 ans갱신
        if (u == 1) ans = max(ans, cnt);

        // 그냥 이동
        for (int v = 1;v <= N;++v)
            if (adj[u][v] >= cnt && !visited[v][jew]) {
                visited[v][jew] = true;
                q.push({ v,jew });
            }

        // 만약 현재 위치에, 나한테 없는 보석이 있다면 들고 이동
        if (jewel[u] && !(jewel[u] & jew)) {
            jew |= jewel[u];
            ++cnt;
            if (u == 1) ans = max(ans, cnt);
            for (int v = 1;v <= N;++v)
                if (adj[u][v] >= cnt && !visited[v][jew]) {
                    visited[v][jew] = true;
                    q.push({ v,jew });
                }
        }
    }
    cout << ans;
    return 0;
}