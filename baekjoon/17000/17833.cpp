#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 2000;
const int max_M = 2000;

struct building {
    int height, cost, u, v;
};

int cost[max_N + 1];
building edge[max_M];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // Dijkstra로 풀었으나 DP로 접근하는게 더 나은 듯
    // DP로 풀었으나 틀렸는데, 아마 같은 건물을 여러번 쓸 수 있는 케이스에서 오류가 있었던 것 같다.

    int N, src, dst, M;
    cin >> N >> src >> dst >> M;
    loop(i, M)
        cin >> edge[i].height >> edge[i].cost >> edge[i].u >> edge[i].v;

    fill(cost + 1, cost + N + 1, INT_MAX);
    cost[src] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ 0,src });

    int ans = -1;
    while (!pq.empty()) {
        auto [c, d] = pq.top(); pq.pop();
        if (cost[d] < c) continue;
        if (d == dst) { ans = c; break; }

        loop(i, M) {
            auto& e = edge[i];
            if (d >= e.u && d + e.height - e.u <= N) {
                int D = d - e.u + e.v, C = c + e.cost;
                if (cost[D] > C) {
                    cost[D] = C;
                    pq.push({ C,D });
                }
            }
            if (d >= e.v && d + e.height - e.v <= N) {
                int D = d - e.v + e.u, C = c + e.cost;
                if (cost[D] > C) {
                    cost[D] = C;
                    pq.push({ C,D });
                }
            }
        }
    }
    cout << ans;
    return 0;
}