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

const int mxN = 50;
const int b = 1 << 15;
const int mov[4][2] = {-1, 0, 0, -1, 0, 1, 1, 0};

char mat[mxN + 2][mxN + 2];
int dist[mxN + 2][mxN + 2];

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
        cin >> (mat[i] + 1);

    for (int i = 1; i <= N; ++i)
        memset(dist[i] + 1, 0x3f, sizeof(int) * M);

    priority_queue<elem> pq;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            if (mat[i][j] == '.' && (mat[i - 1][j] == 'g' || mat[i][j - 1] == 'g' || mat[i][j + 1] == 'g' || mat[i + 1][j] == 'g'))
                mat[i][j] = 'h';
            else if (mat[i][j] == 'S')
                pq.emplace(dist[i][j] = 0, i, j);

    for (;;) {
        auto [d, r, c] = pq.top();
        pq.pop();
        if (dist[r][c] < d) continue;
        if (mat[r][c] == 'F') {
            cout << d / b << ' ' << d % b;
            break;
        }

        for (int i = 0; i < 4; ++i) {
            int R = r + mov[i][0], C = c + mov[i][1], D = d;
            if (mat[R][C] == 'g')
                D += b;
            else if (mat[R][C] == 'h')
                D += 1;

            if (dist[R][C] > D)
                pq.emplace(dist[R][C] = D, R, C);
        }
    }
    return 0;
}