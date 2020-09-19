#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;
struct elem {
    int d, r, c;
    elem(int d, int r, int c) : d(d), r(r), c(c) {}
    bool operator<(const elem& rhs) const {
        return d > rhs.d;
    }
};

const int mx = 1e3;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx][mx];
int w[26], dist[mx][mx];

int solve() {
    int K, W, H;
    cin >> K >> W >> H;
    for (char c; K--;) {
        cin >> c;
        cin >> w[c - 'A'];
    }
    loop(i, H) loop(j, W) cin >> mat[i][j];

    priority_queue<elem> pq;
    loop(i, H) memset(dist[i], 0x3f, sizeof(int) * W);
    loop(i, H) loop(j, W) if (mat[i][j] == 'E') {
        pq.emplace(dist[i][j] = 0, i, j);
        goto out;
    }
out:
    for (;;) {
        auto [d, r, c] = pq.top();
        pq.pop();

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ H && ~C && C ^ W) {
                int D = d + w[mat[R][C] - 'A'];
                if (dist[R][C] > D)
                    pq.emplace(dist[R][C] = D, R, C);
            } else
                return d;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) cout << solve() << '\n';
    return 0;
}