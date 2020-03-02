#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int, int> tup;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int max_N = 100;

int board[max_N][max_N];
int DP[max_N][max_N][201];
// DP[r][c][_max] : (r,c)에 최댓값 _max를 방문한 상태로 가질 수 있는 _min

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> board[i][j];
    queue<tup> q;
    q.push({ 0,0,board[0][0],board[0][0] });
    memset(DP, -1, sizeof(DP));
    DP[0][0][board[0][0]] = board[0][0];

    while (!q.empty()) {
        auto [r, c, _max, _min] = q.front(); q.pop();
        if (DP[r][c][_max] > _min) continue;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            int _MAX = max(_max, board[R][C]);
            int _MIN = min(_min, board[R][C]);
            if (DP[R][C][_MAX] < _MIN) {
                DP[R][C][_MAX] = _MIN;
                q.push({ R,C,_MAX,_MIN });
            }
        }
    }

    int ans = INT_MAX;
    loop(i, 201) if (DP[N - 1][N - 1][i] != -1)
        ans = min(ans, i - DP[N - 1][N - 1][i]);
    cout << ans;
    return 0;
}