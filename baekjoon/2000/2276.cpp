#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef tuple<int, int, int> tup;

const int M = 300;
const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int h[M][M];
bool visited[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int col, row; cin >> col >> row;
    loop(i, row) loop(j, col) cin >> h[i][j];

    priority_queue<tup, vector<tup>, greater<tup>> pq;
    for (int i = 1; i < col - 1; ++i) {
        pq.emplace(h[0][i], 0, i);
        pq.emplace(h[row - 1][i], row - 1, i);
        visited[0][i] = visited[row - 1][i] = true;
    }
    for (int i = 1; i < row - 1; ++i) {
        pq.emplace(h[i][0], i, 0);
        pq.emplace(h[i][col - 1], i, col - 1);
        visited[i][0] = visited[i][col - 1] = true;
    }
    visited[0][0] = visited[0][col - 1] = visited[row - 1][0] = visited[row - 1][col - 1] = true;

    int ans = 0;
    while (!pq.empty()) {
        auto [water, r, c] = pq.top(); pq.pop();
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C]) continue;
            visited[R][C] = true;
            if (water > h[R][C]) {
                ans += water - h[R][C];
                pq.emplace(water, R, C);
            }
            else pq.emplace(h[R][C], R, C);
        }
    }
    cout << ans;
    return 0;
}