#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<int, int> p;
typedef tuple<ll, int, int> tup;

const int MAX = 1000;

vector<p> adj[MAX + 1];
ll cost[MAX + 1];
int flight[MAX + 1];

vector<int> route[MAX];
int pay[MAX];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int src, dst, M; cin >> src >> dst >> M;
    loop(i, M) {
        cin >> pay[i];
        int cnt; cin >> cnt;
        route[i].resize(cnt);
        loop(j, cnt) {
            cin >> route[i][j];
            adj[route[i][j]].emplace_back(i, j);
        }
    }

    memset(cost, 0x3f, sizeof(cost));
    memset(flight, 0x3f, sizeof(flight));
    cost[src] = flight[src] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, 0, src);

    while (!pq.empty()) {
        auto [c, f, u] = pq.top(); pq.pop();
        if (cost[u] < c || (cost[u] == c && flight[u] < f))
            continue;
        if (u == dst) { cout << c << ' ' << f; return 0; }

        for (auto [idx, pos] : adj[u]) {
            ll C = c + pay[idx];
            int F = f;
            while (++pos < route[idx].size()) {
                ++F;
                int v = route[idx][pos];
                if (cost[v] > C || (cost[v] == C && flight[v] > F)) {
                    cost[v] = C, flight[v] = F;
                    pq.emplace(C, F, v);
                }
            }
        }
    }
    cout << "-1 -1";
    return 0;
}