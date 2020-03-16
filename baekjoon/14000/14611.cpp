#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef long long ll;
typedef tuple<ll, int, int> tup;

const int MAX = 300;
const int mov[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };

int price[MAX][MAX];
ll dist[MAX][MAX];

int main() {
    cin.tie(NULL), cout.tie(NULL);
    ios::sync_with_stdio(false);

    int row, col; cin >> row >> col;
    assert(0 < row && row < MAX && 0 < col && col < MAX);

    loop(i, row) loop(j, col) {
        cin >> price[i][j];
        if (price[i][j] == -2) price[i][j] = 0;
    }

    loop(i, row) loop(j, col) dist[i][j] = INT64_MAX;
    priority_queue<tup, vector<tup>, greater<tup>> pq;

    loop(i, row) if (price[i][0] != -1) {
        pq.emplace(price[i][0], i, 0);
        dist[i][0] = price[i][0];
    }
    loop(i, col) if (price[row - 1][i] != -1) {
        pq.emplace(price[row - 1][i], row - 1, i);
        dist[row - 1][i] = price[row - 1][i];
    }

    ll ans = -1;
    while (!pq.empty()) {
        auto [d, r, c] = pq.top(); pq.pop();
        if (dist[r][c] < d) continue;
        if (r == 0 || c == col - 1) { ans = d; break; }

        loop(i, 8) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || price[R][C] == -1)
                continue;

            ll D = d + price[R][C];
            if (dist[R][C] > D) {
                dist[R][C] = D;
                pq.emplace(D, R, C);
            }
        }
    }
    cout << ans;
    return 0;
}