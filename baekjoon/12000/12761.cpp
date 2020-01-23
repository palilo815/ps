#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

bool visited[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<int> q;
    int A, B, u, v;
    cin >> A >> B >> u >> v;
    int mov[6] = { A,B,-A,-B,-1,1 };
    q.push(u), q.push(-1);
    visited[u] = true;
    int ans = 0;
    while (1) {
        int here = q.front(); q.pop();
        if (here == -1) {
            ++ans; q.push(here);
            continue;
        }
        if (here == v) break;
        loop(i, 6) {
            int next = here + mov[i];
            if (next < 0 || next>100000 || visited[next]) continue;
            visited[next] = true;
            q.push(next);
        }
        loop(i, 2) {
            int next = here * mov[i];
            if (next > 100000 || visited[next]) continue;
            visited[next] = true;
            q.push(next);
        }
    }
    cout << ans;
    return 0;
}