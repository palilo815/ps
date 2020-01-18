#include <bits/stdc++.h>
#define LOOP(i,n) for(int i=1;i<=n;++i)
#define P pair<int,int>
using namespace std;

vector<int> adj[10001];
int T[10001], pre[10001];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    LOOP(i, N) {
        int M; cin >> T[i] >> M;
        while (M--) {
            int idx; cin >> idx;
            ++pre[idx];
            adj[i].push_back(idx);
        }
    }

    priority_queue<P, vector<P>, greater<P>>pq;
    // 바로 시작할 수 있는 일을 다 집어넣음
    LOOP(i, N)
        if (!pre[i])
            pq.push({ T[i], i });

    int ans, job;
    while (!pq.empty()) {
        // ans : 해당 job이 끝난 시간, job : 지금 완료한 일
        ans = pq.top().first, job = pq.top().second; pq.pop();

        // 만약 job을 완료함으로써, 모든 선행 관계가 완료되었다면
        // pq에 집어넣는다. 그 일이 끝나는 시간은 job이 끝난 시간 + 그 일에 걸리는 시간이다.
        for (int v : adj[job])
            if (--pre[v] == 0)
                pq.push({ ans + T[v],v });
    }
    cout << ans;
    return 0;
}