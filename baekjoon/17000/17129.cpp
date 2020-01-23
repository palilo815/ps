#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

int mov[4][2] = { -1,0,1,0,0,-1,0,1 };
char M[3000][3000];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<P> q;
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        if (c == '2') {
            q.push({ i,j });
            c = '1';
        }
        M[i][j] = c;
    }

    q.push({ -1,-1 });
    int ans = 0;
    while (1) {
        int r = q.front().first, c = q.front().second; q.pop();
        if (r == -1) {
            if (q.empty()) break;
            q.push({ r,c }); ++ans;
            continue;
        }
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || M[R][C] == '1') continue;
            if (M[R][C] == '0') {
                q.push({ R,C });
                M[R][C] = '1';
            }
            else { cout << "TAK\n" << ans + 1; return 0; }
        }
    }
    cout << "NIE";
    return 0;
}