#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

bool visited[100001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    deque<int> dq;
    int u, v; cin >> u >> v;
    dq.push_back(u);
    visited[u] = true;
    if (u && u * 2 < 100001) {
        dq.push_back(2 * u);
        visited[2 * u] = true;
    }
    dq.push_back(-1);
    int ans = 0;
    while (1) {
        int here = dq.front(); dq.pop_front();
        if (here == -1) {
            ++ans; dq.push_back(here);
            continue;
        }
        if (here == v) break;
        if (here * 2 < 100001 && !visited[here * 2]) {
            dq.push_front(here * 2);
            visited[here * 2] = true;
        }
        if (here + 1 < 100001 && !visited[here + 1]) {
            dq.push_back(here + 1);
            visited[here + 1] = true;
        }
        if (here - 1 >= 0 && !visited[here - 1]) {
            dq.push_back(here - 1);
            visited[here - 1] = true;
        }
    }
    cout << ans;
    return 0;
}