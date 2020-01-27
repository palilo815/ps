#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
const int max_N = 1000;

int box[max_N][max_N], mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<P> q;
    int row, col; cin >> col >> row;
    loop(i, row) loop(j, col) {
        cin >> box[i][j];
        if (box[i][j] == 1) q.push({ i,j });
    }

    q.push({ -1,-1 });
    int ans = 0;
    while (1) {
        int r = q.front().first, c = q.front().second; q.pop();
        if (r == -1) {
            if (q.empty()) break;
            ++ans; q.push({ r,c });
            continue;
        }
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || box[R][C]) continue;
            box[R][C] = 1;
            q.push({ R,C });
        }
    }

    loop(i,row) loop(j,col)
        if (!box[i][j]) {
            ans = -1;
            goto OUT;
        }
OUT:;
    cout << ans;
    return 0;
}