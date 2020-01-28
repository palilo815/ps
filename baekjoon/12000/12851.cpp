#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// visited = {최소 거리, 가짓수}
int visited[100001][2];
void go(queue<int>& q, int u, int v) {
    if (v < 0 || v > 100000) return;

    // u -> v의 최소 경로를 갱신하는 경우
    if (visited[v][0] > visited[u][0] + 1) {
        visited[v][0] = visited[u][0] + 1;
        visited[v][1] = visited[u][1];
        q.push(v);
    }
    // 이미 최소 경로를 찾은 경우, 가짓수만 추가
    else if (visited[v][0] == visited[u][0] + 1)
        visited[v][1] += visited[u][1];
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 100001) visited[i][0] = INT_MAX;
    int src, dst; cin >> src >> dst;
    visited[src][0] = 0, visited[src][1] = 1;

    int ans = 0;
    queue<int> q;
    q.push(src);
    while (1) {
        int curr_size = q.size();
        while (curr_size--) {
            int curr = q.front(); q.pop();
            if (curr == dst) goto OUT;
            go(q, curr, curr - 1);
            go(q, curr, curr + 1);
            go(q, curr, curr * 2);
        }
        ++ans;
    }
OUT:;
    cout << ans << '\n' << visited[dst][1];
    return 0;
}