#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// capacity : 허용량, flow : 흐르는 양
int capacity[52][52], flow[52][52];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** initialize **
    int E; cin >> E;
    while (E--) {
        char u, v; int c;
        cin >> u >> v >> c;
        int num_u = u < 'a' ? u - 'A' : u - 'a' + 26;
        int num_v = v < 'a' ? v - 'A' : v - 'a' + 26;
        // 양 쪽 capacity를 모두 올려준다.
        capacity[num_u][num_v] += c;
        capacity[num_v][num_u] += c;
    }

    // ** network flow **
    int parent[52], ans;
    queue<int> q;
    while (1) {
        // clear parent[] and queue
        memset(parent, -1, sizeof(parent));
        q = queue<int>();
        // 시작은 항상 A
        parent[0] = 0;
        q.push(0);

        // 경로찾기
        while (!q.empty() && parent[25] == -1) {
            int here = q.front(); q.pop();
            loop(i, 52)
                if (capacity[here][i] - flow[here][i] > 0 && parent[i] == -1) {
                    q.push(i);
                    parent[i] = here;
                }
        }

        // Z로 도달하지 못했다면 끝
        if (parent[25] == -1) break;

        // 찾은 경로로 보낼 수 있는 양을 구한다.
        int amount = INT_MAX;
        for (int p = 25;p != 0;p = parent[p])
            amount = min(amount, capacity[parent[p]][p] - flow[parent[p]][p]);

        // flow
        for (int p = 25;p != 0;p = parent[p]) {
            flow[parent[p]][p] += amount;
            flow[p][parent[p]] -= amount;
        }
        ans += amount;
    }
    cout << ans;
    return 0;
}