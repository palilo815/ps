#include <iostream>
#include <queue>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int MAX = 1000;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

bool wall[MAX][MAX];
bool visited[2][MAX][MAX];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    char x;
    loop(i, row) loop(j, col) {
        cin >> x;
        if (x == '1') wall[i][j] = true;
    }

    queue<int> q;
    q.emplace(0), q.emplace(-1);
    int ans = 1;
    while (1) {
        int crash = q.front(); q.pop();
        if (crash == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans, q.emplace(-1);
            continue;
        }

        int c = crash % 1024; crash /= 1024;
        int r = crash % 1024; crash /= 1024;
        if (r == row - 1 && c == col - 1) break;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[crash][R][C]) continue;
            if (!wall[R][C] && !visited[crash][R][C]) {
                visited[crash][R][C] = true;
                q.emplace(crash * 1024 * 1024 + R * 1024 + C);
            }
            else if (wall[R][C] && !crash && !visited[1][R][C]) {
                visited[1][R][C] = true;
                q.emplace(1024 * 1024 + R * 1024 + C);
            }
        }
    }
    cout << ans;
    return 0;
}