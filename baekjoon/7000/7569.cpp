#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define tup tuple<int,int,int>
using namespace std;

int box[100][100][100], mov[6][3] = { -1,0,0, 0,-1,0, 0,0,-1, 0,0,1, 0,1,0, 1,0,0 };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int height, row, col;
    cin >> col >> row >> height;
    queue<tup> q;
    loop(h, height) loop(r, row) loop(c, col) {
        cin >> box[h][r][c];
        if (box[h][r][c] == 1) q.push({ h,r,c });
    }

    int ans = 0;
    q.push({ -1,-1,-1 });
    while (1) {
        int h = get<0>(q.front()), r = get<1>(q.front()), c = get<2>(q.front()); q.pop();
        if (h == -1) {
            if (q.empty()) break;
            ++ans; q.push({ h,r,c });
            continue;
        }
        loop(i, 6) {
            int H = h + mov[i][0], R = r + mov[i][1], C = c + mov[i][2];
            if (H < 0 || H >= height || R < 0 || R >= row || C < 0 || C >= col || box[H][R][C]) continue;
            q.push({ H,R,C });
            box[H][R][C] = 1;
        }
    }
    loop(h, height) loop(r, row) loop(c, col)
        if (!box[h][r][c]) {
            cout << -1;
            return 0;
        }
    cout << ans;
    return 0;
}