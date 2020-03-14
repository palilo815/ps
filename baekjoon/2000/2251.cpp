#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int capacity[3], water[3];
set<int> ans, cache;
void pour(queue<int>& q, int u, int v)
{
    // amount : u->v로 이동하는 양
    int amount = min(capacity[v] - water[v], water[u]);
    if (amount == 0) return;

    int tmp = 0;
    loop(i, 3) {
        int w = water[i];
        // u에서 amount만큼 빼고
        // v에 amount만큼 추가
        if (i == u) w -= amount;
        else if (i == v) w += amount;
        tmp += w * pow(201, 2 - i);
    }
    // tmp에는 부은 후 물의 양의 정보가 담겨있음

    // 만약 이런 경우가 이전에 없었다면, queue에 넣는다.
    if (cache.find(tmp) == cache.end()) {
        cache.insert(tmp);
        q.push(tmp);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 3) cin >> capacity[i];
    cache.insert(capacity[2]);
    queue<int> q;
    q.push(capacity[2]);

    // BFS로 찾자
    while (!q.empty()) {
        water[0] = q.front();
        water[2] = water[0] % 201; water[0] /= 201;
        water[1] = water[0] % 201; water[0] /= 201;
        q.pop();

        // 첫 물통이 비어있으면 Ans set에 세 번째 물통 양을 넣는다.
        if (water[0] == 0 && ans.find(water[2]) == ans.end()) ans.insert(water[2]);
        loop(i, 3) if (water[i]) loop(j, 3)
            if (i != j) pour(q, i, j);
    }
    for (int x : ans) cout << x << ' ';
    return 0;
}