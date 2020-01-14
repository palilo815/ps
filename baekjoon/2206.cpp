#include<iostream>
#include<queue>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)

char maze[1000][1000];
bool visited[2][1000][1000];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    std::ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col)
        cin >> maze[i][j];

    queue<int> q;
    q.push(0), q.push(-1);
    int ans = 1;
    while (1) {
        int crash = q.front(); q.pop();
        if (crash == -1) {
            if (q.empty()) break;
            ++ans, q.push(-1);
            continue;
        }

        int c = crash % 1024; crash /= 1024;
        int r = crash % 1024; crash /= 1024;
        if (r == row - 1 && c == col - 1) break;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[crash][R][C]) continue;
            if (maze[R][C] == '0') {
                visited[crash][R][C] = true;
                q.push(crash * 1024 * 1024 + R * 1024 + C);
            }
            else {
                if (crash) continue;
                visited[1][R][C] = true;
                q.push(1024 * 1024 + R * 1024 + C);
            }
        }
    }
    if (q.empty()) cout << -1;
    else cout << ans;
    return 0;
}