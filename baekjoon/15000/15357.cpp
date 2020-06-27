#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;
using tup = tuple<int, int, int>;

const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};
const int M = 500;

int row, col;
char mat[M][M];
bool visited[M][M];
int to_wall[M][M];
int dist[M][M];
int nxt[M][M][4];

void BFS() {
    queue<p> q;
    loop(i, row) loop(j, col) if (mat[i][j] == '#')
        q.emplace(i, j);

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C] == '#' || visited[R][C])
                continue;
            visited[R][C] = true;
            to_wall[R][C] = to_wall[r][c] + 1;
            q.emplace(R, C);
        }
    }
}
int Dijkstra(int sr, int sc, int dr, int dc) {
    memset(dist, 0x3f, sizeof(dist));
    dist[sr][sc] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, sr, sc);

    while (!pq.empty()) {
        auto [d, r, c] = pq.top(); pq.pop();
        if (dist[r][c] < d) continue;
        if (r == dr && c == dc) return d;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1], D = d + 1;
            if (mat[R][C] != '#' && dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
            R = r + mov[i][0] * nxt[r][c][i];
            C = c + mov[i][1] * nxt[r][c][i];
            D += to_wall[r][c] - 1;
            if (dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
        }
    }
    return -1;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> row >> col;
    int sr, sc, dr, dc;
    loop(i, row) loop(j, col) {
        cin >> mat[i][j];
        if (mat[i][j] == 'C') sr = i, sc = j;
        if (mat[i][j] == 'F') dr = i, dc = j;
    }
    loop(i, row - 1) loop(j, col - 1) {
        if (mat[i][j] != '#') {
            nxt[i][j + 1][1] = nxt[i][j][1] + 1;
            nxt[i + 1][j][0] = nxt[i][j][0] + 1;
        }
        else nxt[i][j][0] = nxt[i][j][1] = 0;
    }
    for (int i = row - 1; i; --i)
        for (int j = col - 1; j; --j) {
            if (mat[i][j] != '#') {
                nxt[i][j - 1][2] = nxt[i][j][2] + 1;
                nxt[i - 1][j][3] = nxt[i][j][3] + 1;
            }
            else nxt[i][j][2] = nxt[i][j][3] = 0;
        }
    BFS();
    int ans = Dijkstra(sr, sc, dr, dc);
    if (ans == -1) cout << "nemoguce";
    else cout << ans;
    return 0;
}