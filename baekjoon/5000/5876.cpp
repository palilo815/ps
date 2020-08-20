#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;

const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

char mat[5][5];
bool visited[5][5];

int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N) loop(j, N) cin >> mat[i][j];
    if (mat[0][0] == ')') {cout << 0; return 0;}

    int ans = 0;
    function<void(int, int, int, int)> dfs = [&](int r, int c, int lt, int rt) {
        if (mat[r][c] == '(') ++lt;
        else if (++rt == lt) {
            ans = max(ans, lt);
            return;
        }

        visited[r][c] = true;
        loop(i, 4) {
            int R = r + mov[i][0], C = c + mov[i][1];
            if (R == -1 || R == N || C == -1 || C == N || visited[R][C]) continue;

            if (mat[R][C] == '(' && mat[r][c] == '(') dfs(R, C, lt, rt);
            if (mat[R][C] == ')' && lt > ans) dfs(R, C, lt, rt);
        }
        visited[r][c] = false;
    };

    dfs(0, 0, 0, 0);
    cout << ans * 2;
    return 0;
}