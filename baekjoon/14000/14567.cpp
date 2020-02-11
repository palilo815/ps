#include <bits/stdc++.h>
using namespace std;

const int max_N = 1000;

int pre[max_N + 1], ans[max_N + 1];
vector<int> adj[max_N + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    while (M--) {
        int u, v; cin >> u >> v;
        ++pre[v];
        adj[u].push_back(v);
    }

    // 선수과목이 없는 애들을 전부 q에 넣는다.
    queue<int> q;
    for (int i = 1; i <= N; ++i)
        if (!pre[i]) q.push(i);
    // pivot
    q.push(-1);

    int t = 1;
    while (1) {
        int u = q.front(); q.pop();
        if (u == -1) {
            if (q.empty()) break;
            ++t; q.push(-1);
            continue;
        }

        // u과목은 t학기에 듣는다.
        ans[u] = t;
        // u가 선수과목인 v의 pre를 전부 1씩 줄여주고,
        // 0이 됐다면 q에 넣는다.
        for (int v : adj[u])
            if (--pre[v] == 0) q.push(v);
    }
    for (int i = 1; i <= N; ++i)
        cout << ans[i] << ' ';
    return 0;
}