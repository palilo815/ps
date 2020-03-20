#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 1000;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int row, col;
char board[MAX][MAX];
queue<p> q[9];
int s[9];

bool BFS(const int p) {
    if (q[p].size() == 1) return false;
    int cnt = 0;
    while (1) {
        auto [r, c] = q[p].front(); q[p].pop();
        if (r == -1) {
            q[p].emplace(-1, -1);
            if (q[p].size() == 1 || ++cnt == s[p]) break;
        }

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || board[R][C] != '.') continue;
            board[R][C] = '1' + p;
            q[p].emplace(R, C);
        }
    }
    return true;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int p; cin >> row >> col >> p;
    loop(i, p) cin >> s[i];
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] > '0')
            q[board[i][j] - '1'].emplace(i, j);
    }
    loop(i, p) q[i].emplace(-1, -1);

    bool update = true;
    while (update) {
        update = false;
        loop(i, p) update |= BFS(i);
    }

    vector<int> ans(p);
    loop(i, row) loop(j, col) if (board[i][j] > '0')
        ++ans[board[i][j] - '1'];
    for (int x : ans) cout << x << ' ';
    return 0;
}