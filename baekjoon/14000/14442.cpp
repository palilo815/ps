#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int max_N = 1000;
const int max_K = 10;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

// 메모리 아끼자. 전부 1Byte로!
bool wall[max_N][max_N];
bool visited[max_N][max_N][max_K + 1];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col, k;
    cin >> row >> col >> k;
    loop(i, row) loop(j, col) {
        char x; cin >> x;
        if (x == '1') wall[i][j] = true;
    }

    visited[0][0][0] = true;
    queue<int> q;
    q.push(0); q.push(-1);

    int ans = 1;
    while (1) {
        int cnt = q.front(); q.pop();
        if (cnt == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.push(-1);
            continue;
        }
        // 극한의 효율충은 tuple따위 쓰지 않는다.
        // int에 다 박아 넣는다. 유사 bitmask
        // cnt : 현재 부신 벽의 개수
        int r = (cnt / 1024) % 1024, c = cnt % 1024;
        cnt /= (1024 * 1024);
        if (r == row - 1 && c == col - 1) break;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            if (wall[R][C]) {
                if (cnt < k && !visited[R][C][cnt + 1]) {
                    visited[R][C][cnt + 1] = true;
                    q.push({ (cnt + 1) * 1024 * 1024 + R * 1024 + C });
                }
            }
            else if (!visited[R][C][cnt]) {
                visited[R][C][cnt] = true;
                q.push({ cnt * 1024 * 1024 + R * 1024 + C });
            }
        }
    }
    cout << ans;
    return 0;
}