#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> P;
const int max_N = 1000;

int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int M[max_N][max_N], dist[max_N][max_N];
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    // 도착지에서 Dijkstra를 사용한다.

    queue<P> q;
    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) dist[i][j] = INT_MAX;
    loop(i, row) loop(j, col) {
        cin >> M[i][j];
        if (M[i][j] == 2) {
            dist[i][j] = 0;
            q.push({ i,j });
        }
    }
    
    while (!q.empty()) {
        int r = q.front().first, c = q.front().second; q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || !M[R][C]) continue;
            if (dist[R][C] > dist[r][c] + 1) {
                dist[R][C] = dist[r][c] + 1;
                q.push({ R,C });
            }
        }
    }

    // dist == INT_MAX : 방문하지 않은 곳
    loop(i, row) {
        loop(j, col)
            if (dist[i][j] == INT_MAX) {
                if (M[i][j]) cout << -1 << ' ';
                else cout << 0 << ' ';
            }
            else cout << dist[i][j] << ' ';
        cout << '\n';
    }
    return 0;
}