#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int max_N = 30;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int N, A, B;
char farm[max_N][max_N];
int dist[max_N][max_N];

int Dijkstra(int sr, int sc) {
    loop(i, N) loop(j, N) dist[i][j] = INT_MAX;
    dist[sr][sc] = 0;

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    pq.emplace(0, sr, sc);

    int ret = 0;
    while (!pq.empty()) {
        auto [d, r, c] = pq.top(); pq.pop();
        if (dist[r][c] < d) continue;
        ret = max(ret, d);

        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            int D = (farm[r][c] == farm[R][C] ? d + A : d + B);
            if (dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
        }
    }
    return ret;
}
int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    cin >> N >> A >> B;
    loop(i, N) loop(j, N) cin >> farm[i][j];

    int ans = 0;
    loop(i, N) loop(j, N)
        ans = max(ans, Dijkstra(i, j));
    cout << ans;
    return 0;
}