#include <bits/stdc++.h>
using namespace std;

const int mov[4][2] = { -1,0,0,-1,0,1,1,0 };

int chance[4];
bool visited[29][29];
double ans;

void solve(int r, int c, int N, double val) {
    if (N == 0) {
        ans += val;
        return;
    }
    for (int i = 0; i < 4; ++i) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (visited[R][C]) continue;

        visited[R][C] = true;
        solve(R, C, N - 1, val * chance[i] / 100);
        visited[R][C] = false;
    }
}
int main() {
    int N; cin >> N;
    cin >> chance[2] >> chance[1] >> chance[3] >> chance[0];

    visited[14][14] = true;
    solve(14, 14, N, 1);
    cout << fixed << setprecision(10) << ans;
    return 0;
}