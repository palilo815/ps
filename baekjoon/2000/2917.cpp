#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;
typedef tuple<int, int, int> tup;

const int MAX = 500;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int row, col;
int cost[MAX][MAX];
int dist[MAX][MAX];

void BFS(queue<p> & q) {
    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || cost[R][C] != -1) continue;
            cost[R][C] = cost[r][c] + 1;
            q.emplace(R, C);
        }
    }
}
int Dijkstra(int sr, int sc, int dr, int dc) {
    memset(dist, -1, sizeof(dist));
    dist[sr][sc] = cost[sr][sc];

    priority_queue<tup> pq;
    pq.emplace(dist[sr][sc], sr, sc);

    while (1) {
        auto [d, r, c] = pq.top(); pq.pop();
        if (dist[r][c] > d) continue;
        if (r == dr && c == dc) return d;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col) continue;
            int D = min(cost[R][C], d);
            if (dist[R][C] < D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
        }
    }
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    queue<p> q;
    int sr, sc, dr, dc;
    memset(cost, -1, sizeof(cost));

    cin >> row >> col;
    loop(i, row) loop(j, col) {
        char x; cin >> x;
        if (x == '+') {
            q.emplace(i, j);
            cost[i][j] = 0;
        }
        else if (x == 'V') sr = i, sc = j;
        else if (x == 'J') dr = i, dc = j;
    }

    BFS(q);
    cout << Dijkstra(sr, sc, dr, dc);
    return 0;
}