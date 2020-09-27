#include <bits/stdc++.h>
using namespace std;
struct elem {
    int d, u;
    elem(int d, int u) : d(d), u(u) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mxN = 50;
const int mask = (1 << 6) - 1;

vector<elem> tile[mxN * mxN + 1];
int dist[mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K;
    cin >> N >> K;
    for (int i = 0, x; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            cin >> x;
            tile[x].emplace_back(i, j);
        }

    memset(dist, 0x3f, sizeof(dist));
    priority_queue<elem> pq;
    for (auto& [r, c] : tile[1])
        pq.emplace(dist[r][c] = 0, 1 << 12 | r << 6 | c);

    while (!pq.empty()) {
        auto [d, num] = pq.top();
        pq.pop();

        int c = num & mask;
        num >>= 6;
        int r = num & mask;
        num >>= 6;

        if (dist[r][c] < d) continue;
        if (num == K) return cout << d, 0;

        for (auto& [R, C] : tile[num + 1]) {
            int D = d + abs(R - r) + abs(C - c);
            if (dist[R][C] > D)
                pq.emplace(dist[R][C] = D, (num + 1) << 12 | R << 6 | C);
        }
    }
    return cout << -1, 0;
}