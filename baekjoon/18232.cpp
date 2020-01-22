#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

vector<int> tele[300001];
bool visited[300001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int V, E, s, e;
    cin >> V >> E >> s >> e;
    while (E--) {
        int u, v; cin >> u >> v;
        tele[u].push_back(v);
        tele[v].push_back(u);
    }

    int ans = 0;
    queue<int> q;
    q.push(s), q.push(-1);
    visited[s] = true;
    while (1) {
        int curr = q.front(); q.pop();
        if (curr == -1) {
            ++ans; q.push(curr);
            continue;
        }
        if (curr == e) break;
        if (curr - 1 > 0 && !visited[curr - 1]) {
            visited[curr - 1] = true;
            q.push(curr - 1);
        }
        if (curr + 1 <= V && !visited[curr + 1]) {
            visited[curr + 1] = true;
            q.push(curr + 1);
        }
        for (int x : tele[curr])
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
    }
    cout << ans;
    return 0;
}