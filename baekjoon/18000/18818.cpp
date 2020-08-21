#include <bits/stdc++.h>
using namespace std;

const int mx = 100;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[mx + 2][mx + 2];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    memset(mat, '#', sizeof(mat));

    int N; cin >> N;
    for (int i = 1; i <= N; ++i)
        cin >> (mat[i] + 1);

    queue<pair<int, int>> q;
    q.emplace(1, 1), q.emplace(-1, -1);

    int ans = 0;
    for (;;) {
        auto [r, c] = q.front(); q.pop();
        if (r == -1) {++ans; q.emplace(-1, -1); continue;}
        if (r == N && c == N) break;

        for (int i = 0; i < 4; ++i)
            for (int R = r + mov[i][0], C = c + mov[i][1]; mat[R][C] ^ '#'; R += mov[i][0], C += mov[i][1]) {
                if (mat[R][C]) q.emplace(R, C);
                mat[R][C] = 0;
            }
    }
    cout << ans;
    return 0;
}