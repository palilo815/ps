#include <bits/stdc++.h>
using namespace std;

bool visited[1 << 10];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    string src, dst; cin >> src >> dst;
    int s = stoi(src, 0, 2), d = stoi(dst, 0, 2);

    queue<int> q;
    q.emplace(s), q.emplace(-1);

    int ans = 0;
    visited[s] = true;

    for (;;) {
        int u = q.front(); q.pop();
        if (u == -1) {++ans; q.emplace(-1); continue;}
        if (u == d) break;

        for (int i = 0; i < 31 - __builtin_clz(u); ++i) {
            int v = u ^ (1 << i);
            if (!visited[v]) {
                visited[v] = true;
                q.emplace(v);
            }
        }
        if (u && !visited[u - 1]) {
            visited[u - 1] = true;
            q.emplace(u - 1);
        }
        if (u + 1 != (1 << 10) && !visited[u + 1]) {
            visited[u + 1] = true;
            q.emplace(u + 1);
        }
    }
    cout << ans;
    return 0;
}