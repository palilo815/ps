#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int pre[100001];
void go(queue<int>& q, int u, int v)
{
    if (v < 0 || v > 100000 || pre[v] != -1) return;
    pre[v] = u;
    q.push(v);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(pre, -1, sizeof(pre));
    int u, v; cin >> u >> v;

    queue<int> q;
    q.push(u), q.push(-1);
    int ans = 0;

    while (1) {
        int here = q.front(); q.pop();
        if (here == -1) {
            ++ans; q.push(here);
            continue;
        }
        if (here == v) break;
        go(q, here, here - 1);
        go(q, here, here + 1);
        go(q, here, here * 2);
    }

    cout << ans << '\n';
    stack<int> stk;
    while (1) {
        stk.push(v);
        if (u == v) break;
        v = pre[v];
    }
    while (!stk.empty()) {
        cout << stk.top() << ' ';
        stk.pop();
    }
    return 0;
}