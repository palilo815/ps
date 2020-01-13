#include<iostream>
#include<queue>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

bool chingu[101][101];
int n;

// BFS
int Kevin(int start)
{
    queue<int> q;
    vector<int> step(n + 1, -1);
    q.push(start);
    step[start] = 0;
    while (!q.empty()) {
        int here = q.front(); q.pop();
        loop(i, n + 1)
            if (chingu[here][i] && step[i] == -1) {
                step[i] = step[here] + 1;
                q.push(i);
            }
    }
    int ret = 0;
    loop(i, n + 1) ret += step[i];
    return ret;
}

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int m;
    cin >> n >> m;
    while (m--) {
        int u, v; cin >> u >> v;
        chingu[u][v] = true, chingu[v][u] = true;
    }

    int min = INT32_MAX, ans;
    for (int i = 1; i <= n; ++i) {
        int tmp = Kevin(i);
        if (tmp < min) {
            min = tmp;
            ans = i;
        }
    }
    cout << ans;
    return 0;
}