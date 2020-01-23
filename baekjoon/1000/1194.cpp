#include <bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

struct minsik {
    int y;
    int x;
    int keys;
};
char maze[50][50];
bool visited[64][50][50]; // [bitmask_keys][y][x]
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int main()
{
    cin.tie(NULL), cin.tie(NULL);
    ios::sync_with_stdio(false);

    queue<minsik> q;
    int row, col; cin >> row >> col;
    int y, x;
    loop(i, row) loop(j, col) {
        cin >> maze[i][j];
        if (maze[i][j] == '0')
            y = i, x = j;
    }
    q.push(minsik{ y,x,0 });
    q.push(minsik{ -1,-1,-1 });
    visited[0][y][x] = true;
    int ans = 0;
    while (1) {
        minsik curr = q.front();
        q.pop();
        if (curr.keys == -1) {
            if (q.empty()) {
                ans = -1; break;
            }
            ++ans; q.push(curr);
            continue;
        }
        int r = curr.y, c = curr.x, keys = curr.keys;
        if (maze[r][c] == '1') break;

        // 얻은 열쇠정보를 bitmask로 저장한다.
        if (maze[r][c] >= 'a' && maze[r][c] <= 'f')
            keys |= (1 << (maze[r][c] - 'a'));

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || maze[R][C] == '#' || visited[keys][R][C])
                continue;
            if (maze[R][C] >= 'A' && maze[R][C] <= 'F')
                // 열쇠가 없는 경우
                if (!(keys & (1 << (maze[R][C] - 'A')))) continue;
            visited[keys][R][C] = true;
            q.push(minsik{ R,C,keys });
        }
    }
    cout << ans;
    return 0;
}