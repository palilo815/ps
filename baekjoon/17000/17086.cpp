#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 50;

int M[max_N][max_N], mov[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    queue<P> q;
    loop(i, row) loop(j, col) {
        cin >> M[i][j];
        if (M[i][j]) q.push({ i,j });
    }

    // M이 거리를 담는 역할도 한다.
    // 써있는 숫자가 지나온 칸
    // 단 처음 시작을 1로 했으므로, 실제 이동 거리는 -1을 해줘야 함.
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second; q.pop();
        loop(i, 8) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || M[R][C]) continue;
            M[R][C] = M[r][c] + 1;
            q.push({ R,C });
        }
    }

    int ans = 0;
    loop(i, row) loop(j, col)
        ans = max(ans, M[i][j]);
    cout << ans - 1;
    return 0;
}