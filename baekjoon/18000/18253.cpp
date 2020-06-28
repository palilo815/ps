#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
using tup = tuple<ll, int, int>;
struct query {
    int r1, c1, r2, c2, idx;
};

const int N = 5, M = 100000;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0 };

int row, col;
int mat[N][M];
ll dist[N][M];
ll ans[M];
query q[M];
priority_queue<tup, vector<tup>, greater<tup>> pq;

void Dijkstra(int s, int m, int e, int src) {
    loop(i, row) memset(dist[i] + s, 0x3f, sizeof(ll) * (e - s));
    pq.emplace(dist[src][m] = 0, src, m);

    while (!pq.empty()) {
        auto [d, r, c] = pq.top(); pq.pop();
        if (dist[r][c] < d) continue;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < s || C >= e) continue;
            ll D = d + mat[R][C];
            if (dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
        }
    }
}
void solve(int s, int e, int qs, int qe) {
    if (s >= e || qs >= qe) return;
    int m = (s + e) >> 1;
    loop(r, row) {
        Dijkstra(s, m, e, r);
        for (int i = qs; i < qe; ++i) {
            auto& [r1, c1, r2, c2, idx] = q[i];
            ans[idx] = min(ans[idx], dist[r1][c1] + dist[r2][c2] + mat[r][m]);
        }
    }

    int it1 = qs, it2 = qs;
    for (int i = qs; i < qe; ++i) {
        if (q[i].c2 < m) {
            query tmp = q[i];
            q[it2++] = q[it1];
            q[it1++] = tmp;
        }
        else if (m < q[i].c1) q[it2++] = q[i];
    }
    solve(s, m, qs, it1), solve(m, e, it1, it2);
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];
    int Q; cin >> Q;
    loop(i, Q) {
        auto& [r1, c1, r2, c2, idx] = q[i];
        cin >> r1 >> c1 >> r2 >> c2;
        --r1, --c1, --r2, --c2;
        if (c1 > c2)
            swap(r1, r2), swap(c1, c2);
        idx = i;
    }

    memset(ans, 0x3f, sizeof(ll) * Q);
    solve(0, col, 0, Q);
    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}