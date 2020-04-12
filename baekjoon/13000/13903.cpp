#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
typedef pair<int, int> p;

const int M = 1000;

bool block[M][M];
bool visited[M][M];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int row, col; cin >> row >> col;
    loop(i, row) loop(j, col) {
        char x; cin >> x;
        if (x == '1') block[i][j] = true;
    }

    vector<p> mov;
    int N; cin >> N;
    while (N--) {
        int dr, dc; cin >> dr >> dc;
        mov.emplace_back(dr, dc);
    }

    queue<p> q;
    loop(i, col) if (block[0][i]) {
        q.emplace(0, i);
        visited[0][i] = true;
    }
    q.emplace(-1, -1);

    int ans = 0;
    while (1) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {
            if (q.empty()) { ans = -1; break; }
            ++ans; q.emplace(-1, -1);
            continue;
        }
        if (r == row - 1) break;

        for (auto [dr, dc] : mov) {
            int R = r + dr, C = c + dc;
            if (R < 0 || R >= row || C < 0 || C >= col || visited[R][C] || !block[R][C]) continue;
            visited[R][C] = true;
            q.emplace(R, C);
        }
    }
    cout << ans;
    return 0;
}