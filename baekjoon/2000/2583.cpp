#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mx = 100;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

int row, col;
bool v[mx][mx];

int dfs(int r, int c) {
    v[r][c] = true;
    int ret = 1;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (~R && R ^ row && ~C && C ^ col && !v[R][C])
            ret += dfs(R, C);
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int K; cin >> row >> col >> K;
    for (int r1, c1, r2, c2; K--;) {
        cin >> c1 >> r1 >> c2 >> r2;
        for (int i = r1; i < r2; ++i)
            for (int j = c1; j < c2; ++j)
                v[i][j] = true;
    }

    vector<int> ans;
    loop(i, row) loop(j, col) if (!v[i][j])
        ans.emplace_back(dfs(i, j));
    sort(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int& x : ans) cout << x << ' ';
    return 0;
}