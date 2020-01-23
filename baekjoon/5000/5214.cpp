#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

// adj_tube[i] : i역과 연결된 튜브의 번호
// tube[i] : i튜브와 연결된 역 목록
vector<int> adj_tube[100001], tube[1000];
// visited : 역의 방문 여부, used : 튜브의 사용 여부
bool visited[100001], used[1000];

int BFS(int src, int dst)
{
    int ret = 1;
    queue<int> q;
    q.push(src); q.push(-1);
    visited[src] = true;
    while (1) {
        int here = q.front(); q.pop();
        // pivot
        if (here == -1) {
            if (q.empty()) return -1;
            ++ret; q.push(-1);
            continue;
        }
        // find answer
        if (here == dst) return ret;
        // move
        for (int tube_num : adj_tube[here]) {
            // 사용한 적 있는 튜브는 패스한다.
            if (used[tube_num]) continue;

            // 해당 튜브로 갈 수 있는 역들을 방문
            used[tube_num] = true;
            for (int next : tube[tube_num])
                if (!visited[next]) {
                    visited[next] = true;
                    q.push(next);
                }
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, K, M; cin >> N >> K >> M;
    loop(i, M) loop(j, K) {
        int st; cin >> st;
        adj_tube[st].push_back(i);
        tube[i].push_back(st);
    }
    cout << BFS(1, N);
    return 0;
}