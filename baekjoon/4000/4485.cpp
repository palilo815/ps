#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define P pair<int,int>
using namespace std;
    
int M[125][125], dist[125][125], mov[4][2] = { -1,0,0,-1,0,1,1,0 };
int Dijkstra(int N)
{
    loop(i, N) loop(j, N) dist[i][j] = INT32_MAX;
    dist[0][0] = M[0][0];
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({ M[0][0],0 });
    while (1) {
        int cost = pq.top().first, r = pq.top().second / 128, c = pq.top().second % 128; pq.pop();
        if (r == N - 1 && c == N - 1) return cost;
        if (dist[r][c] < cost) continue;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            int next_cost = cost + M[R][C];
            if (dist[R][C] > next_cost) {
                dist[R][C] = next_cost;
                pq.push({ next_cost,R * 128 + C });
            }
        }
    }
}
int main()
{
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int num = 0, N;
    while (cin >> N) {
        if (N == 0) break;
        loop(i, N) loop(j, N)
            cin >> M[i][j];
        cout << "Problem " << ++num << ": " << Dijkstra(N) << '\n';
    }
    return 0;
}