#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int MAX = 500;

int board[MAX][MAX];
int dist[MAX][MAX];
int ans[MAX];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> board[i][j];
    loop(i, row) loop(j, col - 1) dist[i][j] = INT_MAX;

    priority_queue<p, vector<p>, greater<p>> pq;
    loop(i, row) pq.emplace(0, i * 512 * 512 + i * 512 + col - 1);

    while (!pq.empty()) {
        auto [d, goal] = pq.top(); pq.pop();
        int c = goal % 512; goal /= 512;
        int r = goal % 512; goal /= 512;
        if (dist[r][c] < d) continue;
        if (c == 0) ++ans[goal];

        d += board[r][c];
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || dist[R][C] <= d) continue;
            dist[R][C] = d;
            pq.emplace(d, goal * 512 * 512 + R * 512 + C);
        }
    }
    loop(i, row) cout << ans[i] << '\n';
    return 0;
}