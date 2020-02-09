#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int maze[100][100];
bool visited[100][100][2];

int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) cin >> maze[i][j];

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.push({ maze[0][0] * 2, 0 });
    /*
        p.first / 2 = min_level     p.second / 128 = row
        p.first % 2 = use           p.second % 128 = col

        Dijkstra이므로, visited check는 pq에서 꺼낸 뒤 해줘도 된다.
    */
    while (1) {
        auto [x, y] = pq.top(); pq.pop();
        int level = x / 2, used = x % 2, r = y / 128, c = y % 128;

        if (visited[r][c][used]) continue;
        visited[r][c][used] = true;

        if (r == row - 1 && c == col - 1) { cout << level; break; }
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C][used]) continue;
            pq.push({ max(level,maze[R][C]) * 2 + used,R * 128 + C });
        }
        if (!used) loop(i, 4) {
            int R = r + 2 * mov[i][0], C = c + 2 * mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C][1]) continue;
            pq.push({ max(level,maze[R][C]) * 2 + 1,R * 128 + C });
        }
    }
    return 0;
}