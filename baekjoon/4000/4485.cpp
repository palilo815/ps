#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 125;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int M[max_N][max_N];
int dist[max_N][max_N];

int Dijkstra(int N) {
    loop(i, N) memset(dist[i], 0x3f, sizeof(int) * N);
    dist[0][0] = M[0][0];

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(M[0][0], 0, 0);

    while (1) {
        auto [d, r, c] = pq.top(); pq.pop();
        if (dist[r][c] < d) continue;
        if (r == N - 1 && c == N - 1) return d;

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            int D = d + M[R][C];
            if (dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
        }
    }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int num = 0, N;
    while (cin >> N) {
        if (N == 0) break;
        loop(i, N) loop(j, N) cin >> M[i][j];
        cout << "Problem " << ++num << ": " << Dijkstra(N) << '\n';
    }
    return 0;
}