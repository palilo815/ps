#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> p;

const int max_N = 10000;

int cost[max_N + 1];
bool made[max_N + 1];
vector<p> recipe[max_N + 1];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    for (int i = 1; i <= N; ++i)
        cin >> cost[i];
    while (M--) {
        int res, a, b; cin >> res >> a >> b;
        recipe[a].emplace_back(b, res);
        recipe[b].emplace_back(a, res);
    }

    priority_queue<p, vector<p>, greater<p>> pq;
    for (int i = 1; i <= N; ++i)
        pq.emplace(cost[i], i);

    while (1) {
        auto [c, u] = pq.top(); pq.pop();
        if (cost[u] < c) continue;
        if (u == 1) { cout << c; break; }

        made[u] = true;
        for (auto [v, res] : recipe[u]) if (made[v]) {
            int C = cost[u] + cost[v];
            if (cost[res] > C) {
                cost[res] = C;
                pq.emplace(C, res);
            }
        }
    }
    return 0;
}
