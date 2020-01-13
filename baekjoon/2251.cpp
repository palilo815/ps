#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int Size[3], Water[3];
set<int> Ans, Cache;
void pour(queue<int>& q, int u, int v)
{
    // amount : u->v로 이동하는 양
    int amount = min(Size[v] - Water[v], Water[u]);
    if (amount == 0) return;

    int tmp = 0;
    loop(i, 3) {
        int w = Water[i];
        // u에서 amount만큼 빼고
        // v에 amount만큼 추가
        if (i == u) w -= amount;
        else if (i == v) w += amount;
        tmp += w * pow(201, 2 - i);
    }
    // tmp에는 부은 후 물의 양의 정보가 담겨있음

    // 만약 이런 경우가 이전에 없었다면, queue에 넣는다.
    if (Cache.find(tmp) == Cache.end()) {
        Cache.insert(tmp);
        q.push(tmp);
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    loop(i, 3) cin >> Size[i];
    Cache.insert(Size[2]);
    queue<int> q;
    q.push(Size[2]);

    // BFS로 찾자
    while (!q.empty()) {
        Water[0] = q.front();
        Water[2] = Water[0] % 201; Water[0] /= 201;
        Water[1] = Water[0] % 201; Water[0] /= 201;
        q.pop();

        // 첫 물통이 비어있으면 Ans set에 세 번째 물통 양을 넣는다.
        if (Water[0] == 0 && Ans.find(Water[2]) == Ans.end()) Ans.insert(Water[2]);
        loop(i, 3)
            if (Water[i])
                loop(j, 3) {
                if (i == j) continue;
                // i를 j에 쏟는다.
                // 만약 쏟은 후의 물통 상황이
                // 이전에 본 적 없는 경우라면 queue에 넣는다.
                pour(q, i, j);
            }
    }

    for (int x : Ans)
        cout << x << ' ';
    return 0;
}