#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool family[101][101], visited[101];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int n, m;
    int A,B; // A-B간 촌수를 계산해야 함
    cin >> n >> A >> B >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        family[u][v] = family[v][u] = true;
    }

    queue<int> q;
    int ans = 0;
    visited[A] = true;
    q.push(A), q.push(-1);

    while (1) {
        int here = q.front(); q.pop();
        if (here == -1) {
            if (q.empty()) break;
            ++ans; q.push(here);
            continue;
        }
        if (here == B) break;
        loop(i, n + 1) {
            if (family[here][i] && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    if (q.empty()) cout << -1;
    else cout << ans;
    return 0;
}