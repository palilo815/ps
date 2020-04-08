#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int MAX = 700;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int row, col;
char board[MAX][MAX];
bool visited[MAX][MAX];
int v_time[MAX][MAX];

bool is_out(int r, int c) {
    return r < 0 || r >= row || c < 0 || c >= col || board[r][c] == 'I';
}
void record_time(int r, int c, int t) {
    loop(d, 4) {
        int R = r + mov[d][0], C = c + mov[d][1];
        while (!is_out(R, C)) {
            v_time[R][C] = min(v_time[R][C], t);
            R += mov[d][0], C += mov[d][1];
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> col;
    int sr, sc, vr, vc;
    loop(i, row) loop(j, col) {
        cin >> board[i][j];
        if (board[i][j] == 'Y')
            sr = i, sc = j;
        else if (board[i][j] == 'V')
            vr = i, vc = j;
    }

    memset(v_time, 0x3f, sizeof(v_time));
    v_time[vr][vc] = 0;

    queue<p> q;
    q.emplace(vr, vc), q.emplace(-1, -1);
    visited[vr][vc] = true;
    int t = 0;

    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) break;
            ++t; q.emplace(-1, -1);
            continue;
        }
        record_time(r, c, t);

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (is_out(R, C) || visited[R][C]) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }

    memset(visited, 0, sizeof(visited));
    visited[sr][sc] = true;
    t = 0;
    q.emplace(sr, sc), q.emplace(-1, -1);

    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) { cout << "NO"; return 0; }
            ++t; q.emplace(-1, -1);
            continue;
        }
        if (v_time[r][c] <= t && (sr != r || sc != c)) continue;
        if (board[r][c] == 'T') break;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (is_out(R, C) || visited[R][C] || v_time[R][C] <= t) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }
    cout << "YES";
    return 0;
}