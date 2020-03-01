#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int, int> tup;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int MAX = 50;

char maze[MAX][MAX];
int cache[MAX][MAX][MAX][MAX];

inline tup decode(int a) {
    int d = a % 64; a /= 64;
    int c = a % 64; a /= 64;
    int b = a % 64; a /= 64;
    return { a,b,c,d };
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int T; cin >> T;
    while (T--) {
        memset(cache, 0, sizeof(cache));
        int row, col; cin >> row >> col;
        int sr1 = -1, sc1 = -1, sr2 = -1, sc2 = -1;
        loop(i, row) loop(j, col) {
            cin >> maze[i][j];
            if (maze[i][j] == 'P') {
                if (sr1 == -1) sr1 = i, sc1 = j;
                else sr2 = i, sc2 = j;
            }
        }
        cache[sr1][sc1][sr2][sc2] = -1;
        int dr = -1, dc = -1;

        queue<tup> q;
        q.emplace(sr1, sc1, sr2, sc2);
        while (!q.empty()) {
            auto [r1, c1, r2, c2] = q.front(); q.pop();
            if (r1 == r2 && c1 == c2) {
                dr = r1, dc = c1;
                break;
            }

            loop(i, 4) {
                int R1 = (r1 + mov[i][0] + row) % row, C1 = (c1 + mov[i][1] + col) % col;
                if (maze[R1][C1] == 'G') continue;
                int R2 = (r2 + mov[i][0] + row) % row, C2 = (c2 + mov[i][1] + col) % col;
                if (maze[R2][C2] == 'G') continue;
                
                if (maze[R1][C1] == 'X') R1 = r1, C1 = c1;
                if (maze[R2][C2] == 'X') R2 = r2, C2 = c2;

                if (cache[R1][C1][R2][C2]) continue;
                cache[R1][C1][R2][C2] = r1 * 64 * 64 * 64 + c1 * 64 * 64 + r2 * 64 + c2;
                q.emplace(R1, C1, R2, C2);
            }
        }

        if (dr == -1) {
            cout << "IMPOSSIBLE\n";
            continue;
        }

        int R1 = dr, C1 = dc, R2 = dr, C2 = dc;
        int cnt = 0;
        vector<char> ans;
        while (cache[R1][C1][R2][C2] != -1) {
            auto [r1, c1, r2, c2] = decode(cache[R1][C1][R2][C2]);
            char x;
            if (r1 != R1) x = (r1 - 1 == R1 || r1 + row - 1 == R1 ? 'N' : 'S');
            else if (r2 != R2) x = (r2 - 1 == R2 || r2 + row - 1 == R2 ? 'N' : 'S');
            else if (c1 != C1) x = (c1 + 1 == C1 || C1 + col - 1 == c1 ? 'E' : 'W');
            else  x = (c2 + 1 == C2 || C2 + col - 1 == c2 ? 'E' : 'W');
            ans.emplace_back(x);
            R1 = r1, C1 = c1, R2 = r2, C2 = c2;
        }
        cout << ans.size() << ' ';
        for (auto it = ans.rbegin(); it != ans.rend(); ++it) cout << *it;
        cout << '\n';
    }
    return 0;
}