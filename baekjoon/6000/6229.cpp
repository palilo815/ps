#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using p = pair<int, int>;

const int mx = 30;

vector<p> mov;
char mat[mx][mx];
short dist[mx][mx];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col, m1, m2;
    cin >> row >> col >> m1 >> m2;
    loop(i, row) loop(j, col) cin >> mat[i][j];

    if (m1 < m2) swap(m1, m2);
    mov = {
        { -m1, -m2}, { -m1, m2}, { -m2, -m1}, { -m2, m1},
        {m2, -m1}, {m2, m1}, {m1, -m2}, {m1, m2}
    };

    queue <p> q;
    loop(i, row) loop(j, col) switch (mat[i][j]) {
    case '0':
    case '2': dist[i][j] = -1; break;
    case '3': q.emplace(i, j);
    }

    for (;;) {
        auto [r, c] = q.front(); q.pop();
        for (auto [dr, dc] : mov) {
            int R = r + dr, C = c + dc;
            if (R < 0 || R >= row || C < 0 || C >= col || dist[R][C]) continue;
            if (mat[R][C] == '4') {cout << dist[r][c] + 1; return 0;}
            else {
                dist[R][C] = dist[r][c] + 1;
                q.emplace(R, C);
            }
        }
    }
    return 0;
}