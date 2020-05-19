#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int M = 1000;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int S[M][M];
bool mine[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, K; cin >> row >> col >> K;
    loop(i, row) loop(j, col) cin >> S[i][j];

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    loop(j, col) {
        pq.emplace(S[0][j], 0, j);
        mine[0][j] = true;
    }
    for (int i = 1; i < row; ++i) {
        pq.emplace(S[i][0], i, 0);
        mine[i][0] = true;
        if (col > 1) {
            pq.emplace(S[i][col - 1], i, col - 1);
            mine[i][col - 1] = true;
        }
    }

    int ans = 0;
    while (K--) {
        auto [d, r, c] = pq.top(); pq.pop();
        ans = max(ans, d);

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || mine[R][C]) continue;
            mine[R][C] = true;
            pq.emplace(S[R][C], R, C);
        }
    }
    cout << ans;
    return 0;
}