#include <bits/stdc++.h>
using namespace std;

const int max_N = 100;

int pre[max_N + 1];
int need[max_N + 1][max_N + 1];
vector<int> adj[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v, cnt; cin >> u >> v >> cnt;
        need[u][v] = cnt;
        ++pre[u];
        adj[v].push_back(u);
    }

    // 선행 부품이 없으면 기본 부품이다.
    // 기본 부품은 자기 자신을 1개 필요로 한다.
    queue<int> q;
    for (int i = 1; i <= N; ++i)
        if (!pre[i]) {
            need[i][i] = 1;
            q.push(i);
        }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            // v는 n을 cnt개 필요로 한다.
            // cnt개의 n을 cnt * (n의 기본 부품)으로 바꾼다.
            int cnt = need[v][u];
            need[v][u] = 0;
            for (int i = 1; i <= N; ++i)
                need[v][i] += cnt * need[u][i];
            if (--pre[v] == 0) q.push(v);
        }
    }

    for (int i = 1; i <= N; ++i)
        if (need[N][i])
            cout << i << ' ' << need[N][i] << '\n';
    return 0;
}