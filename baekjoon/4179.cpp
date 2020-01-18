#include<bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;

char maze[1000][1000];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<P> Fire, Jihun;
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        if (c == 'J') Jihun.push({ i,j });
        else if (c == 'F') {
            Fire.push({ i,j });
            c = '#';
        }
        maze[i][j] = c;
    }

    Jihun.push({ -1,-1 }), Fire.push({ -1,-1 });
    int ans = 0, flag = 0;
    while (!flag) {
        while (1) {
            int r = Fire.front().first, c = Fire.front().second; Fire.pop();
            if (r == -1) {
                Fire.push({ r,c });
                break;
            }
            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (R < 0 || R >= row || C < 0 || C >= col || maze[R][C] == '#') continue;
                maze[R][C] = '#';
                Fire.push({ R,C });
            }
        }
        while (1) {
            int r = Jihun.front().first, c = Jihun.front().second; Jihun.pop();
            if (r == 0 || r == row - 1 || c == 0 || c == col - 1) {
                ++ans, flag = 2;
                break;
            }
            if (r == -1) {
                if (Jihun.empty()) flag = 1;
                else {
                    ++ans;
                    Jihun.push({ r,c });
                }
                break;
            }
            loop(i, 4) {
                int R = r + mov[i][0], C = c + mov[i][1];
                if (maze[R][C] == '.') {
                    maze[R][C] = 'J';
                    Jihun.push({ R,C });
                }
            }
        }
    }
    if (flag == 1) cout << "IMPOSSIBLE";
    else cout << ans;
    return 0;
}