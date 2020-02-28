#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int max_N = 500;
const int max_M = 1000;
const int mov[8][2] = { -2,-1,-2,1,-1,-2,-1,2,1,-2,1,2,2,-1,2,1 };

int board[max_N + 1][max_N + 1];
int ans[max_M + 1];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, M; cin >> N >> M;
    int y, x; cin >> y >> x;
    board[y][x] = -1;
    queue<p> q;
    q.push({ y,x }); q.push({ -1, -1 });
    for (int i = 1; i <= M; ++i) {
        cin >> y >> x;
        board[y][x] = i;
    }

    int cnt = M, dist = 1;
    while (cnt) {
        auto [r, c] = q.front(); q.pop();

        if (r == -1) {
            ++dist; q.push({ -1,-1 });
            continue;
        }

        loop(i, 8) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 1 || R > N || C < 1 || C > N || board[R][C] == -1) continue;
            if (board[R][C]) {
                ans[board[R][C]] = dist;
                --cnt;
            }
            board[R][C] = -1;
            q.push({ R,C });
        }
    }
    for (int i = 1; i <= M; ++i) cout << ans[i] << ' ';
    return 0;
}