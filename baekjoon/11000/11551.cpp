#include <bits/stdc++.h>
using namespace std;

struct elem {
    int cost, i;
    elem(int cost, int i) : cost(cost), i(i) {}
    bool operator<(const elem& rhs) const {
        return cost > rhs.cost;
    }
};
struct pack {
    int i, s, c;
};

const int mxN = 1e5;

int e[mxN + 1];
pack shop[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; ++i)
        cin >> e[i];
    for (int i = 0; i < M; ++i)
        cin >> shop[i].i >> shop[i].s >> shop[i].c;

    partial_sum(e, e + N + 1, e);
    sort(shop, shop + M, [&](auto& a, auto& b) {
        return a.i < b.i;
    });

    priority_queue<elem> pq;
    pq.emplace(0, 1);

    for (int i = 1, j = 0; i <= N; ++i) {
        while (!pq.empty() && pq.top().i < i) pq.pop();
        if (pq.empty()) return cout << -1, 0;

        for (; shop[j].i == i; ++j)
            pq.emplace(pq.top().cost + shop[j].c, upper_bound(e + i - 1, e + N + 1, e[i - 1] + shop[j].s) - e);
    }
    while (!pq.empty() && pq.top().i <= N) pq.pop();
    cout << (pq.empty() ? -1 : pq.top().cost);
}