#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx][mx];
bool visited[mx][mx];

void solve() {
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    function<void(int, int)> dfs = [&](int r, int c) {
        visited[r][c] = true;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (~R && R ^ row && ~C && C ^ col && mat[R][C] == '1' && !visited[R][C])
                dfs(R, C);
        }
    };

    int Q; cin >> Q;
    for (char q, n; Q--;) {
        cin >> q;
        if (q == 'M') {
            int r, c; cin >> r >> c >> n;
            mat[r][c] = n;
        }
        else {
            memset(visited, 0, sizeof(visited));
            int ans = 0;
            loop(i, row) loop(j, col) if (mat[i][j] == '1' && !visited[i][j]) {
                ++ans;
                dfs(i, j);
            }
            cout << ans << '\n';
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    for (int t = 1; t <= T; ++t) {
        cout << "Case #" << t << ":\n";
        solve();
    }
    return 0;
}