#include<bits/stdc++.h>
using namespace std;
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>

int Maze[100][100], dist[100][100];
int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int Dijkstra(int row, int col, int dst)
{
    loop(i, 100) loop(j, 100) dist[i][j] = INT32_MAX;
    dist[0][0] = 0;
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ 0,0 });
    while (1) {
        int cost = pq.top().first, here = pq.top().second; pq.pop();
        if (here == dst) return cost;
        int y = here / 100, x = here % 100;
        if (dist[y][x] < cost) continue;
        loop(i, 4) {
            int Y = y + mov[i][0], X = x + mov[i][1];
            if (Y < 0 || Y >= row || X < 0 || X >= col) continue;
            int nextDist = cost + Maze[Y][X];
            if (dist[Y][X] > nextDist) {
                dist[Y][X] = nextDist;
                pq.push(make_pair(nextDist, 100 * Y + X));
            }
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> col >> row;
    int dst = (row - 1) * 100 + (col - 1);
    loop(i, row) loop(j, col) {
        char c; cin >> c;
        Maze[i][j] = c - '0';
    }
    cout << Dijkstra(row, col, dst);
    return 0;
}