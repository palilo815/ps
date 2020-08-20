#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;

char mat[mx][mx];

void solve() {
    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];

    int ans = 0;
    queue<pair<int, int>> q;
    loop(i, N) loop(j, N) if (mat[i][j] == 'w')
        q.emplace(i, j);

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        for (int R = r - 1; R <= r + 1; ++R)
            for (int C = c - 1; C <= c + 1; ++C)
                if (~R && R ^ N && ~C && C ^ N && mat[R][C] == '-') {
                    ++ans;
                    mat[R][C] = 'w';
                    q.emplace(R, C);
                }
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int T; cin >> T;
    while (T--) solve();
    return 0;
}