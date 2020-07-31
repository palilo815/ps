#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int mx = 25;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

int mat[mx][mx], up[mx][mx], down[mx][mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, T, D;
    cin >> row >> col >> T >> D;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        mat[i][j] = c - (c < 'a' ? 'A' : 'a' - 26);
    }

    memset(up, 0x3f, sizeof(up));
    memset(down, 0x3f, sizeof(down));
    up[0][0] = down[0][0] = 0;
    priority_queue<p, vector<p>, greater<p>> pq;

    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, r] = pq.top(); pq.pop();
        int c = r % mx; r /= mx;
        if (up[r][c] < d) continue;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == row || C == -1 || C == col) continue;

            int gap = abs(mat[R][C] - mat[r][c]);
            if (gap > T) continue;

            int D = d + (mat[R][C] > mat[r][c] ? gap * gap : 1);
            if (up[R][C] > D) {
                up[R][C] = D;
                pq.emplace(D, R * mx + C);
            }
        }
    }

    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, r] = pq.top(); pq.pop();
        int c = r % mx; r /= mx;
        if (down[r][c] < d) continue;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == row || C == -1 || C == col) continue;

            int gap = abs(mat[R][C] - mat[r][c]);
            if (gap > T) continue;

            int D = d + (mat[R][C] < mat[r][c] ? gap * gap : 1);
            if (down[R][C] > D) {
                down[R][C] = D;
                pq.emplace(D, R * mx + C);
            }
        }
    }

    int ans = 0;
    loop(i, row) loop(j, col) if (up[i][j] + down[i][j] <= D)
        ans = max(ans, mat[i][j]);
    cout << ans;
    return 0;
}