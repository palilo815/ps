#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct elem {
    ll c;
    int f, u;
    elem(ll c, int f, int u) : c(c), f(f), u(u) {}
    bool operator<(const elem& rhs) const {
        return c == rhs.c ? f > rhs.f : c > rhs.c;
    }
};

const int mxN = 1e3;

vector<pair<int, int>> ticket[mxN];
ll cost[mxN];
int flight[mxN];

vector<int> route[mxN];
int pay[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int src, dst, N;
    cin >> src >> dst >> N;
    --src, --dst;

    for (int i = 0, cnt; i < N; ++i) {
        cin >> pay[i] >> cnt;
        route[i].resize(cnt);

        for (int j = 0; j < cnt; ++j) {
            cin >> route[i][j];
            ticket[--route[i][j]].emplace_back(i, j);
        }
    }

    memset(cost, 0x3f, sizeof(cost));
    memset(flight, 0x3f, sizeof(flight));

    priority_queue<elem> pq;
    pq.emplace(cost[src] = 0, flight[src] = 0, src);

    while (!pq.empty()) {
        auto [c, f, u] = pq.top();
        pq.pop();
        if (cost[u] != c || flight[u] != f)
            continue;
        if (u == dst) return cout << c << ' ' << f, 0;

        for (auto& [route_num, idx] : ticket[u]) {
            ll C = c + pay[route_num];
            for (int F = f + 1, i = idx + 1; i < route[route_num].size(); ++i, ++F) {
                int v = route[route_num][i];
                if (cost[v] > C || (cost[v] == C && flight[v] > F))
                    pq.emplace(cost[v] = C, flight[v] = F, v);
            }
        }
    }
    cout << "-1 -1";
    return 0;
}