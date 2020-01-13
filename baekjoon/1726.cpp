#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int arr[100][100];
bool visited[4][100][100];
// 상 하 좌 우 이동
int mov[4][2] = { -1,0,0,1,0,-1,1,0 };
// 0에서 1,2로 회전  1에서 0,3으로 회전
// 3에서 1,2로 회전  2에서 0,3으로 회전
int chg[4][2] = { 1,2,0,3,0,3,1,2 };

int main()
{
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(r, row) loop(c, col) cin >> arr[r][c];
    int Y, X, D; cin >> Y >> X >> D;
    --Y, --X, D %= 4;
    visited[D][Y][X] = true;

    queue<tuple<int, int, int>> q;
    q.push(make_tuple(Y, X, D));
    q.push(make_tuple(-1, -1, -1));
    cin >> Y >> X >> D;
    --Y, --X, D %= 4;

    int ans = 0;
    while (1) {
        int r = get<0>(q.front()), c = get<1>(q.front()), d = get<2>(q.front()); q.pop();
        // pivot
        if (r == -1) {
            ++ans; q.push(make_tuple(-1, -1, -1));
            continue;
        }
        // 도착
        if (r == Y && c == X && d == D) break;
        // 이동
        for (int i = 1; i < 4; ++i) {
            int R = r + mov[d][0] * i, C = c + mov[d][1] * i;
            if (R < 0 || R >= row || C < 0 || C >= col || arr[R][C]) break;
            if (!visited[d][R][C]) {
                visited[d][R][C] = true;
                q.push(make_tuple(R, C, d));
            }
        }
        // 방향 전환
        loop(i, 2) {
            int dd = chg[d][i];
            if (!visited[dd][r][c]) {
                visited[dd][r][c] = true;
                q.push(make_tuple(r, c, dd));
            }
        }
    }
    cout << ans;
    return 0;
}