#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 8;

int M[max_N][max_N], tmp[max_N][max_N];
int row, col, ans;
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int safe_area()
{
    memcpy(tmp, M, sizeof(M));
    queue<P> q;
    loop(i, row) loop(j, col)
        if (M[i][j] == 2) q.push({ i,j });

    while (!q.empty()) {
        int r = q.front().first, c = q.front().second; q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || tmp[R][C]) continue;
            tmp[R][C] = 2;
            q.push({ R,C });

        }
    }

    int ret = 0;
    loop(i, row) loop(j, col)
        if (tmp[i][j] == 0) ++ret;
    return ret;
}
void set_wall(int pos, int n)
{
    if (n == 3) {
        ans = max(ans, safe_area());
        return;
    }
    for (int i = pos; i < row * col; ++i) {
        int r = i / col, c = i % col;
        if (M[r][c] == 0) {
            M[r][c] = 1;
            set_wall(i + 1, n + 1);
            M[r][c] = 0;
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> row >> col;
    loop(i, row) loop(j, col) cin >> M[i][j];
    set_wall(0, 0);
    cout << ans;
    return 0;
}