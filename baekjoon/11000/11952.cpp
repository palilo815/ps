#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> P;
const int max_N = 100000;

vector<int> adj[max_N + 1];
int city[max_N + 1];
ll cost[max_N + 1];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M, K, S, pay_s, pay_d;
    cin >> N >> M >> K >> S >> pay_s >> pay_d;

    // 점령당한 K개의 도시는 -1로 표시한다.
    queue<int> q;
    while (K--) {
        int idx; cin >> idx;
        q.push(idx);
        city[idx] = -1;
    }

    while (M--) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    q.push(-1);
    int dist = 0;
    // dist <= S인 도시는 위험한 도시다. 1로 표시한다.
    // dist == S-1일 때 dist == S인 도시를 전부 체크해주므로
    // while(dist < S)라고 해야한다.
    while (dist < S) {
        int u = q.front(); q.pop();
        if (u == -1) {
            ++dist; q.push(-1);
            continue;
        }
        for (int v : adj[u])
            if (city[v] == 0) {
                city[v] = 1;
                q.push(v);
            }
    }

    for (int i = 1; i <= N; ++i)
        cost[i] = INT64_MAX;
    cost[1] = 0;

    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,1 });
    ll ans;
    while (1) {
        ll c = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (c > cost[u]) continue;
        // 도착지에서 숙박할 필요 없으므로 빼준다.
        if (u == N) {
            ans = c - (city[u] ? pay_d : pay_s);
            break;
        }

        for (int v : adj[u]) {
            if (city[v] == -1) continue;
            ll C = c + (city[v] ? pay_d : pay_s);
            if (cost[v] > C) {
                cost[v] = C;
                pq.push({ C, v });
            }
        }
    }
    cout << ans;
    return 0;
}