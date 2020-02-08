#include<bits/stdc++.h>
using namespace std;

const int RANGE = 500000;

int dist[2][RANGE + 1];

void go(queue<int>& q, int v, int cost)
{
    int t = 1 - (cost % 2);
    if (v < 0 || v > RANGE || dist[t][v] != -1) return;
    dist[t][v] = cost;
    q.push(v);
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    memset(dist, -1, sizeof(dist));
    int src, dst; cin >> src >> dst;
    queue<int> q;
    q.push(src), q.push(-1);

    // pos에 t초에 갈 수 있으면
    // t+2, t+4 ... 초에도 역시 pos에 갈 수 있다.
    // 따라서 시간이 짝수일 때, 홀수일 때의 최소거리를 구한다.
    dist[0][src] = 0;
    int cost = 0;
    while (1) {
        int u = q.front(); q.pop();
        if (u == -1) {
            if (q.empty()) break;
            ++cost; q.push(-1);
            continue;
        }
        go(q, u * 2, cost);
        go(q, u - 1, cost);
        go(q, u + 1, cost);
    }
    
    // dst가 d초에 pos에 도착할 수 있고
    // 그 때의 최소거리가 d보다 작다면 만날 수 있다.
    int ans = INT_MAX, d = 0;
    while (dst <= RANGE) {
        if (dist[d % 2][dst] <= d) ans = min(ans, d);
        dst += ++d;
    }
    cout << (ans == INT_MAX ? -1 : ans);
    return 0;
}