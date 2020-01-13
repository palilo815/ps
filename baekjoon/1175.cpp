#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
char mat[50][50];
int visited[3][4][50][50];
// [find][direction][y][x]별로 방문여부 저장
typedef struct {
    int y;
    int x;
    int d;
    int find;
} Stat;
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<Stat> q;
    int row, col; cin >> row >> col;
    bool flag = false;
    loop(i, row) loop(j, col) {
        cin >> mat[i][j];
        if (mat[i][j] == 'S')
            loop(d, 4) {
            visited[0][d][i][j] = true;
            q.push({ i,j,d,0 });
        }
        // 선물 두 개를 구별하기 위해 'C'와 'D'로 저장한다.
        else if (mat[i][j] == 'C') {
            if (flag) mat[i][j] = 'D';
            else flag = true;
        }
    }
    q.push({ -1,-1,-1,-1 });
    int ans = 0;

    while (1) {
        Stat curr = q.front(); q.pop();
        if (curr.y == -1) {
            if (q.empty()) {
                ans = -1; break;
            }
            ++ans; q.push(curr);
            continue;
        }
        // C 선물을 찾았다면 find = 1
        // D 선물을 찾았다면 find = 2
        // (못 찾은 상태는 0)

        // 따라서 find == 1 인 상태에서 D를 찾으면 끝.
        // 마찬가지로 2로 C를 찾으면 끝.
        if (mat[curr.y][curr.x] == 'C' || mat[curr.y][curr.x] == 'D') {
            if (curr.find == 'E' - mat[curr.y][curr.x]) break;
            curr.find = mat[curr.y][curr.x] - 'B';
        }

        loop(i, 4) {
            // 같은 방향으로 이동 불가
            if (i == curr.d) continue;
            int R = curr.y + mov[i][0], C = curr.x + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C] == '#' || visited[curr.find][i][R][C])
                continue;
            visited[curr.find][i][R][C] = true;
            q.push({ R,C,i,curr.find });
        }
    }
    cout << ans;
    return 0;
}