#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef pair<ll, int> p;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };
const int max_N = 100;

int cost[max_N][max_N];
ll dist[max_N][max_N][3];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int N, t; cin >> N >> t;
    loop(i, N) loop(j, N) {
        cin >> cost[i][j];
        loop(k, 3) dist[i][j][k] = INT64_MAX;
    }
    dist[0][0][0] = 0;

    priority_queue<p, vector<p>, greater<p>> pq;
    pq.emplace(0, 0);
    while (1) {
        auto [d, k] = pq.top(); pq.pop();
        int c = k % 128; k /= 128;
        int r = k % 128; k /= 128;
        if (dist[r][c][k] < d) continue;
        if (r == N - 1 && c == N - 1) { cout << d; break; }

        k = (k + 1) % 3;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= N || C < 0 || C >= N) continue;
            int D = d + t + (k == 0 ? cost[R][C] : 0);
            if (dist[R][C][k] > D) {
                dist[R][C][k] = D;
                pq.emplace(D, k * 128 * 128 + R * 128 + C);
            }
        }
    }
    return 0;
}