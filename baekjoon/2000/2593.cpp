#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_M = 100;

p lift[max_M];          // [x,y]
vector<int> adj[max_M]; // i번 lift로 j번 lift와 연결된 층으로 갈 수 있다면 edge연결
bool visited[max_M];    // BFS 방문체크용
bool is_end[max_M];     // lift[i]가 도착층과 연결되어있다면 is_end[i] = true
int parent[max_M];      // 역추적용

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // ** input **
    int N, M; cin >> N >> M;
    loop(i, M) cin >> lift[i].first >> lift[i].second;
    int src, dst; cin >> src >> dst;

    // ** initialize graph **
    loop(i, M - 1) {
        auto [xi, yi] = lift[i];
        for (int j = i + 1; j < M; ++j) {
            auto [xj, yj] = lift[j];
            for (int f = (xi < xj ? xi + ((xj - xi - 1) / yi + 1) * yi : xi); f <= N; f += yi)
                if ((f - xj) % yj == 0) {
                    adj[i].emplace_back(j);
                    adj[j].emplace_back(i);
                    break;
                }
        }
    }

    // 출발층과 연결된 lift는 q에 집어넣고
    // 도착층과 연결된 lift는 is_end 체크
    queue<int> q;
    loop(i, M) {
        auto [x, y] = lift[i];
        if (x <= src && (x - src) % y == 0) { q.emplace(i); visited[i] = true, parent[i] = -1; }
        if (x <= dst && (x - dst) % y == 0) is_end[i] = true;
    }

    // 문제에서 출발층 != 도착층이 보장되었으므로 ans = 1부터 시작한다.
    int ans = 1, last_lift = -1;
    q.emplace(-1);
    while (1) {
        int u = q.front(); q.pop();

        if (u == -1) {
            if (q.empty()) {
                ans = -1; break;
            }
            ++ans; q.emplace(-1);
            continue;
        }

        if (is_end[u]) {
            last_lift = u;
            break;
        }

        for (int v : adj[u]) if (!visited[v]) {
            q.emplace(v);
            visited[v] = true;
            parent[v] = u;
        }
    }

    cout << ans;
    vector<int> path;
    while (last_lift != -1) {
        path.emplace_back(last_lift);
        last_lift = parent[last_lift];
    }
    for (auto it = path.rbegin(); it != path.rend(); ++it)
        cout << '\n' << *it + 1;
    return 0;
}