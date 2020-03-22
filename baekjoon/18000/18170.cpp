#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 20;
const int x = 1 << 5;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int row, col;
char board[max_N][max_N];
set<int> cache;

inline bool is_out(int r, int c) {
    return (r < 0 || r >= row || c < 0 || c >= col);
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int src = 0;
    cin >> row >> col;
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 'o')
            src = src * x * x + i * x + j;
    }

    queue<int> q;
    q.emplace(src), q.emplace(-1);
    cache.emplace(src);

    int ans = 0;
    while (1) {
        int r1 = q.front(); q.pop();
        if (r1 == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.emplace(-1);
            continue;
        }

        int c2 = r1 % x; r1 /= x;
        int r2 = r1 % x; r1 /= x;
        int c1 = r1 % x; r1 /= x;

        loop(i, 4) {
            int R1 = r1 + mov[i][0], R2 = r2 + mov[i][0];
            int C1 = c1 + mov[i][1], C2 = c2 + mov[i][1];

            bool f1 = is_out(R1, C1), f2 = is_out(R2, C2);
            if (f1 ^ f2) {
                cout << ++ans;
                return 0;
            }
            else if (f1 & f2) continue;

            if (board[R1][C1] == '#') R1 = r1, C1 = c1;
            if (board[R2][C2] == '#') R2 = r2, C2 = c2;

            int nxt = R1 * x * x * x + C1 * x * x + R2 * x + C2;
            if (cache.find(nxt) == cache.end()) {
                cache.emplace(nxt);
                q.emplace(nxt);
            }
        }
    }
    cout << ans;
    return 0;
}